// BFS - busca em largura em grafo nao ponderado

void bfs(ll start, vector<vector<ll>> &adj) {
    ll n = adj.size();
    vector<bool> visited(n, false);
    queue<ll> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        ll v = q.front();
        q.pop();
        cout << v << " ";

        for (ll u : adj[v]) {
            if (!visited[u]) {
                visited[u] = true;
                q.push(u);
            }
        }
    }
}
/*LATEX_DESC_BEGIN***************************
-> **BFS - busca em largura**
Percorre o grafo nao ponderado a partir de start, marcando visitados e
imprimindo a ordem de descoberta. Adj 0-indexado, start em [0, n).

Complexidade: O(n + m) tempo, O(n) memoria
Uso:
  bfs(start, adj);   // adj: vector<vector<ll>>

* Sobre o codigo:
  Fila guia a expansao; visited evita reentrada. Para distancias troque o
  cout por dist[v] = dist[u] + 1 e rode em cada componente.

* Problemas e reducoes:
  + Menor numero de arestas: guarde dist[v] = dist[u] + 1.
  + Grafo de estados: codifique o estado em um inteiro e gere vizinhos.
  + Multi-fonte: empilhe todas as fontes com distancia 0.
  + Alcancabilidade / componentes conexas: pare ao fim da fila.

Cuidados: nao ponderado; com pesos use Dijkstra ou 0-1 BFS. Para grafos
  enormes prefira int no lugar de ll.
Catalogo: Grafos (BFS, grafo de estados).
Digitacao: 18 linhas | facil. Atalho: use int em n/v para digitar menos.
*****************************LATEX_DESC_END*/