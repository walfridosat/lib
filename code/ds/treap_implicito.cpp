// Treap implicito - sequencia com split/merge e lazy
struct Treap {
	struct Nd { int l = 0, r = 0, sz = 0; unsigned pr = 0; ll val = 0, sum = 0, lz = 0; bool rev = false; };
	vector<Nd> t; int root = 0;
	mt19937 rng{712367};
	Treap() { t.reserve(1 << 16); t.emplace_back(); } // t[0] = nulo
	int sz(int x) { return t[x].sz; }
	int newnode(ll v) {
		Nd n; n.sz = 1; n.pr = rng(); n.val = n.sum = v; t.push_back(n);
		return t.size() - 1;
	}
	void apply_add(int x, ll v) { if (!x) return; t[x].val += v; t[x].sum += v * t[x].sz; t[x].lz += v; }
	void apply_rev(int x) { if (!x) return; t[x].rev ^= 1; swap(t[x].l, t[x].r); }
	void push(int x) {
		if (t[x].lz) { apply_add(t[x].l, t[x].lz); apply_add(t[x].r, t[x].lz); t[x].lz = 0; }
		if (t[x].rev) { apply_rev(t[x].l); apply_rev(t[x].r); t[x].rev = false; }
	}
	void pull(int x) {
		t[x].sz = 1 + sz(t[x].l) + sz(t[x].r);
		t[x].sum = t[x].val + t[t[x].l].sum + t[t[x].r].sum;
	}
	// separa x em (primeiros k elementos, resto)
	void split(int x, int k, int& a, int& b) {
		if (!x) { a = b = 0; return; }
		push(x);
		if (sz(t[x].l) < k) { split(t[x].r, k - sz(t[x].l) - 1, t[x].r, b); a = x; }
		else { split(t[x].l, k, a, t[x].l); b = x; }
		pull(x);
	}
	int merge(int a, int b) {
		if (!a || !b) return a ? a : b;
		if (t[a].pr > t[b].pr) { push(a); t[a].r = merge(t[a].r, b); pull(a); return a; }
		push(b); t[b].l = merge(a, t[b].l); pull(b); return b;
	}
	int size() { return sz(root); }
	void build(const vector<ll>& v) { root = 0; for (ll x : v) root = merge(root, newnode(x)); }
	void insert(int pos, ll v) { int a, b; split(root, pos, a, b); root = merge(merge(a, newnode(v)), b); }
	void erase(int pos) { int a, b, c; split(root, pos, a, b); split(b, 1, b, c); root = merge(a, c); }
	// aplica f(no_do_intervalo) em [l, r]
	template<class F> void on(int l, int r, F f) {
		int a, b, c; split(root, l, a, b); split(b, r - l + 1, b, c);
		f(b); root = merge(merge(a, b), c);
	}
	void reverse(int l, int r) { on(l, r, [&](int x) { apply_rev(x); }); }
	void add(int l, int r, ll v) { on(l, r, [&](int x) { apply_add(x, v); }); }
	ll sum(int l, int r) { ll s; on(l, r, [&](int x) { s = t[x].sum; }); return s; }
	ll get(int pos) { return sum(pos, pos); }
	void move(int l, int r, int pos) { // bloco [l,r] vai para depois de 'pos' elementos do restante
		int a, b, c, d; split(root, l, a, b); split(b, r - l + 1, b, c);
		int rest = merge(a, c); split(rest, pos, a, d);
		root = merge(merge(a, b), d);
	}
	void dump(vector<ll>& out) { out.clear(); dfs(root, out); }
	void dfs(int x, vector<ll>& out) { if (!x) return; push(x); dfs(t[x].l, out); out.push_back(t[x].val); dfs(t[x].r, out); }
};
/*LATEX_DESC_BEGIN***************************
-> **Treap Implicito**
Sequencia dinamica com split/merge: insere/remove por posicao, corta/cola
pedacos, reverte intervalo, soma e add em intervalo. 0-based, [l, r] inclusivo.

Complexidade: O(log n) esperado por operacao.
Uso:
  Treap t;                              // raiz = t.root (0 = vazio)
  t.build(vector<ll> v);
  t.insert(pos, val); t.erase(pos);
  t.reverse(l, r); t.add(l, r, v); t.sum(l, r);   // [l, r]
  t.move(l, r, pos);   // [l,r] vai para depois de pos elementos restantes
  t.get(pos); t.size(); t.dump(vector<ll>&);      // em ordem

* Sobre o codigo:
  Cada no guarda tamanho, prioridade, valor, soma e lazies de add/reverse.
  split(x, k) separa os k primeiros; merge junta por prioridade. on isola
  [l, r] com dois splits e aplica f na raiz do pedaco.

* Problemas e reducoes:
  + Mover bloco / cortar e colar substring.
  + Reverter intervalo (lazy de reverse).
  + Range add + range sum numa sequencia.
  + Inserir/remover no meio (segtree com insercao).

Cuidados: split(t, k) separa os primeiros k em L. push() antes de descer.
  Para outro agregado (min, max) edite pull()/apply(). Nos nunca sao
  reaproveitados (MAXN = total de insercoes).
Catalogo: Estruturas de dados (Treap implicito, lazy).
Digitacao: 54 linhas | dificil. Atalho: sum() pode ler t[b].sum direto.
*****************************LATEX_DESC_END*/
