// DSU com paridade - bipartido online / xor
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
/*LATEX_DESC_BEGIN***************************
-> **DSU com paridade**
Mantem, para cada no, a paridade (xor) da distancia ate a raiz. Detecta
contradicao em restricoes x_a xor x_b = w e ciclo impar.

Complexidade: O(alfa(n)) amortizado.
Uso:
  DSUP d(n);                 // 0-based
  d.unite(a, b, w) -> 1 se ok (novo ou consistente), 0 se contradicao
    w=1 significa "diferentes"; w=0 "iguais"
  d.diff(a, b) -> -1 se componentes distintas, senao xor de a e b

* Sobre o codigo:
  d[x] = xor de x ate p[x]; find comprime acumulando a paridade.
  unite pendura rb em ra com d[rb] = d[a]^d[b]^w.

* Problemas e reducoes:
  + Bipartido online / detectar ciclo impar.
  + Restricoes x_a xor x_b = w.
  + Mentirosos/verdadeiros e coloracao por paridade.
  + Consistencia de equacoes de xor.

Cuidados: para valores nao-binarios (soma/mod k) veja dsu_potencial.cpp.
  Se houver contradicao, o estado nao muda.
Catalogo: Estruturas de dados.
Digitacao: 23 linhas | media.
*****************************LATEX_DESC_END*/
