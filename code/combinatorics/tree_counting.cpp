// Contagens de arvores rotuladas e estruturas classicas (Cayley, Prufer, componentes)
//
// O que faz: Cayley n^{n-2}; # arvores com graus dados; com vertice de grau d;
//   # formas de ligar k componentes em arvore; florestas com k raizes;
//   K_{a,b}; arvores com raiz, florestas com raiz; grafos conexos e DAGs
//   rotulados (O(n^2)); emparelhamentos perfeitos (2n-1)!!.
// Quando usar: "Catalogo > Combinatoria" (Prufer; Contar arvores que conectam componentes;
//   Grafos conexos e DAGs rotulados; Contagens classicas rotuladas).
//   Codificacao/decodificacao de Prufer: code/tree.
// Complexidade: O(1)..O(n) por formula; conexos/DAG O(n^2).
// Requer: code/combinatorics/binom_mod.cpp (cole antes).
// Uso: precisa de binom_mod.cpp (C, fact, ifact, pw, init_comb) colado antes.
//   cayley(n); trees_with_degrees(d) (d_i >= 1, soma = 2n-2); trees_vertex_degree(n,d);
//   join_components(sizes); forest_k_roots(n,k); bipartite_trees(a,b);
//   connected_graphs(N) -> c[0..N]; labeled_dags(N) -> a[0..N]; perfect_matchings(n pares).
// Cuidados: n pequeno (n=1,2) tem casos de borda tratados; expoentes negativos viram 1.
ll cayley(ll n) { return n <= 1 ? 1 : pw(n, n - 2); }
ll trees_with_degrees(const vector<int>& d) { // (n-2)! / prod (d_i-1)!
    int n = d.size(); ll s = 0;
    for (int x : d) { if (x < 1) return 0; s += x; }
    if (s != 2 * n - 2) return 0;
    if (n == 1) return 1;
    ll r = fact[n - 2];
    for (int x : d) r = r * ifact[x - 1] % MOD;
    return r;
}
ll trees_vertex_degree(ll n, ll d) { // C(n-2,d-1) (n-1)^{n-d-1}
    if (n == 1) return d == 0;
    if (n == 2) return d == 1;
    if (d < 1 || d > n - 1) return 0;
    return C(n - 2, d - 1) * pw(n - 1, n - d - 1) % MOD;
}
ll join_components(const vector<ll>& s) { // n^{k-2} prod s_i
    ll n = 0, k = s.size(), r = 1;
    for (ll x : s) { n += x; r = r * (x % MOD) % MOD; }
    if (k == 1) return 1;
    return r * pw(n, k - 2) % MOD;
}
ll forest_k_roots(ll n, ll k) { // k raizes especificadas: k n^{n-k-1}
    if (k == n) return 1;
    return k % MOD * pw(n, n - k - 1) % MOD;
}
ll bipartite_trees(ll a, ll b) { return pw(a, b - 1) * pw(b, a - 1) % MOD; } // geradoras de K_{a,b}
ll rooted_trees(ll n) { return pw(n, n - 1); }
ll rooted_forests(ll n) { return pw(n + 1, n - 1); }
ll perfect_matchings(ll n) { ll r = 1; for (ll i = 1; i < 2 * n; i += 2) r = r * i % MOD; return r; } // (2n-1)!!
// grafos conexos rotulados: c(n)=2^{C(n,2)} - sum_{k<n} C(n-1,k-1) c(k) 2^{C(n-k,2)}
vector<ll> connected_graphs(int N) {
    vector<ll> c(N + 1, 0), p2(N + 1);
    auto g = [&](ll n) { return pw(2, n * (n - 1) / 2); };
    for (int n = 1; n <= N; n++) {
        ll s = g(n);
        for (int k = 1; k < n; k++) s = (s - C(n - 1, k - 1) * c[k] % MOD * g(n - k)) % MOD;
        c[n] = (s % MOD + MOD) % MOD;
    }
    c[0] = 0; return c;
}
// DAGs rotulados: a(n)=sum_{k>=1} (-1)^{k+1} C(n,k) 2^{k(n-k)} a(n-k)
vector<ll> labeled_dags(int N) {
    vector<ll> a(N + 1); a[0] = 1;
    for (int n = 1; n <= N; n++) {
        ll s = 0;
        for (int k = 1; k <= n; k++) {
            ll t = C(n, k) * pw(2, (ll)k * (n - k)) % MOD * a[n - k] % MOD;
            s += (k & 1) ? t : MOD - t;
        }
        a[n] = s % MOD;
    }
    return a;
}
