// Fatoriais e binomiais modulo primo
//
// O que faz: pre-calcula fact, ifact e inv_[1..N]; responde C(n,k), P(n,k),
//   multinomial, estrelas e barras (com e sem limite superior) e somas
//   parciais de binomiais S(n,m)=sum_{i<=m} C(n,i) deslizando n e m em O(1).
// Quando usar: "Catalogo > Combinatoria, contagem e probabilidade" (fatorial ate 1e6,
//   estrelas e barras, IE com limites, somas parciais de binomiais).
// Complexidade: init O(N); cada consulta O(1) (bounded_sb: O(k)).
// Uso: init_comb(N) uma vez (N < MAXN). C(n,k) com 0<=k<=n<=N, senao devolve 0.
//   multiset(n,k) = multiconjuntos de tamanho k de n tipos = C(n+k-1,k).
//   bounded_sb(n,k,u) = # (x_1..x_k) com 0<=x_i<=u e soma n.
//   PartialBinom pb(n,m); pb.n_up(); pb.m_up(); ... mantem S(n,m).
// Cuidados: MOD deve ser primo > N. n fora de [0,N] nao e tratado (use
//   lucas.cpp ou binom_general.cpp). Para n ate 1e18 e k pequeno use C_big.
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
// C(n,k) com n ate 1e18 e k pequeno (k < MOD): produto direto, precisa ifact[k]
ll C_big(ll n, ll k) {
    if (k < 0 || k > n) return 0;
    ll r = 1;
    for (ll i = 0; i < k; i++) r = r * ((n - i) % MOD) % MOD;
    return r * ifact[k] % MOD;
}
// # solucoes de x_1+..+x_k = n com 0<=x_i<=u, por IE: sum_j (-1)^j C(k,j) C(n-j(u+1)+k-1,k-1)
ll bounded_sb(ll n, ll k, ll u) {
    ll r = 0;
    for (ll j = 0; j <= k && n - j * (u + 1) >= 0; j++) {
        ll t = C(k, j) * C(n - j * (u + 1) + k - 1, k - 1) % MOD;
        r = (r + (j & 1 ? MOD - t : t)) % MOD;
    }
    return r;
}
// Soma parcial S(n,m)=sum_{i<=m} C(n,i), movendo n,m em O(1) por passo
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
