// LCA com binary lifting (+ k-esimo ancestral, distancia, k-esimo no caminho)
//
// O que faz: pre-processa pai 2^k de cada vertice; responde LCA, distancia,
//   k-esimo ancestral e k-esimo vertice do caminho u->v.
// Quando usar: queries de caminho / distancia em arvore; "LCA", "k-esimo ancestral"
//   (Catalogo > Arvores). Para O(1) por query ver lca_sparse.cpp.
// Complexidade: build O(n log n), query O(log n). Memoria O(n log n).
// Uso: LCA t(g, raiz); g = lista de adjacencia 0-based (vector<vector<int>>).
//   t.lca(u,v); t.dist(u,v); t.kth(u,k) (-1 se k > d[u]); t.on_path(u,v,k) (k=0 -> u);
//   t.top(u, f): ancestral mais alto w tal que f(w) vale, supondo f monotona
//   (verdadeira em u e, subindo, verdadeira ate certo ponto e depois falsa).
// Cuidados: up[0][raiz] = raiz (saltar alem da raiz fica na raiz). Build iterativo
//   (sem recursao). Para arestas ponderadas guarde d em ll separado.
struct LCA {
    int n, LG;
    vector<vector<int>> up;
    vector<int> d;
    LCA(const vector<vector<int>>& g, int r = 0) : n(g.size()) {
        LG = 1; while ((1 << LG) < n) LG++;
        up.assign(LG, vector<int>(n, r));
        d.assign(n, 0);
        vector<int> st = {r};
        while (!st.empty()) {
            int v = st.back(); st.pop_back();
            for (int w : g[v]) if (w != up[0][v]) {
                up[0][w] = v; d[w] = d[v] + 1;
                // pai de v ja tem a tabela pronta (foi desempilhado antes)
                for (int k = 1; k < LG; k++) up[k][w] = up[k-1][up[k-1][w]];
                st.push_back(w);
            }
        }
    }
    int kth(int u, ll k) const {          // k-esimo ancestral de u (k=0 -> u)
        if (k > d[u]) return -1;
        for (int b = 0; b < LG; b++) if (k >> b & 1) u = up[b][u];
        return u;
    }
    int lca(int u, int v) const {
        if (d[u] < d[v]) swap(u, v);
        u = kth(u, d[u] - d[v]);
        if (u == v) return u;
        for (int b = LG - 1; b >= 0; b--)
            if (up[b][u] != up[b][v]) u = up[b][u], v = up[b][v];
        return up[0][u];
    }
    int dist(int u, int v) const { return d[u] + d[v] - 2 * d[lca(u, v)]; }
    int on_path(int u, int v, int k) const { // k-esimo vertice (0-based) do caminho u->v, -1 se nao existe
        int l = lca(u, v), a = d[u] - d[l], b = d[v] - d[l];
        if (k > a + b) return -1;
        return k <= a ? kth(u, k) : kth(v, a + b - k);
    }
    template<class F> int top(int u, F f) const { // sobe enquanto f(ancestral) for verdadeiro
        for (int b = LG - 1; b >= 0; b--)
            if (f(up[b][u])) u = up[b][u];
        return u;
    }
};
