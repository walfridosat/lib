// Range Graph - arestas vertice-intervalo
struct RangeGraph {
    int n, sz;                        // sz = potencia de 2 >= n
    vector<vector<pair<int,ll>>> g;
    // ids: folhas 0..n-1; out-tree i -> n + i
    // in-tree i -> n + 2sz + i
    int OUT(int i) { return n + i; }
    int IN(int i) { return n + 2 * sz + i; }
    RangeGraph(int n_) : n(n_) {
        sz = 1; while (sz < n) sz <<= 1;
        g.assign(n + 4 * sz, {});
        for (int i = 1; i < sz; i++) {
            g[OUT(i)].push_back({OUT(2 * i), 0});
            g[OUT(i)].push_back({OUT(2 * i + 1), 0});
            g[IN(2 * i)].push_back({IN(i), 0});
            g[IN(2 * i + 1)].push_back({IN(i), 0});
        }
        for (int i = 0; i < n; i++) {
            g[OUT(sz + i)].push_back({i, 0});
            g[i].push_back({IN(sz + i), 0});
        }
    }
    void edge(int u, int v, ll w) { g[u].push_back({v, w}); }
    template<class F> void go(int l, int r, F f) {   // decompoe [l,r] em nos
        for (l += sz, r += sz + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) f(l++);
            if (r & 1) f(--r);
        }
    }
    void to_range(int u, int l, int r, ll w) { go(l, r, [&](int x) { g[u].push_back({OUT(x), w}); }); }
    void from_range(int l, int r, int v, ll w) { go(l, r, [&](int x) { g[IN(x)].push_back({v, w}); }); }
    vector<ll> dijkstra(int s) {
        vector<ll> d(g.size(), LLONG_MAX / 4);
        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
        d[s] = 0; pq.push({0, s});
        while (!pq.empty()) {
            auto [du, u] = pq.top(); pq.pop();
            if (du > d[u]) continue;
            for (auto [v, w] : g[u]) if (du + w < d[v]) d[v] = du + w, pq.push({d[v], v});
        }
        d.resize(n);
        return d;
    }
};
/*LATEX_DESC_BEGIN***************************
-> **Range Graph - arestas vertice-intervalo**
Arestas u -> [l,r] e [l,r] -> v com custo w, usando duas segtrees de arestas
(out: pai->filho custo 0; in: filho->pai custo 0). Cada consulta vira
O(log n) arestas. 0-based, intervalo inclusivo.

Complexidade: O((n + q log n) log) para o Dijkstra
Uso:
  RangeGraph g(n);
  g.to_range(u, l, r, w);     // u -> cada v em [l, r]
  g.from_range(l, r, v, w);   // cada u em [l, r] -> v
  g.edge(u, v, w);            // aresta comum
  auto d = g.dijkstra(s);     // d[v] para v em 0..n-1 (folhas)

* Sobre o codigo:
  sz = potencia de 2 >= n. IDs: folhas reais 0..n-1; out-tree n + i; in-tree
  n + 2sz + i. Out-tree desce de pai para filho com custo 0, in-tree sobe.
  go(l, r, f) decompoe o intervalo em O(log n) nos; to_range liga u a OUT(x)
  e from_range liga IN(x) a v.

* Problemas e reducoes:
  + Arestas de um vertice para um intervalo: to_range.
  + Arestas de um intervalo para um vertice: from_range.
  + Grafo implicito por faixas / intervalos.
  + Dijkstra sobre o grafo expandido; resposta nas folhas 0..n-1.

Cuidados: o grafo tem cerca de 4n..8n vertices. Para "proximo nao visitado"
  em BFS, prefira DSU/set (bfs_complemento). Pesos >= 0 para Dijkstra.
Catalogo: Grafos (segtree de arestas, arestas para intervalos).
Digitacao: 43 linhas | dificil. Atalho: as duas arvores compartilham os lacos
  de construcao; una com um offset.
*****************************LATEX_DESC_END*/
