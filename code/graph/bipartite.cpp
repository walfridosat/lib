// Bipartido - 2-coloracao e ciclo impar
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
                    // mesma cor: sobe os dois ate o LCA
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
/*LATEX_DESC_BEGIN***************************
-> **Bipartido / 2-coloracao**
Colore o grafo com 2 cores por BFS; se impossivel devolve um ciclo impar.
g[u] = vizinhos, 0-based.

Complexidade: O(n + m)
Uso:
  vector<int> color, cyc;
  bool ok = bipartite(n, g, color, cyc);
  // ok:  color[v] em {0,1}
  // !ok: cyc = vertices de um ciclo impar

* Sobre o codigo:
  BFS alternando color[v] = color[u] ^ 1. Uma aresta entre vertices da mesma
  cor fecha um ciclo impar; sobe os dois pela arvore BFS ate o LCA e monta o ciclo.

* Problemas e reducoes:
  + Bipartido sse nao ha ciclo impar; cyc e o certificado.
  + Self-loop e ciclo impar de tamanho 1 (cyc = {v}).
  + Arestas online / unioes: use DSU com paridade.
  + 2-coloracao pronta em color[].

Cuidados: grafo pode ser desconexo (laco por raiz). BFS iterativo, sem recursao.
Catalogo: Grafos (bipartido, 2-coloracao, ciclo impar).
Digitacao: 30 linhas | media.
*****************************LATEX_DESC_END*/
