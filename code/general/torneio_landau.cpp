// Torneio com pontuacoes dadas (Landau)
//
// O que faz: decide se uma sequencia de pontuacoes e de um torneio e constroi o torneio.
// Quando usar: "n times, cada um com s_i vitorias". Catalogo > Construtivos e interativos (Torneio com sequencia de pontuacao)
// Complexidade: O(n^2 log n)
// Uso: bool ok = landau(s, W);  W[i][j]=1 se i vence j (i != j). s indexada pelos times.
// Cuidados: condicao: ordenada crescente, soma dos k menores >= C(k,2) para todo k, com igualdade em k=n.
//           Construcao: o time de MAIOR pontuacao perde para s_max... aqui usamos a remocao do menor:
//           o time de menor pontuacao s vence os s times de menor pontuacao restantes e perde dos demais.
bool landau(const vector<int>& s, vector<vector<int>>& W) {
    int n = s.size(); W.assign(n, vector<int>(n, 0));
    ll tot = 0; for (int x : s) tot += x;
    if (tot != (ll)n * (n - 1) / 2) return false;
    vector<int> ord(n); iota(ord.begin(), ord.end(), 0);
    vector<int> sc(s);
    // processa removendo o vertice de menor pontuacao restante
    vector<int> alive(ord);
    while (alive.size() > 1) {
        sort(alive.begin(), alive.end(), [&](int a, int b) { return sc[a] < sc[b]; });
        int v = alive[0], k = sc[v], m = alive.size() - 1;     // v tem k vitorias entre os m outros
        if (k > m || k < 0) return false;
        // v vence os k de menor pontuacao restante entre os outros? Para manter viabilidade, v perde dos de menor pontuacao
        // e vence os de maior: v perde de m-k vertices (que ganham 1 ponto de v) e vence k.
        // Escolha: quem ganha de v sao os de MENOR pontuacao (precisam de pontos).
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
