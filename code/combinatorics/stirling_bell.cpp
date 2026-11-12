// Stirling 1a e 2a especie, Bell, Eulerianos (tabelas O(n^2) e valor unico)
//
// O que faz: tabelas S2[n][k], S1[n][k] (sem sinal), Eulerianos A[n][k],
//   linha do triangulo de Bell; S2(n,k) isolado em O(k log n); Bell por DP.
// Quando usar: "Catalogo > Combinatoria" (Stirling 2a/1a, Bell, Eulerianos/descidas,
//   surjecoes, momentos E[X^n]). Linha inteira com n grande: ver code/algebra (NTT).
// Complexidade: tabelas O(N^2) memoria e tempo; stirling2_one O(k log n); bell O(n^2).
// Requer: code/combinatorics/binom_mod.cpp (cole antes).
// Uso: build_stirling(N) preenche S1,S2,Eul (0..N). stirling2_one(n,k) usa
//   fact/ifact de binom_mod.cpp (cole junto). bell_row(n) devolve B_0..B_n.
//   S1[n][k]: perms de n com k ciclos. Eul[n][k]: perms de n com k descidas.
// Cuidados: MAXS controla o tamanho das tabelas (int mod 998244353 = 4 bytes).
//   Bell: B_{n+1} = sum_k C(n,k) B_k, usa triangulo para nao depender de binomiais.
const int MAXS = 2005;
static int S1[MAXS][MAXS], S2[MAXS][MAXS], Eul[MAXS][MAXS];
void build_stirling(int N) {
    S1[0][0] = S2[0][0] = 1;
    for (int n = 1; n <= N; n++)
        for (int k = 1; k <= n; k++) {
            S2[n][k] = (S2[n-1][k-1] + (ll)k * S2[n-1][k]) % MOD;      // S(n,k)=S(n-1,k-1)+k S(n-1,k)
            S1[n][k] = (S1[n-1][k-1] + (ll)(n - 1) * S1[n-1][k]) % MOD; // c(n,k)=c(n-1,k-1)+(n-1)c(n-1,k)
        }
    // Euleriano A(n,k), k = # descidas (0..n-1): A(n,k)=(k+1)A(n-1,k)+(n-k)A(n-1,k-1)
    Eul[0][0] = 1;
    for (int n = 1; n <= N; n++)
        for (int k = 0; k < n; k++)
            Eul[n][k] = ((ll)(k + 1) * Eul[n-1][k] + (k ? (ll)(n - k) * Eul[n-1][k-1] : 0)) % MOD;
}
// S2(n,k) = (1/k!) sum_j (-1)^{k-j} C(k,j) j^n   (precisa binom_mod.cpp)
ll stirling2_one(ll n, int k) {
    ll r = 0;
    for (int j = 0; j <= k; j++) {
        ll t = C(k, j) * pw(j, n) % MOD;
        r += ((k - j) & 1) ? MOD - t : t;
    }
    return r % MOD * ifact[k] % MOD;
}
// Numeros de Bell B_0..B_n pelo triangulo de Bell (O(n^2))
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
