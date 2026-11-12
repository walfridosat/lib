// Dijkstra em grafo implicito / de estados (grid, k cupons, camadas)
//
// O que faz: Dijkstra generico onde os vizinhos sao gerados por uma lambda; estados sao
//   inteiros 0..N-1 (codifique (celula,dir), (v,j), (v,paridade), ...). Inclui exemplo
//   de "k arestas gratis" (dist[v][j]).
// Quando usar: Catalogo > Grafos ("Grafo de estados", "Dijkstra em grafo implicito",
//   "k arestas gratis / k cupons", "Caminho com paridade/cores", "alterna tipos de aresta").
// Complexidade: O((N + E) log N), N = numero de estados
// Uso: auto d = dij_impl(N, {src...}, [&](int u, auto&& push){ push(v, w); ... });
//   Exemplo grid H x W: estado = i*W+j; vizinhos 4-dir dentro da grade com custo c.
//   Exemplo cupons: estado = v*(K+1)+j; aresta (u,v,w): push(v*(K+1)+j, w) e, se j<K,
//   push(v*(K+1)+j+1, 0). Resposta = min_j d[t*(K+1)+j].
// Cuidados: pesos >= 0. Memoria N pode ser n*K; K grande com custo convexo => Aliens.
//   Estado = (v, paridade): vizinho (u, p^1). "Chegar mais cedo nunca piora" (FIFO) =>
//   Dijkstra por tempo de chegada, custo da aresta pode depender do tempo atual d[u].
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

// Exemplo pronto: menor caminho de s a t usando ate K arestas gratis.
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
