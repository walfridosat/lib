// Busca binaria paralela - queries monotonicas no tempo
template<class R, class A, class O>
vector<int> pbs(int T, int Q, R reset, A addev, O ok) {
	vector<int> lo(Q, 0), hi(Q, T); // resposta em [lo, hi]; hi==T significa "nunca"
	vector<vector<int>> at(T + 1);
	while (true) {
		bool ch = false;
		for (auto& v : at) v.clear();
		for (int q = 0; q < Q; q++) if (lo[q] < hi[q]) { at[(lo[q] + hi[q]) / 2].push_back(q); ch = true; }
		if (!ch) break;
		reset();
		for (int t = 0; t < T; t++) {
			addev(t);
			for (int q : at[t]) { if (ok(q)) hi[q] = t; else lo[q] = t + 1; }
		}
	}
	return lo;
}
/*LATEX_DESC_BEGIN***************************
-> **Busca binaria paralela**
Para Q queries "primeiro tempo t em que pred(query) vale", com uma
estrutura que so avanca no tempo, responde todas em O(log T) passadas.

Complexidade: O((T + Q) log T * custo de evento/consulta).
Uso:
  vector<int> ans = pbs(T, Q, reset, addev, ok);
  reset()    // zera a estrutura
  addev(t)   // aplica o evento t (0..T-1)
  ok(q)      // true se a query q ja esta satisfeita no estado atual
  ans[q] = menor t (0..T-1) com ok(q) apos os eventos 0..t, ou T se nunca.
  Ex. DSU: reset: d=DSU(n); addev: d.join(ea[t],eb[t]);
           ok: d.find(u[q])==d.find(v[q]).

* Sobre o codigo:
  Cada query guarda lo/hi; as queries sao agrupadas pelo mid atual.
  Em cada nivel os eventos 0..T-1 sao aplicados uma vez e cada ok(q)
  decide se a resposta esta em [lo,mid] ou [mid+1,hi].

* Problemas e reducoes:
  + Primeiro instante em que u e v ficam conectados (DSU).
  + Quando a cidade i recebe >= k meteoros (BIT).
  + Primeira vez que uma condicao vale com estrutura incremental.
  + Queries de conectividade offline por tempo.

Cuidados: pred precisa ser monotono no tempo. Cada nivel aplica os eventos
  em ordem 0..T-1 uma unica vez. Se a estrutura nao zera barato, use a
  variante D&C com rollback (resolva(lo,hi,queries)).
Catalogo: Busca binaria e otimizacao.
Digitacao: 17 linhas | media.
*****************************LATEX_DESC_END*/
