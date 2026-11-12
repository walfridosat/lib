// Merge sort tree - contagens em intervalo
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
/*LATEX_DESC_BEGIN***************************
-> **Merge Sort Tree**
Cada no guarda o intervalo ordenado; conta elementos < x, <= x ou em [lo,hi]
dentro de a[l..r). Array estatico, 0-based, intervalos [l, r).

Complexidade: build O(n log n); query O(log^2 n); memoria O(n log n).
Uso:
  MST m(a);                       // vector<ll>
  int q = m.less(l, r, x);        // #{i in [l,r) : a[i] < x}
  int p = m.count(l, r, lo, hi);  // #{a[i] in [lo,hi]}

* Sobre o codigo:
  Arvore iterativa 2n; a folha i+n tem {a[i]} e cada no interno e o merge
  ordenado dos filhos. A query decompoe [l,r) e faz lower_bound nos blocos,
  somando as contagens.

* Problemas e reducoes:
  + Contar a_i < x em [l,r) com less.
  + Contar a_i em [lo,hi] com count (inclusive nas pontas).
  + Contar a_i <= x: use less(l, r, x + 1).
  + k-esimo em [l,r] online: busca binaria no valor + less.

Cuidados: intervalo meio-aberto [l, r). Nao suporta update; para isso use
  BIT de BITs. Para evitar o log extra use wavelet (code/ds/wavelet.cpp).
Catalogo: Estruturas de dados.
Digitacao: 19 linhas | facil. Atalho: ok.
*****************************LATEX_DESC_END*/
