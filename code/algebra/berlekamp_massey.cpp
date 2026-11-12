// Berlekamp-Massey + n-esimo termo de recorrencia linear (Kitamasa O(k^2 log n))
//
// O que faz: dado s[0..m) de uma recorrencia linear de ordem L (mod primo), acha os
//   coeficientes c com s[i] = sum_j c[j]*s[i-1-j]; kth(s, c, n) calcula s[n].
// Quando usar: "n-esimo termo de DP de estado pequeno": calcule ~2*estados termos por brute,
//   BM, depois Kitamasa (Catalogo > Algebra, polinomios e FFT: Berlekamp-Massey, Kitamasa,
//   Recorrencia linear <-> matriz).
// Complexidade: BM O(m^2); kth O(L^2 log n) (para L grande ver code/algebra/bostan_mori.cpp).
// Uso: vector<ll> c = berlekampMassey(s); // c.size() = L, pode ser 0 (sequencia nula)
//      ll x = kth(s, c, n);              // s[n] mod MOD, n 0-based, n ate 1e18
// Cuidados: precisa de pelo menos 2L termos para o resultado ser confiavel; MOD primo.
//   Se o chute de L estourar m/2, a recorrencia achada pode ser falsa: gere mais termos.
//   A ordem minima achada serve tambem para polinomio minimo de matriz (Wiedemann).
const ll MOD = 1000000007;
ll pw(ll b, ll e) {
    ll r = 1; b %= MOD; if (b < 0) b += MOD;
    for (; e; e >>= 1, b = b * b % MOD) if (e & 1) r = r * b % MOD;
    return r;
}
vector<ll> berlekampMassey(vector<ll> s) {
    int n = s.size(), L = 0, m = 0;
    vector<ll> C(n), B(n), T;
    C[0] = B[0] = 1;
    ll b = 1;
    for (int i = 0; i < n; i++) {
        m++;
        ll d = s[i] % MOD; // discrepancia: erro da recorrencia atual em i
        for (int j = 1; j <= L; j++) d = (d + C[j] * s[i - j]) % MOD;
        if (!d) continue;
        T = C;
        ll coef = d * pw(b, MOD - 2) % MOD;
        for (int j = m; j < n; j++) C[j] = (C[j] - coef * B[j - m]) % MOD;
        if (2 * L > i) continue;
        L = i + 1 - L; B = T; b = d; m = 0;
    }
    C.resize(L + 1); C.erase(C.begin());
    for (ll& x : C) x = (MOD - x) % MOD;
    return C; // s[i] = sum_j C[j] * s[i-1-j]
}
// x^k mod f(x), f(x) = x^n - sum_j c[j] x^(n-1-j); devolve vetor de tamanho n
vector<ll> polmod(vector<ll> a, vector<ll> b, const vector<ll>& c) {
    int n = c.size();
    vector<ll> r(2 * n, 0);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) r[i + j] = (r[i + j] + a[i] * b[j]) % MOD;
    for (int i = 2 * n - 1; i >= n; i--) // x^i = sum_j c[j] x^(i-1-j)
        for (int j = 0; j < n; j++) r[i - 1 - j] = (r[i - 1 - j] + r[i] * c[j]) % MOD;
    r.resize(n);
    return r;
}
ll kth(const vector<ll>& s, const vector<ll>& c, ll k) {
    int n = c.size();
    if (n == 0) return 0;
    if (k < (ll)s.size()) return (s[k] % MOD + MOD) % MOD;
    vector<ll> res(n, 0), e(n, 0); // res = x^0, e = x^1
    res[0] = 1;
    if (n == 1) e[0] = c[0]; else e[1] = 1;
    for (; k; k >>= 1, e = polmod(e, e, c))
        if (k & 1) res = polmod(res, e, c);
    ll ans = 0; // x^k = sum res[i] x^i  ->  s[k] = sum res[i] s[i]
    for (int i = 0; i < n; i++) ans = (ans + res[i] * s[i]) % MOD;
    return ans;
}
