// Arvores rotuladas - Cayley, Prufer e componentes
// Requer: code/combinatorics/binom_mod.cpp (cole antes).
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
// grafos conexos rotulados
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
// DAGs rotulados
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
/*LATEX_DESC_BEGIN***************************
-> **Arvores rotuladas e estruturas classicas**
Cayley, arvores com graus dados, uniao de componentes, florestas, K_{a,b}, grafos conexos, DAGs e emparelhamentos.

Complexidade: O(1) a O(n) por formula; conexos/DAG O(n^2).
Uso:
  ll c = cayley(n);
  ll td = trees_with_degrees(d);
  ll tv = trees_vertex_degree(n, d);
  ll jc = join_components(sizes);
  ll fr = forest_k_roots(n, k);
  ll bt = bipartite_trees(a, b);
  ll rt = rooted_trees(n), rf = rooted_forests(n);
  vector<ll> cg = connected_graphs(N), dg = labeled_dags(N);
  ll pm = perfect_matchings(n);

* Sobre o codigo:
  Cayley n^(n-2) vem de Prufer; com graus d_i, o numero e
  (n-2)! / prod (d_i-1)!. join_components usa n^(k-2) prod s_i.
  connected_graphs subtrai as componentes que contem um vertice fixo;
  labeled_dags usa inclusao-exclusao sobre fontes. perfect_matchings e (2n-1)!!.

* Problemas e reducoes:
  + Arvores geradoras completas em K_n -> cayley(n).
  + Arvores com graus prescritos -> trees_with_degrees.
  + Conectar k componentes em arvore -> join_components.
  + Florestas com k raizes -> forest_k_roots.
  + Arvores geradoras de K_{a,b} -> bipartite_trees.
  + Grafos rotulados conexos -> connected_graphs.
  + DAGs rotulados -> labeled_dags.
  + Emparelhamentos perfeitos de 2n vertices -> perfect_matchings.

Cuidados: n = 1 e n = 2 tem casos de borda tratados; expoentes negativos
  viram 1; precisa de init_comb de binom_mod.cpp.
Catalogo: Combinatoria.
Digitacao: 54 linhas | media.
*****************************LATEX_DESC_END*/
