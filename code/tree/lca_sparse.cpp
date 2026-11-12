// LCA O(1) com sparse table sobre a ordem de DFS (n posicoes)
//
// O que faz: LCA em O(1) por query. Para u != v com tin[u] < tin[v], o LCA e o
//   pai do vertice de menor tin entre as posicoes (tin[u], tin[v]]; guardamos
//   tin do pai em cada posicao e tiramos o minimo.
// Quando usar: muitas queries de LCA/distancia (Catalogo > Arvores, "LCA com sparse
//   table sobre ordem de DFS").
// Complexidade: build O(n log n), query O(1).
// Uso: LCAS t(g, raiz); t.lca(u,v); t.dist(u,v); t.tin[v], t.tout[v] (subarvore =
//   [tin, tout) ), t.ord[i] = vertice na posicao i. 0-based.
// Cuidados: DFS iterativa (sem estouro de pilha). u==v tratado a parte.
struct LCAS {
    int n;
    vector<int> tin, tout, ord, d, par;
    vector<vector<int>> sp;
    LCAS(const vector<vector<int>>& g, int r = 0) : n(g.size()), tin(n), tout(n), ord(n), d(n), par(n, -1) {
        int t = 0;
        vector<int> st = {r}, it(n, 0);
        tin[r] = t; ord[t++] = r;
        while (!st.empty()) {
            int v = st.back();
            if (it[v] < (int)g[v].size()) {
                int w = g[v][it[v]++];
                if (w == par[v]) continue;
                par[w] = v; d[w] = d[v] + 1;
                tin[w] = t; ord[t++] = w;
                st.push_back(w);
            } else { tout[v] = t; st.pop_back(); }
        }
        int LG = 1; while ((1 << LG) < n) LG++;
        sp.assign(LG, vector<int>(n));
        for (int i = 1; i < n; i++) sp[0][i] = tin[par[ord[i]]]; // tin do pai (pos 0 = raiz, nunca usada)
        for (int k = 1; k < LG; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                sp[k][i] = min(sp[k-1][i], sp[k-1][i + (1 << (k-1))]);
    }
    int lca(int u, int v) const {
        if (u == v) return u;
        int l = tin[u], r = tin[v];
        if (l > r) swap(l, r);
        l++;                               // intervalo (tin[u], tin[v]]
        int k = 31 - __builtin_clz(r - l + 1);
        return ord[min(sp[k][l], sp[k][r - (1 << k) + 1])];
    }
    int dist(int u, int v) const { return d[u] + d[v] - 2 * d[lca(u, v)]; }
    bool anc(int u, int v) const { return tin[u] <= tin[v] && tin[v] < tout[u]; } // u e ancestral de v
};
