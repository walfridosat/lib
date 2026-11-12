// Prefixos 2D, diferencas 2D e maior submatriz de soma maxima
//
// O que faz: soma de retangulo em O(1); adicionar retangulo em O(1) (aplicar no fim); Kadane 2D.
// Quando usar: muitas adicoes em retangulos + leitura final; soma de submatriz; "maior soma de submatriz".
//              Catalogo > Arrays e guloso (Prefixo 2D e diferencas 2D, Maior soma de submatriz)
// Complexidade: O(nm) construir, O(1) consulta; Kadane 2D O(min(n,m)^2 * max(n,m))
// Uso: Pref2D P(g);  P.query(r1,c1,r2,c2) inclusivo, 0-based.
//      Diff2D D(n, m); D.add(r1,c1,r2,c2,v); auto res = D.build();  res[i][j].
//      maxSubmatrix(g) -> maior soma de submatriz nao vazia.
// Cuidados: indices 0-based inclusivos; vetor 1-based interno; soma pode estourar int.
struct Pref2D {
    int n, m; vector<vector<ll>> p;
    Pref2D(const vector<vector<ll>>& g) : n(g.size()), m(g.empty() ? 0 : g[0].size()), p(n + 1, vector<ll>(m + 1, 0)) {
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
            p[i + 1][j + 1] = g[i][j] + p[i][j + 1] + p[i + 1][j] - p[i][j];
    }
    ll query(int r1, int c1, int r2, int c2) const {
        return p[r2 + 1][c2 + 1] - p[r1][c2 + 1] - p[r2 + 1][c1] + p[r1][c1];
    }
};
struct Diff2D {
    int n, m; vector<vector<ll>> d;
    Diff2D(int n, int m) : n(n), m(m), d(n + 2, vector<ll>(m + 2, 0)) {}
    void add(int r1, int c1, int r2, int c2, ll v) {
        d[r1][c1] += v; d[r1][c2 + 1] -= v; d[r2 + 1][c1] -= v; d[r2 + 1][c2 + 1] += v;
    }
    vector<vector<ll>> build() {   // prefixo 2D das diferencas
        vector<vector<ll>> r(n, vector<ll>(m));
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
            if (i) d[i][j] += d[i - 1][j];
            if (j) d[i][j] += d[i][j - 1];
            if (i && j) d[i][j] -= d[i - 1][j - 1];
            r[i][j] = d[i][j];
        }
        return r;
    }
};
ll maxSubmatrix(vector<vector<ll>> g) {
    int n = g.size(), m = g[0].size();
    if (n > m) {                          // transpoe para que as linhas fixadas sejam o lado menor
        vector<vector<ll>> t(m, vector<ll>(n));
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) t[j][i] = g[i][j];
        g = t; swap(n, m);
    }
    ll best = LLONG_MIN;
    for (int a = 0; a < n; a++) {
        vector<ll> col(m, 0);
        for (int b = a; b < n; b++) {
            ll cur = 0;
            for (int j = 0; j < m; j++) {
                col[j] += g[b][j];
                cur = max(cur, 0LL) + col[j];     // Kadane (nao vazio)
                best = max(best, cur);
            }
        }
    }
    return best;
}
