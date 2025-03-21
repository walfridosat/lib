// BFS
//
// 
// 
// 
// 
// 

void bfs(ll start, vector<vector<ll>> &adj) {
    ll n = adj.size();
    vector<bool> visited(n, false);
    queue<ll> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        ll v = q.front();
        q.pop();
        cout << v << " ";

        for (ll u : adj[v]) {
            if (!visited[u]) {
                visited[u] = true;
                q.push(u);
            }
        }
    }
}