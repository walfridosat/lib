// BIT 2D - soma em retangulo
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
/*LATEX_DESC_BEGIN***************************
-> **BIT 2D**
Update pontual (soma) e soma em retangulo numa grade n x m. Indexacao 1-based.

Complexidade: O(log n * log m) por operacao; memoria O(n*m).
Uso:
  BIT2D b(n, m); b.add(x, y, v);
  b.query(x1, y1, x2, y2)       // inclusivo

* Sobre o codigo:
  t[i][j] cobre (i-lowbit(i), i] x (j-lowbit(j), j].
  add e pre aninhados nos dois eixos; query usa inclusao-exclusao.

* Problemas e reducoes:
  + Contar pontos em retangulo online.
  + Soma de submatriz com updates pontuais.
  + Dominancia 2D (contar pontos com x <= X e y <= Y).
  + Contar pares/inversoes em duas dimensoes.

Cuidados: memoria n*m longs (n*m <= ~2e7). Para range-add 2D precisaria
  de 4 BITs (nao incluido). Coordenadas esparsas grandes: comprima offline
  ou use code/ds/seg2d.cpp (interna dinamica).
Catalogo: Estruturas de dados.
Digitacao: 17 linhas | facil.
*****************************LATEX_DESC_END*/
