// Merge sort tree
//
// O que faz: cada no guarda seu intervalo ordenado; conta elementos < x,
//   <= x ou em [lo,hi] dentro de a[l..r).
// Quando usar: Catalogo > Estruturas de dados (Merge sort tree; contar
//   a_i <= x em [l, r]; k-esimo online via busca binaria no valor).
// Complexidade: build O(n log n); query O(log^2 n); memoria O(n log n).
// Uso: MST m(a) (vector<int>/ll, 0-based); m.less(l, r, x) = #{i in [l,r) : a[i] < x};
//   m.count(l, r, lo, hi) = #{a[i] in [lo,hi]}. Nao suporta update
//   (use BIT de BITs / ordered set por no se precisar).
// Cuidados: intervalo meio-aberto [l, r). Para sem log extra: fractional
//   cascading (nao incluido) ou wavelet (code/ds/wavelet.cpp).
struct MST {
    int n; vector<vector<ll>> t;
    MST(const vector<ll>& a) : n(a.size()), t(2 * a.size()) {
        for (int i = 0; i < n; i++) t[i + n] = {a[i]};
        for (int i = n - 1; i > 0; i--) { // operacao comutativa (contagem): ok para n qualquer
            t[i].resize(t[2 * i].size() + t[2 * i + 1].size());
            merge(t[2 * i].begin(), t[2 * i].end(), t[2 * i + 1].begin(), t[2 * i + 1].end(), t[i].begin());
        }
    }
    int less(int l, int r, ll x) { // #{a[i] < x}
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) { res += lower_bound(t[l].begin(), t[l].end(), x) - t[l].begin(); l++; }
            if (r & 1) { --r; res += lower_bound(t[r].begin(), t[r].end(), x) - t[r].begin(); }
        }
        return res;
    }
    int count(int l, int r, ll lo, ll hi) { return less(l, r, hi + 1) - less(l, r, lo); }
};
