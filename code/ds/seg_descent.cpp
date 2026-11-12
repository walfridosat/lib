// Segtree com descida: primeiro i>=l com a[i]>=x, ultimo i<=r, k-esimo 1
//
// O que faz: segtree de max (point update) com first_ge/last_ge em O(log n),
//   mais segtree de soma com k-esimo (kth) por descida.
// Quando usar: Catalogo > Estruturas de dados (Segtree com descida em vez
//   de binaria+query; "primeiro i>=l com a_i>=x"; k-esimo 1; primeiro
//   prefixo <= 0; salto com condicao; MEX).
// Complexidade: O(log n) por operacao.
// Uso: SegMax s(n); s.set(i,v) 0-based; s.first_ge(l,x) -> menor i>=l com
//   a[i]>=x ou -1; s.last_ge(r,x) -> maior i<=r com a[i]>=x ou -1.
//   SegSum t(n); t.add(i,v); t.kth(k) -> menor i com soma[0..i] >= k (k>=1,
//   valores >=0) ou -1. Para min troque max por min e >= por <=.
// Cuidados: tamanho interno e potencia de 2; folhas extras = -INF/0.
struct SegMax {
    int n, N; vector<ll> t;
    SegMax(int n) : n(n) { N = 1; while (N < n) N <<= 1; t.assign(2 * N, LLONG_MIN); }
    void set(int p, ll v) { for (t[p += N] = v; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]); }
    int first_ge(int l, ll x) { return fg(1, 0, N, l, x); }
    int fg(int o, int lo, int hi, int l, ll x) {
        if (hi <= l || t[o] < x) return -1;
        if (hi - lo == 1) return lo;
        int m = (lo + hi) / 2;
        int r = fg(2 * o, lo, m, l, x);
        return r != -1 ? r : fg(2 * o + 1, m, hi, l, x);
    }
    int last_ge(int r, ll x) { return lg(1, 0, N, r, x); }
    int lg(int o, int lo, int hi, int r, ll x) {
        if (lo > r || t[o] < x) return -1;
        if (hi - lo == 1) return lo;
        int m = (lo + hi) / 2;
        int res = lg(2 * o + 1, m, hi, r, x);
        return res != -1 ? res : lg(2 * o, lo, m, r, x);
    }
};
struct SegSum {
    int n, N; vector<ll> t;
    SegSum(int n) : n(n) { N = 1; while (N < n) N <<= 1; t.assign(2 * N, 0); }
    void add(int p, ll v) { for (p += N; p; p >>= 1) t[p] += v; }
    int kth(ll k) { // menor i com soma[0..i] >= k
        if (k > t[1] || k < 1) return -1;
        int o = 1;
        while (o < N) { o <<= 1; if (t[o] < k) k -= t[o++]; }
        return o - N;
    }
};
