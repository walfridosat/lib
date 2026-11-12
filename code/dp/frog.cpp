// frog - custo minimo pulando de 1 a k posicoes
ll dp_frog(const vector<ll>& a, int k = 2) {
    int n = a.size();
    if (n == 0) return 0;
    const ll INF = LLONG_MAX / 4;
    vector<ll> dp(n, INF);
    dp[0] = 0;
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= k && j <= i; j++)
            dp[i] = min(dp[i], dp[i - j] + abs(a[i] - a[i - j]));
    return dp[n - 1];
}
/*LATEX_DESC_BEGIN***************************
-> **frog - custo minimo com saltos de 1..k**
dp[i] = min_{1<=j<=k} dp[i-j] + |a[i]-a[i-j]|, 0-based.

Complexidade: O(n*k) tempo, O(n) memoria.
Uso:
  ll ans = dp_frog(a, 2);   // k = numero maximo de posicoes por salto

* Sobre o codigo:
  DP direta: para cada posicao i, testa os k saltos anteriores e cobra o modulo
  da diferenca de altura. dp[0] = 0 e o resto comeca em INF.

* Problemas e reducoes:
  + Sapo que pula ate k pedras com custo |altura_i - altura_j|.
  + Caminho minimo em DAG com arestas de i para i+1..i+k.

Cuidados: n = 0 devolve 0; INF = LLONG_MAX/4 evita overflow na soma.
Catalogo: DP (Frog).
Digitacao: 11 linhas | facil.
*****************************LATEX_DESC_END*/
