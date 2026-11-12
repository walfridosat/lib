// Conectividade dinamica offline (segtree no tempo + DSU com rollback)
//
// O que faz: cada aresta existe em um intervalo de tempo [l, r). Insere a
//   aresta em O(log T) nos da segtree sobre o tempo; um DFS aplica as unioes
//   (com rollback) e responde as queries nas folhas.
// Quando usar: "Catalogo > Estruturas de dados" (DSU offline dinamico);
//   add/remove aresta com queries de conectividade, numero de componentes,
//   bipartido (troque pela DSU com paridade com rollback), MST offline.
// Complexidade: O((m + q) log T log n).
// Uso: DynCon dc(T);           // tempos 0..T-1
//   dc.add(l, r, a, b);        // aresta (a,b) viva em tempos [l, r)
//   dc.run(n, f);              // f(t) chamado em cada folha t (0..T-1)
//   Dentro de f use dc.comps, dc.find(x), dc.sz[dc.find(x)].
//   Ex: dc.run(n, [&](int t){ ans[t] = dc.comps; });
//   DSU com rollback embutida (mesma de code/ds/dsu_rollback.cpp).
// Cuidados: aresta ainda viva no fim -> r = T. Se a mesma aresta aparece e
//   some varias vezes, adicione um intervalo por aparicao (use map p/ achar l).
//   Recursao profundidade log T. Se so quer responder em alguns tempos,
//   marque e filtre em f.
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
