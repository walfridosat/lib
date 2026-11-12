// Interval DP - exemplos classicos em O(n^3)
ll burst_balloons(vector<ll> a){
    a.insert(a.begin(), 1); a.push_back(1);                 // sentinelas
    int n = a.size();
    vector<vector<ll>> dp(n, vector<ll>(n, 0));            // dp[l][r]: estourar tudo entre l e r
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
    vector<vector<ll>> dp(n, vector<ll>(n, 0));            // melhor (meu - dele) em [l,r]
    for(int i = 0; i < n; i++) dp[i][i] = a[i];
    for(int len = 2; len <= n; len++)
        for(int l = 0; l + len - 1 < n; l++){
            int r = l + len - 1;
            dp[l][r] = max(a[l] - dp[l+1][r], a[r] - dp[l][r-1]);
        }
    return n ? dp[0][n-1] : 0;
}
/*LATEX_DESC_BEGIN***************************
-> **DP em intervalo - exemplos classicos**
Moldes de dp[l][r] O(n^3):
burst_balloons: maximo de moedas estourando baloes; strange_printer: minimo de
turnos para imprimir a string; game_interval: melhor diferenca pegando das pontas.

Complexidade: burst_balloons e strange_printer O(n^3); game_interval O(n^2).
Uso:
  ll a = burst_balloons(v);       // v[i] valores, 0-based
  int b = strange_printer(s);
  ll c = game_interval(v);

* Sobre o codigo:
  Em burst_balloons, escolhe-se o ULTIMO balao k estourado em (l,r), o que separa
  o problema em (l,k) e (k,r); sentinelas 1 nas pontas. Em strange_printer,
  colapsam-se repetidos e t[l] pode ser pintado junto com t[k] igual. Em
  game_interval, dp[l][r] = max(a[l] - dp[l+1][r], a[r] - dp[l][r-1]).

* Problemas e reducoes:
  + Estourar baloes maximizando moedas (escolha do ultimo).
  + Impressora estranha: minimo de turnos para pintar a string.
  + Jogo em intervalo pegando das pontas (diferenca otima).
  + Intervalo circular: duplique o array e limite r-l < n.
  + Remover caixas/palindromos com custo por intervalo.

Cuidados: burst usa dp[l][r] com l,r exclusivos e sentinelas; printer remove
  repetidos consecutivos antes. Para circular, duplique o array.
Catalogo: DP > DP em intervalo classica O(n^3) / intervalo circular.
Digitacao: 39 linhas | media.
*****************************LATEX_DESC_END*/
