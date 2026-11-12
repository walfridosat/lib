// Disjoint sparse table
//
// O que faz: query de qualquer operacao ASSOCIATIVA (soma, produto mod, xor,
//   composicao de funcoes, matriz) em O(1), sem precisar ser idempotente.
// Quando usar: Catalogo > Estruturas de dados (Disjoint sparse table;
//   produto mod m em intervalo sem inverso; composicao estatica).
// Complexidade: build O(n log n), query O(1) (um f por query).
// Uso: DST d(a, f); d.q(l, r) com l<=r inclusivo, 0-based.
//   Ex.: DST d(a, [](ll x, ll y){ return x * y % MOD; });
// Cuidados: f associativa (ordem esquerda->direita respeitada, pode ser
//   nao comutativa). Memoria n log n elementos. Padding repete a.back().
template<class T, class F> struct DST {
    F f; int n, lg; vector<vector<T>> t; vector<T> a;
    DST(vector<T> v, F f) : f(f), a(v) {
        n = 1; lg = 0; while (n < (int)v.size()) n <<= 1, lg++;
        a.resize(n, v.back());
        t.assign(lg + 1, vector<T>(n));
        for (int h = 1; h <= lg; h++) { // nivel h: blocos de tamanho 2^h, metade 2^(h-1)
            int half = 1 << (h - 1);
            for (int s = 0; s < n; s += 1 << h) {
                int mid = s + half;
                t[h][mid - 1] = a[mid - 1];
                for (int i = mid - 2; i >= s; i--) t[h][i] = f(a[i], t[h][i + 1]);
                t[h][mid] = a[mid];
                for (int i = mid + 1; i < s + (1 << h); i++) t[h][i] = f(t[h][i - 1], a[i]);
            }
        }
    }
    T q(int l, int r) {
        if (l == r) return a[l];
        int h = 32 - __builtin_clz(l ^ r); // nivel em que l e r caem em metades diferentes
        return f(t[h][l], t[h][r]);
    }
};
