// toposort
//
// 
// 
// 
// 
// 

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

    if (order.size() != n) {
        cout<<"Ciclo"<<endl;
        return {};
    }
    return order;
}