// Conectividade dinamica offline - segtree no tempo + DSU rollback
struct DynCon {
	int T, comps;
	vector<vector<pair<int,int>>> seg;
	vector<int> p, sz; vector<pair<int,int>> st; // DSU com rollback (sem compressao)
	DynCon(int T) : T(T), comps(0), seg(4 * T + 4) {}
	int find(int x) { while (p[x] != x) x = p[x]; return x; }
	void join(int a, int b) {
		a = find(a); b = find(b);
		if (a == b) return;
		if (sz[a] < sz[b]) swap(a, b);
		p[b] = a; sz[a] += sz[b]; comps--; st.push_back({b, a});
	}
	void rollback(size_t t) {
		while (st.size() > t) {
			auto [b, a] = st.back(); st.pop_back();
			p[b] = b; sz[a] -= sz[b]; comps++;
		}
	}
	void add(int l, int r, int a, int b, int x = 1, int lo = 0, int hi = -1) {
		if (hi < 0) hi = T;
		if (r <= lo || hi <= l || l >= r) return;
		if (l <= lo && hi <= r) { seg[x].push_back({a, b}); return; }
		int m = (lo + hi) / 2;
		add(l, r, a, b, 2 * x, lo, m);
		add(l, r, a, b, 2 * x + 1, m, hi);
	}
	template<class F> void dfs(int x, int lo, int hi, F& f) {
		size_t s = st.size();
		for (auto [a, b] : seg[x]) join(a, b);
		if (hi - lo == 1) f(lo);
		else {
			int m = (lo + hi) / 2;
			dfs(2 * x, lo, m, f);
			dfs(2 * x + 1, m, hi, f);
		}
		rollback(s);
	}
	template<class F> void run(int n, F f) {
		p.resize(n); iota(p.begin(), p.end(), 0); sz.assign(n, 1); comps = n; st.clear();
		dfs(1, 0, T, f);
	}
};
/*LATEX_DESC_BEGIN***************************
-> **Conectividade dinamica offline**
Cada aresta existe em um intervalo [l,r); ela entra em O(log T) nos da
segtree sobre o tempo e um DFS com DSU rollback responde as folhas.

Complexidade: O((m + q) log T log n).
Uso:
  DynCon dc(T);              // tempos 0..T-1
  dc.add(l, r, a, b);        // aresta (a,b) viva em tempos [l, r)
  dc.run(n, [&](int t){ ans[t] = dc.comps; });
  // dentro de f: dc.comps, dc.find(x), dc.sz[dc.find(x)]

* Sobre o codigo:
  Segtree sobre o tempo guarda as arestas; o DFS aplica as unioes, chama f
  nas folhas e desfaz com rollback ao voltar (sem compressao de caminho).

* Problemas e reducoes:
  + Add/remove aresta com queries de conectividade (offline).
  + Numero de componentes por tempo.
  + Grafo bipartido online: use DSU com paridade com rollback.
  + MST offline e consultas por tempo.

Cuidados: aresta viva ate o fim -> r = T. Se a mesma aresta aparece e some
  varias vezes, adicione um intervalo por aparicao. Recursao de profundidade
  log T. Se so quer responder em alguns tempos, marque e filtre em f.
Catalogo: Estruturas de dados.
Digitacao: 42 linhas | dificil. Atalho: a DSU com rollback pode ser a de
  dsu_rollback.cpp, evitando duplicar join/rollback.
*****************************LATEX_DESC_END*/
