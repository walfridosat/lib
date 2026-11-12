// Johnson (todos-os-pares com pesos negativos, esparso)
//
// O que faz: Bellman-Ford de super-fonte para achar potenciais h, reponderar
//   w' = w + h[u] - h[v] >= 0 e rodar Dijkstra de cada vertice.
// Quando usar: Catalogo > Grafos ("Dijkstra com pesos negativos... potenciais h(v) (Johnson)").
//   n*m log n menor que n^3 (grafo esparso). Tambem serve para potenciais de MCMF.
// Complexidade: O(n*m + n*m log n)
// Uso: adj[u] = {(v,w)}, 0-based. bool ok = johnson(n, adj, D); ok=false se ciclo negativo.
//   D[i][j] = dist (JO_INF se inalcancavel).
// Cuidados: pesos negativos permitidos; ciclo negativo => retorna false.
const ll JO_INF = LLONG_MAX / 4;

bool johnson(int n, const vector<vector<pair<int,ll>>>& adj, vector<vector<ll>>& D) {
    vector<ll> h(n, 0);                      // super-fonte: dist inicial 0 para todos
    bool ch = true;
    for (int it = 0; it <= n && ch; it++) {
        ch = false;
        for (int u = 0; u < n; u++)
            for (auto [v, w] : adj[u])
                if (h[u] + w < h[v]) h[v] = h[u] + w, ch = true;
        if (ch && it == n) return false;     // ainda relaxa na rodada n+1 => ciclo negativo
    }
    D.assign(n, vector<ll>(n, JO_INF));
    for (int s = 0; s < n; s++) {
        priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
        auto& d = D[s];
        d[s] = 0; pq.push({0, s});
        while (!pq.empty()) {
            auto [du, u] = pq.top(); pq.pop();
            if (du > d[u]) continue;
            for (auto [v, w] : adj[u]) {
                ll nw = w + h[u] - h[v];     // >= 0
                if (du + nw < d[v]) d[v] = du + nw, pq.push({d[v], v});
            }
        }
        for (int v = 0; v < n; v++)
            if (d[v] < JO_INF) d[v] += h[v] - h[s];   // desfaz a reponderacao
    }
    return true;
}
