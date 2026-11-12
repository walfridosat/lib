// Sparse table para minimo em intervalo estatico
//
// O que faz: pre-processa um array e responde min(a[l..r]) em O(1).
// Quando usar: Catalogo > Estruturas de dados e queries (Sparse table).
//   Array estatico, muitas consultas de min/max/gcd/OR/AND.
// Complexidade: build O(n log n), memoria O(n log n), query O(1).
// Uso: SparseMin st(a); st.query(l, r) com 0 <= l <= r < n.
// Cuidados: so vale para operacoes idempotentes (min, max, gcd, OR, AND).
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
