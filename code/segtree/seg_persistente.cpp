// Segtree persistente generica - point update gera versao nova, query em qualquer versao
template<class Node> struct PSeg {
    int n; vector<Node> t; vector<int> L, R;      // no 0 = vazio (Node())
    PSeg(int n) : n(n), t(1), L(1), R(1) {}
    int cp(int p) { t.push_back(t[p]), L.push_back(L[p]), R.push_back(R[p]); return t.size() - 1; }
    template<class T> int build(const vector<T>& v, int l = 0, int r = -1) {
        if (r < 0) r = n - 1;
        int q = cp(0);
        if (l == r) { t[q] = Node(v[l]); return q; }
        int m = (l + r) / 2, a = build(v, l, m), b = build(v, m + 1, r);
        L[q] = a, R[q] = b, t[q] = t[a] + t[b];
        return q;
    }
    template<class V> int upd(int p, int i, V v, int l = 0, int r = -1) { // devolve a raiz nova
        if (r < 0) r = n - 1;
        int q = cp(p);
        if (l == r) { t[q].apply(v); return q; }
        int m = (l + r) / 2;
        if (i <= m) { int x = upd(L[p], i, v, l, m); L[q] = x; }
        else { int x = upd(R[p], i, v, m + 1, r); R[q] = x; }
        t[q] = t[L[q]] + t[R[q]];
        return q;
    }
    Node qry(int p, int a, int b, int l = 0, int r = -1) {
        if (r < 0) r = n - 1;
        if (!p || b < l || r < a) return Node();
        if (a <= l && r <= b) return t[p];
        int m = (l + r) / 2;
        return qry(L[p], a, b, l, m) + qry(R[p], a, b, m + 1, r);
    }
};
// Node: o mesmo de code/segtree/seg.cpp (Node(), Node(v), apply(v), operator+).

/* BEGIN kth
    // k-esimo menor (1-based) em a[l..r]: ru = raiz da versao l, rv = raiz da versao r+1,
    // onde a versao i+1 = versao i + "cnt[a_i] += 1" (a_i comprimido em [0, n)). Node = soma.
    // uso: int idx = s.kth(raiz[l], raiz[r + 1], k);  valor = valores_comprimidos[idx]
    int kth(int u, int v, ll k, int l = 0, int r = -1) {
        if (r < 0) r = n - 1;
        if (l == r) return l;
        int m = (l + r) / 2; ll c = t[L[v]].s - t[L[u]].s;
        return k <= c ? kth(L[u], L[v], k, l, m) : kth(R[u], R[v], k - c, m + 1, r);
    }
END kth */
/*LATEX_DESC_BEGIN***************************
-> **Segtree persistente generica**
Cada update copia so o caminho raiz-folha (log n nos) e devolve a raiz da versao nova;
as versoes antigas continuam validas. 0-indexed.

Complexidade: upd O(log n) tempo e memoria | qry O(log n) | build O(n)
Uso:
  PSeg<Node> s(n);
  vector<int> raiz = {s.build(v)};            // ou {0}: versao 0 = tudo Node()
  raiz.push_back(s.upd(raiz.back(), i, val)); // versao nova
  Node x = s.qry(raiz[k], a, b);              // query na versao k

* Sobre o codigo:
  t, L, R sao vetores paralelos; o no 0 e o vazio e e filho de si mesmo (L[0] = R[0] = 0),
  entao descer por um caminho que nunca existiu so devolve Node().
  cp(p) clona o no p; upd clona o caminho e religa o filho que mudou.

* Problemas e reducoes:
  + k-esimo menor em a[l..r] online: versao i = prefixo a[0..i) como contagem por valor;
    diferenca de duas versoes = contagem em [l, r]; snippet kth.
  + Quantos a_i <= x em a[l..r] online: qry(raiz[r+1], 0, x) - qry(raiz[l], 0, x).
  + Distintos em a[l..r] online: versao r marca 1 na ultima ocorrencia de cada valor
    (e zera a anterior); resposta = soma de [l, r] na versao r.
  + Desfazer / voltar no tempo ("estado apos a operacao k"): guarde as raizes.
  + Caminhos em arvore: versao do filho = versao do pai + a_v; caminho u-v com
    raiz[u] + raiz[v] - raiz[lca] - raiz[pai(lca)] (k-esimo no caminho).

Cuidados: memoria ~ n * 4 + Q * (log n + 1) nos; faca reserve. Persistente com lazy:
  tag permanente (nao empurre; some as tags no caminho da query).
Catalogo: Estruturas de dados e queries.
Digitacao: 30 linhas | media.
*****************************LATEX_DESC_END*/
