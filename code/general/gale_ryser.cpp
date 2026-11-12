// Matriz 0/1 com somas de linhas e colunas dadas (Gale-Ryser) e canto noroeste
//
// O que faz: constroi matriz 0/1 com somas r[i] (linhas) e c[j] (colunas), ou diz que nao existe;
//            canto noroeste para valores inteiros nao negativos (transporte).
// Quando usar: grafo bipartido com graus dados; "preencha a matriz com somas por linha/coluna".
//              Catalogo > Construtivos e interativos (Matriz 0/1 com somas, Grafo bipartido com graus dados)
// Complexidade: O(n m log m) para construcao gulosa
// Uso: bool ok = galeRyser(r, c, M);  M[i][j] em {0,1}.   northWest(r, c) -> matriz com <= n+m-1 entradas nao nulas (sum r == sum c).
// Cuidados: sum(r) deve ser igual a sum(c). Construcao: para cada linha, liga as colunas de maior soma restante.
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
        if (r[i] == 0) i++; else j++;    // se ambos zeram, avanca so a linha (ainda ha coluna com 0, passa depois)
    }
    return M;
}
