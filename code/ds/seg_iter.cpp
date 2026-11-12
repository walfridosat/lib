// Segtree iterativa - monoide generico (nao comutativo ok)
template<class T, class F> struct Seg {
    int n; T id; F f; vector<T> t;
    Seg(int n, T id, F f) : n(n), id(id), f(f), t(2 * n, id) {}
    void build() { for (int i = n - 1; i > 0; i--) t[i] = f(t[2 * i], t[2 * i + 1]); }
    void set(int p, T v) {
        for (t[p += n] = v; p > 1; p >>= 1) t[p >> 1] = f(t[p & ~1], t[p | 1]);
    }
    T query(int l, int r) { // [l, r)
        T rl = id, rr = id; // resl e resr separados por causa da nao comutatividade
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) rl = f(rl, t[l++]);
            if (r & 1) rr = f(t[--r], rr);
        }
        return f(rl, rr);
    }
};
/*LATEX_DESC_BEGIN***************************
-> **Segtree Iterativa Generica**
Update de ponto e query de intervalo para qualquer operacao associativa
(soma, min, gcd, composicao de funcoes, matriz, hash), inclusive nao comutativa.

Complexidade: build O(n), update/query O(log n). 2-3x mais rapida que recursiva.
Uso:
  Seg<T, F> s(n, id, f);   // T tipo, id neutro, f(a, b)
  Seg s(n, (ll)0, [](ll a, ll b){ return a + b; });  // C++17 deduz
  s.set(p, v);             // 0-based, substitui
  T q = s.query(l, r);      // [l, r) meio-aberto
  s.t[p + n] = x; s.build();  // build O(n)

* Sobre o codigo:
  Arvore em array 2n, folhas em [n, 2n). query acumula rl e rr separados para
  respeitar a ordem esquerda->direita; set sobe recombinando pais.

* Problemas e reducoes:
  + Soma/min/max/gcd em range com update de ponto.
  + Composicao de funcoes (afim, matriz) em ordem.
  + String/vector hashing em range.
  + Base para segtree de monoides com nos customizados (seg_nodes.cpp).

Cuidados: f(a,b) na ordem esquerda->direita. Query vazia (l >= r) devolve id.
  Nos maiores (struct) veja code/ds/seg_nodes.cpp.
Catalogo: Estruturas de dados (Segtree nao comutativa, iterativa).
Digitacao: 16 linhas | facil. Atalho: ok.
*****************************LATEX_DESC_END*/
