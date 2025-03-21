// DSU
//
// 
// 
// 
// 
// a(1e6)==5

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
