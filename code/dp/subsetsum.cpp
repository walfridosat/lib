// subsetsum - maior soma de subconjunto <= t (Pisinger)
int subset_sum(vector<int> w, int t) {
	sort(w.begin(), w.end());
	int pref = 0, k = 0;
	int n = w.size();
	while (k < n and pref + w[k] <= t) pref += w[k++];
	if (k == n) return pref;
	int W = *max_element(w.begin(), w.end());
	vector<int> last, dp(2*W, -1);
	dp[W - (t-pref)] = k;
	for (int i = k; i < n; i++) {
		last = dp;
		for (int x = 0; x < W; x++) dp[x+w[i]] = max(dp[x+w[i]], last[x]);
		for (int x = 2*W - 1; x > W; x--)
			for (int j = max(0, last[x]); j < dp[x]; j++)
				dp[x-w[j]] = max(dp[x-w[j]], j);
	}
	int ans = t;
	while (dp[W - (t-ans)] < 0) ans--;
	return ans;
}
/*LATEX_DESC_BEGIN***************************
-> **Maior soma de subconjunto <= t (subset sum otimizado)**
Dado w (pesos inteiros >= 0) e limite t, devolve o maior valor <= t que e soma
de um subconjunto. Ordena w e comprime a DP em 2*max(w).

Complexidade: O(n * W) apos ordenar, W = max(w); memoria O(W).
Uso:
  int best = subset_sum(w, t);   // w e copiado, pode passar o original

* Sobre o codigo:
  Primeiro pega o guloso de itens pequenos ate passar de t. Se nao couberem
  todos, a DP trabalha em uma janela de largura 2*W: dp[x] guarda o maior indice
  de item usado para obter a soma correspondente. A resposta e o maior valor
  alcancavel <= t.

* Problemas e reducoes:
  + Subset sum quando t e grande mas os pesos sao pequenos.
  + Maior soma <= t com pesos nao negativos.
  + Mochila booleana com valores iguais aos pesos.

Cuidados: assume pesos >= 0; se todos couberem, devolve o total. Para
  reconstruir o subconjunto e preciso guardar os pais (aqui so o valor). Para t
  pequeno, um bitset e mais simples e rapido.
Catalogo: DP (Mochila/subset sum).
Digitacao: 20 linhas | dificil. Atalho: para t pequeno, use o bitset de
  code/dp/bitset_subset_sum.cpp.
*****************************LATEX_DESC_END*/