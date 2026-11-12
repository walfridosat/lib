// Aliens trick (WQS) - otimiza DP convexo em k
ll aliens(ll K, ll lo, ll hi, function<pair<ll,ll>(ll)> eval) {
	// menor L tal que cnt(L) <= K (cnt eh nao crescente em L)
	while (lo < hi) {
		ll mid = lo + (hi - lo) / 2; // piso (hi-lo >= 0)
		if (eval(mid).second <= K) hi = mid; else lo = mid + 1;
	}
	return eval(lo).first - lo * K;
}
/*LATEX_DESC_BEGIN***************************
-> **Aliens trick (WQS binary search)**
Acha f(K) para f(k) convexa em k resolvendo o problema sem restricao com
penalidade lambda por item: g(L) = min_k f(k) + L*k. Sem indexacao.

Complexidade: O(log(range) * custo de uma avaliacao)
Uso:
  ll ans = aliens(K, lo, hi, [&](ll L) { return eval(L); });
  eval(L) -> pair<ll,ll>{g(L), cnt}; cnt = MAIOR numero de itens entre as
  solucoes otimas (desempate). Retorna f(K); resposta interna = g(L) - L*K.
  L inteiro em [lo, hi]; lo <= -(max |custo|), hi >= max.
  MINIMIZACAO: com f crescente em k, L tipicamente negativo forca mais itens.
  MAXIMIZACAO: negue os custos e a resposta.
  Ex.: eval(L) faz dp[i] = min_j dp[j].first + (S[i]-S[j])^2 + L,
  comparando pares (valor, -cnt) lexicograficamente; cnt = -second.

* Sobre o codigo:
  Binaria em L: menor L tal que cnt(L) <= K (cnt nao crescente em L).
  Cada eval resolve o problema com custo + L por item escolhido e devolve
  (valor penalizado, numero de itens). A resposta real e g(L) - L*K.

* Problemas e reducoes:
  + Exatamente k subarrays disjuntos com custo soma de quadrados (particionar em k blocos).
  + Exatamente k subarrays disjuntos com custo aditivo qualquer (f(k) convexa).
  + MST com exatamente k arestas de uma cor: penalize essas arestas com L.
  + Escolher exatamente k itens com custo convexo em k.
  + k transacoes/trocas em acoes maximizando lucro (negue os custos).

Cuidados: prove/teste a convexidade (compare f(k) com brute para k pequeno).
  O desempate (cnt maximo) precisa ser consistente no eval: compare
  (custo, -cnt) lexicograficamente no DP. Resposta = g(L) - L*K, nao g(L).
  Se K for maior que o maximo possivel de itens, a resposta e invalida.
Catalogo: Busca binaria e otimizacao.
Digitacao: 8 linhas | media. Atalho: sem empate, eval pode devolver ll e a
  comparacao (valor, -cnt) some.
*****************************LATEX_DESC_END*/
