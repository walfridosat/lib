// Grafo com arestas para intervalos (segtree de arestas) + Dijkstra
//
// O que faz: permite arestas u -> [l,r] e [l,r] -> v com custo w usando duas arvores
//   (out: pai->filho custo 0; in: filho->pai custo 0), em O(log n) arestas por consulta.
// Quando usar: Catalogo > Grafos ("Arestas de um vertice para um intervalo -> segtree de
//   arestas", "Grafo de intervalos/arestas implicitas por faixas").
// Complexidade: O((n + q log n) log) para Dijkstra
// Uso: RangeGraph g(n); g.to_range(u,l,r,w) (u -> cada v em [l,r], custo w);
//   g.from_range(l,r,v,w) (cada u em [l,r] -> v, custo w); g.edge(u,v,w).
//   d = g.dijkstra(s); d[v] para v em 0..n-1 (folhas). 0-based, intervalo inclusivo.
// Cuidados: no total 4n..8n vertices. Se so precisa de "proximo nao visitado" em BFS,
//   prefira DSU/set (ver code/graph/bfs_complemento.cpp).
struct RangeGraph {
    int n, sz;                        // sz = potencia de 2 >= n
    vector<vector<pair<int,ll>>> g;
    // ids: folhas 0..n-1 (compartilhadas); out-tree no i (1..2sz-1) -> n + i ;
    // in-tree no i -> n + 2sz + i. Folha da out-tree/in-tree ligada a folha real.
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
