// Kosaraju - SCC em ordem topologica (iterativo)
int kosaraju(int n, const vector<vector<int>>& g, vector<int>& comp) {
    vector<vector<int>> rg(n);
    for (int u = 0; u < n; u++) for (int v : g[u]) rg[v].push_back(u);
    vector<int> order, it(n, 0), st;
    vector<char> vis(n, 0);
    for (int r = 0; r < n; r++) {          // 1a passada: ordem de saida
        if (vis[r]) continue;
        vis[r] = 1; st.push_back(r);
        while (!st.empty()) {
            int u = st.back();
            if (it[u] < (int)g[u].size()) {
                int v = g[u][it[u]++];
                if (!vis[v]) vis[v] = 1, st.push_back(v);
            } else order.push_back(u), st.pop_back();
        }
    }
    comp.assign(n, -1);
    int C = 0;
    for (int i = n - 1; i >= 0; i--) {     // 2a passada: reverso, por saida decrescente
        int r = order[i];
        if (comp[r] != -1) continue;
        comp[r] = C; st.push_back(r);
        while (!st.empty()) {
            int u = st.back(); st.pop_back();
            for (int v : rg[u]) if (comp[v] == -1) comp[v] = C, st.push_back(v);
        }
        C++;
    }
    return C;
}
/*LATEX_DESC_BEGIN***************************
-> **Kosaraju - SCC e condensacao**
Componentes fortemente conexas; comp[v] numeradas em ORDEM TOPOLOGICA
(comp 0 = fonte: se u->v entre comps distintas, comp[u] < comp[v]). 0-based.

Complexidade: O(n + m)
Uso:
  vector<int> comp;
  int C = kosaraju(n, g, comp);   // g[u] = vizinhos, dirigido

* Sobre o codigo:
  1a passada: DFS iterativa guarda a ordem de saida. 2a passada: percorre o
  grafo reverso na ordem de saida decrescente, rotulando cada SCC. O grafo
  reverso e construido internamente. Tudo iterativo.

* Problemas e reducoes:
  + Condensar grafo dirigido com ciclos em DAG de SCCs.
  + Ordem topologica das componentes pronta em comp[].
  + DP em DAG: percorra comps em ordem crescente (fontes primeiro) ou inverta
    a ordem conforme a direcao das arestas.
  + 2-SAT: x verdadeiro sse comp[x] > comp[!x] (comp 0 = fonte).
  + Alcancabilidade: u alcanca v e comp[u] <= comp[v] e ha caminho no DAG.

Cuidados: constroi o grafo reverso internamente (memoria O(n + m)). Iterativo,
  sem risco de estouro de pilha.
Catalogo: Grafos (SCC, condensacao, ordem topologica).
Digitacao: 30 linhas | media.
*****************************LATEX_DESC_END*/
