// Dijkstra implicito - estados e k cupons
const ll IM_INF = LLONG_MAX / 4;

template<class F>
vector<ll> dij_impl(int N, const vector<int>& src, F expand) {
    vector<ll> d(N, IM_INF);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    for (int s : src) d[s] = 0, pq.push({0, s});
    while (!pq.empty()) {
        auto [du, u] = pq.top(); pq.pop();
        if (du > d[u]) continue;
        expand(u, [&](int v, ll w) {          // push(v, w): aresta u->v de custo w
            if (du + w < d[v]) d[v] = du + w, pq.push({d[v], v});
        });
    }
    return d;
}

// exemplo: ate K arestas gratis de s a t
// adj[u] = {(v,w)}. Retorna o custo minimo.
ll dij_k_gratis(const vector<vector<pair<int,ll>>>& adj, int s, int t, int K) {
    int n = adj.size();
    auto d = dij_impl(n * (K + 1), {s * (K + 1)}, [&](int x, auto&& push) {
        int u = x / (K + 1), j = x % (K + 1);
        for (auto [v, w] : adj[u]) {
            push(v * (K + 1) + j, w);
            if (j < K) push(v * (K + 1) + j + 1, 0);
        }
    });
    ll r = IM_INF;
    for (int j = 0; j <= K; j++) r = min(r, d[t * (K + 1) + j]);
    return r;
}
/*LATEX_DESC_BEGIN***************************
-> **Dijkstra em grafo implicito / de estados**
Dijkstra generico em que os vizinhos sao gerados por uma lambda. Estados sao
inteiros 0..N-1: codifique (celula,dir), (v,j), (v,paridade), etc. 0-based.

Complexidade: O((N + E) log N), N = numero de estados
Uso:
  auto d = dij_impl(N, {src...}, [&](int u, auto&& push) { push(v, w); ... });
  // grid: estado = i*W + j; vizinhos 4-dir com custo
  // k cupons: estado = v*(K+1) + j; resposta = min_j d[t*(K+1) + j]
  ll c = dij_k_gratis(adj, s, t, K);   // usa ate K arestas gratis

* Sobre o codigo:
  Heap minima sobre os N estados; push(v, w) relaxa uma aresta implicita.
  dij_k_gratis: camada j = quantos cupons usados; aresta normal mantem j,
  usar cupom vai para j+1 com custo 0.

* Problemas e reducoes:
  + Grafo de estados / implicito: gere vizinhos sob demanda.
  + Ate K arestas gratis / K cupons: camada extra por cupom usado.
  + Caminho com paridade: estado (v, p) e vizinho (u, p^1).
  + Grid: estado = celula, vizinhos so dentro da grade.

Cuidados: pesos >= 0. Memoria N pode ser n*K; K grande com custo convexo pede
  Aliens. Se o custo depende do tempo, use Dijkstra por tempo de chegada (FIFO).
Catalogo: Grafos (grafo de estados, implicito, k cupons).
Digitacao: 30 linhas | media.
*****************************LATEX_DESC_END*/
