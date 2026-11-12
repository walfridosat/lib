// ODT - set de intervalos com valor constante
struct ODT {
	map<int, ll> m; // inicio -> valor; intervalo vai ate o proximo inicio
	int n;
	ODT(int n = 0, ll v = 0) : n(n) { m[0] = v; m[n] = 0; } // m[n] = sentinela
	map<int, ll>::iterator split(int pos) { // retorna it com chave == pos
		auto it = m.lower_bound(pos);
		if (it != m.end() && it->first == pos) return it;
		--it;
		return m.emplace_hint(next(it), pos, it->second);
	}
	void assign(int l, int r, ll v) {
		auto ir = split(r), il = split(l); // r primeiro: split(l) nao invalida ir (map)
		m.erase(il, ir);
		m[l] = v;
	}
	template<class F> void apply(int l, int r, F f) { // f(tamanho, valor&)
		auto ir = split(r), il = split(l);
		for (; il != ir; ++il) f(next(il)->first - il->first, il->second);
	}
};
/*LATEX_DESC_BEGIN***************************
-> **ODT / Chtholly**
Mantem [0, n) particionado em intervalos de valor constante. split(pos) cria
um intervalo comecando em pos; assign(l, r, v) cola [l, r) em v. 0-based.

Complexidade: amortizado O((n + q) log n) com assign frequente; sem assign
  aleatorio pode degenerar para O(nq).
Uso:
  ODT o(n, v0);                // [0, n) com valor v0
  o.assign(l, r, v);           // [l, r) semiaberto
  o.apply(l, r, [&](ll len, ll& val){ ... });  // varre os pedacos
  ll s = 0; o.apply(l, r, [&](ll len, ll& v){ s += len * v; });

* Sobre o codigo:
  map<int, ll> m guarda inicio -> valor; o intervalo vai ate o proximo inicio
  (m[n] e sentinela). split(pos) quebra o intervalo que contem pos. assign e
  apply varrem os pedacos entre split(l) e split(r).

* Problemas e reducoes:
  + "Atribua v em [l,r]" aleatorio com consultas que varrem os intervalos.
  + Soma/contagem/min por range com apply sobre os pedacos.
  + Valor no ponto x: split(x) e leia o valor do iterador.
  + Operacoes que ficam baratas quando o numero de intervalos cai.

Cuidados: intervalos semiabertos [l,r). Chame split(r) antes de split(l) para
  nao invalidar iteradores (ja tratado). Troque ll se precisar de outro tipo.
Catalogo: Estruturas de dados (Chtholly / ODT).
Digitacao: 20 linhas | media. Atalho: ok.
*****************************LATEX_DESC_END*/
