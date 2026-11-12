// Kruskal: arvore geradora minima
//
// O que faz: calcula a MST de um grafo nao direcionado e diz se ele e conexo.
// Quando usar: Catalogo > Grafos (MST/Kruskal). MST, gargalo minimax, componentes
//   por peso, segunda MST.
// Complexidade: O(m log m) tempo (ordenacao), O(n + m) memoria.
// Uso: kruskal(n, edges) -> {custo, true} se conexo; {custo, false} caso contrario. 0-based.
// Cuidados: arestas como {peso, u, v}; use ll no custo.
struct KEdge {
    ll w; int u, v;
    bool operator<(const KEdge& o) const { return w < o.w; }
};

pair<ll, bool> kruskal(int n, vector<KEdge> edges) {
    sort(edges.begin(), edges.end());
    vector<int> par(n);
    iota(par.begin(), par.end(), 0);
    function<int(int)> find = [&](int u) {
        return par[u] == u ? u : par[u] = find(par[u]);
    };
    ll cost = 0;
    int cnt = 0;
    for (const auto& e : edges) {
        int a = find(e.u), b = find(e.v);
        if (a != b) {
            par[a] = b;
            cost += e.w;
            cnt++;
        }
    }
    return {cost, cnt == n - 1};
}
