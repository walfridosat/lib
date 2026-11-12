// BIT 2D
//
// O que faz: update pontual (soma) e soma em retangulo numa grade n x m.
// Quando usar: Catalogo > Estruturas de dados (BIT 2D, dominancia 2D,
//   contar pontos em retangulo online). Com coordenadas esparsas grandes
//   comprima offline ou use code/ds/seg2d.cpp (interna dinamica).
// Complexidade: O(log n * log m) por operacao; memoria O(n*m).
// Uso: 1-based. BIT2D b(n,m); b.add(x,y,v); b.query(x1,y1,x2,y2) (inclusivo).
// Cuidados: memoria n*m longs (n*m <= ~2e7). Para range-add 2D precisaria
//   de 4 BITs (nao incluido).
struct BIT2D {
    int n, m; vector<vector<ll>> t;
    BIT2D(int n = 0, int m = 0) : n(n), m(m), t(n + 1, vector<ll>(m + 1, 0)) {}
    void add(int x, int y, ll v) {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= m; j += j & -j) t[i][j] += v;
    }
    ll pre(int x, int y) {
        ll s = 0;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j) s += t[i][j];
        return s;
    }
    ll query(int x1, int y1, int x2, int y2) {
        return pre(x2, y2) - pre(x1 - 1, y2) - pre(x2, y1 - 1) + pre(x1 - 1, y1 - 1);
    }
};
