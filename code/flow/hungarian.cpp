// Hungarian - problema de atribuicao de custo minimo
//
// O que faz: dada matriz de custos n x m (n <= m), atribui cada linha a uma coluna
//   distinta minimizando o custo total. Devolve tambem o potencial (dual).
// Quando usar: "atribuir n tarefas a n pessoas com custo", matching ponderado bipartido
//   (Catalogo > Grafos "Matching maximo ponderado", Otimizacao > "Problema de atribuicao").
// Complexidade: O(n^2 m).
// Uso: ll c=hungarian(a, ans); a 0-indexed n x m (vector<vector<ll>>), ans[i] = coluna
//   da linha i. Maximizar: passe -a. Matching perfeito exigido: arestas proibidas = INF
//   grande (ex. 1e12) e confira que c < INF.
// Cuidados: exige n <= m (transponha se preciso). Custos negativos ok. Para k pares
//   exatos use mcmf com k augmentacoes.
ll hungarian(const vector<vector<ll>>& a, vector<int>& ans) {
    int n = a.size(), m = a[0].size(); const ll INF = LLONG_MAX / 4;
    vector<ll> u(n + 1), v(m + 1); vector<int> p(m + 1), way(m + 1);
    for (int i = 1; i <= n; i++) {
        p[0] = i; int j0 = 0;
        vector<ll> minv(m + 1, INF); vector<char> used(m + 1, false);
        do {
            used[j0] = true; int i0 = p[j0], j1 = 0; ll delta = INF;
            for (int j = 1; j <= m; j++) if (!used[j]) {
                ll cur = a[i0 - 1][j - 1] - u[i0] - v[j];
                if (cur < minv[j]) minv[j] = cur, way[j] = j0;
                if (minv[j] < delta) delta = minv[j], j1 = j;
            }
            for (int j = 0; j <= m; j++)
                if (used[j]) u[p[j]] += delta, v[j] -= delta;
                else minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do { int j1 = way[j0]; p[j0] = p[j1]; j0 = j1; } while (j0);
    }
    ans.assign(n, -1);
    for (int j = 1; j <= m; j++) if (p[j]) ans[p[j] - 1] = j - 1;
    return -v[0];
}
