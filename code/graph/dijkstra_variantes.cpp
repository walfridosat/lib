// Dijkstra: variantes (denso O(n^2), gargalo/minimax, contagem de caminhos, arestas em
// algum caminho minimo, caminho)
//
// O que faz: dij_dense (sem heap); dij_count (dist + numero de caminhos minimos mod M +
//   pai); dij_minimax (minimiza o maior peso no caminho); on_shortest (arestas que pertencem
//   a algum caminho minimo s->t).
// Quando usar: Catalogo > Grafos ("Dijkstra lazy vs decrease-key", "custo maximo ou
//   bottleneck", "contagem de caminhos minimos", "arestas em algum caminho minimo").
// Complexidade: dense O(n^2); demais O(m log n)
// Uso: adj[u] = {(v,w)}, 0-based; ver exemplo em cada funcao. Dijkstra basico: code/graph/dijkstra.
// Cuidados: pesos >= 0 (w=0 ok em dij_count desde que sem ciclo de peso 0 que quebre a
//   contagem: com ciclo de peso 0 a contagem de caminhos fica infinita). Multiplicativo
//   (maximizar produto de prob <= 1): max-heap com combinacao *, ou use -log.
typedef vector<vector<pair<int,ll>>> GW;
const ll DJ_INF = LLONG_MAX / 4;

// Denso: matriz w[i][j] (DJ_INF = sem aresta).
vector<ll> dij_dense(const vector<vector<ll>>& w, int s) {
    int n = w.size();
    vector<ll> d(n, DJ_INF);
    vector<char> done(n, 0);
    d[s] = 0;
    for (int it = 0; it < n; it++) {
        int u = -1;
        for (int i = 0; i < n; i++) if (!done[i] && (u < 0 || d[i] < d[u])) u = i;
        if (d[u] >= DJ_INF) break;
        done[u] = 1;
        for (int v = 0; v < n; v++) if (w[u][v] < DJ_INF) d[v] = min(d[v], d[u] + w[u][v]);
    }
    return d;
}

// dist + numero de caminhos minimos (mod DJM) + pai de um caminho minimo.
const ll DJM = 1000000007;
void dij_count(const GW& adj, int s, vector<ll>& d, vector<ll>& cnt, vector<int>& par) {
    int n = adj.size();
    d.assign(n, DJ_INF); cnt.assign(n, 0); par.assign(n, -1);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    d[s] = 0; cnt[s] = 1; pq.push({0, s});
    while (!pq.empty()) {
        auto [du, u] = pq.top(); pq.pop();
        if (du > d[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (du + w < d[v]) { d[v] = du + w; cnt[v] = cnt[u]; par[v] = u; pq.push({d[v], v}); }
            else if (du + w == d[v]) cnt[v] = (cnt[v] + cnt[u]) % DJM;
        }
    }
}

// minimax: dist[v] = min sobre caminhos do maior peso de aresta. (maximin: troque min/max)
vector<ll> dij_minimax(const GW& adj, int s) {
    int n = adj.size();
    vector<ll> d(n, DJ_INF);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    d[s] = 0; pq.push({0, s});
    while (!pq.empty()) {
        auto [du, u] = pq.top(); pq.pop();
        if (du > d[u]) continue;
        for (auto [v, w] : adj[u]) {
            ll nd = max(du, w);
            if (nd < d[v]) d[v] = nd, pq.push({nd, v});
        }
    }
    return d;
}

// Arestas (u,v,w) que estao em algum caminho minimo s->t: ds[u]+w+dt[v]==ds[t].
// ds = Dijkstra de s em adj; dt = Dijkstra de t no grafo REVERSO radj. Retorna indices
// (u, posicao em adj[u]).
vector<pair<int,int>> on_shortest(const GW& adj, const vector<ll>& ds, const vector<ll>& dt, int t) {
    vector<pair<int,int>> r;
    for (int u = 0; u < (int)adj.size(); u++)
        for (int i = 0; i < (int)adj[u].size(); i++) {
            auto [v, w] = adj[u][i];
            if (ds[u] < DJ_INF && dt[v] < DJ_INF && ds[u] + w + dt[v] == ds[t]) r.push_back({u, i});
        }
    return r;
}
