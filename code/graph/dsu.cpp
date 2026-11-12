// DSU (union-find com path compression + union by size)
//
// O que faz: find(u) com compressao; join(u, v) une as componentes; sz guarda tamanhos.
// Quando usar: Catalogo > Grafos (DSU, Kruskal, componentes, remocoes ao contrario).
//            Para rollback use code/ds/dsu_rollback.cpp; com peso/potencial use dsu_potencial.
// Complexidade: O(alpha(n)) amortizado por operacao; memoria O(n).
// Uso: DSU d(n); d.join(u, v); if (d.find(u) == d.find(v)) ...
// Cuidados: indices 0..n (o construtor aloca n+1); para 0-indexado puro use DSU(n-1)
//            ou ajuste; nao use find em indice fora do intervalo.
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
