// Line container (CHT dinamico, estilo KACTL)
//
// O que faz: insere retas y=k*x+m em qualquer ordem e consulta o MAXIMO em x.
// Quando usar: "Catalogo > Estruturas de dados" (CHT insercoes arbitrarias,
//   set ordenado de retas). Alternativa: code/ds/lichao.cpp.
// Complexidade: O(log n) amortizado por insercao e consulta.
// Uso: LineContainer lc; lc.add(k, m); lc.query(x) -> max_i(k_i*x+m_i).
//   Para MINIMO: add(-k,-m) e negue a resposta.
// Cuidados: query em container vazio eh indefinido. Divisao usa floor para
//   inteiros (isec). Valores ate ~1e18 ok; k*x+m deve caber em ll.
struct Line {
	mutable ll k, m, p; // p = ate onde essa reta eh a melhor
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<>> {
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); } // floor
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, false;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
	}
	ll query(ll x) {
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};
