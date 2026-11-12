// Knuth optimization (DP em intervalo)
//
// O que faz: dp[l][r] = min_{l<=k<r} dp[l][k] + dp[k+1][r] + w(l,r) em O(n^2) usando opt[l][r-1] <= opt[l][r] <= opt[l+1][r].
// Quando usar: Catalogo > DP > "Knuth (intervalo)", "DP em intervalo classica O(n^3)", arvore de busca binaria otima,
//   juntar pilhas/arquivos adjacentes com custo = soma do intervalo.
// Complexidade: O(n^2) tempo e memoria.
// Uso: knuth(a) com a[0..n-1]; w(l,r) = soma a[l..r] (prefix sums). Retorna custo minimo de juntar tudo. 0-based.
// Cuidados: w precisa satisfazer quadrangulo (w(a,c)+w(b,d) <= w(a,d)+w(b,c)) e ser monotono em intervalos.
//   Se so quer a resposta e w e soma, Garsia-Wachs/Hu-Tucker faz O(n log n). Memoria n^2 ll: n=5000 ~ 200MB (cuidado).
ll knuth(const vector<ll>& a){
    int n = a.size();
    vector<ll> P(n+1, 0);
    for(int i = 0; i < n; i++) P[i+1] = P[i] + a[i];
    auto w = [&](int l, int r){ return P[r+1] - P[l]; };   // custo de juntar [l,r]
    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    vector<vector<int>> opt(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++) opt[i][i] = i;               // dp[i][i] = 0 (um bloco so)
    for(int len = 2; len <= n; len++){
        for(int l = 0; l + len - 1 < n; l++){
            int r = l + len - 1;
            dp[l][r] = LLONG_MAX;
            // k varia em [opt[l][r-1], opt[l+1][r]], com k < r
            for(int k = opt[l][r-1]; k <= min(opt[l+1][r], r-1); k++){
                ll v = dp[l][k] + dp[k+1][r] + w(l, r);
                if(v < dp[l][r]){ dp[l][r] = v; opt[l][r] = k; }
            }
        }
    }
    return n ? dp[0][n-1] : 0;
}
