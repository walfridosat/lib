// DSU com potencial - diferencas pot[b]-pot[a]
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
/*LATEX_DESC_BEGIN***************************
-> **DSU com potencial (soma)**
Mantem w[x] = pot[x] - pot[raiz], permitindo restricoes pot[b]-pot[a] = c
e consultar a diferenca se conectados.

Complexidade: O(alfa(n)) amortizado.
Uso:
  DSUW d(n);                 // 0-based
  d.unite(a, b, c) -> pot[b]-pot[a]=c; false se contradiz
  d.dist(a, b) -> pot[b]-pot[a], ou LLONG_MIN se nao conectados

* Sobre o codigo:
  w[x] = pot[x]-pot[p[x]]; find comprime somando os pesos ate a raiz.
  unite calcula x = c - w[b] + w[a] e pendura rb em ra com peso x.

* Problemas e reducoes:
  + Sistemas de diferencas.
  + "A pesa X a mais que B" e distancias relativas.
  + Restricoes de soma pot[b]-pot[a] = c.
  + Consistencia de equacoes lineares em componentes.

Cuidados: overflow se pesos grandes (use ll). Para mod k troque + e - por
  aritmetica mod k. Para xor veja dsu_paridade.cpp.
Catalogo: Estruturas de dados.
Digitacao: 23 linhas | media.
*****************************LATEX_DESC_END*/
