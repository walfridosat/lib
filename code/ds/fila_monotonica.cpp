// Fila/janela monotonica + fila com agregado (duas pilhas)
//
// O que faz: (1) deque monotono: min de janela deslizante em O(n).
//   (2) QueueAgg: fila com qualquer operacao ASSOCIATIVA sem inverso (gcd,
//   min, matriz, composicao) via duas pilhas, push/pop/get O(1) amortizado.
// Quando usar: "Catalogo > Estruturas de dados" (Duas pilhas, janela
//   deslizante com qualquer monoide), DP com janela (knapsack limitado,
//   dp[i]=min(dp[j]) j em [i-k,i-1]).
// Complexidade: O(n) amortizado.
// Uso: janela_min(a, k) -> vetor m onde m[j] = min(a[j..j+k-1]).
//   QueueAgg<ll> q(f, e); q.push(x); q.pop(); q.get(); q.size()
//     f = operacao associativa (antigo f novo), e = elemento neutro.
// Cuidados: em QueueAgg a operacao NAO precisa ser comutativa (ordem
//   preservada). Para max na janela troque >= por <= no while.
vector<ll> janela_min(const vector<ll>& a, int k) {
	deque<int> d; vector<ll> r; // d guarda indices com valores crescentes
	for (int i = 0; i < (int)a.size(); i++) {
		while (!d.empty() && a[d.back()] >= a[i]) d.pop_back();
		d.push_back(i);
		if (d.front() <= i - k) d.pop_front(); // saiu da janela
		if (i >= k - 1) r.push_back(a[d.front()]);
	}
	return r;
}
template<class T> struct QueueAgg {
	function<T(T, T)> f; T e;
	vector<pair<T, T>> in, out; // (valor, agregado)
	QueueAgg(function<T(T, T)> f, T e) : f(f), e(e) {}
	int size() { return in.size() + out.size(); }
	void push(T x) { in.push_back({x, f(in.empty() ? e : in.back().second, x)}); }
	void pop() {
		if (out.empty()) // despeja 'in' invertendo; agregado = f(valor, anterior)
			while (!in.empty()) {
				T x = in.back().first; in.pop_back();
				out.push_back({x, f(x, out.empty() ? e : out.back().second)});
			}
		out.pop_back();
	}
	T get() { return f(out.empty() ? e : out.back().second, in.empty() ? e : in.back().second); }
};
