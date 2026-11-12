// Convolucao com modulo arbitrario por 3 NTT + CRT (Garner)
//
// O que faz: c = a*b mod M para M qualquer (ex.: 1e9+7), exato (sem erro de ponto flutuante).
// Quando usar: precisa de convolucao mod 1e9+7 / modulo composto
//   (Catalogo > Algebra, polinomios e FFT: Modulo arbitrario (MTT)).
// Complexidade: O(n log n), 9 NTTs (3 primos x 3 transformadas).
// Uso: vector<ll> c = convArb(a, b, M); // 0-based, coeficientes em [0, M)
// Cuidados: o coeficiente real chega a n*M^2; o produto dos 3 primos e ~8e25, entao
//   vale para n*M^2 < 8e25 (n=1e6 e M=1e9 da 1e24: ok). Tamanho <= 2^23.
//   Alternativa em double: code/algebra/fft.cpp (convMod).
template<int P, int RT> struct NTTm { // NTT para primo P e raiz primitiva RT
    static ll pw(ll b, ll e) { ll r = 1; b %= P; for (; e; e >>= 1, b = b * b % P) if (e & 1) r = r * b % P; return r; }
    static void run(vector<int>& a, bool inv) {
        int n = a.size();
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            ll w = pw(RT, (P - 1) / len);
            if (inv) w = pw(w, P - 2);
            int h = len / 2;
            vector<int> ws(h); ws[0] = 1;
            for (int k = 1; k < h; k++) ws[k] = (ll)ws[k - 1] * w % P;
            for (int i = 0; i < n; i += len)
                for (int j = 0; j < h; j++) {
                    int u = a[i + j], v = (ll)a[i + j + h] * ws[j] % P;
                    a[i + j] = u + v >= P ? u + v - P : u + v;
                    a[i + j + h] = u - v < 0 ? u - v + P : u - v;
                }
        }
        if (inv) { ll ni = pw(n, P - 2); for (auto& x : a) x = x * ni % P; }
    }
    static vector<int> mul(const vector<ll>& a, const vector<ll>& b) { // a*b mod P
        int need = a.size() + b.size() - 1, n = 1;
        while (n < need) n <<= 1;
        vector<int> x(n), y(n);
        for (size_t i = 0; i < a.size(); i++) x[i] = a[i] % P;
        for (size_t i = 0; i < b.size(); i++) y[i] = b[i] % P;
        run(x, false); run(y, false);
        for (int i = 0; i < n; i++) x[i] = (ll)x[i] * y[i] % P;
        run(x, true);
        x.resize(need);
        return x;
    }
};
vector<ll> convArb(const vector<ll>& a, const vector<ll>& b, ll M) {
    if (a.empty() || b.empty()) return {};
    const int P1 = 998244353, P2 = 167772161, P3 = 469762049;
    auto r1 = NTTm<P1, 3>::mul(a, b), r2 = NTTm<P2, 3>::mul(a, b), r3 = NTTm<P3, 3>::mul(a, b);
    auto pw = [](ll b, ll e, ll m) { ll r = 1; b %= m; for (; e; e >>= 1, b = b * b % m) if (e & 1) r = r * b % m; return r; };
    ll inv12 = pw(P1, P2 - 2, P2);                // P1^-1 mod P2
    ll inv123 = pw((ll)P1 * P2 % P3, P3 - 2, P3); // (P1*P2)^-1 mod P3
    vector<ll> c(r1.size());
    for (size_t i = 0; i < c.size(); i++) {
        // Garner: x = r1 + P1*k1 + P1*P2*k2
        ll k1 = (r2[i] - r1[i]) % P2; if (k1 < 0) k1 += P2;
        k1 = k1 * inv12 % P2;
        ll x12 = r1[i] + (ll)P1 * k1; // < P1*P2 ~ 1.7e17, cabe em ll
        ll k2 = ((r3[i] - x12) % P3 + P3) % P3 * inv123 % P3;
        c[i] = (x12 % M + (ll)((__int128)P1 * P2 % M) * k2 % M) % M;
    }
    return c;
}
