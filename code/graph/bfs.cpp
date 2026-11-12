// BFS (busca em largura)
//
// O que faz: percorre o grafo nao ponderado a partir de start, marcando visitados e
//            imprimindo a ordem de descoberta.
// Quando usar: Catalogo > Grafos (BFS, grafo de estados, 0-1 BFS quando ha pesos).
//            Para distancias troque o cout por dist[v] = dist[u] + 1.
// Complexidade: O(n + m) tempo e O(n) memoria.
// Uso: bfs(start, adj) com adj 0-indexado; start em [0, n).
// Cuidados: grafo nao ponderado (para pesos use Dijkstra/0-1 BFS); se o grafo for
//            enorme evite queue de ll e use vector<int>; descomente as varias componentes.

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