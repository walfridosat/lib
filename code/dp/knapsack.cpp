// Mochila 0/1
//
// O que faz: valor maximo com peso total <= w, cada item no maximo uma vez.
// Quando usar: Catalogo > DP (Mochila 0/1). Pesos inteiros nao negativos.
// Complexidade: O(n*w) tempo, O(w) memoria.
// Uso: knapsack(peso, valor, w) -> valor maximo. 0-based.
// Cuidados: itens com peso > w sao ignorados; w = 0 e valido.
ll knapsack(const vector<ll>& peso, const vector<ll>& valor, ll w) {
    vector<ll> dp(w + 1, 0);
    for (size_t i = 0; i < peso.size(); i++)
        for (ll j = w; j >= peso[i]; j--)
            dp[j] = max(dp[j], dp[j - peso[i]] + valor[i]);
    return dp[w];
}
