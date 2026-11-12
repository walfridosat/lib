// Kuhn - emparelhamento bipartido maximo (com heuristicas)
//
// O que faz: matching maximo em bipartido L x R por caminhos aumentantes.
// Quando usar: "emparelhamento, cobertura, atribuir" (Catalogo > Grafos: "Kuhn com
//   heuristica"). n ate ~1e4..5e4 passa; para n=1e5 use hopcroft_karp.cpp.
// Complexidade: O(VE) pior caso; com a heuristica (init guloso + visited resetado so
//   quando acha caminho) pratico ~ O(E sqrt V).
// Uso: Kuhn k(nl, nr); k.add(l, r); int m=k.solve(); k.ml[l] = r casado (ou -1);
//   k.mr[r] = l casado (ou -1). 0-indexed.
// Cuidados: recursao ate profundidade nl (cuidado com pilha em nl~1e5). Para cobertura
//   minima / independente maximo veja konig.cpp.
struct Kuhn {
    int nl, nr; vector<vector<int>> g; vector<int> ml, mr, vis;
    Kuhn(int nl, int nr) : nl(nl), nr(nr), g(nl), ml(nl, -1), mr(nr, -1), vis(nl, 0) {}
    void add(int l, int r) { g[l].push_back(r); }
    bool dfs(int u) {
        vis[u] = 1;
        for (int v : g[u]) if (mr[v] < 0) { ml[u] = v; mr[v] = u; return true; }
        for (int v : g[u]) if (!vis[mr[v]] && dfs(mr[v])) { ml[u] = v; mr[v] = u; return true; }
        return false;
    }
    int solve() {
        mt19937 rng(712367);
        for (auto &a : g) shuffle(a.begin(), a.end(), rng); // ordem aleatoria
        int res = 0;
        for (bool found = true; found; ) { // vis so e zerado quando houve progresso
            found = false; fill(vis.begin(), vis.end(), 0);
            for (int u = 0; u < nl; u++) if (ml[u] < 0 && dfs(u)) found = true, res++;
        }
        return res;
    }
};
