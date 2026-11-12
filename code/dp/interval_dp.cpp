// DP em intervalo: exemplos classicos (baloes, impressora estranha, jogo em intervalo, circular)
//
// O que faz: moldes de dp[l][r] O(n^3):
//   burst_balloons: maximo de moedas estourando baloes (escolhe o ULTIMO a estourar no intervalo).
//   strange_printer: minimo de turnos para imprimir a string (cada turno pinta um segmento com 1 letra).
//   game_interval: melhor diferenca (primeiro - segundo) pegando das pontas do array.
// Quando usar: Catalogo > DP > "DP em intervalo classica O(n^3)", "Intervalo: escolha o ultimo elemento",
//   "Intervalo com string", "Intervalo circular" (duplique o array e use dp[i][i+n-1]), "DP em jogos".
// Complexidade: burst/printer O(n^3); game O(n^2).
// Uso: burst_balloons(a) (a[i] valores, 0-based); strange_printer(s); game_interval(a).
// Cuidados: burst: coloca sentinelas 1 nas pontas; dp[l][r] com l,r exclusivos (nenhum bala em l e r). printer: remova
//   repetidos consecutivos antes. Para circular: duplicar o array e limitar r-l<n.
ll burst_balloons(vector<ll> a){
    a.insert(a.begin(), 1); a.push_back(1);                 // sentinelas
    int n = a.size();
    vector<vector<ll>> dp(n, vector<ll>(n, 0));            // dp[l][r]: estourar tudo estritamente entre l e r
    for(int len = 2; len < n; len++)
        for(int l = 0; l + len < n; l++){
            int r = l + len;
            for(int k = l+1; k < r; k++)                    // k = ultimo balao estourado em (l,r)
                dp[l][r] = max(dp[l][r], dp[l][k] + dp[k][r] + a[l]*a[k]*a[r]);
        }
    return dp[0][n-1];
}
int strange_printer(string s){
    string t;
    for(char c : s) if(t.empty() || t.back() != c) t += c;  // colapsa repetidos
    int n = t.size();
    if(n == 0) return 0;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++) dp[i][i] = 1;
    for(int len = 2; len <= n; len++)
        for(int l = 0; l + len - 1 < n; l++){
            int r = l + len - 1;
            dp[l][r] = dp[l+1][r] + 1;                      // imprime t[l] sozinho
            for(int k = l+1; k <= r; k++) if(t[k] == t[l])  // t[l] e t[k] pintados no mesmo turno
                dp[l][r] = min(dp[l][r], dp[l][k-1] + (k+1 <= r ? dp[k+1][r] : 0));
        }
    return dp[0][n-1];
}
ll game_interval(const vector<ll>& a){
    int n = a.size();
    vector<vector<ll>> dp(n, vector<ll>(n, 0));            // dp[l][r] = melhor (meu - dele) jogando agora em [l,r]
    for(int i = 0; i < n; i++) dp[i][i] = a[i];
    for(int len = 2; len <= n; len++)
        for(int l = 0; l + len - 1 < n; l++){
            int r = l + len - 1;
            dp[l][r] = max(a[l] - dp[l+1][r], a[r] - dp[l][r-1]);
        }
    return n ? dp[0][n-1] : 0;
}
