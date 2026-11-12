// CHT monotonico - deque para retas ordenadas
struct CHT {
	deque<pair<ll,ll>> d; // (m, b)
	// retas B (do meio) eh desnecessaria entre A e C?
	bool bad(const pair<ll,ll>& A, const pair<ll,ll>& B, const pair<ll,ll>& C) {
		// intersecao(A,C) <= intersecao(A,B)
		return (__int128)(C.second - A.second) * (A.first - B.first)
		    <= (__int128)(B.second - A.second) * (A.first - C.first);
	}
	void add(ll m, ll b) { // m estritamente menor que a anterior (min)
		if (!d.empty() && d.back().first == m) {
			if (d.back().second <= b) return;
			d.pop_back();
		}
		while (d.size() >= 2 && bad(d[d.size() - 2], d.back(), {m, b})) d.pop_back();
		d.push_back({m, b});
	}
	ll eval(int i, ll x) { return d[i].first * x + d[i].second; }
	ll query(ll x) { // binaria: o valor eh unimodal ao longo do hull
		int lo = 0, hi = d.size() - 1;
		while (lo < hi) {
			int mid = (lo + hi) / 2;
			if (eval(mid, x) >= eval(mid + 1, x)) lo = mid + 1; else hi = mid;
		}
		return eval(lo, x);
	}
	ll query_mono(ll x) { // x nao decrescente entre chamadas
		while (d.size() >= 2 && eval(0, x) >= eval(1, x)) d.pop_front();
		return eval(0, x);
	}
};
/*LATEX_DESC_BEGIN***************************
-> **CHT monotonico (deque)**
Mantem a envoltoria inferior de retas y=m*x+b inseridas com inclinacao
estritamente decrescente (minimo). x crescente -> ponteiro; arbitrario -> binaria.

Complexidade: O(n) total com ponteiro; O(log n) por query com binaria.
Uso:
  CHT h; h.add(m, b);      // m estritamente decrescente para minimo
  h.query(x)               // qualquer x, busca binaria
  h.query_mono(x)          // x nao decrescente, ponteiro O(1) amortizado
  MAXIMO com m crescente: add(-m,-b) e negue a resposta.

* Sobre o codigo:
  deque de retas; bad remove B quando a intersecao A-C vem antes da A-B
  ((b_C-b_A)*(m_A-m_B) <= (b_B-b_A)*(m_A-m_C), em __int128).
  query binaria porque o valor e unimodal ao longo do hull.

* Problemas e reducoes:
  + dp[i]=min_j(dp[j]+b[j]*a[i]) com b[j] e a[i] ordenados.
  + Otimizacao de DP com retas inseridas em ordem de inclinacao.
  + Maximo via negacao das retas.
  + Envoltoria de retas com consultas monotonas.

Cuidados: produtos em __int128 na checagem de intersecao (evita overflow).
  Inclinacoes iguais: mantem a de menor b (tratado). m*x+b deve caber em ll.
  Sem monotonicidade: code/ds/lichao.cpp ou cht_dinamico.cpp.
Catalogo: Busca binaria e otimizacao; Estruturas de dados.
Digitacao: 30 linhas | media. Atalho: se todas as consultas sao em x
  crescente, a query binaria pode sair e so query_mono fica.
*****************************LATEX_DESC_END*/
