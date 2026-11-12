// DSU proximo livre - menor indice nao removido
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
/*LATEX_DESC_BEGIN***************************
-> **DSU proximo livre**
nxt(i) = menor j >= i ainda nao removido; cada posicao e consumida uma vez.
Posicoes 0..n-1 com sentinela n.

Complexidade: O(alfa(n)) amortizado.
Uso:
  Prox d(n);
  d.nxt(i) -> proximo livre >= i (n se nenhum)
  d.rem(i) remove i
  Pintar [l,r]: for(i=d.nxt(l); i<=r; i=d.nxt(i)) { pinta(i); d.rem(i); }

* Sobre o codigo:
  p[i] aponta para o proximo candidato; nxt comprime caminhos de forma
  iterativa (sem recursao) e a sentinela n nunca sai.

* Problemas e reducoes:
  + Pintar intervalo onde cada posicao so pinta uma vez.
  + Atribuir valores distintos.
  + Achar o proximo indice ativo.
  + Ocupar a primeira vaga livre.

Cuidados: sentinela n sempre livre. Para "anterior livre" espelhe indices.
Catalogo: Estruturas de dados.
Digitacao: 11 linhas | facil.
*****************************LATEX_DESC_END*/
