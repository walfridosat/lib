// Hopcroft-Karp - emparelhamento bipartido maximo
//
// O que faz: matching maximo em bipartido L x R em fases (BFS de niveis + DFS).
// Quando usar: bipartido grande (n, m ~ 1e5..1e6) - Catalogo > Grafos ("Fluxo em
//   unidade", "Kuhn com heuristica"), Otimizacao > "Dinic em redes especiais".
// Complexidade: O(E sqrt V).
// Uso: HK h(nl, nr); h.add(l, r); int m=h.solve(); h.ml[l]=r (ou -1), h.mr[r]=l (ou -1).
//   0-indexed. Arestas duplicadas ok.
// Cuidados: DFS recursivo tem profundidade ate o comprimento do caminho aumentante.
struct HK {
    int nl, nr; vector<vector<int>> g; vector<int> ml, mr, d, it;
    HK(int nl, int nr) : nl(nl), nr(nr), g(nl), ml(nl, -1), mr(nr, -1), d(nl), it(nl) {}
    void add(int l, int r) { g[l].push_back(r); }
    bool bfs() {
        queue<int> q; bool ok = false;
        for (int u = 0; u < nl; u++) { d[u] = ml[u] < 0 ? 0 : -1; if (ml[u] < 0) q.push(u); }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) {
                if (mr[v] < 0) ok = true; // achou livre em R: ha caminho aumentante
                else if (d[mr[v]] < 0) d[mr[v]] = d[u] + 1, q.push(mr[v]);
            }
        }
        return ok;
    }
    bool dfs(int u) {
        for (int &i = it[u]; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (mr[v] < 0 || (d[mr[v]] == d[u] + 1 && dfs(mr[v]))) { ml[u] = v; mr[v] = u; return true; }
        }
        d[u] = -1; // beco sem saida nesta fase
        return false;
    }
    int solve() {
        int res = 0;
        while (bfs()) {
            fill(it.begin(), it.end(), 0);
            for (int u = 0; u < nl; u++) if (ml[u] < 0 && dfs(u)) res++;
        }
        return res;
    }
};
