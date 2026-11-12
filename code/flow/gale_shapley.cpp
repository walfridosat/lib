// Gale-Shapley - casamento estavel
//
// O que faz: n homens e n mulheres com listas de preferencia completas; devolve
//   casamento estavel otimo para quem propoe (homens).
// Quando usar: "casamento estavel", alocacao com preferencias, residentes/hospitais
//   (Catalogo > Grafos, emparelhamento).
// Complexidade: O(n^2).
// Uso: auto w = galeShapley(pm, pw); pm[i] = lista de mulheres de i por preferencia
//   (melhor primeiro), pw[j] = lista de homens de j. w[i] = mulher casada com o homem i.
//   0-indexed.
// Cuidados: listas completas e do mesmo tamanho n. Para capacidade >1 (hospitais) replique
//   o hospital em varias vagas com a mesma lista.
vector<int> galeShapley(const vector<vector<int>>& pm, const vector<vector<int>>& pw) {
    int n = pm.size();
    vector<vector<int>> rk(n, vector<int>(n)); // rk[j][i] = posicao do homem i para a mulher j
    for (int j = 0; j < n; j++) for (int k = 0; k < n; k++) rk[j][pw[j][k]] = k;
    vector<int> nxt(n, 0), wife(n, -1), husb(n, -1); queue<int> q;
    for (int i = 0; i < n; i++) q.push(i);
    while (!q.empty()) {
        int m = q.front(); q.pop();
        int w = pm[m][nxt[m]++];
        if (husb[w] < 0) husb[w] = m, wife[m] = w;
        else if (rk[w][m] < rk[w][husb[w]]) { // ela prefere m: o antigo volta a fila
            int old = husb[w]; wife[old] = -1; q.push(old);
            husb[w] = m; wife[m] = w;
        } else q.push(m);
    }
    return wife;
}
