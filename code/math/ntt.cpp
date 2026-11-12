// NTT - convolucao mod 998244353
const int MOD = 998244353;
const int G = 3;
const int MAXCOEF = 1e6 + 1; // pra calcular mod x^n

vector<int> roots{0, 1}, rev; // roots[1]=1; prep_roots completa
ll power(ll b, ll e) {
    ll r = 1; b %= MOD;
    for (; e > 0; e >>= 1, b = b * b % MOD) if (e & 1) r = r * b % MOD;
    return r;
}

void prep_roots(int n) {
    if ((int)roots.size() >= n) return;
    int len = __builtin_ctz(roots.size());
    roots.resize(n);
    while ((1 << len) < n) {
        int z = power(G, (MOD - 1) >> (len + 1));
        for (int i = 1 << (len - 1); i < (1 << len); i++) {
            roots[2 * i] = roots[i];
            roots[2 * i + 1] = 1LL * roots[i] * z % MOD;
        }
        len++;
    }
}


void ntt(vector<int> &a) {
    int n = a.size();
    
    if ((int)rev.size() != n) {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; i++) {
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    
    prep_roots(n);
    
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                int z = 1LL * a[i + j + k] * roots[j + k] % MOD;
                a[i + j + k] = a[i + j] - z;
                if (a[i + j + k] < 0) a[i + j + k] += MOD; 
                a[i + j] = a[i + j] + z;
                if (a[i + j] >= MOD) a[i + j] -= MOD;  
            }
        }
    }
}

vector<int> convolution(vector<int> a, vector<int> b) {
    if (a.empty() || b.empty()) return {};
    
    int sz = a.size() + b.size() - 1;
    int n = 1;
    while (n < sz) n *= 2;
    
    a.resize(n);
    b.resize(n);
    
    ntt(a);
    ntt(b);
    
    for (int i = 0; i < n; ++i) {
        a[i] = 1LL * a[i] * b[i] % MOD;
    }
    
    ntt(a);
    reverse(a.begin() + 1, a.end()); 
 
    int inv_n = power(n, MOD - 2);
    for (int i = 0; i < n; ++i) {
        a[i] = 1LL * a[i] * inv_n % MOD;
    }
    
    a.resize(min(sz, MAXCOEF));
    return a;
}
/*LATEX_DESC_BEGIN***************************
-> **NTT - convolucao mod 998244353**
Convolucao de polinomios inteiros modulo 998244353 (raiz primitiva 3).

Complexidade: O(n log n) tempo; O(n) memoria.
Uso:
  prep_roots(n);              // n potencia de 2
  ntt(a);                     // transformada direta
  vector<int> c = convolution(a, b);

* Sobre o codigo:
  prep_roots pre-calcula as raizes em roots; ntt aplica bit-reversal em rev e
  as borboletas. A inversa e outra ntt seguida de reverse e escala por inv_n,
  dentro de convolution. MAXCOEF trunca a resposta.

* Problemas e reducoes:
  + Multiplicar polinomios mod 998244353 -> convolution.
  + Multiplicar inteiros grandes (base 10^k) -> convolution dos digitos.
  + Contar pares/somas de produtos -> convolucao das frequencias.
  + Somas de convolucao c[k] = sum a[i]*b[k-i] -> convolution.
  + Quadrado de um polinomio -> convolution(a, a).
  + Series formais (exp, log) usando NTT -> NTT como bloco base.

Cuidados: n potencia de 2 <= 2^23; roots comeca {0, 1}; sem includes/constantes
  globais proprias (usa MOD, G, MAXCOEF); nao misture com outro arquivo que
  defina MOD/roots/power com outro sentido.
Catalogo: Algebra, polinomios e FFT.
Digitacao: 68 linhas | dificil. Atalho: uma funcao inversa explicita evita o reverse manual.
*****************************LATEX_DESC_END*/
