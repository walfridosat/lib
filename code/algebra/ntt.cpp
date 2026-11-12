// NTT e convolucao mod 998244353
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
/*LATEX_DESC_BEGIN***************************
-> **NTT e convolucao mod 998244353**
Multiplica dois polinomios com coeficientes mod 998244353 (raiz primitiva 3),
0-based.

Complexidade: O(n log n) por transformada.
Uso:
  vector<int> c = multiply(a, b);   // c[k] = sum a[i]*b[k-i] mod MOD
  ntt(a, false);                   // transformada (tamanho potencia de 2)
  ntt(a, true);                    // inversa

* Sobre o codigo:
  ntt faz bit-reversal e os estagios de borboleta com potencias de
  w = g^((p-1)/len); a inversa usa w^-1 e divide por n. multiply cai no ingenuo
  quando um dos vetores tem tamanho <= 16.

* Problemas e reducoes:
  + Convolucao de polinomios e somas de pares a_i + b_j = s.
  + Contagem que vira produto de polinomios.
  + Knapsack de contagem via exp/ln (ver poly.cpp).

Cuidados: tamanho maximo 2^23 neste primo; entradas em [0, MOD). Outros primos
  NTT: 167772161, 469762049, 1004535809 (g=3) e 754974721 (g=11). Para modulo
  arbitrario ver conv_mod.cpp.
Catalogo: Algebra, polinomios e FFT (Convolucao de somas / NTT primos).
Digitacao: 52 linhas | media.
*****************************LATEX_DESC_END*/
