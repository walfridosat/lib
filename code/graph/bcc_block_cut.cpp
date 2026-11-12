// BCC (componentes biconexas por vertices) e Block-Cut Tree
//
// O que faz: separa o grafo em blocos (BCCs). Constroi a block-cut tree: vertices
//   originais 0..n-1 + um no por bloco (n..n+B-1); bloco ligado a cada vertice seu.
// Quando usar: Catalogo > Grafos ("Block-cut tree", "u e v separados se remover w",
//   "Pontes e articulacoes"). Vertice de corte = vertice original com grau >= 2 na arvore.
// Complexidade: O(n + m)
// Uso: BlockCut bc(n); bc.add(u,v); bc.build();  bc.T = adj da arvore (tamanho n+B),
//   bc.blocks[b] = vertices do bloco b, bc.B = #blocos. Um vertice isolado vira um bloco
//   com so ele. 0-based.
//   "w separa u de v?" => w e vertice de corte no caminho u..v da arvore (use LCA/DFS).
// Cuidados: DFS recursiva. Multiarestas e self-loops sao inofensivos aqui (sem
//   ids de aresta o pai e pulado por vertice, o que nao muda a biconexao por vertices).
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
