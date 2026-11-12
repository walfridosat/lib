// Divisores - listar, formulas e altamente compostos
vector<ll> divs_sqrt(ll n) {
    vector<ll> a, b;
    for (ll i = 1; i * i <= n; i++) if (n % i == 0) {
        a.push_back(i);
        if (i != n / i) b.push_back(n / i);
    }
    reverse(b.begin(), b.end());
    a.insert(a.end(), b.begin(), b.end()); // ja ordenado
    return a;
}
vector<pair<ll, int>> trial_fact(ll n) { // n <= ~1e12
    vector<pair<ll, int>> f;
    for (ll p = 2; p * p <= n; p++) if (n % p == 0) {
        int e = 0;
        while (n % p == 0) n /= p, e++;
        f.push_back({p, e});
    }
    if (n > 1) f.push_back({n, 1});
    return f;
}
vector<ll> divs_fact(const vector<pair<ll, int>> &f) {
    vector<ll> d = {1};
    for (auto [p, e] : f) {
        int sz = d.size(); ll pk = 1;
        for (int k = 1; k <= e; k++) {
            pk *= p;
            for (int i = 0; i < sz; i++) d.push_back(d[i] * pk);
        }
    }
    return d;
}
ll tau_f(const vector<pair<ll, int>> &f) { // numero de divisores
    ll r = 1;
    for (auto [p, e] : f) r *= e + 1;
    return r;
}
// sigma(n) mod m: usa geo() (m qualquer)
ll geo(ll p, ll e, ll m) { // 1 + p + ... + p^e mod m, divisao e conquista
    if (e == 0) return 1 % m;
    if (e % 2 == 1) { // (1+p+...+p^((e-1)/2)) * (1 + p^((e+1)/2))
        ll h = (e - 1) / 2, a = geo(p, h, m), pw = 1 % m, b = p % m;
        for (ll k = h + 1; k; k >>= 1, b = (__int128)b * b % m) if (k & 1) pw = (__int128)pw * b % m;
        return (__int128)a * ((1 + pw) % m) % m;
    }
    // e par: 1 + p*(1+...+p^(e-1))
    return (1 + (__int128)(p % m) * geo(p, e - 1, m)) % m;
}
ll sigma_mod(const vector<pair<ll, int>> &f, ll m) {
    ll r = 1 % m;
    for (auto [p, e] : f) r = (__int128)r * geo(p, e, m) % m;
    return r;
}
// HCN: expoentes nao crescentes em 2,3,5,...
const int HP[15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
ll hc_best_tau, hc_best_n;
void hc_dfs(int i, ll n, ll tau, int maxe, ll N) {
    if (tau > hc_best_tau || (tau == hc_best_tau && n < hc_best_n)) hc_best_tau = tau, hc_best_n = n;
    if (i == 15) return;
    ll cur = n;
    for (int e = 1; e <= maxe; e++) {
        if (cur > N / HP[i]) break; // evita overflow
        cur *= HP[i];
        hc_dfs(i + 1, cur, tau * (e + 1), e, N);
    }
}
pair<ll, ll> hcn_max_tau(ll N) { // {tau maximo, menor n <= N que o atinge}
    hc_best_tau = 0; hc_best_n = 1;
    hc_dfs(0, 1, 1, 62, N);
    return {hc_best_tau, hc_best_n};
}
/*LATEX_DESC_BEGIN***************************
-> **Divisores, tau/sigma e altamente compostos**
Lista divisores por sqrt ou pela fatoracao, calcula tau/sigma/produto e acha o menor n <= N com tau maximo.

Complexidade: divs_sqrt O(sqrt n); divs_fact O(tau); hcn O(#candidatos).
Uso:
  vector<ll> d = divs_sqrt(n);                 // ordenado
  auto f = trial_fact(n);                      // ou factorize de pollard_rho
  vector<ll> d2 = divs_fact(f);                // nao ordenado
  ll t = tau_f(f);
  ll s = sigma_mod(f, m);                      // m qualquer, sem inverso
  pair<ll,ll> h = hcn_max_tau(N);              // {tau maximo, menor n}

* Sobre o codigo:
  divs_sqrt junta os pares i e n/i; divs_fact multiplica potencias de cada primo.
  geo(p, e, m) soma 1 + p + ... + p^e por divisao e conquista, sem inverso,
  e alimenta sigma_mod. hcn_dfs usa expoentes nao crescentes nos 15 primeiros
  primos, podando quando n * p passa de N.

* Problemas e reducoes:
  + Listar todos os divisores de n -> divs_sqrt (n ate ~1e12) ou divs_fact.
  + Numero/soma de divisores a partir da fatoracao -> tau_f / sigma_mod.
  + Menor n <= N com o maior numero de divisores -> hcn_max_tau.
  + Soma de serie geometrica mod m sem inverso -> geo(p, e, m).
  + Produto dos divisores ou soma dos quadrados -> usar os expoentes.
  + Divisores de um produto/MMC a partir das fatoracoes -> somar expoentes.

Cuidados: divs_sqrt e O(sqrt n), so ate ~1e12; sigma pode estourar ll (use
  __int128 ou mod); hcn usa 15 primos (basta para N <= 1e18).
Catalogo: Teoria dos numeros.
Digitacao: 70 linhas | media. Atalho: tau_f e uma reducao de expoentes; cabe em uma linha.
*****************************LATEX_DESC_END*/
