// Fatoriais e binomiais modulo M (versao antiga e simples)
//
// O que faz: pre-calcula fact/invFact e responde C(n,k) modulo M.
// Quando usar: Catalogo > Combinatoria, contagem e probabilidade (binomiais).
//   n <= MAXN e M primo > MAXN. Para uso geral prefira binom_mod.cpp.
// Complexidade: precompute O(MAXN); cada binomial O(1).
// Uso: precompute(); binomial(n,k) com 0 <= k <= n <= MAXN.
// Cuidados: M deve ser primo; nao cole junto com binom_mod.cpp (nomes repetidos).
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
