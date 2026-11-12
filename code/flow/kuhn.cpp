// Kuhn - matching bipartido maximo com heuristicas
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
/*LATEX_DESC_BEGIN***************************
-> **Kuhn - matching bipartido maximo**
Matching maximo em bipartido L x R por caminhos aumentantes, com inicial
guloso e embaralhamento das listas. 0-indexed.

Complexidade: O(VE) pior caso; com as heuristicas, pratico ~ O(E sqrt V).
Uso:
  Kuhn k(nl, nr); k.add(l, r); int m = k.solve();
  k.ml[l] = r casado (ou -1); k.mr[r] = l casado (ou -1).

* Sobre o codigo:
  dfs(u) tenta achar um caminho aumentante a partir de u: aresta livre em R
  fecha; senao tenta remanejar o par de v recursivamente. vis[] evita voltar
  ao mesmo L na mesma busca; solve() so zera vis quando houve progresso.

* Problemas e reducoes:
  + Matching bipartido maximo: L e R, arestas = pares permitidos cap 1;
    resposta = solve(), pares em ml[]/mr[].
  + Matching que satura L: perfeito a esquerda sse solve() == nl.
  + Cobertura minima/independente: use o matching e a construcao de
    konig.cpp (Konig).
  + Atribuicao um-para-um: pessoas x tarefas, aresta = tarefa aceitavel;
    matching = atribuicao maxima.
  + Atribuicao com capacidades: clone pessoas/tarefas em slots cap 1.
  + Torres que nao se atacam: L = linhas, R = colunas, aresta por casa livre.
  + Dominos em tabuleiro: cores da casa como L/R, aresta entre vizinhas.
  + Cobertura de DAG por caminhos disjuntos: L = out(u), R = in(v); resposta
    = n - matching; caminhos por ml[].
  + Emparelhar cada aluno a uma escola com vaga: clone escolas em vagas.
  + Hall: impossivel saturar L se algum S tem |N(S)| < |S|.

Cuidados: recursao ate profundidade nl (cuidado com pilha em nl ~ 1e5).
  Para cobertura minima / independente maximo veja konig.cpp. 0-indexed.
Catalogo: Grafos (Kuhn com heuristica).
Digitacao: 21 linhas | facil. Atalho: ok.
*****************************LATEX_DESC_END*/
