// Dijkstra - pesos nao negativos

vector<ll> dijkstra(ll start, vector<vector<pair<ll, ll>>> &adj) {
    ll n = adj.size();
    vector<ll> dist(n, LLONG_MAX);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();

        if (d > dist[v]) continue;

        for (auto [u, w] : adj[v]) {
            if (dist[v] + w < dist[u]) {
                dist[u] = dist[v] + w;
                pq.push({dist[u], u});
            }
        }
    }

    return dist;
}
/*LATEX_DESC_BEGIN***************************
-> **Dijkstra - fonte unica, pesos nao negativos**
Devolve dist[] com a menor distancia de start a todos os vertices.
Adj 0-indexado: adj[v] = {{vizinho, peso}, ...}.

Complexidade: O((n + m) log n) tempo, O(n + m) memoria
Uso:
  vector<ll> d = dijkstra(start, adj);
  // d[v] == LLONG_MAX se inalcancavel

* Sobre o codigo:
  Priority queue minima com pares (dist, vertice). A checagem d > dist[v]
  descarta entradas velhas; relaxa as arestas de v.

* Problemas e reducoes:
  + Distancias de fonte unica com pesos >= 0.
  + Reconstruir caminho: guarde par[v] = u ao relaxar.
  + Multi-fonte: empilhe todas as fontes com distancia 0.
  + Grafo de estados: gere vizinhos por uma lambda (dijkstra_estados).
  + Pesos 0/1: bfs01 e mais rapido; negativos: Bellman-Ford/SPFA.

Cuidados: pesos negativos quebram o algoritmo. Nao some peso em LLONG_MAX.
Catalogo: Grafos (Dijkstra, 0-1 BFS, grafo de estados).
Digitacao: 19 linhas | facil.
*****************************LATEX_DESC_END*/