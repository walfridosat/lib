// Cobertura minima de caminhos em DAG (disjuntos em vertices, ou com repeticao)
//
// O que faz: minimo de caminhos que cobrem todos os vertices de um DAG. Reconstroi os
//   caminhos. Versao "com vertices repetidos" usa fecho transitivo antes.
// Quando usar: "minimo de caminhoes/tarefas encadeadas", Dilworth (antichain maxima =
//   min cadeias) - Catalogo > Grafos ("Cobertura minima de caminhos em DAG", "Dilworth").
// Complexidade: O(E sqrt V) (+ O(V^3/64) bitset para o fecho se repeticao).
// Uso: auto paths = dagPathCover(n, edges, false); // edges: pares (u,v) u->v, 0-indexed
//   paths.size() = minimo; cada paths[i] e a lista de vertices em ordem.
//   repeat=true: caminhos podem compartilhar vertices (passar por vertice ja coberto).
// Cuidados: o grafo DEVE ser DAG (sem ciclos). Resposta = n - matching. Caso repeat:
//   fecho transitivo O(n^3/64) com bitset <= 2000 vertices (aumente MAXB se precisar).
vector<vector<int>> dagPathCover(int n, vector<pair<int,int>> edges, bool repeat) {
    const int MAXB = 2048;
    if (repeat) { // fecho transitivo: ordem topologica + bitset
        vector<vector<int>> adj(n); vector<int> deg(n, 0), ord;
        for (auto [u, v] : edges) adj[u].push_back(v), deg[v]++;
        for (int i = 0; i < n; i++) if (!deg[i]) ord.push_back(i);
        for (int k = 0; k < (int)ord.size(); k++)
            for (int v : adj[ord[k]]) if (!--deg[v]) ord.push_back(v);
        vector<bitset<MAXB>> reach(n);
        for (int k = n - 1; k >= 0; k--) {
            int u = ord[k];
            for (int v : adj[u]) reach[u] |= reach[v], reach[u][v] = 1;
        }
        edges.clear();
        for (int u = 0; u < n; u++) for (int v = 0; v < n; v++) if (reach[u][v]) edges.push_back({u, v});
    }
    // matching bipartido (out-copy -> in-copy) por Kuhn
    vector<vector<int>> g(n); vector<int> mr(n, -1), ml(n, -1), vis(n, 0);
    for (auto [u, v] : edges) g[u].push_back(v);
    function<bool(int)> dfs = [&](int u) {
        vis[u] = 1;
        for (int v : g[u]) if (mr[v] < 0 || (!vis[mr[v]] && dfs(mr[v]))) { ml[u] = v; mr[v] = u; return true; }
        return false;
    };
    for (int u = 0; u < n; u++) { fill(vis.begin(), vis.end(), 0); dfs(u); }
    vector<vector<int>> res;
    for (int u = 0; u < n; u++) if (mr[u] < 0) { // inicio de caminho
        vector<int> p;
        for (int x = u; x >= 0; x = ml[x]) p.push_back(x);
        res.push_back(p);
    }
    return res;
}
