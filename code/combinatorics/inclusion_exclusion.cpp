// Inclusao-exclusao - utilitarios
// Requer: code/combinatorics/binom_mod.cpp (cole antes).
ll ce_rec(const vector<ll>& d, size_t i, ll l, ll N, int sg) {
    ll res = 0;
    for (size_t j = i; j < d.size(); j++) {
        ll g = __gcd(l, d[j]);
        __int128 nl = (__int128)l / g * d[j];
        if (nl > N) continue;              // N/lcm = 0 e todo superconjunto tambem
        res += sg * (N / (ll)nl) + ce_rec(d, j + 1, (ll)nl, N, -sg);
    }
    return res;
}
ll count_coprime(ll N, vector<ll> d) {
    sort(d.begin(), d.end()); d.erase(unique(d.begin(), d.end()), d.end());
    return N + ce_rec(d, 0, 1, N, -1);   // N - sum |A_i| + sum |A_i ^ A_j| - ...
}
// inversao binomial de "pelo menos k"
vector<ll> exact_from_atleast(const vector<ll>& g) {
    int n = g.size();
    vector<ll> f(n, 0);
    for (int k = 0; k < n; k++)
        for (int j = k; j < n; j++) {
            ll t = C(j, k) * g[j] % MOD;
            f[k] = (f[k] + (((j - k) & 1) ? MOD - t : t)) % MOD;
        }
    return f;
}
template<class F> ll ie_subsets(int n, F N) { // N(mask) = satisfaz todos os defeitos
    ll r = 0;
    for (int m = 0; m < (1 << n); m++) {
        ll t = N(m) % MOD;
        r += (__builtin_popcount(m) & 1) ? MOD - t : t;
    }
    return r % MOD;
}
ll minmax_expect(int n, const vector<ll>& minv) { // max = sum_{T != 0} (-1)^{|T|+1} min(T)
    ll r = 0;
    for (int m = 1; m < (1 << n); m++) {
        ll t = minv[m] % MOD;
        r += (__builtin_popcount(m) & 1) ? t : MOD - t;
    }
    return r % MOD;
}
ll sum_binom_mod_class(ll n, int m, int r) { // (1+x)^n mod (x^m - 1)
    auto mul = [&](const vector<ll>& a, const vector<ll>& b) {
        vector<ll> c(m, 0);
        for (int i = 0; i < m; i++) if (a[i])
            for (int j = 0; j < m; j++) { int k = i + j; if (k >= m) k -= m; c[k] = (c[k] + a[i] * b[j]) % MOD; }
        return c;
    };
    vector<ll> res(m, 0), base(m, 0);
    res[0] = 1; base[1 % m] += 1; base[0] += 1;   // 1 + x (se m=1: x = 1, base[0]=2)
    for (; n > 0; n >>= 1, base = mul(base, base)) if (n & 1) res = mul(res, base);
    return res[r % m];
}
/*LATEX_DESC_BEGIN***************************
-> **Inclusao-exclusao - utilitarios**
Contagem por IE, inversao "exatamente k", IE sobre subconjuntos, min-max e soma de binomiais por classe.

Complexidade: (1) O(2^m) com poda; (3)(4) O(2^n n); (5) O(m^2 log n).
Uso:
  ll c = count_coprime(N, d);
  vector<ll> f = exact_from_atleast(g);
  ll s = ie_subsets(n, N);             // N e lambda mask -> ll
  ll e = minmax_expect(n, minv);
  ll sb = sum_binom_mod_class(n, m, r);

* Sobre o codigo:
  count_coprime faz IE por DFS sobre os divisores, podando lcm > N.
  exact_from_atleast inverte a relacao binomial. ie_subsets e minmax_expect
  varrem mascaras com sinal. sum_binom_mod_class eleva (1+x) a n modulo
  x^m - 1 por exponenciacao binaria.

* Problemas e reducoes:
  + Contar x em [1,N] nao divisiveis por nenhum d_i -> count_coprime.
  + Passar de "pelo menos k" para "exatamente k" -> exact_from_atleast.
  + Somar (-1)^|S| N(S) sobre subconjuntos -> ie_subsets.
  + Esperanca do maximo a partir do minimo de cada subconjunto -> minmax_expect.
  + Coupon collector com taxas desiguais -> minmax_expect.
  + Soma de C(n,k) com k = r mod m -> sum_binom_mod_class.
  + Sobrejecoes e uniao de eventos -> IE classica.

Cuidados: (1) d_i com lcm > N sao podados (contribuem 0); sem d_i = 0.
  (2) usa binomiais C(j,k) e precisa de init_comb.
Catalogo: Combinatoria.
Digitacao: 53 linhas | media. Atalho: ie_subsets e minmax_expect repetem o laco por mascara.
*****************************LATEX_DESC_END*/
