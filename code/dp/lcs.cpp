// LCS classica O(n*m) (subsequencia comum maxima)
//
// O que faz: dp[i][j] = LCS dos prefixos a[0..i) e b[0..j); devolve o comprimento.
// Quando usar: Catalogo > DP (Strings/DP em duas strings). Para n*m grande use
//            code/string/bitset_match.cpp (lcs_bits) ou code/dp/lcs_bitset.cpp.
// Complexidade: O(n*m) tempo e memoria (pode rolar para O(min(n,m))).
// Uso: int k = lcs(a, b).
// Cuidados: copie as strings por valor ou use const& (aqui por valor, sem risco);
//            para reconstruir a subsequencia guarde os pais ou refaca o caminho.
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