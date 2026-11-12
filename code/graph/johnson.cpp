// Johnson - todos os pares com pesos negativos
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
/*LATEX_DESC_BEGIN***************************
-> **Johnson - todos os pares com pesos negativos**
Bellman-Ford de super-fonte acha potenciais h; repondera w' = w + h[u] - h[v]
>= 0 e roda Dijkstra de cada vertice (com h[source] = 0). 0-based.

Complexidade: O(n*m + n*m log n)
Uso:
  vector<vector<ll>> D;
  bool ok = johnson(n, adj, D);   // adj[u] = {(v,w)}
  // ok = false se ha ciclo negativo; D[i][j] == JO_INF se inalcancavel

* Sobre o codigo:
  h[] comeca 0 (super-fonte implicita); apos n rodadas sem mudanca, h sao os
  potenciais. Se a rodada n ainda relaxa, ha ciclo negativo. Cada Dijkstra usa
  nw = w + h[u] - h[v] >= 0 e depois desfaz: d[v] += h[v] - h[s].

* Problemas e reducoes:
  + Todos os pares com arestas negativas e sem ciclo negativo, grafo esparso.
  + Potenciais h para MCMF (custo reduzido nao negativo).
  + Alternativa ao Floyd quando n*m log n < n^3.
  + Deteccao de ciclo negativo alcancavel de qualquer vertice.

Cuidados: pesos negativos permitidos; ciclo negativo retorna false. JO_INF e
  sentinela. Potenciais de Johnson so valem apos convergir.
Catalogo: Grafos (Johnson, Dijkstra com pesos negativos, potenciais).
Digitacao: 29 linhas | media. Atalho: reutilize o Dijkstra comum no laco s.
*****************************LATEX_DESC_END*/
