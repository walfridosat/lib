// Fila monotonica e fila com agregado (duas pilhas)
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
/*LATEX_DESC_BEGIN***************************
-> **Fila monotonica e fila com agregado**
Deque monotonico para min de janela deslizante em O(n); QueueAgg da fila
com qualquer operacao associativa sem inverso (gcd, min, matriz).

Complexidade: O(n) amortizado.
Uso:
  janela_min(a, k)           // m[j] = min(a[j..j+k-1])
  QueueAgg<ll> q(f, e); q.push(x); q.pop(); q.get(); q.size()
  // f associativa (antigo f novo), e = elemento neutro

* Sobre o codigo:
  O deque guarda indices com valores crescentes e descarta quem saiu da
  janela. QueueAgg usa duas pilhas com agregados de prefixo/sufixo; get
  combina out.back com in.back.

* Problemas e reducoes:
  + Minimo/maximo em janela deslizante.
  + dp[i]=min(dp[j]) com j em [i-k,i-1] (knapsack limitado).
  + Fila com gcd/min/matriz/composicao sem inverso.
  + Agregado em fila com push e pop.

Cuidados: em QueueAgg a operacao NAO precisa ser comutativa (ordem
  preservada). Para max na janela troque >= por <= no while.
Catalogo: Estruturas de dados.
Digitacao: 26 linhas | media.
*****************************LATEX_DESC_END*/
