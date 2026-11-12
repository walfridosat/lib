// Wavelet matrix - k-esimo e contagens em range
struct WM {
    int n, LOG; vector<vector<int>> c0; vector<int> zeros;
    WM(vector<int> a, int LOG = 20) : n(a.size()), LOG(LOG), c0(LOG, vector<int>(a.size() + 1)), zeros(LOG) {
        for (int lv = LOG - 1; lv >= 0; lv--) {
            vector<int> b0, b1;
            for (int i = 0; i < n; i++) {
                bool bit = a[i] >> lv & 1;
                c0[lv][i + 1] = c0[lv][i] + !bit;
                (bit ? b1 : b0).push_back(a[i]);
            }
            zeros[lv] = b0.size();
            a = b0; a.insert(a.end(), b1.begin(), b1.end()); // zeros primeiro, estavel
        }
    }
    int kth(int l, int r, int k) { // k-esimo menor (0-based) em [l, r)
        int res = 0;
        for (int lv = LOG - 1; lv >= 0; lv--) {
            int z = c0[lv][r] - c0[lv][l];
            if (k < z) { l = c0[lv][l]; r = c0[lv][r]; }
            else { k -= z; res |= 1 << lv; l = zeros[lv] + l - c0[lv][l]; r = zeros[lv] + r - c0[lv][r]; }
        }
        return res;
    }
    int less(int l, int r, int x) { // #{a[i] < x}
        if (x >= (1 << LOG)) return r - l;
        if (x <= 0) return 0;
        int res = 0;
        for (int lv = LOG - 1; lv >= 0; lv--) {
            int z = c0[lv][r] - c0[lv][l];
            if (x >> lv & 1) { res += z; l = zeros[lv] + l - c0[lv][l]; r = zeros[lv] + r - c0[lv][r]; }
            else { l = c0[lv][l]; r = c0[lv][r]; }
        }
        return res;
    }
    int range(int l, int r, int lo, int hi) { return less(l, r, hi + 1) - less(l, r, lo); }
    int eq(int l, int r, int x) { return range(l, r, x, x); }
};
/*LATEX_DESC_BEGIN***************************
-> **Wavelet Matrix**
Sobre array estatico de inteiros >= 0: k-esimo menor, contar < x, contar em
[lo,hi] e contar igual a x, tudo em [l, r). 0-based.

Complexidade: build O(n LOG), query O(LOG); memoria n*LOG ints.
Uso:
  WM w(a, LOG = 20);        // valores em [0, 2^LOG); comprima se maiores
  int q = w.kth(l, r, k);   // k-esimo menor, k 0-based
  int a = w.less(l, r, x);  // #{a[i] < x}
  int b = w.range(l, r, lo, hi);  // valores em [lo, hi]
  int c = w.eq(l, r, x);    // #{a[i] == x}

* Sobre o codigo:
  c0[lv][i] conta zeros ate i no nivel lv; zeros[lv] e o total de zeros.
  Cada nivel particiona estavelmente os valores pelo bit; kth/less descem
  usando as contagens para remapear l e r.

* Problemas e reducoes:
  + k-esimo menor em [l, r] online.
  + Contar valores < x ou em [lo, hi].
  + Quantil/mediana de subarray.
  + Contar iguais a x (via range(x, x)).

Cuidados: valores negativos exigem offset ou compressao. Maior <= x ou menor
  >= x: combine less e kth (ex.: kth(l, r, less(l, r, x + 1) - 1)).
Catalogo: Estruturas de dados (Wavelet tree/matrix).
Digitacao: 37 linhas | media. Atalho: ok.
*****************************LATEX_DESC_END*/
