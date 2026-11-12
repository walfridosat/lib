// Pollard rho (Brent) + fatoracao completa
//
// O que faz: fatora n < 2^63 (~9e18; o +c do polinomio precisa caber) em primos.
// Quando usar: Catalogo > Teoria dos numeros (fatorar ate 1e18; divisores de
//   numeros grandes; ver divisores.cpp para gerar divisores a partir daqui).
// Complexidade: ~O(n^(1/4)) mulmods por fator.
// Uso: factorize(n) -> vector<pair<ull,int>> (primo, expoente) ordenado.
//   n=1 devolve vazio.
// Cuidados: contem copia de mulmod/powmod/is_prime de miller_rabin.cpp
//   (apague uma das duas copias se colar os dois). Primos pequenos sao
//   retirados por divisao antes (rho falha em n pequeno / quadrado de primo
//   pequeno).
typedef unsigned long long ull;
ull mulmod(ull a, ull b, ull m) { return (__uint128_t)a * b % m; }
ull powmod(ull a, ull e, ull m) {
    ull r = 1 % m; a %= m;
    for (; e; e >>= 1, a = mulmod(a, a, m)) if (e & 1) r = mulmod(r, a, m);
    return r;
}
bool is_prime(ull n) {
    if (n < 2) return false;
    for (ull p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
        if (n % p == 0) return n == p;
    ull d = n - 1; int s = __builtin_ctzll(d); d >>= s;
    for (ull a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        ull x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool ok = false;
        for (int r = 1; r < s && !ok; r++) { x = mulmod(x, x, n); ok = (x == n - 1); }
        if (!ok) return false;
    }
    return true;
}
mt19937_64 rho_rng(712367);
ull rho(ull n) { // devolve um divisor nao trivial de n composto impar
    while (true) {
        ull c = rho_rng() % (n - 1) + 1, y = rho_rng() % n, x = 0, ys = 0, g = 1, q = 1;
        auto f = [&](ull v) { return (mulmod(v, v, n) + c) % n; };
        auto df = [&](ull a, ull b) { return a > b ? a - b : b - a; };
        const int M = 128;
        for (ull r = 1; g == 1; r <<= 1) {
            x = y;
            for (ull i = 0; i < r; i++) y = f(y);
            for (ull k = 0; k < r && g == 1; k += M) {
                ys = y;
                for (ull i = 0; i < (ull)M && i < r - k; i++) { // produto acumulado p/ gcd em lote
                    y = f(y); q = mulmod(q, df(x, y), n);
                }
                g = __gcd(q, n);
            }
        }
        if (g == n) { // lote falhou: refaz passo a passo
            do { ys = f(ys); g = __gcd(df(x, ys), n); } while (g == 1);
        }
        if (g != n) return g;
    }
}
void fact_rec(ull n, vector<ull> &f) {
    if (n == 1) return;
    if (is_prime(n)) { f.push_back(n); return; }
    ull d = rho(n);
    fact_rec(d, f); fact_rec(n / d, f);
}
vector<pair<ull, int>> factorize(ull n) {
    vector<ull> f;
    for (ull p = 2; p < 50 && p * p <= n; p++) // primos pequenos por divisao
        while (n % p == 0) f.push_back(p), n /= p;
    if (n > 1) fact_rec(n, f); // is_prime cuida de n pequeno
    sort(f.begin(), f.end());
    vector<pair<ull, int>> r;
    for (ull p : f) {
        if (!r.empty() && r.back().first == p) r.back().second++;
        else r.push_back({p, 1});
    }
    return r;
}
