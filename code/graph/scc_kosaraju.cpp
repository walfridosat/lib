// SCC (Kosaraju iterativo)
//
// O que faz: componentes fortemente conexas; comp[v] numeradas em ORDEM TOPOLOGICA
//   (comp 0 = fonte: se u->v entre comps distintas, comp[u] < comp[v]).
// Quando usar: Catalogo > Grafos ("Direcionado com ciclos -> condense em SCC"). Alternativa
//   ao Tarjan quando se quer ordem topologica direta.
// Complexidade: O(n + m)
// Uso: vector<int> comp; int C = kosaraju(n, g, comp); g[u] = lista de vizinhos, 0-based.
// Cuidados: constroi o grafo reverso internamente. Iterativo.
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
