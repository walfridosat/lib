// Mochila de moedas: minimo de moedas para um valor
//
// O que faz: dp[i] = minimo de moedas (uso ilimitado) para somar i.
// Quando usar: Catalogo > DP (Mochila/moedas). "menor numero de moedas", troco ilimitado.
// Complexidade: O(target * |coins|) tempo, O(target) memoria.
// Uso: dp_coins(coins, target) -> minimo de moedas, ou -1 se impossivel. 0-based.
// Cuidados: INF = target + 1 (nunca use MAXN como infinito); ignore moedas <= 0.
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
