// Pollard rho (Brent) e fatoracao
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
ull rho(ull n) { // divisor nao trivial de n composto impar
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
/*LATEX_DESC_BEGIN***************************
-> **Pollard rho (Brent) e fatoracao**
Fatora n < 2^63 em primos com Miller-Rabin + Pollard rho.

Complexidade: ~O(n^(1/4)) mulmods por fator.
Uso:
  auto f = factorize(n);       // vector<pair<ull,int>> ordenado; n = 1 -> vazio

* Sobre o codigo:
  factorize tira primos pequenos por divisao; fact_rec testa is_prime e, se
  composto, chama rho. rho usa o metodo de Brent, acumulando produtos para
  fazer gcd em lote e refazendo passo a passo se o lote falhar.

* Problemas e reducoes:
  + Fatorar n ate 1e18 -> factorize.
  + Gerar divisores de um numero grande -> factorize + divs_fact.
  + Contar fatores primos distintos / com multiplicidade -> fatoracao.
  + Provar que um numero grande e composto -> is_prime.
  + Base para phi, mu e ordem de n grande -> fatoracao.

Cuidados: contem copia de mulmod/powmod/is_prime de miller_rabin.cpp (apague
  uma copia ao colar os dois); primos pequenos sao retirados por divisao antes;
  o +c do polinomio precisa caber.
Catalogo: Teoria dos numeros.
Digitacao: 64 linhas | dificil. Atalho: incluir miller_rabin.cpp em vez de duplicar as tres funcoes.
*****************************LATEX_DESC_END*/
