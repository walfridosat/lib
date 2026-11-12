// Inclusao-exclusao: utilitarios
//
// O que faz: (1) contar inteiros em [1,N] nao divisiveis por nenhum de uma lista
//   (IE com DFS e poda); (2) "exatamente k" a partir de "pelo menos k" (inversao
//   binomial); (3) IE sobre subconjuntos por mascara com funcao N(S); (4) min-max:
//   max(S) = sum_{T} (-1)^{|T|+1} min(T) (esperanca do maximo, coupon desigual);
//   (5) sum_{k = r mod m} C(n,k) via (1+x)^n mod (x^m - 1).
// Quando usar: "Catalogo > Combinatoria" (Inclusao-exclusao; Exatamente k; Min-max;
//   Filtro de raizes da unidade). Sobrejecoes: stirling_bell.cpp (surjections).
// Complexidade: (1) O(2^m) com poda; (3)(4) O(2^n * n); (5) O(m^2 log n).
// Requer: code/combinatorics/binom_mod.cpp (cole antes).
// Uso: precisa de binom_mod.cpp (MOD, pw, C, init_comb) colado antes.
//   count_coprime(N, d): # x em [1,N] com x % d_i != 0 para todo i.
//   exact_from_atleast(g): g[k] = sum_{|S|=k} N(S) (pelo menos); devolve f[k] = # com exatamente k.
//   ie_subsets(n, N): sum_S (-1)^{|S|} N(mask), N vira lambda mask->ll (mod MOD).
//   minmax_expect(n, minv): minv[mask] = E[min dos elementos de mask] mod p -> E[max de todos].
//   sum_binom_mod_class(n, m, r) = sum_{k = r (mod m)} C(n,k) mod MOD (n ate 1e18, m ate ~2000).
// Cuidados: (1) d_i com lcm > N sao podados (contribuem 0); sem d_i=0. (2) usa binomiais C(j,k).
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
// g[k] = sum_{|S|=k} N(S); f[k] = sum_{j>=k} (-1)^{j-k} C(j,k) g[j]
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
template<class F> ll ie_subsets(int n, F N) { // N(mask) = # que satisfazem todos os defeitos de mask
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
