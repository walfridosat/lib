// lcs - subsequencia comum maxima O(n*m)
int lcs(string a, string b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n][m];
}
/*LATEX_DESC_BEGIN***************************
-> **LCS classica O(n*m)**
dp[i][j] = LCS dos prefixos a[0..i) e b[0..j); devolve o comprimento, 0-based.

Complexidade: O(n*m) tempo e memoria (pode rolar para O(min(n,m))).
Uso:
  int k = lcs(a, b);

* Sobre o codigo:
  Se a[i-1] == b[j-1], dp[i][j] = dp[i-1][j-1] + 1; senao, o maximo entre
  descartar um caractere de a ou de b. As strings chegam por valor.

* Problemas e reducoes:
  + Maior subsequencia comum entre duas strings.
  + Distancia de edicao sem troca (so inserir/remover).
  + Alinhamento de sequencias.

Cuidados: para n*m grande use lcs_bitset.cpp. Para reconstruir a subsequencia,
  guarde os pais ou refaca o caminho. Strings por valor, sem risco de copia.
Catalogo: DP (strings / DP em duas strings).
Digitacao: 13 linhas | facil. Atalho: para so o comprimento, use duas linhas
  em vez da matriz inteira.
*****************************LATEX_DESC_END*/