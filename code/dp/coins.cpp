// coins - minimo de moedas para um valor
ll dp_coins(const vector<ll>& coins, ll target) {
    const ll INF = target + 1;
    vector<ll> dp(target + 1, INF);
    dp[0] = 0;
    for (ll i = 1; i <= target; i++)
        for (ll c : coins)
            if (c > 0 && c <= i && dp[i - c] + 1 < dp[i])
                dp[i] = dp[i - c] + 1;
    return dp[target] == INF ? -1 : dp[target];
}
/*LATEX_DESC_BEGIN***************************
-> **coins - minimo de moedas**
dp[i] = minimo de moedas (uso ilimitado) para somar i, 0-based.
Devolve -1 se a soma for impossivel.

Complexidade: O(target * |coins|) tempo, O(target) memoria.
Uso:
  ll r = dp_coins(coins, target);

* Sobre o codigo:
  DP classica de troco: para cada valor i, tenta a ultima moeda c e usa
  dp[i-c] + 1. Como as moedas sao ilimitadas, o laco de i e crescente.

* Problemas e reducoes:
  + Troco com numero minimo de moedas (moedas ilimitadas).
  + Caminho minimo em grafo implicito com arestas de tamanho c.

Cuidados: INF = target + 1 evita overflow e funciona como infinito; moedas <= 0
  sao ignoradas. Para contar formas, troque min por soma.
Catalogo: DP (mochila/moedas).
Digitacao: 10 linhas | facil.
*****************************LATEX_DESC_END*/
