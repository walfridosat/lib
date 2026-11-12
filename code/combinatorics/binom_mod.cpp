// Fatoriais e binomiais modulo primo
const ll MOD = 998244353;
const int MAXN = 2000005;
ll fact[MAXN], ifact[MAXN], inv_[MAXN];
ll pw(ll b, ll e) { // potencia modular
    ll r = 1; b %= MOD; if (b < 0) b += MOD;
    for (; e > 0; e >>= 1, b = b * b % MOD) if (e & 1) r = r * b % MOD;
    return r;
}
void init_comb(int N = MAXN - 1) {
    fact[0] = 1;
    for (int i = 1; i <= N; i++) fact[i] = fact[i-1] * i % MOD;
    ifact[N] = pw(fact[N], MOD - 2);
    for (int i = N; i > 0; i--) ifact[i-1] = ifact[i] * i % MOD;
    inv_[1] = 1;
    for (int i = 2; i <= N; i++) inv_[i] = (MOD - MOD / i) * inv_[MOD % i] % MOD; // inverso linear
}
ll C(ll n, ll k) {
    if (k < 0 || n < 0 || k > n) return 0;
    return fact[n] * ifact[k] % MOD * ifact[n-k] % MOD;
}
ll P(ll n, ll k) { // arranjo n!/(n-k)!
    if (k < 0 || n < 0 || k > n) return 0;
    return fact[n] * ifact[n-k] % MOD;
}
ll multinomial(const vector<int>& v) { // (sum v)! / prod v_i!
    ll s = 0, r = 1;
    for (int x : v) { s += x; r = r * ifact[x] % MOD; }
    return r * fact[s] % MOD;
}
ll multiset(ll n, ll k) { // n tipos, escolhe k com repeticao
    if (n == 0) return k == 0;
    return C(n + k - 1, k);
}
// C(n,k) com n grande e k pequeno (k < MOD)
ll C_big(ll n, ll k) {
    if (k < 0 || k > n) return 0;
    ll r = 1;
    for (ll i = 0; i < k; i++) r = r * ((n - i) % MOD) % MOD;
    return r * ifact[k] % MOD;
}
// solucoes com 0<=x_i<=u, por inclusao-exclusao
ll bounded_sb(ll n, ll k, ll u) {
    ll r = 0;
    for (ll j = 0; j <= k && n - j * (u + 1) >= 0; j++) {
        ll t = C(k, j) * C(n - j * (u + 1) + k - 1, k - 1) % MOD;
        r = (r + (j & 1 ? MOD - t : t)) % MOD;
    }
    return r;
}
// S(n,m)=sum_{i<=m} C(n,i), move n,m em O(1)
struct PartialBinom {
    ll n, m, S;
    PartialBinom(ll n_, ll m_) : n(n_), m(m_) { // calcula S inicial em O(m)
        S = 0; for (ll i = 0; i <= m; i++) S = (S + C(n, i)) % MOD;
    }
    void n_up() { S = (2 * S - C(n, m) + MOD) % MOD; n++; } // S(n+1,m)=2S(n,m)-C(n,m)
    void n_down() { n--; S = (S + C(n, m)) % MOD * ((MOD + 1) / 2) % MOD; } // inversa da anterior
    void m_up() { m++; S = (S + C(n, m)) % MOD; }
    void m_down() { S = (S - C(n, m) + MOD) % MOD; m--; }
};
/*LATEX_DESC_BEGIN***************************
-> **Fatoriais e binomiais mod primo**
Pre-calcula fatorial, inverso do fatorial e inversos; responde C, P, multinomial e somas parciais.

Complexidade: init O(N); consulta O(1) (bounded_sb O(k)).
Uso:
  init_comb(N);                 // N < MAXN
  ll c = C(n, k), p = P(n, k);
  ll m = multinomial(v), ms = multiset(n, k);
  ll b = bounded_sb(n, k, u);
  PartialBinom pb(n, m); pb.n_up(); pb.m_up(); // S(n,m) = sum_{i<=m} C(n,i)

* Sobre o codigo:
  fact/ifact em O(N); inv_ e o inverso linear. C e P checam o intervalo.
  multiset e estrelas e barras; bounded_sb aplica inclusao-exclusao.
  C_big usa produto direto para k pequeno. PartialBinom move n e m em O(1):
  S(n+1,m) = 2S(n,m) - C(n,m).

* Problemas e reducoes:
  + C(n,k) e P(n,k) mod primo com n <= 1e6 -> init_comb + C/P.
  + Estrelas e barras (multiconjuntos) -> multiset(n,k).
  + Solucoes de x_1+...+x_k = n com 0 <= x_i <= u -> bounded_sb.
  + Somas parciais sum_{i<=m} C(n,i) com n,m variando -> PartialBinom.
  + Multinomial (arranjos de grupos) -> multinomial.
  + C(n,k) com n ate 1e18 e k pequeno -> C_big.
  + Probabilidades combinatorias mod p -> C/P.

Cuidados: MOD primo > N; n fora de [0, N] nao e tratado (use lucas.cpp ou
  binom_general.cpp); bounded_sb e O(k).
Catalogo: Combinatoria, contagem e probabilidade.
Digitacao: 60 linhas | media. Atalho: C e P repetem a checagem de intervalo; helper comum.
*****************************LATEX_DESC_END*/
