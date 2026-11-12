// Interpolacao de Lagrange em pontos consecutivos (0..d)
//
// O que faz: dado y[i] = P(i) para i = 0..d (P de grau <= d), calcula P(n) para n qualquer.
// Quando usar: "n ate 1e18 mas a resposta parece polinomial": calcule d+2 valores por brute
//   e interpole; DP cuja resposta e polinomio em n
//   (Catalogo > Algebra, polinomios e FFT: Lagrange em pontos consecutivos, Grau d -> d+1 pontos).
// Complexidade: O(d), sem inverso por termo (prefixos/sufixos de prod(n-j)).
// Uso: vector<ll> y = {P(0), ..., P(d)}; ll r = lagrange(y, n); // 0-based
//   Se f(n) = sum_{i<=n} g(i) com g de grau d, f tem grau d+1: passe d+2 pontos.
// Cuidados: MOD primo e d < MOD. Se n <= d devolve y[n] direto (evita divisao por zero).
//   Para pontos nao consecutivos use code/algebra/poly.cpp (interpolate) ou O(n^2) classico.
const ll MOD = 1000000007;
ll pw(ll b, ll e) {
    ll r = 1; b %= MOD; if (b < 0) b += MOD;
    for (; e; e >>= 1, b = b * b % MOD) if (e & 1) r = r * b % MOD;
    return r;
}
ll lagrange(const vector<ll>& y, ll n) {
    int d = (int)y.size() - 1;
    if (n >= 0 && n <= d) return y[n] % MOD;
    n %= MOD; if (n < 0) n += MOD;
    vector<ll> pre(d + 2, 1), suf(d + 2, 1), fi(d + 1), f(d + 1, 1);
    for (int i = 1; i <= d; i++) f[i] = f[i - 1] * i % MOD;
    fi[d] = pw(f[d], MOD - 2);
    for (int i = d; i > 0; i--) fi[i - 1] = fi[i] * i % MOD;
    for (int i = 0; i <= d; i++) pre[i + 1] = pre[i] * ((n - i + MOD) % MOD) % MOD;      // prod_{j<=i}(n-j)
    for (int i = d; i >= 0; i--) suf[i] = suf[i + 1] * ((n - i + MOD) % MOD) % MOD;      // prod_{j>=i}(n-j)
    ll res = 0;
    for (int i = 0; i <= d; i++) {
        ll t = y[i] % MOD * pre[i] % MOD * suf[i + 1] % MOD * fi[i] % MOD * fi[d - i] % MOD;
        if ((d - i) & 1) t = (MOD - t) % MOD; // sinal (-1)^(d-i)
        res = (res + t) % MOD;
    }
    return res;
}
