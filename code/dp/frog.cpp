// Frog: custo minimo pulando de 1 a k posicoes
//
// O que faz: dp[i] = min_{1<=j<=k} dp[i-j] + |a[i]-a[i-j]|.
// Quando usar: Catalogo > DP (Frog). "sapo" com saltos 1..k; array de custos 0-based.
// Complexidade: O(n*k) tempo, O(n) memoria.
// Uso: dp_frog(a, k=2) -> custo minimo de 0 ate n-1.
// Cuidados: n = 0 devolve 0; INF = LLONG_MAX/4 para nao estourar na soma.
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
