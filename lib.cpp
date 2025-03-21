#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
 
#define pb push_back
#define ppb pop_back
#define all(a) (a).begin(), (a).end()
#define pii pair<ll, ll>
#define endl '\n'
#define Merami_THE_ORAL_CIGARETTES_Mou_Ii_kai_RAIN_HD_NC_FC ios_base::sync_with_stdio(false)
#define keep_gambling cin.tie(NULL)
#define FORI(n) for(ll i = 0; i < (n); i++)
#define FORJ(n) for(ll j = 0; j < (n); j++)

/* 

grafos

representação é com vector<vector<ll>>

*/

struct DSU {
	vector<int> pai, sz;
	DSU(int n) : pai(n+1), sz(n+1, 1) {
		for(int i=0; i<=n; i++) pai[i] = i;
	}
	
	int find(int u){ return pai[u] == u ? u : pai[u] = find(pai[u]); }

	void join(int u, int v){
		u = find(u), v = find(v);

		if(u == v) return;
		if(sz[v] > sz[u]) swap(u, v);

		pai[v] = u;
		sz[u] += sz[v];
	}
};

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

void dfs(ll v, vector<vector<ll>> &adj, vector<bool> &visited) {
    visited[v] = true;
    cout << v << " ";

    for (ll u : adj[v]) {
        if (!visited[u]) {
            dfs(u, adj, visited);
        }
    }
}

vector<ll> dijkstra(ll start, vector<vector<pair<ll, ll>>> &adj) {
    ll n = adj.size();
    vector<ll> dist(n, LLONG_MAX);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();

        if (d > dist[v]) continue;

        for (auto [u, w] : adj[v]) {
            if (dist[v] + w < dist[u]) {
                dist[u] = dist[v] + w;
                pq.push({dist[u], u});
            }
        }
    }

    return dist;
}

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

//teoria dos numeros:

vector<bool> is_prime(MAXN + 1, true);
vector<ll> primes;

void sieve() {
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= MAXN; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (ll j = i * i; j <= MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return (a / gcd(a, b)) * b;
}

ll mod_add(ll a, ll b) {
    return (a % MOD + b % MOD) % MOD;
}

ll mod_sub(ll a, ll b) {
    return ((a % MOD - b % MOD) + MOD) % MOD;
}

ll mod_mul(ll a, ll b) {
    return (a % MOD * b % MOD) % MOD;
}

ll fexp(ll b, ll p){
	ll ans = 1;

	while(p){
		if(p&1) ans = (ans*b) % MOD;
		b = b * b % MOD;
		p >>= 1;
	}

	return ans % MOD;
}

ll mod_inv(ll a) {
    return fexp(a, MOD - 2);
}

/*

queries

*/

vector<vector<ll>> ps2d(vector<vector<ll>>& palao){
    ll n=palao.size();
    ll m=palao[0].size();
    vector<vector<ll>>prefix(n, vector<ll>(m,0));
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            prefix[i][j]=palao[i][j];
            if(i>0) prefix[i][j]+= prefix[i-1][j];
            if(j>0) prefix[i][j]+= prefix[i][j-1];
            if(i>0 && j>0) prefix[i][j] -=prefix[i-1][j-1];
        }
    }
    return prefix;
}

ll ps2d_query(vector<vector<ll>>& prefix, ll x1, ll y1, ll x2, ll y2) {
    ll sum = prefix[x2][y2];
    if (x1 > 0) sum -= prefix[x1 - 1][y2];
    if (y1 > 0) sum -= prefix[x2][y1 - 1];
    if (x1 > 0 && y1 > 0) sum += prefix[x1 - 1][y1 - 1];
    return sum;
}

class SegTree {
    private:
        vector<ll> tree, lazy;
        ll n;
    
        void push(ll node, ll start, ll end) {
            if (lazy[node] != 0) {
                tree[node] += (end - start + 1) * lazy[node];
                if (start != end) {
                    lazy[2 * node] += lazy[node];
                    lazy[2 * node + 1] += lazy[node];
                }
                lazy[node] = 0;
            }
        }
    
        void build(const vector<ll>& arr, ll node, ll start, ll end) {
            if (start == end) {
                tree[node] = arr[start];
            } else {
                ll mid = (start + end) / 2;
                build(arr, 2 * node, start, mid);
                build(arr, 2 * node + 1, mid + 1, end);
                tree[node] = tree[2 * node] + tree[2 * node + 1];
            }
        }
    
        void updateRange(ll node, ll start, ll end, ll l, ll r, ll val) {
            push(node, start, end);
            if (r < start || end < l) return;
            if (l <= start && end <= r) {
                lazy[node] += val;
                push(node, start, end);
                return;
            }
            ll mid = (start + end) / 2;
            updateRange(2 * node, start, mid, l, r, val);
            updateRange(2 * node + 1, mid + 1, end, l, r, val);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    
        ll query(ll node, ll start, ll end, ll l, ll r) {
            push(node, start, end);
            if (r < start || end < l) return 0;
            if (l <= start && end <= r) return tree[node];
            ll mid = (start + end) / 2;
            return query(2 * node, start, mid, l, r) + 
                   query(2 * node + 1, mid + 1, end, l, r);
        }
    
    public:
        SegTree(const vector<ll>& arr) {
            n = arr.size();
            tree.resize(4 * n, 0);
            lazy.resize(4 * n, 0);
            build(arr, 1, 0, n - 1);
        }
    
        void update(ll l, ll r, ll val) {
            updateRange(1, 0, n - 1, l, r, val);
        }
    
        ll query(ll l, ll r) {
            return query(1, 0, n - 1, l, r);
        }
    };

/*

dp basico

*/

void dp_coins(vector<ll>& coins, ll target){
    vector<ll> dp(target + 1, MAXN+1);
    dp[0] = 0;

    for (ll i = 1; i <= target; i++) {
        for (auto c : coins) {
            if (i - c >= 0)
                dp[i] = min(dp[i], dp[i - c] + 1);
        }
    }

}

void dp_frog(vector<ll>& palao){
    ll MAXV=LLONG_MAX;
    ll n = palao.size();
    ll k = 2; //opçoes pulo
    vector<ll>dp(MAXN,MAXV+1);
    dp[0]=0;
    for(int i = 1; i < n; i++){
        for(int j = 1; j<=k; j++){
            if(i-j>=0){
                dp[i]=min(dp[i],dp[i-j] + abs(palao[i] - palao[i-j]));
            }
        }
    }
}

ll lis(vector<ll> &palao) {
    vector<ll>tfg;
    for(auto x : palao){
        auto it = lower_bound(all(tfg), x);
        if (it == tfg.end()) tfg.pb(x);
        else *it = x;
    }
    return tfg.size();
}

void knapsack(vector<ll>&palao, vector<ll>&ryei){
    //palao = peso
    //ryei = valor
    ll n=palao.size();
    ll w = 0; //peso que vc quer
    FORI(n){
        cin>>palao[i];
        cin>>ryei[i];
    }

    vector<ll> dp(w+1, 0); // dp em w
    FORI(n) {
        for (ll j = w; j >= palao[i]; j--) {
            dp[j] = max(dp[j], dp[j - palao[i]] + ryei[i]);
        }
    }
}

/*

buscas

*/

vector<vector<ll>> subsets(vector<ll>& nums) {
    ll n = nums.size();
    vector<vector<ll>> subsets;
    
    ll totalSubsets = 1 << n; 
    
    for (ll mask = 0; mask < totalSubsets; ++mask) {
        vector<ll> subset;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                subset.push_back(nums[i]);
            }
        }
        subsets.push_back(subset);
    }
    
    return subsets;
}

void backtrack(vector<ll>& nums, vector<bool>& used, vector<ll>& current, vector<vector<ll>>& result) {
    if (current.size() == nums.size()) {
        result.push_back(current);
        return;
    }

    for (int i = 0; i < nums.size(); ++i) {
        if (!used[i]) {
            used[i] = true;
            current.push_back(nums[i]);

            backtrack(nums, used, current, result);

            current.pop_back();
            used[i] = false;
        }
    }
}

vector<vector<ll>> generatePermutations(vector<ll>& nums) {
    vector<vector<ll>> result;
    vector<ll> current;
    vector<bool> used(nums.size(), false);
    backtrack(nums, used, current, result);
    return result;
}