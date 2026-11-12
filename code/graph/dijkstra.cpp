// Dijkstra (menores caminhos de fonte unica, pesos nao negativos)
//
// O que faz: devolve dist[] com a menor distancia de start a todos os vertices.
// Quando usar: Catalogo > Grafos (Dijkstra, 0-1 BFS, grafo de estados). Pesos >= 0;
//            para negativos use Bellman-Ford/SPFA; para 0/1 use bfs01/0-1 BFS.
// Complexidade: O((n + m) log n) tempo, O(n + m) memoria.
// Uso: vector<ll> d = dijkstra(start, adj); adj[v] = {{vizinho, peso}, ...} 0-indexado.
// Cuidados: LLONG_MAX marca inalcancavel (nao some pesos nele); pesos negativos quebram;
//            para reconstruir o caminho guarde o pai ao relaxar.

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