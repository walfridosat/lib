// 0-1 BFS e BFS com pesos pequenos (Dial)
//
// O que faz: menor distancia com pesos em {0,1} usando deque (bfs01), ou com pesos
//   inteiros em [0,W] usando buckets circulares (dial).
// Quando usar: Catalogo > Grafos ("Pesos 0/1 -> 0-1 BFS", "0-1 BFS com custo de virar",
//   grid com setas, estado (celula,direcao)).
// Complexidade: bfs01 O(n+m); dial O(n+m+W*n)
// Uso: adj[u] = {(v,w)}, 0-based. d = bfs01(n, adj, s); d[v]==INF01 se inalcancavel.
//   Para multi-fonte: ligue super-fonte com custo 0 (ou inicialize varias fontes).
// Cuidados: um vertice pode entrar mais de uma vez no deque (ok, so relaxa se melhorar).
//   Em grid, codifique o estado como (celula*4+dir) para "mudar de direcao custa 1".
const ll INF01 = LLONG_MAX / 4;

vector<ll> bfs01(int n, const vector<vector<pair<int,int>>>& adj, int s) {
    vector<ll> d(n, INF01);
    deque<int> dq;
    d[s] = 0; dq.push_back(s);
    while (!dq.empty()) {
        int u = dq.front(); dq.pop_front();
        for (auto [v, w] : adj[u])
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                if (w == 0) dq.push_front(v); else dq.push_back(v);
            }
    }
    return d;
}

// Dial: pesos em [0,W]. Buckets circulares de tamanho W+1.
vector<ll> dial(int n, const vector<vector<pair<int,int>>>& adj, int s, int W) {
    vector<ll> d(n, INF01);
    vector<vector<int>> bk(W + 1);
    d[s] = 0; bk[0].push_back(s);
    ll cur = 0; int pend = 1;              // pend = quantidade de entradas nos buckets
    while (pend > 0) {
        auto& b = bk[cur % (W + 1)];
        while (!b.empty()) {
            int u = b.back(); b.pop_back(); pend--;
            if (d[u] != cur) continue;      // entrada velha
            for (auto [v, w] : adj[u])
                if (cur + w < d[v]) {
                    d[v] = cur + w;
                    bk[d[v] % (W + 1)].push_back(v); pend++;
                }
        }
        cur++;
    }
    return d;
}
