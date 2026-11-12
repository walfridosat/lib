// SPFA (Bellman-Ford com fila)
//
// O que faz: menor caminho com pesos negativos; detecta ciclo negativo alcancavel de s.
// Quando usar: Catalogo > Grafos ("SPFA e so heuristica"). Pesos negativos sem ciclo,
//   grafo esparso aleatorio. Evite se o problema pode ter teste anti-SPFA.
// Complexidade: O(n*m) pior caso, tipicamente O(m)
// Uso: adj[u] = {(v,w)}, 0-based. bool ok = spfa(n, adj, s, d); ok=false se ha ciclo negativo.
// Cuidados: d[v]=SPFA_INF se inalcancavel. Ciclo negativo detectado por cnt[v] >= n
//   (numero de arestas do caminho).
const ll SPFA_INF = LLONG_MAX / 4;

bool spfa(int n, const vector<vector<pair<int,ll>>>& adj, int s, vector<ll>& d) {
    d.assign(n, SPFA_INF);
    vector<int> cnt(n, 0);
    vector<char> in(n, 0);
    queue<int> q;
    d[s] = 0; q.push(s); in[s] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop(); in[u] = 0;
        for (auto [v, w] : adj[u])
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) return false;   // ciclo negativo
                if (!in[v]) in[v] = 1, q.push(v);
            }
    }
    return true;
}
