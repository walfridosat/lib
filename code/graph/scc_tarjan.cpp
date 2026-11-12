// Tarjan - SCC e condensacao
struct SCC {
    int n, C = 0;
    vector<vector<int>> g, dag;
    vector<int> comp;
    SCC(int n) : n(n), g(n) {}
    void add(int u, int v) { g[u].push_back(v); }
    void build() {
        vector<int> idx(n, -1), low(n, 0), st, it(n, 0), cs;
        vector<char> on(n, 0);
        comp.assign(n, -1);
        int timer = 0;
        for (int r = 0; r < n; r++) {
            if (idx[r] != -1) continue;
            cs.push_back(r); idx[r] = low[r] = timer++; st.push_back(r); on[r] = 1;
            while (!cs.empty()) {
                int u = cs.back();
                if (it[u] < (int)g[u].size()) {
                    int v = g[u][it[u]++];
                    if (idx[v] == -1) {
                        idx[v] = low[v] = timer++; st.push_back(v); on[v] = 1; cs.push_back(v);
                    } else if (on[v]) low[u] = min(low[u], idx[v]);
                } else {
                    if (low[u] == idx[u]) {
                        while (true) {
                            int w = st.back(); st.pop_back(); on[w] = 0; comp[w] = C;
                            if (w == u) break;
                        }
                        C++;
                    }
                    cs.pop_back();
                    if (!cs.empty()) low[cs.back()] = min(low[cs.back()], low[u]);
                }
            }
        }
        dag.assign(C, {});
        for (int u = 0; u < n; u++)
            for (int v : g[u]) if (comp[u] != comp[v]) dag[comp[u]].push_back(comp[v]);
        for (auto& a : dag) { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
    }
    // min arestas p/ fortemente conexo = max(src,snk)
    int min_edges_strong() {
        if (C == 1) return 0;
        vector<int> in(C, 0);
        int src = 0, snk = 0;
        for (int c = 0; c < C; c++) for (int d : dag[c]) in[d]++;
        for (int c = 0; c < C; c++) src += in[c] == 0, snk += dag[c].empty();
        return max(src, snk);
    }
};
/*LATEX_DESC_BEGIN***************************
-> **Tarjan - SCC e condensacao**
Componentes fortemente conexas. comp[v] em 0..C-1, em ORDEM TOPOLOGICA
REVERSA (comp 0 = sumidouro: se u->v entre comps, comp[u] > comp[v]). 0-based.

Complexidade: O(n + m)
Uso:
  SCC s(n); s.add(u, v); s.build();
  s.comp[v]   -> SCC de v;  s.C = numero de SCCs
  s.dag       -> adj entre comps (sem duplicatas)
  s.min_edges_strong() -> arestas a adicionar para ficar fortemente conexo

* Sobre o codigo:
  Tarjan iterativo com pilha cs e indices idx/low; quando low[u] == idx[u],
  desempilha ate u formando um SCC. A pilha st guarda os vertices ainda nao
  atribuidos; on[] marca os que estao nela. dag e montada e deduplicada.

* Problemas e reducoes:
  + Condensar grafo dirigido com ciclos em DAG.
  + DP no DAG: processe comps de 0 a C-1 (sumidouros primeiro).
  + 2-SAT: x verdadeiro sse comp[2x] < comp[2x+1] (Tarjan, sink primeiro).
  + Minimo de arestas para fortemente conexo: max(#fontes, #sumidouros), 0 se C==1.
  + Ordem topologica das comps: a numeracao reversa ja a da.

Cuidados: iterativo, sem estouro de pilha. A numeracao e o oposto da de
  Kosaraju. dag pode ter duplicatas antes da deduplicacao final.
Catalogo: Grafos (SCC, condensacao, 2-SAT, minimo de arestas).
Digitacao: 49 linhas | dificil. Atalho: o laco de Tarjan tambem aparece em
  two_sat; extraia um helper de SCC.
*****************************LATEX_DESC_END*/
