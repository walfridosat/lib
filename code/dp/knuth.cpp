// Knuth optimization - DP em intervalo O(n^2)
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
            // k em [opt[l][r-1], opt[l+1][r]], k < r
            for(int k = opt[l][r-1]; k <= min(opt[l+1][r], r-1); k++){
                ll v = dp[l][k] + dp[k+1][r] + w(l, r);
                if(v < dp[l][r]){ dp[l][r] = v; opt[l][r] = k; }
            }
        }
    }
    return n ? dp[0][n-1] : 0;
}
/*LATEX_DESC_BEGIN***************************
-> **Knuth optimization (DP em intervalo)**
dp[l][r] = min_{l<=k<r} dp[l][k] + dp[k+1][r] + w(l,r) em O(n^2), usando
opt[l][r-1] <= opt[l][r] <= opt[l+1][r], 0-based.

Complexidade: O(n^2) tempo e memoria.
Uso:
  ll cost = knuth(a);   // w(l,r) = soma de a[l..r], custo de juntar tudo

* Sobre o codigo:
  O intervalo [l,r] e dividido em [l,k] e [k+1,r]; opt guarda o melhor k. A
  monotonicidade de opt reduz o laco de k de O(n) para O(1) amortizado. w usa
  prefix sums.

* Problemas e reducoes:
  + Arvore de busca binaria otima (custo de acesso).
  + Juntar pilhas/arquivos adjacentes com custo = soma do intervalo.
  + DP em intervalo com quadrangulo e custo aditivo.

Cuidados: w precisa satisfazer a desigualdade do quadrangulo e ser monotonica
  em intervalos. Memoria n^2 ll: n = 5000 ~ 200MB. Se so quer a resposta e w
  e soma, Garsia-Wachs/Hu-Tucker faz O(n log n).
Catalogo: DP > Knuth (intervalo) / DP em intervalo classica O(n^3).
Digitacao: 20 linhas | media.
*****************************LATEX_DESC_END*/
