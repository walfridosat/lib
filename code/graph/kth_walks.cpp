// K menores caminhos (walks) de s a t
//
// O que faz: devolve os k menores comprimentos de walks (vertices/arestas podem repetir)
//   de s ate t, deixando cada vertice ser extraido ate k vezes.
// Quando usar: Catalogo > Grafos ("Segundo menor caminho / k-esimo caminho (walks)").
//   Para caminhos simples use Yen (k * n Dijkstras, nao implementado) ou Eppstein.
// Complexidade: O(k * m log(k*m))
// Uso: adj[u] = {(v,w)}, w >= 0, 0-based. r = kth_walks(adj, s, t, k); r.size() <= k
//   (menos se ha poucos walks; com ciclo alcancavel sempre ha k).
// Cuidados: se s==t, o walk vazio (custo 0) conta como o primeiro.
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
