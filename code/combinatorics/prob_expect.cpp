// Probabilidade e esperanca mod p
// Requer: code/combinatorics/binom_mod.cpp (cole antes).
vector<ll> solve_mod(vector<vector<ll>> A, vector<ll> b) {
    int n = A.size();
    for (int i = 0; i < n; i++) { A[i].push_back(b[i]); for (auto& x : A[i]) x = (x % MOD + MOD) % MOD; }
    for (int c = 0; c < n; c++) {
        int pv = -1;
        for (int i = c; i < n; i++) if (A[i][c]) { pv = i; break; }
        if (pv < 0) return {};
        swap(A[pv], A[c]);
        ll iv = pw(A[c][c], MOD - 2);
        for (int j = c; j <= n; j++) A[c][j] = A[c][j] * iv % MOD;
        for (int i = 0; i < n; i++) if (i != c && A[i][c]) {
            ll f = A[i][c];
            for (int j = c; j <= n; j++) A[i][j] = ((A[i][j] - f * A[c][j]) % MOD + MOD) % MOD;
        }
    }
    vector<ll> x(n);
    for (int i = 0; i < n; i++) x[i] = A[i][n];
    return x;
}
// E[i] = 1 + sum_j P[i][j] E[j]
vector<ll> markov_absorbing(const vector<vector<ll>>& P, const vector<bool>& absorb) {
    int n = P.size(); vector<int> id(n, -1), who;
    for (int i = 0; i < n; i++) if (!absorb[i]) { id[i] = who.size(); who.push_back(i); }
    int m = who.size();
    vector<vector<ll>> A(m, vector<ll>(m, 0)); vector<ll> b(m, 1);
    for (int a = 0; a < m; a++) {
        A[a][a] = 1;
        for (int j = 0; j < n; j++) if (id[j] >= 0) A[a][id[j]] = ((A[a][id[j]] - P[who[a]][j]) % MOD + MOD) % MOD;
    }
    vector<ll> x = solve_mod(A, b), E(n, 0);
    if (m && x.empty()) return {};
    for (int a = 0; a < m; a++) E[who[a]] = x[a];
    return E;
}
ll coupon_k(ll n, ll k) { // coletar k tipos distintos de n
    ll r = 0;
    for (ll i = 0; i < k; i++) r = (r + n % MOD * pw(n - i, MOD - 2)) % MOD;
    return r;
}
ll coupon(ll n) { return coupon_k(n, n); } // n H_n
// tempo esperado ate ver s (alfabeto q)
ll pattern_time(const string& s, ll q) {
    int n = s.size(); ll r = 0;
    for (int k = 1; k <= n; k++) if (s.substr(0, k) == s.substr(n - k)) r = (r + pw(q, k)) % MOD;
    return r;
}
// P(chegar a N); p = prob de +1
ll gambler_win(ll i, ll N, ll p, ll q) {
    if (p == q) return i % MOD * pw(N, MOD - 2) % MOD; // justo: i/N
    ll rr = q * pw(p, MOD - 2) % MOD;
    return (pw(rr, i) - 1 + MOD) % MOD * pw((pw(rr, N) - 1 + MOD) % MOD, MOD - 2) % MOD;
}
ll quicksort_cmp(ll n) { // comparacoes esperadas do quicksort
    ll r = 0;
    for (ll d = 1; d < n; d++) r = (r + 2 * (n - d) % MOD * pw(d + 1, MOD - 2)) % MOD;
    return r;
}
ll expected_max_dice(ll k, ll m) { // sum_{j=1}^{m} (1 - ((j-1)/m)^k)
    ll r = 0, im = pw(m, MOD - 2);
    for (ll j = 1; j <= m; j++) r = (r + 1 - pw((j - 1) * im % MOD, k) + MOD) % MOD;
    return r;
}
ll expected_distinct(ll N, ll n) { // N (1 - (1-1/N)^n)
    ll im = pw(N, MOD - 2);
    return N % MOD * ((1 - pw((1 - im + MOD) % MOD, n) + MOD) % MOD) % MOD;
}
/*LATEX_DESC_BEGIN***************************
-> **Probabilidade e esperanca mod p**
Cadeia de Markov absorvente, coupon collector, tempo ate padrao, ruina, quicksort e indicadores.

Complexidade: Gauss O(n^3); formulas O(n) a O(n log).
Uso:
  vector<ll> x = solve_mod(A, b);
  vector<ll> E = markov_absorbing(P, absorb);
  ll c = coupon(n), ck = coupon_k(n, k);
  ll t = pattern_time(s, q);
  ll gw = gambler_win(i, N, p, q);
  ll qc = quicksort_cmp(n), md = expected_max_dice(k, m);
  ll ed = expected_distinct(N, n);

* Sobre o codigo:
  solve_mod faz Gauss-Jordan mod p (vazio se singular). markov_absorbing
  monta (I-Q)E = 1 so para estados nao absorventes. As formulas usam
  inversos mod p: coupon = n H_n; pattern_time soma q^k nas bordas; gambler
  resolve o passeio +-1; quicksort soma 2/(j-i+1).

* Problemas e reducoes:
  + Tempo esperado ate absorver em cadeia de Markov -> markov_absorbing.
  + Coupon collector uniforme e com k tipos -> coupon/coupon_k.
  + Tempo esperado ate ver uma string em alfabeto q -> pattern_time.
  + Probabilidade de ruina / chegar a N -> gambler_win.
  + Comparacoes esperadas do quicksort -> quicksort_cmp.
  + Maximo esperado de k dados de m faces -> expected_max_dice.
  + Valores distintos esperados em n sorteios -> expected_distinct.
  + Resolver sistema linear mod p -> solve_mod.

Cuidados: probabilidades como fracao mod p (a/b -> a * pw(b, MOD-2)); nunca
  use double se a saida e mod p; estados absorventes tem a linha ignorada;
  no padrao, E = sum q^k sobre k com prefixo_k = sufixo_k (inclui k = |s|).
Catalogo: Combinatoria.
Digitacao: 66 linhas | dificil. Atalho: as formulas repetem pw(...,MOD-2); guarde inversos.
*****************************LATEX_DESC_END*/
