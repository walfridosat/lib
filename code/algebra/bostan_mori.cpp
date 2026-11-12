// Bostan-Mori: [x^n] P(x)/Q(x) mod 998244353
//
// O que faz: n-esimo coeficiente de uma serie racional P/Q (Q[0] != 0). Para recorrencia
//   s[i] = sum_j c[j] s[i-1-j] monta Q = 1 - sum c[j] x^(j+1), P = (s * Q) mod x^L.
// Quando usar: recorrencia linear de ordem k >= ~50 e n enorme (1e18)
//   (Catalogo > Algebra, polinomios e FFT: Kitamasa / Bostan-Mori).
// Complexidade: O(k log k log n) com NTT.
// Uso: ll v = nth_linear_rec(s, c, n);  // s = primeiros L termos, c = coef. (como em BM)
//      ll w = bostan_mori(P, Q, n);     // P, Q vetores de int, 0-based
// Cuidados: MOD = 998244353 (NTT). Para MOD 1e9+7 troque mul por convArb de conv_mod.cpp
//   ou use kth de berlekamp_massey.cpp (O(k^2 log n)). Q[0] deve ser invertivel.
const int MOD = 998244353, G = 3;
ll pw(ll b, ll e) {
    ll r = 1; b %= MOD; if (b < 0) b += MOD;
    for (; e; e >>= 1, b = b * b % MOD) if (e & 1) r = r * b % MOD;
    return r;
}
typedef vector<int> P;
void ntt(P& a, bool inv) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll w = pw(G, (MOD - 1) / len);
        if (inv) w = pw(w, MOD - 2);
        int h = len / 2;
        P ws(h); ws[0] = 1;
        for (int k = 1; k < h; k++) ws[k] = (ll)ws[k - 1] * w % MOD;
        for (int i = 0; i < n; i += len)
            for (int j = 0; j < h; j++) {
                int u = a[i + j], v = (ll)a[i + j + h] * ws[j] % MOD;
                a[i + j] = u + v >= MOD ? u + v - MOD : u + v;
                a[i + j + h] = u - v < 0 ? u - v + MOD : u - v;
            }
    }
    if (inv) { ll ni = pw(n, MOD - 2); for (auto& x : a) x = x * ni % MOD; }
}
P mul(P a, P b) {
    int need = a.size() + b.size() - 1;
    if (min(a.size(), b.size()) <= 16) {
        P c(need, 0);
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = 0; j < b.size(); j++) c[i + j] = (c[i + j] + (ll)a[i] * b[j]) % MOD;
        return c;
    }
    int n = 1;
    while (n < need) n <<= 1;
    a.resize(n); b.resize(n);
    ntt(a, false); ntt(b, false);
    for (int i = 0; i < n; i++) a[i] = (ll)a[i] * b[i] % MOD;
    ntt(a, true);
    a.resize(need);
    return a;
}
ll bostan_mori(P p, P q, ll n) {
    while (n) {
        P qm = q; // Q(-x)
        for (size_t i = 1; i < qm.size(); i += 2) qm[i] = qm[i] ? MOD - qm[i] : 0;
        P u = mul(p, qm), v = mul(q, qm); // v so tem potencias pares
        p.clear(); q.clear();
        for (size_t i = n & 1; i < u.size(); i += 2) p.push_back(u[i]); // paridade de n escolhe o numerador
        for (size_t i = 0; i < v.size(); i += 2) q.push_back(v[i]);
        n >>= 1;
    }
    return p.empty() ? 0 : (ll)p[0] * pw(q[0], MOD - 2) % MOD;
}
ll nth_linear_rec(const vector<ll>& s, const vector<ll>& c, ll n) {
    int L = c.size();
    if (L == 0) return 0;
    P q(L + 1, 0), p(L, 0);
    q[0] = 1;
    for (int j = 0; j < L; j++) q[j + 1] = (MOD - c[j] % MOD) % MOD;
    for (int i = 0; i < L; i++) // p = s * q mod x^L
        for (int j = 0; j <= i; j++) p[i] = (p[i] + (ll)(s[j] % MOD) * q[i - j]) % MOD;
    return bostan_mori(p, q, n);
}
