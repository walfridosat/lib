// Sparse table - minimo em intervalo estatico
struct SparseMin {
    vector<vector<ll>> t;
    vector<int> lg;
    SparseMin(const vector<ll>& a) {
        int n = a.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        int K = n ? lg[n] + 1 : 1;
        t.assign(K, vector<ll>(n));
        if (n) t[0] = a;
        for (int j = 1; j < K; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                t[j][i] = min(t[j - 1][i], t[j - 1][i + (1 << (j - 1))]);
    }
    ll query(int l, int r) const {
        int j = lg[r - l + 1];
        return min(t[j][l], t[j][r - (1 << j) + 1]);
    }
};
/*LATEX_DESC_BEGIN***************************
-> **Sparse Table de Minimo**
Pre-processa um array estatico e responde min(a[l..r]) em O(1). 0-based.

Complexidade: build O(n log n), memoria O(n log n), query O(1).
Uso:
  SparseMin st(a);
  ll mn = st.query(l, r);   // 0 <= l <= r < n

* Sobre o codigo:
  t[j][i] = minimo de 2^j posicoes a partir de i; lg precalcula o piso do log.
  A query cobre [l, r] com dois blocos de tamanho 2^j que se sobrepoem.

* Problemas e reducoes:
  + RMQ estatico de min/max com muitas consultas.
  + LCA O(1) via Euler tour + profundidade.
  + gcd em intervalo (operacao idempotente).
  + OR/AND em intervalo.

Cuidados: so vale para operacoes idempotentes (min, max, gcd, OR, AND).
Catalogo: Estruturas de dados e queries (Sparse table).
Digitacao: 19 linhas | facil. Atalho: ok.
*****************************LATEX_DESC_END*/
