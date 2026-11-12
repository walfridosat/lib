// Gale-Ryser e canto noroeste - matriz 0/1 com somas de linhas e colunas dadas
bool galeRyser(const vector<int>& r, const vector<int>& c, vector<vector<int>>& M) {
    int n = r.size(), m = c.size();
    M.assign(n, vector<int>(m, 0));
    if (accumulate(r.begin(), r.end(), 0LL) != accumulate(c.begin(), c.end(), 0LL)) return false;
    vector<int> rem(c); vector<int> id(m); iota(id.begin(), id.end(), 0);
    for (int i = 0; i < n; i++) {
        if (r[i] > m) return false;
        sort(id.begin(), id.end(), [&](int a, int b) { return rem[a] > rem[b]; });
        for (int k = 0; k < r[i]; k++) {
            if (rem[id[k]] <= 0) return false;
            rem[id[k]]--; M[i][id[k]] = 1;
        }
    }
    for (int x : rem) if (x) return false;
    return true;
}
vector<vector<ll>> northWest(vector<ll> r, vector<ll> c) {
    int n = r.size(), m = c.size(); vector<vector<ll>> M(n, vector<ll>(m, 0));
    for (int i = 0, j = 0; i < n && j < m;) {
        ll t = min(r[i], c[j]); M[i][j] = t; r[i] -= t; c[j] -= t;
        if (r[i] == 0) i++; else j++;    // se ambos zeram, avanca so a linha
    }
    return M;
}
/*LATEX_DESC_BEGIN***************************
-> **Gale-Ryser / Canto Noroeste**
Constroi matriz 0/1 com somas r[i] nas linhas e c[j] nas colunas, ou diz que nao
existe; northWest resolve transporte inteiro nao negativo (<= n+m-1 nao nulas).

Complexidade: O(n m log m) na construcao gulosa
Uso:
  bool ok = galeRyser(r, c, M);  // M[i][j] em {0,1}
  vector<vector<ll>> M = northWest(r, c);  // sum(r) == sum(c)

* Sobre o codigo:
  Para cada linha, ordena as colunas pela soma restante e liga as maiores.
  northWest avanca linha ou coluna conforme o menor saldo zera.

* Problemas e reducoes:
  + Grafo bipartido com graus dados: linhas x colunas com r e c.
  + Matriz 0/1 com somas de linha e coluna dadas.
  + Transporte: canto noroeste acha uma solucao basica viavel.

Cuidados: sum(r) deve ser igual a sum(c); no northWest, se ambos zeram avanca so a linha.
Catalogo: Construtivos e interativos (Matriz 0/1 com somas, Grafo bipartido com graus dados)
Digitacao: 24 linhas | media.
*****************************LATEX_DESC_END*/
