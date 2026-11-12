// Stirling, Bell e Eulerianos
// Requer: code/combinatorics/binom_mod.cpp (cole antes).
const int MAXS = 2005;
static int S1[MAXS][MAXS], S2[MAXS][MAXS], Eul[MAXS][MAXS];
void build_stirling(int N) {
    S1[0][0] = S2[0][0] = 1;
    for (int n = 1; n <= N; n++)
        for (int k = 1; k <= n; k++) {
            S2[n][k] = (S2[n-1][k-1] + (ll)k * S2[n-1][k]) % MOD;      // S(n,k)=S(n-1,k-1)+k S(n-1,k)
            S1[n][k] = (S1[n-1][k-1] + (ll)(n - 1) * S1[n-1][k]) % MOD; // c(n,k)=c(n-1,k-1)+(n-1)c(n-1,k)
        }
    // A(n,k) = (k+1)A(n-1,k) + (n-k)A(n-1,k-1)
    Eul[0][0] = 1;
    for (int n = 1; n <= N; n++)
        for (int k = 0; k < n; k++)
            Eul[n][k] = ((ll)(k + 1) * Eul[n-1][k] + (k ? (ll)(n - k) * Eul[n-1][k-1] : 0)) % MOD;
}
// S2(n,k) pela formula de inclusao
ll stirling2_one(ll n, int k) {
    ll r = 0;
    for (int j = 0; j <= k; j++) {
        ll t = C(k, j) * pw(j, n) % MOD;
        r += ((k - j) & 1) ? MOD - t : t;
    }
    return r % MOD * ifact[k] % MOD;
}
// Bell B_0..B_n pelo triangulo de Bell
vector<ll> bell_row(int n) {
    vector<ll> B(n + 1), row = {1}, nxt;
    B[0] = 1;
    for (int i = 1; i <= n; i++) {
        nxt.assign(i + 1, 0);
        nxt[0] = row.back();
        for (int j = 1; j <= i; j++) nxt[j] = (nxt[j-1] + row[j-1]) % MOD;
        row = nxt; B[i] = row[0];
    }
    return B;
}
// # sobrejecoes [n]->[k] = k! S(n,k)
ll surjections(ll n, int k) { return fact[k] * stirling2_one(n, k) % MOD; }
/*LATEX_DESC_BEGIN***************************
-> **Stirling, Bell e Eulerianos**
Tabelas de Stirling de 1a e 2a especie, Eulerianos, Bell e S2(n,k) isolado.

Complexidade: tabelas O(N^2) tempo e memoria; stirling2_one O(k log n); bell O(n^2).
Uso:
  build_stirling(N);                 // S1, S2, Eul (0..N)
  ll s2 = stirling2_one(n, k);
  vector<ll> B = bell_row(n);
  ll surj = surjections(n, k);

* Sobre o codigo:
  S2(n,k) = S2(n-1,k-1) + k*S2(n-1,k); S1 analogo com (n-1).
  Eul(n,k) = (k+1)Eul(n-1,k) + (n-k)Eul(n-1,k-1). stirling2_one usa a
  formula de inclusao com C(k,j) j^n. bell_row usa o triangulo de Bell.

* Problemas e reducoes:
  + Particoes de um conjunto em k blocos -> S2[n][k].
  + Permutacoes com k ciclos -> S1[n][k].
  + Permutacoes com k descidas -> Eul[n][k].
  + Numero de Bell (particoes de um conjunto) -> bell_row.
  + Sobrejecoes [n] -> [k] -> surjections.
  + S2(n,k) com n grande e k pequeno -> stirling2_one.
  + Momentos E[X^n] via Stirling -> S2.

Cuidados: MAXS controla as tabelas (int mod 998244353 = 4 bytes); Bell usa
  B_{n+1} = sum_k C(n,k) B_k, mas o triangulo evita binomiais.
Catalogo: Combinatoria.
Digitacao: 38 linhas | media.
*****************************LATEX_DESC_END*/
