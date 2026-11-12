// Ordenacao topologica (Kahn)
//
// O que faz: devolve uma ordem topologica de um DAG; se sobrar vertice, ha ciclo
//            (o vetor retornado tem tamanho < n).
// Quando usar: Catalogo > Grafos (DAG, SCC, DP em DAG). Para ordem lexicografica
//            troque queue por priority_queue.
// Complexidade: O(n + m) tempo e O(n) memoria.
// Uso: vector<ll> ord = topoSort(adj); if (ord.size() < adj.size()) tem ciclo.
// Cuidados: grafo dirigido 0-indexado; arestas duplicadas contam em dobro no grau
//            (ok para Kahn, mas remova-as se precisar de semantica exata).


vector<ll> topoSort(vector<vector<ll>> &adj) {
    ll n = adj.size();
    vector<ll> in_degree(n, 0);
    vector<ll> order;
    queue<ll> q;

    for (ll u = 0; u < n; u++) {
        for (ll v : adj[u]) {
            in_degree[v]++;
        }
    }

    for (ll i = 0; i < n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        ll v = q.front();
        q.pop();
        order.push_back(v);

        for (ll u : adj[v]) {
            in_degree[u]--;
            if (in_degree[u] == 0) {
                q.push(u);
            }
        }
    }

    if ((ll)order.size() != n) {
        cout<<"Ciclo"<<endl;
        return {};
    }
    return order;
}