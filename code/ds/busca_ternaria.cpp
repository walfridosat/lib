// Busca ternaria - minimo unimodal e Dinkelbach
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
/*LATEX_DESC_BEGIN***************************
-> **Busca ternaria e Dinkelbach**
Acha o minimo de f unimodal/convexa, em reais ou inteiros, e a razao
maxima (sum a)/(sum b) por Dinkelbach.

Complexidade: O(log(range)) avaliacoes.
Uso:
  double x = tern_real(l, r, [&](double x){ return g(x); });
  ll x = tern_int(l, r, [&](ll x){ return g(x); });
  pair<ll,ll> f = dinkelbach(oracle);  // {num, den} da razao otima
  Ternaria aninhada: tern_real(.., [&](double x){ double y=tern_real(..); return f(x,y); });
  Dinkelbach: oracle(num,den) escolhe o subconjunto que maximiza
  sum(a - r*b), r = num/den; repete r <- sumA/sumB ate nao melhorar.

* Sobre o codigo:
  tern_real compara f(m1) e f(m2) e descarta um terco.
  tern_int e uma binaria em f(m) <= f(m+1) (o minimo esta em <= m).
  dinkelbach compara sa*den com num*sb em __int128 (fracoes exatas).

* Problemas e reducoes:
  + Distancia minima maxima a pontos (convexa).
  + Area/perimetro minimo com funcao convexa.
  + Razao maxima de subconjunto (sum a)/(sum b) -> Dinkelbach.
  + Ternaria aninhada para funcao convexa em 2 variaveis.
  + Minimizar soma ou maximo de convexas.

Cuidados: plato fora do otimo quebra a ternaria; exija estritamente
  unimodal ou convexa. Soma e maximo de convexas sao convexas. Em reais
  use ~100 iteracoes e nao compare eps. Dinkelbach com ll pode precisar
  de __int128 nos produtos.
Catalogo: Busca binaria e otimizacao.
Digitacao: 27 linhas | media.
*****************************LATEX_DESC_END*/
