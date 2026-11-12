// Aliens trick / WQS binary search (lambda optimization) generico
//
// O que faz: se f(k) = melhor custo usando EXATAMENTE k itens eh CONVEXA
//   (minimizacao), acha f(K) resolvendo apenas o problema sem restricao de k
//   com uma penalidade lambda por item: g(L) = min_k f(k) + L*k.
// Quando usar: "Catalogo > Busca binaria e otimizacao" (Aliens): exatamente
//   k subarrays disjuntos, MST com k arestas vermelhas, particionar em k
//   blocos com custo quadrangular, k trocas em acoes.
// Complexidade: O(log(range) * custo de eval).
// Uso: aliens(K, lo, hi, eval): eval(L) devolve pair<ll,ll>{g(L), cnt} onde
//   cnt = MAIOR numero de itens entre as solucoes otimas (desempate!).
//   Retorna f(K). L inteiro em [lo, hi]; use lo<=-(max |custo|) .. hi>=max
//   (para minimizacao com f crescente em k, L tipicamente negativo para
//   forcar mais itens). Ver exemplo no fim.
//   MAXIMIZACAO: negue os custos e a resposta.
// Cuidados: provar/testar convexidade (compare f(k) de brute p/ k pequeno).
//   O desempate (cnt maximo) PRECISA ser consistente no eval (compare
//   (custo, -cnt) no DP). Resposta = g(L) - L*K, nao g(L). Se K for maior que
//   o maximo possivel de itens, a resposta eh invalida.
// Exemplo (particionar a em K blocos, custo do bloco = (soma)^2, dp O(n^2)):
//   eval(L): dp[i] = min_j dp[j].first + (S[i]-S[j])^2 + L, pares
//   (valor, -cnt) comparados lexicograficamente; cnt = -second.
ll aliens(ll K, ll lo, ll hi, function<pair<ll,ll>(ll)> eval) {
	// menor L tal que cnt(L) <= K (cnt eh nao crescente em L)
	while (lo < hi) {
		ll mid = lo + (hi - lo) / 2; // piso (hi-lo >= 0)
		if (eval(mid).second <= K) hi = mid; else lo = mid + 1;
	}
	return eval(lo).first - lo * K;
}
