// Dijkstra - variantes
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

// dist + caminhos minimos mod DJM + pai
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

// minimax: menor maior-peso; maximin: troque
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

// aresta em algum caminho minimo: ds+w+dt==ds[t]
// dt vem do grafo reverso; retorna (u, posicao)
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
/*LATEX_DESC_BEGIN***************************
-> **Dijkstra - variantes**
dij_dense (sem heap, O(n^2)); dij_count (dist + numero de caminhos minimos
mod DJM + pai); dij_minimax (minimiza o maior peso do caminho); on_shortest
(arestas em algum caminho minimo s->t). Adj 0-indexado: adj[u] = {(v,w)}.

Complexidade: dij_dense O(n^2); as demais O(m log n)
Uso:
  d = dij_dense(w, s);                    // w[i][j], DJ_INF = sem aresta
  dij_count(adj, s, d, cnt, par);         // cnt mod DJM, par = pai
  d = dij_minimax(adj, s);                // (maximin: troque min/max)
  auto e = on_shortest(adj, ds, dt, t);   // indices (u, posicao em adj[u])

* Sobre o codigo:
  dij_dense escolhe o minimo nao-fechado por varredura. O(n^2) bom para n
  pequeno e grafo denso. dij_count soma cnt[u] quando empata dist; minimax
  relaxa com nd = max(du, w). on_shortest testa ds[u] + w + dt[v] == ds[t],
  com dt de Dijkstra no grafo reverso.

* Problemas e reducoes:
  + Contagem de caminhos minimos mod primo: dij_count.
  + Maior aresta do caminho (minimax/bottleneck): dij_minimax.
  + Arestas/vertices em algum caminho minimo: on_shortest.
  + Probabilidades (maximizar produto <= 1): max-heap com *, ou -log.
  + Grafo denso com n pequeno: dij_dense dispensa heap.

Cuidados: pesos >= 0. Em dij_count, ciclo de peso 0 torna a contagem infinita.
  DJM e primo fixo (1e9+7); troque se precisar.
Catalogo: Grafos (Dijkstra lazy vs decrease-key, bottleneck, contagem).
Digitacao: 61 linhas | dificil. Atalho: dij_minimax e o Dijkstra basico diferem
  so na relaxacao; una com um parametro.
*****************************LATEX_DESC_END*/
