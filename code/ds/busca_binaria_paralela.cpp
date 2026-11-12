// Busca binaria paralela (por niveis)
//
// O que faz: para Q queries "primeiro tempo t em que pred(query) vale", com
//   uma estrutura que so avanca no tempo (add de eventos), responde todas
//   simulando os T eventos O(log T) vezes.
// Quando usar: "Catalogo > Busca binaria e otimizacao" (Binaria paralela):
//   "primeiro instante em que u e v conectam" (DSU), "quando a cidade i
//   recebe >= k de meteoros" (BIT), etc.
// Complexidade: O((T + Q) log T * custo de evento/consulta).
// Uso: ans = pbs(T, Q, reset, addev, ok):
//   reset()    -> zera a estrutura
//   addev(t)   -> aplica o evento t (0..T-1)
//   ok(q)      -> true se a query q ja esta satisfeita no estado atual
//   ans[q] = menor t (0..T-1) com ok(q) apos aplicar eventos 0..t, ou T se nunca.
//   Exemplo (DSU): reset: d=DSU(n); addev: d.join(ea[t],eb[t]); ok: d.find(u[q])==d.find(v[q]).
// Cuidados: pred precisa ser monotono no tempo. Cada nivel aplica os
//   eventos em ordem 0..T-1 uma unica vez. Se a estrutura nao zera barato,
//   use a variante D&C com rollback (resolva(lo,hi,queries)).
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
