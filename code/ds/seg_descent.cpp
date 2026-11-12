// Segtree com descida - first_ge, last_ge e kth
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
/*LATEX_DESC_BEGIN***************************
-> **Segtree com Descida**
Segtree de maximo com update de ponto e buscas first_ge/last_ge por descida;
segunda arvore de soma com k-esimo. Tudo O(log n), 0-based.

Complexidade: O(log n) por operacao.
Uso:
  SegMax s(n); s.set(i, v);
  int a = s.first_ge(l, x);  // menor i >= l com a[i] >= x, ou -1
  int b = s.last_ge(r, x);   // maior i <= r com a[i] >= x, ou -1
  SegSum t(n); t.add(i, v);
  int k = t.kth(k);          // menor i com soma[0..i] >= k (k >= 1), ou -1

* Sobre o codigo:
  fg desce pela esquerda quando o no tem maximo >= x e o intervalo alcanca l;
  lg faz o espelho pela direita. kth desce a arvore de soma comparando o filho
  esquerdo com o restante k.

* Problemas e reducoes:
  + Primeiro i >= l com a[i] >= x (first_ge).
  + Ultimo i <= r com a[i] >= x (last_ge).
  + K-esimo prefixo com soma >= k (kth).
  + Primeiro prefixo <= 0: adapte a descida para o minimo.
  + MEX: marque presencas e ache o primeiro zero.

Cuidados: tamanho interno potencia de 2; folhas extras valem -INF/0. Para min
  troque max por min e >= por <=.
Catalogo: Estruturas de dados.
Digitacao: 32 linhas | media. Atalho: ok.
*****************************LATEX_DESC_END*/
