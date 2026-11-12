// comb - fatoriais e binomiais modulo M (versao simples)
const ll M = 1000000007;
const int MAXN = 2000005;
ll fact[MAXN], invFact[MAXN];

ll modExp(ll b, ll e, ll m) {
    ll r = 1; b %= m;
    for (; e > 0; e >>= 1, b = b * b % m) if (e & 1) r = r * b % m;
    return r;
}

void precompute() {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = fact[i - 1] * i % M;
        invFact[i] = modExp(fact[i], M - 2, M);
    }
}

ll binomial(ll n, ll k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invFact[k] % M * invFact[n - k] % M;
}
/*LATEX_DESC_BEGIN***************************
-> **comb - fatoriais e binomiais modulo M**
Pre-calcula fact e invFact e responde C(n,k) mod M, com M primo > MAXN.
Versao antiga e simples; para uso geral prefira binom_mod.cpp.

Complexidade: precompute O(MAXN); cada binomial O(1).
Uso:
  precompute();
  ll c = binomial(n, k);   // 0 <= k <= n <= MAXN

* Sobre o codigo:
  fact[i] = i! mod M; invFact[i] = (i!)^(-1) mod M via Fermat. binomial usa
  fact[n] * invFact[k] * invFact[n-k]. modExp e exponenciacao binaria.

* Problemas e reducoes:
  + Contagem de caminhos em grade: C(n+m, n).
  + Coeficientes do binomio de Newton e probabilidades discretas.
  + Numero de subconjuntos de tamanho k.

Cuidados: M deve ser primo e > MAXN; nao cole junto com binom_mod.cpp
  (nomes repetidos). MAXN fixo em 2e6.
Catalogo: Combinatoria, contagem e probabilidade (binomiais).
Digitacao: 19 linhas | facil.
*****************************LATEX_DESC_END*/
