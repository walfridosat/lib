// Busca binaria - templates (inteira, real, k-esimo)
template<class T, class F> T bs_first(T lo, T hi, F ok) {
	T ans = hi + 1; // invariante: ans eh o menor ok conhecido
	while (lo <= hi) {
		T m = lo + (hi - lo) / 2;
		if (ok(m)) ans = m, hi = m - 1; else lo = m + 1;
	}
	return ans;
}
template<class T, class F> T bs_last(T lo, T hi, F ok) {
	T ans = lo - 1;
	while (lo <= hi) {
		T m = lo + (hi - lo) / 2;
		if (ok(m)) ans = m, lo = m + 1; else hi = m - 1;
	}
	return ans;
}
template<class F> double bs_real(double lo, double hi, F ok) {
	for (int it = 0; it < 100; it++) {
		double m = (lo + hi) / 2;
		if (ok(m)) hi = m; else lo = m;
	}
	return hi;
}
template<class F> ll bs_exp(F ok) { // menor x >= 1 com ok(x), ok monotono
	ll hi = 1;
	while (!ok(hi)) hi *= 2; // cuidado: se nunca ok, laco infinito
	return bs_first<ll>(hi == 1 ? 1 : hi / 2 + 1, hi, ok);
}
ll isqrt(ll n) { // floor(sqrt(n)), n >= 0
	ll r = sqrtl((long double)n);
	while (r * r > n) r--;
	while ((r + 1) * (r + 1) <= n) r++;
	return r;
}
ll iroot(ll n, int k) { // floor(n^(1/k)), n >= 0, k >= 1
	if (k == 1) return n;
	auto pot_le = [&](ll b) { // b^k <= n ? (sem overflow)
		__int128 r = 1;
		for (int i = 0; i < k; i++) { r *= b; if (r > n) return false; }
		return true;
	};
	return bs_last<ll>(0, 3037000500LL, pot_le); // raiz de n<=9.2e18 (k>=2) cabe em 3.04e9
}
// k-esimo (1-based) da uniao de dois arrays ordenados
ll kth_dois(const vector<ll>& A, const vector<ll>& B, int k) {
	int n = A.size(), m = B.size();
	int lo = max(0, k - m), hi = min(k, n); // quantos tirar de A
	while (lo < hi) {
		int i = lo + (hi - lo) / 2, j = k - i; // i de A, j de B
		// se A[i] < B[j-1], tiramos poucos de A
		if (j > 0 && i < n && A[i] < B[j - 1]) lo = i + 1; else hi = i;
	}
	int i = lo, j = k - lo;
	ll r = LLONG_MIN;
	if (i > 0) r = max(r, A[i - 1]);
	if (j > 0) r = max(r, B[j - 1]);
	return r;
}
// k-esimo menor de A[i]+B[j]: binaria + 2 ponteiros
ll kth_soma(const vector<ll>& A, const vector<ll>& B, ll k) {
	auto cnt = [&](ll x) { // quantos pares com soma <= x
		ll c = 0; int j = B.size();
		for (int i = 0; i < (int)A.size(); i++) {
			while (j > 0 && A[i] + B[j - 1] > x) j--;
			c += j;
		}
		return c;
	};
	return bs_first<ll>(A[0] + B[0], A.back() + B.back(), [&](ll x) { return cnt(x) >= k; });
}
/*LATEX_DESC_BEGIN***************************
-> **Busca binaria: templates**
Colecao de templates de binaria na resposta: inteira, real, limite
desconhecido, k-esimo de uniao e de somas, raiz inteira.

Complexidade: O(log(range) * custo do check).
Uso:
  bs_first<ll>(lo, hi, ok)   // menor x com ok(x); hi+1 se nenhum
  bs_last<ll>(lo, hi, ok)    // maior x com ok(x); lo-1 se nenhum
  bs_real(lo, hi, ok)        // 100 iteracoes; menor x real com ok
  bs_exp(ok)                 // menor x >= 1, limite superior dobrado
  isqrt(n); iroot(n, k)      // raiz inteira exata (n >= 0)
  kth_dois(A, B, k)          // k-esimo (1-based) da uniao de 2 arrays ordenados
  kth_soma(A, B, k)          // k-esimo menor de A[i]+B[j]
  Ex.: ll x = bs_first<ll>(0, 1e18, [&](ll m){ return check(m); });
  "minimizar o maximo" -> bs_first; "maximizar o minimo" -> bs_last.
  Binaria na segtree/BIT: descida propria (ver code/ds).

* Sobre o codigo:
  bs_first mantem ans = menor ok conhecido; bs_last o simetrico.
  bs_real faz 100 iteracoes de bissecao; bs_exp dobra ate ok e chama bs_first.
  isqrt/iroot ajustam o valor inicial para baixo e para cima sem erro de double.
  kth_dois faz binaria na particao i de A; kth_soma conta pares <= x com 2 ponteiros.

* Problemas e reducoes:
  + Minimizar o maximo -> bs_first; maximizar o minimo -> bs_last.
  + k-esimo de dois arrays ordenados -> kth_dois.
  + k-esimo de somas de dois arrays -> kth_soma.
  + Limite superior desconhecido -> bs_exp.
  + Raiz inteira / potencia exata -> isqrt, iroot.
  + Equilibrio ou interseccao em reais -> bs_real.

Cuidados: mid = lo + (hi-lo)/2 (nao (lo+hi)/2); com hi-lo >= 0 o piso serve
  para negativos. Em check com m*m ou m*k perto de 1e18 use __int128 ou
  compare com divisao. Em reais use ~100 iteracoes, nao while(hi-lo>eps).
  A monotonicidade de ok deve ser provada.
Catalogo: Busca binaria e otimizacao.
Digitacao: 70 linhas | media. Atalho: bs_last pode ser
  bs_first(lo, hi, negacao de ok) - 1, eliminando a segunda busca.
*****************************LATEX_DESC_END*/
