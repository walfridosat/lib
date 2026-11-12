// Sparse table (RMQ O(1) para operacoes idempotentes) com indice
//
// O que faz: min/max estatico em O(1). Guarda INDICE do minimo (desempate:
//   mais a esquerda), entao devolve tambem "onde". Versao generica abaixo
//   para gcd/and/or.
// Quando usar: Catalogo > Estruturas de dados (Sparse table; sparse table de
//   indices; LCA O(1) via Euler tour; queries de gcd em intervalo).
// Complexidade: build O(n log n), query O(1).
// Uso: SparseIdx sp(a) (vector<ll>, 0-based); sp.arg(l, r) -> indice do
//   minimo em [l, r] inclusivo; sp.get(l, r) -> valor minimo.
//   Maximo: construa com a negado, ou troque a comparacao.
//   SparseOp<F> (gcd): SparseOp sp(a, [](ll x, ll y){return __gcd(x,y);}); sp.q(l,r)
// Cuidados: SO para operacao idempotente (min, max, gcd, and, or) - soma NAO.
//   Para soma/xor/produto: code/ds/disjoint_sparse.cpp. Guarda referencia
//   para a (nao destrua/modifique a).
struct SparseIdx {
    const vector<ll>& a; vector<vector<int>> t;
    int better(int i, int j) { return (a[j] < a[i]) ? j : i; } // empate fica com i (menor indice se i<j)
    SparseIdx(const vector<ll>& a) : a(a) {
        int n = a.size(), K = 32 - __builtin_clz(max(n, 1));
        t.assign(K, vector<int>(n));
        iota(t[0].begin(), t[0].end(), 0);
        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                t[k][i] = better(t[k - 1][i], t[k - 1][i + (1 << (k - 1))]);
    }
    int arg(int l, int r) { // [l, r] inclusivo
        int k = 31 - __builtin_clz(r - l + 1);
        return better(t[k][l], t[k][r - (1 << k) + 1]);
    }
    ll get(int l, int r) { return a[arg(l, r)]; }
};
template<class F> struct SparseOp {
    F f; vector<vector<ll>> t;
    SparseOp(const vector<ll>& a, F f) : f(f) {
        int n = a.size(), K = 32 - __builtin_clz(max(n, 1));
        t.assign(K, vector<ll>(n));
        t[0] = a;
        for (int k = 1; k < K; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                t[k][i] = f(t[k - 1][i], t[k - 1][i + (1 << (k - 1))]);
    }
    ll q(int l, int r) { // [l, r] inclusivo; sobrepoe dois blocos (idempotente)
        int k = 31 - __builtin_clz(r - l + 1);
        return f(t[k][l], t[k][r - (1 << k) + 1]);
    }
};
