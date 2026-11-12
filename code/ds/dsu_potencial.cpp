// DSU com pesos / potencial (soma)
//
// O que faz: mantem w[x] = pot[x] - pot[raiz]. Permite restricoes do tipo
//   pot[b] - pot[a] = c e consultar pot[b]-pot[a] se conectados.
// Quando usar: "Catalogo > Estruturas de dados" (DSU com potencial);
//   sistemas de diferencas, "A pesa X a mais que B", distancias relativas.
// Complexidade: O(alfa(n)) amortizado.
// Uso: DSUW d(n); // 0-based
//   d.unite(a,b,c) -> pot[b]-pot[a]=c; retorna false se contradiz.
//   d.dist(a,b) -> pot[b]-pot[a], ou LLONG_MIN se nao conectados.
// Cuidados: overflow se pesos grandes (use ll). Para mod k troque + e - por
//   aritmetica mod k. Para xor veja dsu_paridade.cpp.
struct DSUW {
	vector<int> p, sz; vector<ll> w; // w[x] = pot[x]-pot[p[x]]
	DSUW(int n = 0) : p(n), sz(n, 1), w(n, 0) { iota(p.begin(), p.end(), 0); }
	int find(int x) {
		if (p[x] == x) return x;
		int r = find(p[x]);
		w[x] += w[p[x]]; // w[p[x]] ja relativo a raiz
		return p[x] = r;
	}
	ll dist(int a, int b) {
		if (find(a) != find(b)) return LLONG_MIN;
		return w[b] - w[a];
	}
	bool unite(int a, int b, ll c) { // pot[b]-pot[a]=c
		int ra = find(a), rb = find(b);
		if (ra == rb) return w[b] - w[a] == c;
		// pot[rb]-pot[ra] = (pot[b]-w[b]) - (pot[a]-w[a]) = c - w[b] + w[a]
		ll x = c - w[b] + w[a];
		if (sz[ra] < sz[rb]) { swap(ra, rb); x = -x; } // pendura rb em ra com peso x
		p[rb] = ra; w[rb] = x; sz[ra] += sz[rb];
		return true;
	}
};
