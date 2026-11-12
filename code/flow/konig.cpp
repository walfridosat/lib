// Konig - cobertura minima de vertices e conjunto independente maximo em bipartido
//
// O que faz: a partir do matching maximo (Hopcroft-Karp embutido) constroi cobertura
//   minima de vertices e independente maximo. Tambem da a antichain maxima (Dilworth)
//   quando o bipartido e o fecho transitivo de um poset.
// Quando usar: "cobertura minima", "maior conjunto sem conflito" em bipartido
//   (Catalogo > Grafos "Konig", "Antichain maxima a partir de Konig", "Hall").
// Complexidade: O(E sqrt V).
// Uso: Konig k(nl, nr); k.add(l, r); int m=k.solve();
//   k.coverL[l] / k.coverR[r] = vertice na cobertura minima (|cobertura| = m);
//   independente maximo = os que NAO estao na cobertura (tamanho nl+nr-m).
//   Antichain (poset com fecho transitivo, nl=nr=n, aresta i->j se i<j no poset):
//   elementos i com !coverL[i] && !coverR[i].
// Cuidados: construcao: BFS alternada a partir dos L nao casados; cobertura = (L nao
//   visitados) U (R visitados). 0-indexed.
struct Konig {
    int nl, nr; vector<vector<int>> g; vector<int> ml, mr, d, it;
    vector<char> coverL, coverR;
    Konig(int nl, int nr) : nl(nl), nr(nr), g(nl), ml(nl, -1), mr(nr, -1), d(nl), it(nl) {}
    void add(int l, int r) { g[l].push_back(r); }
    bool bfs() {
        queue<int> q; bool ok = false;
        for (int u = 0; u < nl; u++) { d[u] = ml[u] < 0 ? 0 : -1; if (ml[u] < 0) q.push(u); }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) {
                if (mr[v] < 0) ok = true;
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
        d[u] = -1; return false;
    }
    int solve() {
        int res = 0;
        while (bfs()) {
            fill(it.begin(), it.end(), 0);
            for (int u = 0; u < nl; u++) if (ml[u] < 0 && dfs(u)) res++;
        }
        // BFS alternada: de L livre, arestas nao casadas L->R, casadas R->L
        vector<char> vl(nl, 0), vr(nr, 0); queue<int> q;
        for (int u = 0; u < nl; u++) if (ml[u] < 0) vl[u] = 1, q.push(u);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) if (!vr[v] && ml[u] != v) {
                vr[v] = 1;
                if (mr[v] >= 0 && !vl[mr[v]]) vl[mr[v]] = 1, q.push(mr[v]);
            }
        }
        coverL.assign(nl, 0); coverR.assign(nr, 0);
        for (int u = 0; u < nl; u++) coverL[u] = !vl[u];
        for (int v = 0; v < nr; v++) coverR[v] = vr[v];
        return res;
    }
};
