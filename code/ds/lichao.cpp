// Li Chao - minimo de retas e segmentos em x
struct LiChao {
	struct L { ll a, b; ll f(ll x) const { return a * x + b; } };
	struct Nd { L ln; int l = -1, r = -1; };
	static constexpr ll INF = LLONG_MAX;
	ll lo, hi;
	vector<Nd> t;
	vector<pair<int, Nd>> hist; // historico para rollback: (indice, estado anterior)
	LiChao(ll lo, ll hi) : lo(lo), hi(hi) { t.push_back({{0, INF}}); } // no 0 = raiz vazia
	bool empty(const L& x) { return x.b == INF; }
	int mk() { t.push_back({{0, INF}}); return t.size() - 1; }
	void save(int i) { hist.push_back({i, t[i]}); }
	int snap() { return hist.size(); }
	void rollback(int s) {
		while ((int)hist.size() > s) { // restaura; nos criados ficam orfaos (inofensivos)
			t[hist.back().first] = hist.back().second; hist.pop_back();
		}
	}
	void add(ll a, ll b) { ins(0, lo, hi, {a, b}); }
	void ins(int i, ll l, ll r, L nw) {
		if (empty(t[i].ln)) { save(i); t[i].ln = nw; return; }
		ll m = l + (r - l) / 2; // meio sem overflow, vale p/ negativos
		bool lef = nw.f(l) < t[i].ln.f(l), mid = nw.f(m) < t[i].ln.f(m);
		if (mid) { save(i); swap(t[i].ln, nw); } // fica no no a reta melhor em m
		if (l == r) return;
		if (lef != mid) { // a perdedora pode vencer na esquerda
			if (t[i].l < 0) { int c = mk(); save(i); t[i].l = c; }
			ins(t[i].l, l, m, nw);
		} else {
			if (t[i].r < 0) { int c = mk(); save(i); t[i].r = c; }
			ins(t[i].r, m + 1, r, nw);
		}
	}
	// segmento: reta vale apenas em x em [sl, sr]
	void add_seg(ll a, ll b, ll sl, ll sr) { seg(0, lo, hi, sl, sr, {a, b}); }
	void seg(int i, ll l, ll r, ll sl, ll sr, L nw) {
		if (sr < l || r < sl) return;
		if (sl <= l && r <= sr) { ins(i, l, r, nw); return; }
		ll m = l + (r - l) / 2;
		if (t[i].l < 0) { int c = mk(); save(i); t[i].l = c; }
		seg(t[i].l, l, m, sl, sr, nw);
		if (t[i].r < 0) { int c = mk(); save(i); t[i].r = c; }
		seg(t[i].r, m + 1, r, sl, sr, nw);
	}
	ll query(ll x) {
		ll res = INF; int i = 0; ll l = lo, r = hi;
		while (i >= 0) {
			if (!empty(t[i].ln)) res = min(res, t[i].ln.f(x));
			if (l == r) break;
			ll m = l + (r - l) / 2;
			if (x <= m) { i = t[i].l; r = m; } else { i = t[i].r; l = m + 1; }
		}
		return res;
	}
};
/*LATEX_DESC_BEGIN***************************
-> **Li Chao - Minimo de Retas**
Estrutura dinamica sobre [lo, hi] que insere retas y = a*x + b (ou segmentos)
e devolve o minimo em qualquer x inteiro.

Complexidade: O(log U) por insercao e consulta; memoria O(#insercoes).
Uso:
  LiChao lc(lo, hi); lc.add(a, b); lc.add_seg(a, b, l, r);
  ll mn = lc.query(x);               // LiChao::INF se nao ha reta
  int s = lc.snap(); lc.rollback(s); // desfaz inserts desde s

* Sobre o codigo:
  Cada no guarda uma reta; ins compara as duas no meio m, mantem a melhor em m
  e empurra a perdedora para o lado onde ela ainda pode vencer. query desce da
  raiz ate a folha de x pegando o minimo. hist guarda estados para rollback.

* Problemas e reducoes:
  + DP com transicao linear dp[i] = min_j (dp[j] + b_j * a_i): a reta de j tem
    a = b_j, b = dp[j]; consulte em a_i.
  + Menor valor de um conjunto de retas em x quaisquer, online ou offline.
  + Maximo: insira (-a, -b) e negue o resultado do query.
  + Reta valida so num subintervalo de x: add_seg(a, b, l, r).
  + CHT em arvore / DSU on tree: snap() e rollback() desfazem insercoes.

Cuidados: a*x + b deve caber em ll (|a|,|x| ~1e9 e b ~1e18 ja no limite).
  Dominio pequeno pode ser [0, n-1]; rollback deixa nos orfaos, inofensivos.
Catalogo: Estruturas de dados; Busca binaria e otimizacao (CHT).
Digitacao: 54 linhas | media. Atalho: empty() pode checar t[i].ln.b == INF.
*****************************LATEX_DESC_END*/
