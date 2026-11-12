// Catalan e contagens classicas de caminhos
// Requer: code/combinatorics/binom_mod.cpp (cole antes).
ll catalan(ll n) { return n < 0 ? 0 : (C(2 * n, n) - C(2 * n, n + 1) + MOD) % MOD; }
// A sempre a frente de B (a>b)
ll ballot_strict(ll a, ll b) {
    if (a <= b) return 0;
    return (C(a + b, a) - C(a + b, a + 1) + MOD) % MOD; // equivale a (a-b)/(a+b)*C(a+b,a)
}
// A nunca atras (empates permitidos)
ll ballot_tie(ll a, ll b) {
    if (a < b) return 0;
    return (C(a + b, b) - C(a + b, b - 1) + MOD) % MOD;
}
// Narayana: Dyck de 2n passos com k picos
ll narayana(ll n, ll k) {
    if (k < 1 || k > n) return 0;
    return C(n, k) * C(n, k - 1) % MOD * pw(n, MOD - 2) % MOD;
}
// arvores m-arias ordenadas com n nos
ll fuss(ll m, ll n) { return C(m * n, n) * pw((m - 1) * n + 1, MOD - 2) % MOD; }
// Motzkin M_0..M_n
vector<ll> motzkin(int n) {
    vector<ll> M(max(n + 1, 2)); M[0] = M[1] = 1;
    for (int k = 2; k <= n; k++)
        M[k] = ((2 * k + 1) * M[k-1] + 3LL * (k - 1) % MOD * M[k-2]) % MOD * pw(k + 2, MOD - 2) % MOD;
    return M;
}
// Delannoy: passos (1,0),(0,1),(1,1)
ll delannoy(ll m, ll n) {
    ll r = 0, p2 = 1;
    for (ll k = 0; k <= min(m, n); k++, p2 = p2 * 2 % MOD) r = (r + C(m, k) * C(n, k) % MOD * p2) % MOD;
    return r;
}
// caminhos que tocam y = x + c (reflexao)
ll touch_line(ll n, ll m, ll c) {
    if (m >= n + c) return C(n + m, n); // destino na reta ou alem: todos tocam
    return C(n + m, n + c);
}
// +-1 com minimo de prefixo >= -k
ll prefix_ge(ll n, ll k) { return (C(2 * n, n) - C(2 * n, n + k + 1) + MOD) % MOD; }
// Escolher k de n em linha sem dois adjacentes
ll nonadj_line(ll n, ll k) { return C(n - k + 1, k); }
// ... em circulo: n/(n-k) * C(n-k,k)
ll nonadj_circle(ll n, ll k) {
    if (k == 0) return 1;
    if (n - k <= 0 || n - k < k) return 0;
    return n % MOD * pw(n - k, MOD - 2) % MOD * C(n - k, k) % MOD;
}
// em linha com distancia >= d
ll gap_pick(ll n, ll k, ll d) { return k == 0 ? 1 : C(n - (k - 1) * (d - 1), k); }
/*LATEX_DESC_BEGIN***************************
-> **Familia de Catalan e caminhos classicos**
Catalan, ballot, Narayana, Fuss-Catalan, Motzkin, Delannoy, reflexao e escolhas sem vizinhos.

Complexidade: O(1) por consulta (Motzkin O(n), Delannoy O(min(m,n))).
Uso:
  ll c = catalan(n);
  ll bs = ballot_strict(a, b), bt = ballot_tie(a, b);
  ll na = narayana(n, k), fu = fuss(m, n);
  vector<ll> mo = motzkin(n);
  ll de = delannoy(m, n);
  ll tl = touch_line(n, m, c), pg = prefix_ge(n, k);
  ll nl = nonadj_line(n, k), nc = nonadj_circle(n, k), gp = gap_pick(n, k, d);

* Sobre o codigo:
  Tudo sai de C(n,k) e pw (de binom_mod.cpp). Catalan = C(2n,n)/(n+1);
  ballot pela diferenca de binomiais; Narayana e Fuss-Catalan dividem por n
  ou (m-1)n+1. touch_line reflete o destino. nonadj usa as formulas classicas.

* Problemas e reducoes:
  + Contar sequencias de parenteses balanceados -> catalan(n).
  + Eleicao em que A sempre lidera -> ballot_strict/ballot_tie.
  + Dyck com k picos -> narayana(n,k).
  + Arvores m-arias ordenadas com n nos -> fuss(m,n).
  + Caminhos sem dois passos iguais consecutivos -> motzkin(n).
  + Caminhos com passos diagonais -> delannoy(m,n).
  + Caminhos que tocam y = x + c -> touch_line.
  + Escolher k sem vizinhos em linha/circulo -> nonadj_line/nonadj_circle.

Cuidados: depende de binom_mod.cpp (nao repetido aqui); indices fora dos
  dominios devolvem 0; Catalan(n) = C(2n,n) - C(2n,n+1).
Catalogo: Combinatoria.
Digitacao: 48 linhas | media. Atalho: narayana/fuss chamam pw(a, MOD-2); use inv_ de binom_mod.
*****************************LATEX_DESC_END*/
