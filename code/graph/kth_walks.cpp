// K menores walks de s a t
vector<ll> kth_walks(const vector<vector<pair<int,ll>>>& adj, int s, int t, int k) {
    int n = adj.size();
    vector<int> cnt(n, 0);
    vector<ll> res;
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    pq.push({0, s});
    while (!pq.empty() && (int)res.size() < k) {
        auto [d, u] = pq.top(); pq.pop();
        if (cnt[u] >= k) continue;
        cnt[u]++;
        if (u == t) res.push_back(d);
        for (auto [v, w] : adj[u]) pq.push({d + w, v});
    }
    return res;
}
/*LATEX_DESC_BEGIN***************************
-> **K menores walks de s a t**
Devolve os k menores comprimentos de walks (vertices/arestas podem repetir)
de s ate t, extraindo cada vertice no maximo k vezes. Adj 0-based, w >= 0.

Complexidade: O(k * m log(k*m))
Uso:
  vector<ll> r = kth_walks(adj, s, t, k);
  // r.size() <= k; com ciclo alcancavel sempre ha k

* Sobre o codigo:
  Heap minima de (dist, vertice). Ao extrair u, conta cnt[u]; se u == t grava
  a distancia e relaxa as arestas. Cada vertice sai no maximo k vezes, entao
  cada um contribui com no maximo k walks.

* Problemas e reducoes:
  + k-esimo menor walk (caminho com repeticoes): kth_walks direto.
  + Segundo caminho mais curto (k = 2) com pesos >= 0.
  + Menor ciclo por um vertice: caminho de s a s nao vazio (k = 2).
  + Caminhos simples usam Yen/Eppstein (nao implementado aqui).

Cuidados: se s == t, o walk vazio (custo 0) conta como o primeiro. Para
  caminhos simples este algoritmo pode repetir vertices.
Catalogo: Grafos (segundo menor caminho, k-esimo caminho/walks).
Digitacao: 15 linhas | facil.
*****************************LATEX_DESC_END*/
