// Segtree iterativa - soma, ponto e intervalo
struct IterSeg {
    int n;
    vector<ll> t;
    IterSeg(const vector<ll>& a) {
        n = 1; while (n < (int)a.size()) n <<= 1;
        t.assign(2 * n, 0);
        for (int i = 0; i < (int)a.size(); i++) t[n + i] = a[i];
        for (int i = n - 1; i >= 1; i--) t[i] = t[2 * i] + t[2 * i + 1];
    }
    void set(int p, ll v) {
        if (p < 0 || p >= n) return;
        t[p += n] = v;
        for (p >>= 1; p; p >>= 1) t[p] = t[2 * p] + t[2 * p + 1];
    }
    void add(int p, ll v) { if (p >= 0 && p < n) set(p, t[n + p] + v); }
    ll query(int l, int r) const { // [l, r)
        ll res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += t[l++];
            if (r & 1) res += t[--r];
        }
        return res;
    }
};
/*LATEX_DESC_BEGIN***************************
-> **Segtree Iterativa de Soma**
Arvore de soma com update de ponto e query de intervalo, ambos O(log n).
0-based; n arredondado para potencia de 2; versao minima e rapida.

Complexidade: O(n) para construir, O(log n) por operacao, O(n) memoria.
Uso:
  IterSeg st(a);
  st.add(i, x); st.set(i, x);
  ll s = st.query(l, r);   // soma em [l, r)

* Sobre o codigo:
  Folhas em [n, 2n); set sobe recombinando; add chama set(p, t[n+p]+v).
  query acumula os blocos da decomposicao iterativa de [l, r).

* Problemas e reducoes:
  + Soma/contagem em range com update de ponto.
  + Prefixo dinamico: query(0, r).
  + Para min/max nao inversivel use seg_lazy.cpp ou segtree.cpp.

Cuidados: indices fora de [0, n) sao ignorados em add/set; query exige l <= r.
Catalogo: Estruturas de dados e queries (Segtree).
Digitacao: 24 linhas | facil. Atalho: ok.
*****************************LATEX_DESC_END*/
