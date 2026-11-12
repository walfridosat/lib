// Soma de potencias sum_{k=1}^n k^d mod p (Faulhaber via Lagrange)
//
// O que faz: calcula S(n,d) = 1^d + 2^d + ... + n^d mod 1e9+7 para n ate 1e18 e d ate ~1e6.
//   Tambem soma_geo: sum_{k=0}^{n-1} k^d * r^k (r != 1).
// Quando usar: "soma de k^d" com n gigante (Catalogo > Algebra, polinomios e FFT: Sigma k^d,
//   Sigma k^d r^k).
// Complexidade: O(d log d) (potencias por pw; troque por crivo linear se d ~ 1e7), depois O(d).
// Uso: ll r = power_sum(n, d); // d >= 0, S(n,0) = n
//      ll g = power_geo(n, d, r); // sum_{k=0}^{n-1} k^d r^k mod p, r != 1, r mod p != 1
// Cuidados: S(n,d) e polinomio em n de grau d+1 -> usa d+2 pontos. power_geo usa que
//   sum_{k<n} k^d r^k = r^n Q(n) - Q(0) com deg Q = d: Q(m) vem das somas parciais T(m) e
//   de Q(0) (incognita, achada impondo diferenca finita de ordem d+1 igual a zero); depois
//   Lagrange em Q. Convencao 0^0 = 1.
const ll MOD = 1000000007;
ll pw(ll b, ll e) {
    ll r = 1; b %= MOD; if (b < 0) b += MOD;
    for (; e; e >>= 1, b = b * b % MOD) if (e & 1) r = r * b % MOD;
    return r;
}
ll lagrange(const vector<ll>& y, ll n) { // P(n) dado P(0..d); ver code/algebra/lagrange.cpp
    int d = (int)y.size() - 1;
    if (n >= 0 && n <= d) return y[n] % MOD;
    n %= MOD; if (n < 0) n += MOD;
    vector<ll> pre(d + 2, 1), suf(d + 2, 1), fi(d + 1), f(d + 1, 1);
    for (int i = 1; i <= d; i++) f[i] = f[i - 1] * i % MOD;
    fi[d] = pw(f[d], MOD - 2);
    for (int i = d; i > 0; i--) fi[i - 1] = fi[i] * i % MOD;
    for (int i = 0; i <= d; i++) pre[i + 1] = pre[i] * ((n - i + MOD) % MOD) % MOD;
    for (int i = d; i >= 0; i--) suf[i] = suf[i + 1] * ((n - i + MOD) % MOD) % MOD;
    ll res = 0;
    for (int i = 0; i <= d; i++) {
        ll t = y[i] % MOD * pre[i] % MOD * suf[i + 1] % MOD * fi[i] % MOD * fi[d - i] % MOD;
        if ((d - i) & 1) t = (MOD - t) % MOD;
        res = (res + t) % MOD;
    }
    return res;
}
ll power_sum(ll n, int d) {
    vector<ll> y(d + 2, 0); // y[i] = S(i, d)
    for (int i = 1; i <= d + 1; i++) y[i] = (y[i - 1] + pw(i, d)) % MOD;
    return lagrange(y, n);
}
// sum_{k=0}^{n-1} k^d r^k. Seja T(m) = soma parcial. T(m) = r^m Q(m) - Q(0), deg Q = d.
// Tomamos o ponto (m, T(m)) para m = 0..d+1 e resolvemos Q(m) = (T(m)+Q(0)) / r^m;
// Q(0) e determinado impondo grau(Q) <= d: a (d+1)-esima diferenca finita de Q e zero.
ll power_geo(ll n, int d, ll r) {
    r %= MOD;
    vector<ll> T(d + 2, 0), rp(d + 2, 1), ri(d + 2, 1);
    ll rinv = pw(r, MOD - 2);
    for (int i = 1; i <= d + 1; i++) { rp[i] = rp[i - 1] * r % MOD; ri[i] = ri[i - 1] * rinv % MOD; }
    for (int i = 1; i <= d + 1; i++) T[i] = (T[i - 1] + pw(i - 1, d) * rp[i - 1]) % MOD; // T[i] = sum_{k<i}
    // Q(m) = (T[m] + c) * ri[m], c = Q(0). Diferenca de ordem d+1 de Q em 0..d+1 = 0 e linear em c.
    // sum_j (-1)^j C(d+1,j) Q(j) = 0 -> c * A + B = 0, A = sum (-1)^j C ri[j], B = sum (-1)^j C T[j] ri[j]
    ll A = 0, B = 0, C = 1; // C = C(d+1, j)
    for (int j = 0; j <= d + 1; j++) {
        ll sg = (j & 1) ? MOD - 1 : 1;
        A = (A + sg * C % MOD * ri[j]) % MOD;
        B = (B + sg * C % MOD * T[j] % MOD * ri[j]) % MOD;
        C = C * (d + 1 - j) % MOD * pw(j + 1, MOD - 2) % MOD;
    }
    ll c = (MOD - B) % MOD * pw(A, MOD - 2) % MOD;
    vector<ll> q(d + 1); // Q(0..d)
    for (int m = 0; m <= d; m++) q[m] = (T[m] + c) % MOD * ri[m] % MOD;
    ll Qn = lagrange(q, n);
    return (pw(r, n) * Qn % MOD - c + MOD) % MOD; // r^n Q(n) - Q(0)
}
