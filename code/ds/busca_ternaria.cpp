// Busca ternaria (real, inteira) e Dinkelbach
//
// O que faz: acha o minimo de f unimodal/convexa.
//   tern_real(lo,hi,f) : minimo em reais (100 iteracoes), devolve o x.
//   tern_int(lo,hi,f)  : minimo em inteiros via binaria em f(m) vs f(m+1)
//                        (robusta; exige f estritamente decrescente ate o
//                        minimo e estritamente crescente depois, ou plato
//                        so no minimo). Devolve o x.
//   dinkelbach(oracle) : max (sum a)/(sum b) sobre subconjunto nao vazio
//                        escolhido por um oraculo (ver abaixo).
// Quando usar: "Catalogo > Busca binaria e otimizacao" (Funcao unimodal,
//   convexidade fecha por soma/max, ternaria aninhada, Dinkelbach para razao).
//   Distancia minima maxima a pontos (convexa), area minima, etc.
// Complexidade: O(log(range)) avaliacoes.
// Uso: double x = tern_real(l, r, [&](double x){ return g(x); });
//   ll x = tern_int(l, r, [&](ll x){ return g(x); });
//   Ternaria aninhada: tern_real(.., [&](double x){ double y=tern_real(.., [&](double y){return f(x,y);}); return f(x,y); });
//   Dinkelbach: iterate r; oraculo escolhe subconjunto maximizando
//   sum(a - r*b); r <- sum a / sum b ate nao melhorar. Converge em poucas
//   iteracoes e permite resposta exata com fracoes.
// Cuidados: plato fora do otimo quebra a ternaria; use binaria em f(m)<f(m+1)
//   se estritamente unimodal. Convexas: soma e max de convexas sao convexas.
//   Em reais, para f com ruido numerico use ~100 iteracoes e nao compare eps.
template<class F> double tern_real(double lo, double hi, F f) {
	for (int it = 0; it < 100; it++) {
		double m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
		if (f(m1) < f(m2)) hi = m2; else lo = m1;
	}
	return (lo + hi) / 2;
}
template<class F> ll tern_int(ll lo, ll hi, F f) { // minimo, f convexa/estr. unimodal
	while (lo < hi) {
		ll m = lo + (hi - lo) / 2;
		if (f(m) <= f(m + 1)) hi = m; else lo = m + 1; // f(m)<=f(m+1): minimo em <= m
	}
	return lo;
}
// Dinkelbach: oracle(r) devolve {sumA, sumB} do subconjunto que maximiza
// sum(a_i - r*b_i), r = num/den dado como fracao exata (use ll/__int128 por dentro:
// compare a_i*den - num*b_i). Retorna a fracao otima {sumA, sumB}.
template<class O> pair<ll,ll> dinkelbach(O oracle) {
	auto [num, den] = oracle(0, 1); // comeca com o melhor subconjunto para r=0 (viavel)
	while (true) {
		auto [sa, sb] = oracle(num, den);
		// melhora se sa/sb > num/den  <=>  sa*den > num*sb
		if ((__int128)sa * den <= (__int128)num * sb) break;
		num = sa; den = sb;
	}
	return {num, den};
}
