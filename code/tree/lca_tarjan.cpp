// LCA offline de Tarjan (DFS + DSU)
//
// O que faz: responde um lote de queries (u,v) de LCA sem tabela de saltos.
// Quando usar: memoria apertada, queries conhecidas de antemao
//   (Catalogo > Arvores, "LCA offline (Tarjan)").
// Complexidade: O((n + q) alpha(n)).
// Uso: vector<int> r = lca_offline(g, queries, raiz); r[i] = LCA da query i.
//   queries = vector<pair<int,int>>, 0-based.
// Cuidados: DFS iterativa. Ao sair de v, v e unido ao pai; a query (u,v) e
//   respondida quando o segundo extremo e visitado: LCA = find(primeiro).
vector<int> lca_offline(const vector<vector<int>>& g, const vector<pair<int,int>>& qs, int r = 0) {
    int n = g.size();
    vector<vector<pair<int,int>>> q(n);
    for (int i = 0; i < (int)qs.size(); i++) {
        q[qs[i].first].push_back({qs[i].second, i});
        q[qs[i].second].push_back({qs[i].first, i});
    }
    vector<int> dsu(n), anc(n), par(n, -1), res(qs.size(), -1), it(n, 0);
    vector<char> vis(n, 0);
    iota(dsu.begin(), dsu.end(), 0); iota(anc.begin(), anc.end(), 0);
    auto find = [&](int x) { // compressao iterativa
        int y = x; while (dsu[y] != y) y = dsu[y];
        while (dsu[x] != y) { int nx = dsu[x]; dsu[x] = y; x = nx; }
        return y;
    };
    vector<int> st = {r};
    vis[r] = 1;
    while (!st.empty()) {
        int v = st.back();
        if (it[v] < (int)g[v].size()) {
            int w = g[v][it[v]++];
            if (w == par[v]) continue;
            par[w] = v; vis[w] = 1; st.push_back(w);
        } else {
            // v terminou: responde queries cujo outro extremo ja terminou (ou e o proprio v)
            for (auto [w, i] : q[v]) if (res[i] < 0 && (vis[w] == 2 || w == v)) res[i] = w == v ? v : anc[find(w)];
            vis[v] = 2; st.pop_back();
            if (par[v] >= 0) { dsu[find(v)] = find(par[v]); anc[find(par[v])] = par[v]; }
        }
    }
    return res;
}
