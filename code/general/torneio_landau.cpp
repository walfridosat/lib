// Torneio de Landau - pontuacoes dadas e construcao
bool landau(const vector<int>& s, vector<vector<int>>& W) {
    int n = s.size(); W.assign(n, vector<int>(n, 0));
    ll tot = 0; for (int x : s) tot += x;
    if (tot != (ll)n * (n - 1) / 2) return false;
    vector<int> ord(n); iota(ord.begin(), ord.end(), 0);
    vector<int> sc(s);
    // remove o vertice de menor pontuacao restante
    vector<int> alive(ord);
    while (alive.size() > 1) {
        sort(alive.begin(), alive.end(), [&](int a, int b) { return sc[a] < sc[b]; });
        int v = alive[0], k = sc[v], m = alive.size() - 1;     // v tem k vitorias entre os m outros
        if (k > m || k < 0) return false;
        // v perde para m-k e vence os k restantes
        for (int idx = 1; idx <= m; idx++) {
            int u = alive[idx];
            if (idx <= m - k) { W[u][v] = 1; sc[u]--; }        // u vence v: gasta uma vitoria de u
            else W[v][u] = 1;                                   // v vence u
        }
        for (int idx = 1; idx <= m; idx++) if (sc[alive[idx]] < 0) return false;
        alive.erase(alive.begin());
    }
    return sc[alive[0]] == 0;
}
/*LATEX_DESC_BEGIN***************************
-> **Torneio com Pontuacoes Dadas (Landau)**
Decide se uma sequencia de pontuacoes e de um torneio e constroi o torneio.
W[i][j] = 1 se i vence j.

Complexidade: O(n^2 log n)
Uso:
  bool ok = landau(s, W);  // s indexada pelos times

* Sobre o codigo:
  Condicao: ordenada crescente, sum dos k menores >= C(k,2) para todo k,
  com igualdade em k = n.
  Constroi removendo o time de menor pontuacao: ele perde para os m-k de
  menor pontuacao restante e vence os k restantes.

* Problemas e reducoes:
  + n times com s_i vitorias cada: decidir e construir o torneio.

Cuidados: a construcao usa a remocao do menor; W deve ser zerado no inicio.
Catalogo: Construtivos e interativos (Torneio com sequencia de pontuacao)
Digitacao: 23 linhas | media.
*****************************LATEX_DESC_END*/
