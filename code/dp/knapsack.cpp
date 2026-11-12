// knapsack - mochila 0/1
ll knapsack(const vector<ll>& peso, const vector<ll>& valor, ll w) {
    vector<ll> dp(w + 1, 0);
    for (size_t i = 0; i < peso.size(); i++)
        for (ll j = w; j >= peso[i]; j--)
            dp[j] = max(dp[j], dp[j - peso[i]] + valor[i]);
    return dp[w];
}
/*LATEX_DESC_BEGIN***************************
-> **knapsack - mochila 0/1**
Valor maximo com peso total <= w, cada item usado no maximo uma vez, 0-based.

Complexidade: O(n*w) tempo, O(w) memoria.
Uso:
  ll best = knapsack(peso, valor, w);

* Sobre o codigo:
  dp[x] = melhor valor com capacidade x. Para cada item, o laco de x e
  decrescente, o que garante que o item seja usado no maximo uma vez.

* Problemas e reducoes:
  + Mochila 0/1 classica.
  + Subconjunto de peso maximo <= w quando o valor e o peso.
  + Escolha de itens com custo e beneficio, cada um uma vez.

Cuidados: itens com peso > w sao ignorados; w = 0 e valido. Pesos nao negativos.
Catalogo: DP (Mochila 0/1).
Digitacao: 7 linhas | facil.
*****************************LATEX_DESC_END*/
