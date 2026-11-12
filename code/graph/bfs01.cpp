// 0-1 BFS e Dial - distancias com pesos pequenos
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

// Dial: pesos [0,W]; buckets de tamanho W+1
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
/*LATEX_DESC_BEGIN***************************
-> **0-1 BFS e Dial - pesos pequenos**
Menor distancia com pesos em {0,1} via deque (bfs01), ou com pesos inteiros
em [0, W] via buckets circulares (dial). Vertices 0-based.

Complexidade: bfs01 O(n + m); dial O(n + m + W*n)
Uso:
  auto d = bfs01(n, adj, s);         // d[v] == INF01 se inalcancavel
  auto d = dial(n, adj, s, W);       // pesos em [0, W]

* Sobre o codigo:
  bfs01: peso 0 vai para a frente do deque, peso 1 para o fim (ordem por dist).
  dial: bucket cur % (W+1); entradas velhas sao descartadas por d[u] != cur.

* Problemas e reducoes:
  + Pesos 0/1 (custo de virar, grid com setas): 0-1 BFS direto.
  + k trocas de direcao: estado (celula, direcao), mudar de direcao custa 1.
  + Multi-fonte: inicialize varias fontes com 0 (ou super-fonte de custo 0).
  + Pesos inteiros limitados: Dial em vez de heap de Dijkstra.

Cuidados: um vertice pode entrar mais de uma vez no deque; so relaxa se
  melhorar. Em grid use id = celula*4 + dir para o estado.
Catalogo: Grafos (0-1 BFS, Dial, grafo de estados).
Digitacao: 36 linhas | media. Atalho: dial pode usar Dijkstra comum se W for grande.
*****************************LATEX_DESC_END*/
