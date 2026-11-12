// Teste de bipartido / 2-coloracao com ciclo impar
//
// O que faz: colore o grafo com 2 cores por BFS; se impossivel devolve um ciclo impar.
// Quando usar: Catalogo > Grafos ("Bipartido / 2-coloracao -> ciclo impar = nao bipartido",
//   "Ciclo de comprimento impar"). Para arestas online use DSU com paridade (code/ds).
// Complexidade: O(n + m)
// Uso: vector<int> color, cyc; bool ok = bipartite(n, g, color, cyc);
//   ok: color[v] em {0,1}. !ok: cyc = vertices de um ciclo impar. g[u] = vizinhos, 0-based.
// Cuidados: self-loop e ciclo impar de tamanho 1 (cyc = {v}). Grafo pode ser desconexo.
bool bipartite(int n, const vector<vector<int>>& g, vector<int>& color, vector<int>& cyc) {
    color.assign(n, -1);
    vector<int> par(n, -1), dep(n, 0);
    for (int r = 0; r < n; r++) {
        if (color[r] != -1) continue;
        color[r] = 0;
        queue<int> q; q.push(r);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1; par[v] = u; dep[v] = dep[u] + 1; q.push(v);
                } else if (color[v] == color[u]) {
                    // aresta entre mesma cor: sobe os dois ate o LCA na arvore BFS
                    vector<int> a, b;
                    int x = u, y = v;
                    while (dep[x] > dep[y]) a.push_back(x), x = par[x];
                    while (dep[y] > dep[x]) b.push_back(y), y = par[y];
                    while (x != y) a.push_back(x), b.push_back(y), x = par[x], y = par[y];
                    a.push_back(x);
                    reverse(b.begin(), b.end());
                    cyc = a;
                    cyc.insert(cyc.end(), b.begin(), b.end());
                    return false;
                }
            }
        }
    }
    return true;
}
