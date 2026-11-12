// Konig - cobertura minima e independente maximo em bipartido
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
/*LATEX_DESC_BEGIN***************************
-> **Konig - cobertura minima e independente maximo**
Matching maximo embutido (Hopcroft-Karp) + construcao da cobertura minima de
vertices e do conjunto independente maximo em bipartido. Tambem da a
anticadeia maxima (Dilworth) no comparability bipartido de um poset.
0-indexed.

Complexidade: O(E sqrt V).
Uso:
  Konig k(nl, nr); k.add(l, r); int m = k.solve();
  k.coverL[l] / k.coverR[r] -> vertice na cobertura minima (|cover| = m);
  independente maximo = vertices com coverL/coverR falsos (tamanho nl+nr-m).
  Antichain: poset com fecho transitivo (nl = nr = n, aresta i -> j se i < j);
  elementos i com !coverL[i] && !coverR[i].

* Sobre o codigo:
  solve() roda Hopcroft-Karp. Depois faz BFS alternada a partir dos L livres
  (L -> R por aresta nao casada, R -> L pela aresta casada). A cobertura e
  (L nao visitados) U (R visitados); o complemento e independente.

* Problemas e reducoes:
  + Cobertura minima de vertices em bipartido: minimo de vertices que tocam
    todas as arestas; tamanho = matching; coverL/coverR dao os vertices.
  + Conjunto independente maximo em bipartido: nl + nr - matching; o
    complemento da cobertura.
  + Anticadeia maxima em poset (Dilworth): fecho transitivo em bipartido
    n x n, aresta i -> j se i < j; anticadeia = independente, tamanho n - m.
  + Decomposicao minima em cadeias: n - matching; as cadeias saem dos pares
    do matching no comparability.
  + Cobertura de arestas por vertices (vertex cover) em bipartido.
  + Remover o minimo de vertices para eliminar todas as arestas: cobertura.
  + Maximo de vertices sem aresta entre si: independente.
  + Torres que nao se atacam: L = linhas, R = colunas, aresta por casa livre;
    matching = torres; cobertura = linhas/colunas que atacam todas as casas.
  + Hall: matching satura L sse nao ha S com |N(S)| < |S|; matching = nl.
  + Verificar um certificado de cobertura: toda aresta tem extremo no cover.
  + Maximo de elementos de um poset dois a dois incomparaveis: anticadeia.

Cuidados: a construcao da cobertura so vale para bipartido. Para poset, monte
  o fecho transitivo antes (aresta i -> j se i < j). 0-indexed.
Catalogo: Grafos (Konig, anticadeia maxima a partir de Konig, Hall).
Digitacao: 46 linhas | media. Atalho: quase identico a hopcroft_karp.cpp;
  poderia compartilhar a struct e acrescentar so a BFS da cobertura.
*****************************LATEX_DESC_END*/
