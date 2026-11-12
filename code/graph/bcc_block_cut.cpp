// Block-Cut Tree - biconexas por vertices
struct BlockCut {
    int n, B = 0, timer = 0;
    vector<vector<int>> g, T, blocks;
    vector<int> tin, low, st;
    BlockCut(int n) : n(n), g(n) {}
    void add(int u, int v) { g[u].push_back(v); g[v].push_back(u); }
    void dfs(int u, int p) {
        tin[u] = low[u] = timer++;
        st.push_back(u);
        for (int v : g[u]) {
            if (v == p) continue;
            if (tin[v] != -1) low[u] = min(low[u], tin[v]);
            else {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= tin[u]) {          // u separa a subarvore de v: novo bloco
                    blocks.push_back({u});
                    while (true) {
                        int w = st.back(); st.pop_back();
                        blocks.back().push_back(w);
                        if (w == v) break;
                    }
                }
            }
        }
    }
    void build() {
        tin.assign(n, -1); low.assign(n, 0);
        for (int r = 0; r < n; r++) if (tin[r] == -1) {
            dfs(r, -1);
            if (g[r].empty()) blocks.push_back({r});    // isolado
            st.clear();
        }
        B = blocks.size();
        T.assign(n + B, {});
        for (int b = 0; b < B; b++)
            for (int v : blocks[b]) T[n + b].push_back(v), T[v].push_back(n + b);
    }
};
/*LATEX_DESC_BEGIN***************************
-> **Block-Cut Tree / BCC (biconexas por vertices)**
Separa o grafo em blocos (BCCs) e constroi a arvore: vertices 0..n-1 mais um
no por bloco (n..n+B-1), cada bloco ligado a todos os seus vertices. 0-based.

Complexidade: O(n + m)
Uso:
  BlockCut bc(n); bc.add(u, v); bc.build();
  bc.T         -> adj da block-cut tree (tamanho n + bc.B)
  bc.blocks[b] -> vertices do bloco b;  bc.B = numero de blocos
  vertice de corte = original com grau >= 2 na arvore
  "w separa u de v?" -> w esta no caminho u..v da arvore (use LCA/DFS)

* Sobre o codigo:
  DFS com tin/low e pilha de vertices: low[v] >= tin[u] abre um bloco novo.
  Vertice isolado vira um bloco com so ele. T e montada ao final unindo
  cada bloco aos seus vertices.

* Problemas e reducoes:
  + Articulacoes: vertices originais com grau >= 2 na block-cut tree.
  + Pontes: blocos com exatamente 2 vertices (sem multiarestas).
  + u e v ficam desconectados ao remover w sse w esta no caminho u..v da arvore.
  + Componentes 2-vertices-conexas: os blocos da block-cut tree.
  + Blocos por aresta (2-aresta-conexas) usam pilha de arestas; aqui e por vertices.

Cuidados: DFS recursiva (profundidade O(n)); multiarestas e self-loops sao
  inofensivos (pai pulado por vertice, sem ids de aresta).
Catalogo: Grafos (block-cut tree, articulacoes e pontes).
Digitacao: 39 linhas | media. Atalho: montar T dentro do dfs ao fechar cada bloco.
*****************************LATEX_DESC_END*/
