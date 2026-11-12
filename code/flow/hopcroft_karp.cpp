// Hopcroft-Karp - matching bipartido maximo
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
/*LATEX_DESC_BEGIN***************************
-> **Hopcroft-Karp - matching bipartido maximo**
Matching maximo em bipartido L x R por fases (BFS de niveis + DFS).
0-indexed.

Complexidade: O(E sqrt V).
Uso:
  HK h(nl, nr); h.add(l, r); int m = h.solve();
  h.ml[l] = r (ou -1); h.mr[r] = l (ou -1).

* Sobre o codigo:
  bfs marca as camadas a partir dos L livres e indica se ha caminho
  aumentante. dfs so anda para a camada seguinte e usa it[] para nao repetir
  arestas na mesma fase. Cada fase aumenta o matching em varios caminhos
  disjuntos.

* Problemas e reducoes:
  + Matching bipartido maximo: vertices = L e R, arestas = pares compativeis
    cap 1; resposta = solve(), pares em ml[]/mr[].
  + Matching que satura L (Hall): resposta = nl sse todos os L casam.
  + Cobertura minima de vertices: |cover| = matching (Konig); L nao
    alcancados + R alcancados na BFS alternada.
  + Conjunto independente maximo: nl + nr - matching.
  + Atribuicao um-para-um (pessoas x tarefas): bipartido pessoas-tarefas,
    aresta = tarefa aceitavel; matching = atribuicao maxima.
  + Atribuicao com capacidades: clone cada pessoa/tarefa em c slots cap 1 e
    ligue os pares permitidos; matching nos slots.
  + Torres que nao se atacam: L = linhas, R = colunas, aresta por casa livre;
    matching = maximo de torres.
  + Dominos em tabuleiro bipartido: L/R = cores da casa, aresta entre casas
    vizinhas livres; matching = maximo de dominos.
  + Cobertura de DAG por caminhos disjuntos: L = out(u), R = in(v), aresta
    u -> v; resposta = n - matching.
  + Maximo de pares sem conflito em bipartido (escalonamento): idem item 1.

Cuidados: DFS recursivo tem profundidade ate o comprimento do caminho
  aumentante. Arestas duplicadas ok. 0-indexed.
Catalogo: Grafos (fluxo em unidade, Kuhn com heuristica), Otimizacao
  (Dinic em redes especiais).
Digitacao: 33 linhas | media. Atalho: quase identico a konig.cpp; poderia ser
  uma struct so com flag para construir a cobertura.
*****************************LATEX_DESC_END*/
