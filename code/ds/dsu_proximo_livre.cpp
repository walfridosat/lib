// DSU "proximo livre"
//
// O que faz: nxt(i) = menor j >= i ainda nao removido. Cada posicao eh
//   "consumida" uma vez.
// Quando usar: "Catalogo > Estruturas de dados" (DSU proximo livre): pintar
//   intervalo onde cada posicao so pinta uma vez; atribuir valores distintos;
//   achar proximo indice ativo.
// Complexidade: O(alfa(n)) amortizado.
// Uso: Prox d(n); // posicoes 0..n-1, sentinela n
//   d.nxt(i) -> proximo livre >= i (n se nenhum);  d.rem(i) remove i.
//   Pintar [l,r]: for(i=d.nxt(l); i<=r; i=d.nxt(i)) { pinta(i); d.rem(i); }
// Cuidados: sentinela n sempre livre. Para "anterior livre" espelhe indices.
struct Prox {
	vector<int> p;
	Prox(int n = 0) : p(n + 1) { iota(p.begin(), p.end(), 0); }
	int nxt(int x) { // iterativo para nao estourar pilha
		int r = x;
		while (p[r] != r) r = p[r];
		while (p[x] != r) { int t = p[x]; p[x] = r; x = t; }
		return r;
	}
	void rem(int x) { p[x] = x + 1; }
};
