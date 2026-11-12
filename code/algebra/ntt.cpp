// NTT (transformada teorica dos numeros) e convolucao mod 998244353
//
// O que faz: multiplica dois polinomios com coeficientes mod 998244353 (g = 3).
// Quando usar: "contagem vira produto de polinomios", soma de pares a_i+b_j=s
//   (Catalogo > Algebra, polinomios e FFT: Convolucao de somas, NTT primos amigaveis).
// Complexidade: O(n log n) por transformada.
// Uso: vector<int> c = multiply(a, b); // c[k] = sum a[i]*b[k-i] mod MOD, 0-based
//   ntt(a, false) transforma (tamanho potencia de 2); ntt(a, true) e a inversa.
//   Outros primos NTT: 167772161 (g=3), 469762049 (g=3), 1004535809 (g=3), 754974721 (g=11).
// Cuidados: tamanho maximo 2^23 neste primo; entradas devem estar em [0, MOD).
//   Para modulo arbitrario ver code/algebra/conv_mod.cpp.
const int MOD = 998244353, G = 3;
ll pw(ll b, ll e) { // b^e mod MOD
    ll r = 1; b %= MOD; if (b < 0) b += MOD;
    for (; e; e >>= 1, b = b * b % MOD) if (e & 1) r = r * b % MOD;
    return r;
}
void ntt(vector<int>& a, bool inv) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) { // permutacao bit-reversal
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll w = pw(G, (MOD - 1) / len);
        if (inv) w = pw(w, MOD - 2);
        int h = len / 2;
        vector<int> ws(h); // potencias de w do estagio
        ws[0] = 1;
        for (int k = 1; k < h; k++) ws[k] = (ll)ws[k - 1] * w % MOD;
        for (int i = 0; i < n; i += len)
            for (int j = 0; j < h; j++) {
                int u = a[i + j], v = (ll)a[i + j + h] * ws[j] % MOD;
                a[i + j] = u + v >= MOD ? u + v - MOD : u + v;
                a[i + j + h] = u - v < 0 ? u - v + MOD : u - v;
            }
    }
    if (inv) { // divide por n
        ll ni = pw(n, MOD - 2);
        for (auto& x : a) x = x * ni % MOD;
    }
}
vector<int> multiply(vector<int> a, vector<int> b) {
    if (a.empty() || b.empty()) return {};
    int need = a.size() + b.size() - 1;
    if (min(a.size(), b.size()) <= 16) { // pequeno: ingenuo
        vector<int> c(need, 0);
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = 0; j < b.size(); j++)
                c[i + j] = (c[i + j] + (ll)a[i] * b[j]) % MOD;
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
