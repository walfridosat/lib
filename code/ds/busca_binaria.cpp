// Busca binaria: templates (inteira, real, exponencial, k-esimo, mediana)
//
// O que faz: colecao de templates de binaria na resposta.
//   bs_first(lo,hi,ok)  : menor x em [lo,hi] com ok(x) (ok monotono F..FT..T);
//                         retorna hi+1 se nenhum.
//   bs_last(lo,hi,ok)   : maior x em [lo,hi] com ok(x) (ok monotono T..TF..F);
//                         retorna lo-1 se nenhum.
//   bs_real(lo,hi,ok)   : 100 iteracoes; devolve o menor x real com ok(x)=true.
//   bs_exp(ok)          : limite superior desconhecido: dobra ate ok, acha menor x>=1.
//   isqrt / iroot       : raiz inteira exata (sem erro de double).
//   kth_dois(A,B,k)     : k-esimo (1-based) da uniao de dois arrays ordenados.
//   kth_soma(A,B,k)     : k-esimo menor de A[i]+B[j] (arrays ordenados).
// Quando usar: "Catalogo > Busca binaria e otimizacao" (binaria na resposta,
//   k-esimo de conjunto implicito, binaria em reais, limite desconhecido,
//   mediana de dois arrays). Binaria na segtree/BIT: ver code/ds (descida).
// Complexidade: O(log(range) * custo do check).
// Uso: ll x = bs_first<ll>(0, 1e18, [&](ll m){ return check(m); });
//   Ex: "minimizar o maximo" -> bs_first; "maximizar o minimo" -> bs_last.
// Cuidados: mid = lo + (hi-lo)/2 (nao (lo+hi)/2 com overflow); para valores
//   negativos o piso aqui eh correto pois hi-lo >= 0. Em check com m*m ou
//   m*k em 1e18 use __int128 ou compare com divisao. Em reais NAO use
//   while(hi-lo>eps) com valores grandes. Monotonicidade deve ser provada.
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
// k-esimo (1-based) da uniao de dois arrays ordenados, O(log) por binaria na particao
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
// k-esimo menor (1-based) entre todas as somas A[i]+B[j]: binaria no valor + 2 ponteiros
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
