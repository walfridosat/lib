// Maior soma de subconjunto <= t (subset sum otimizado)
//
// O que faz: dado w (pesos inteiros >= 0) e limite t, devolve o maior valor <= t
//            que e soma de um subconjunto. Ordena w e usa DP comprimida em 2*max(w).
// Quando usar: Catalogo > DP (Mochila/subset sum) quando t e grande mas os pesos sao
//            pequenos; para t pequeno use bitset (code/bits/bitset_subset_sum.cpp).
// Complexidade: O(n * W) apos ordenar, W = max(w); memoria O(W).
// Uso: int best = subset_sum(w, t) (w e copiado, pode passar o vetor original).
// Cuidados: assume pesos >= 0; se todos couberem, devolve o total; para reconstruir
//            o subconjunto e preciso guardar os pais (aqui so o valor).
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