// Edit distance (Levenshtein) - distancia e reconstrucao
int edit_dist(const string& a, const string& b, string& ops){
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    for(int i = 0; i <= n; i++) dp[i][0] = i;
    for(int j = 0; j <= m; j++) dp[0][j] = j;
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++)
        dp[i][j] = min({dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1] + (a[i-1] != b[j-1])});
    ops = "";
    int i = n, j = m;
    while(i > 0 || j > 0){                                   // refaz o caminho de tras para frente
        if(i > 0 && j > 0 && dp[i][j] == dp[i-1][j-1] + (a[i-1] != b[j-1])){
            ops += (a[i-1] == b[j-1]) ? 'M' : 'S'; i--; j--;
        } else if(i > 0 && dp[i][j] == dp[i-1][j] + 1){ ops += 'D'; i--; }
        else { ops += 'I'; j--; }
    }
    reverse(ops.begin(), ops.end());
    return dp[n][m];
}
int edit_band(const string& a, const string& b, int k){
    int n = a.size(), m = b.size();
    if(abs(n - m) > k) return k + 1;
    const int INF = 1e9;
    // dp[i][j] guardado em indice j-i+k (0..2k)
    vector<int> prv(2*k+1, INF), cur(2*k+1, INF);
    for(int j = 0; j <= min(m, k); j++) prv[j + k] = j;     // linha i=0
    for(int i = 1; i <= n; i++){
        fill(cur.begin(), cur.end(), INF);
        for(int d = -k; d <= k; d++){
            int j = i + d; if(j < 0 || j > m) continue;
            int best = INF;
            if(j == 0) best = i;
            else {
                best = prv[d + k] + (a[i-1] != b[j-1]);      // diagonal: (i-1,j-1) tem mesmo d
                if(d + 1 <= k) best = min(best, prv[d + 1 + k] + 1);   // (i-1,j): d+1
                if(d - 1 >= -k) best = min(best, cur[d - 1 + k] + 1);  // (i,j-1): d-1
            }
            cur[d + k] = min(best, INF);
        }
        swap(prv, cur);
    }
    int r = prv[m - n + k];
    return r > k ? k + 1 : r;
}
/*LATEX_DESC_BEGIN***************************
-> **Edit distance (Levenshtein) e versao em faixa**
edit_dist: distancia minima (inserir/remover/trocar) entre a e b, com uma
sequencia de operacoes. edit_band: so verifica se a distancia e <= k.

Complexidade: edit_dist O(nm) tempo/memoria; edit_band O((n+m) k).
Uso:
  int d = edit_dist(a, b, ops);   // ops: 'M' igual, 'S' troca, 'I' insere, 'D' remove
  int e = edit_band(a, b, k);     // distancia se <= k, senao k+1

* Sobre o codigo:
  dp[i][j] = distancia entre a[0..i) e b[0..j). A recorrencia pega remocao,
  insercao ou troca. A reconstrucao volta de (n,m) para (0,0) escolhendo a
  transicao que gerou dp[i][j] e inverte ops. edit_band guarda so a diagonal
  j-i em [-k,k], no indice j-i+k.

* Problemas e reducoes:
  + Distancia de edicao com custo unitario por operacao.
  + Testar se duas strings diferem em no maximo k edicoes (edit_band).
  + Alinhamento de sequencias com substituicao, insercao e remocao.

Cuidados: memoria n*m ints (5000x5000 = 100MB); para so o valor use 2 linhas.
  edit_band exige |n-m| <= k. Pesos diferentes: troque os "+1". Myers bitset
  nao incluido.
Catalogo: DP > LCS/edit distance / reconstrucao do caminho.
Digitacao: 42 linhas | media. Atalho: para so o valor, descarte a matriz e use
  duas linhas (ou a banda).
*****************************LATEX_DESC_END*/
