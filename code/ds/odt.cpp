// ODT / Chtholly (set de intervalos com valor constante)
//
// O que faz: mantem a particao de [0,n) em intervalos de valor constante.
//   split(pos) garante um intervalo comecando em pos; assign(l,r,v) cola.
// Quando usar: "Catalogo > Estruturas de dados" (Chtholly / ODT): "atribua v
//   em [l,r]" aleatorio, com outras operacoes feitas varrendo os intervalos.
// Complexidade: amortizado O((n + q) log n) se ha assign frequente (numero de
//   intervalos cai); sem assign aleatorio pode virar O(nq).
// Uso: ODT o(n, v0); // [0,n) com valor v0
//   o.assign(l, r, v);   // [l, r) semiaberto!
//   o.apply(l, r, [&](ll len, ll& val){ ... }); // varre pedacos de [l,r)
//   Ex soma: ll s=0; o.apply(l,r,[&](ll len, ll& v){ s+=len*v; });
// Cuidados: intervalos semiabertos [l,r). Sempre split(r) antes de split(l)
//   evita invalidar iterador (aqui ja tratado). Troque ll por outro tipo se
//   precisar.
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
