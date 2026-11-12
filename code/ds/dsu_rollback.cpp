// DSU com rollback - uniao sem compressao, undo O(1)
struct DSUR {
	vector<int> p, sz; // p[x]<0 nao usado; p[x]==x raiz
	vector<pair<int,int>> st; // (filho, raiz) de cada uniao feita (-1 se nada)
	int comps;
	DSUR(int n = 0) : p(n), sz(n, 1), comps(n) { iota(p.begin(), p.end(), 0); }
	int find(int x) { while (p[x] != x) x = p[x]; return x; }
	bool same(int a, int b) { return find(a) == find(b); }
	int snap() { return st.size(); }
	bool join(int a, int b) {
		a = find(a); b = find(b);
		if (a == b) { st.push_back({-1, -1}); return false; } // empilha p/ manter contagem
		if (sz[a] < sz[b]) swap(a, b);
		p[b] = a; sz[a] += sz[b]; comps--;
		st.push_back({b, a});
		return true;
	}
	void undo() {
		auto [b, a] = st.back(); st.pop_back();
		if (b < 0) return;
		p[b] = b; sz[a] -= sz[b]; comps++;
	}
	void rollback(int t) { while ((int)st.size() > t) undo(); }
};
/*LATEX_DESC_BEGIN***************************
-> **DSU com rollback**
Uniao-busca sem compressao de caminho, com desfazer (undo) das ultimas
unioes em O(1).

Complexidade: find O(log n); join O(log n); undo O(1).
Uso:
  DSUR d(n);                 // 0-based
  int t = d.snap(); d.join(a, b); ... d.rollback(t);
  d.comps                    // numero de componentes
  d.sz[d.find(x)]            // tamanho da componente

* Sobre o codigo:
  Uniao por tamanho garante altura log n; a pilha guarda (filho, raiz).
  join empilha tambem no caso de mesma componente para manter a contagem
  do rollback; undo restaura p, sz e comps.

* Problemas e reducoes:
  + Segtree no tempo (DSU offline dinamico).
  + Mo com rollback.
  + Divide e conquista com desfazer.
  + Conectividade offline com remocoes.

Cuidados: NAO use compressao de caminho (quebra o rollback). Uniao por
  tamanho garante altura log n.
Catalogo: Estruturas de dados.
Digitacao: 23 linhas | media.
*****************************LATEX_DESC_END*/
