// CHT dinamico - LineContainer (KACTL)
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
/*LATEX_DESC_BEGIN***************************
-> **CHT dinamico (LineContainer)**
Insere retas y=k*x+m em qualquer ordem e consulta o MAXIMO em x.
Para MINIMO: add(-k,-m) e negue a resposta.

Complexidade: O(log n) amortizado por insercao e consulta.
Uso:
  LineContainer lc; lc.add(k, m);
  ll v = lc.query(x);   // max_i(k_i*x + m_i)

* Sobre o codigo:
  multiset ordenado por inclinacao; p = x a partir do qual a reta e melhor.
  isect calcula a intersecao (divisao floor); add remove vizinhas dominadas.

* Problemas e reducoes:
  + DP com retas inseridas em ordem arbitraria.
  + Maximo de k*x+m para consultas em qualquer x.
  + Minimo via negacao das retas e da resposta.
  + Manter envelope superior de retas online.

Cuidados: query em container vazio e indefinido. A divisao de isect e floor
  para inteiros. k*x+m deve caber em ll (valores ate ~1e18 ok).
  Alternativa: code/ds/lichao.cpp.
Catalogo: Estruturas de dados.
Digitacao: 25 linhas | dificil.
*****************************LATEX_DESC_END*/
