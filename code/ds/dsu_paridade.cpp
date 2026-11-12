// DSU com paridade (bipartido online / equacoes xor)
//
// O que faz: mantem, para cada no, a paridade (xor) da distancia ate a raiz.
//   Detecta se adicionar a aresta "a e b diferentes" (ou "a xor b = w")
//   gera contradicao (ciclo impar).
// Quando usar: "Catalogo > Estruturas de dados" (DSU com paridade/potencial);
//   bipartido online, "mentirosos/verdadeiros", restricoes x_a xor x_b = w.
// Complexidade: O(alfa(n)) amortizado.
// Uso: DSUP d(n); // 0-based
//   d.unite(a,b,w) -> 1 se ok (novo ou consistente), 0 se contradicao.
//     w=1 significa "diferentes" (aresta de grafo bipartido); w=0 "iguais".
//   d.diff(a,b) -> -1 se em componentes distintas, senao xor de a e b.
// Cuidados: para valores nao-binarios (soma/mod k) veja dsu_potencial.cpp.
//   Se contradicao, o estado nao muda.
struct DSUP {
	vector<int> p, sz, d; // d[x] = xor de x ate p[x]
	DSUP(int n = 0) : p(n), sz(n, 1), d(n, 0) { iota(p.begin(), p.end(), 0); }
	int find(int x) { // compressao com acumulo de paridade
		if (p[x] == x) return x;
		int r = find(p[x]);
		d[x] ^= d[p[x]]; // d[p[x]] ja eh relativo a raiz apos a recursao
		return p[x] = r;
	}
	int par(int x) { find(x); return d[x]; }
	int diff(int a, int b) {
		if (find(a) != find(b)) return -1;
		return d[a] ^ d[b];
	}
	bool unite(int a, int b, int w = 1) {
		int ra = find(a), rb = find(b);
		int x = d[a] ^ d[b] ^ w; // paridade que a aresta raiz-raiz deve ter
		if (ra == rb) return x == 0;
		if (sz[ra] < sz[rb]) swap(ra, rb);
		p[rb] = ra; d[rb] = x; sz[ra] += sz[rb];
		return true;
	}
};
