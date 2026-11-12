// Segtree lazy generica (ACL) - update em range e max_right
struct S { ll sum; ll len; };           // no
struct F { ll add; };                   // tag
S op(S a, S b) { return {a.sum + b.sum, a.len + b.len}; }
S e() { return {0, 0}; }
S mapping(F f, S s) { return {s.sum + f.add * s.len, s.len}; }
F comp(F f, F g) { return {f.add + g.add}; } // f depois de g
F fid() { return {0}; }
// ---- fim da parte editavel ----
struct LazySeg {
    int n; vector<S> t; vector<F> z;
    LazySeg(int n) : LazySeg(vector<S>(n, S{0, 1})) {}
    LazySeg(const vector<S>& a) : n(a.size()), t(4 * max<int>(1, a.size())), z(4 * max<int>(1, a.size()), fid()) {
        if (n) build(1, 0, n, a);
    }
    void build(int o, int lo, int hi, const vector<S>& a) {
        if (hi - lo == 1) { t[o] = a[lo]; return; }
        int m = (lo + hi) / 2;
        build(2 * o, lo, m, a); build(2 * o + 1, m, hi, a);
        t[o] = op(t[2 * o], t[2 * o + 1]);
    }
    void ap(int o, F f) { t[o] = mapping(f, t[o]); z[o] = comp(f, z[o]); }
    void push(int o) { ap(2 * o, z[o]); ap(2 * o + 1, z[o]); z[o] = fid(); }
    void upd(int o, int lo, int hi, int l, int r, F f) {
        if (r <= lo || hi <= l) return;
        if (l <= lo && hi <= r) { ap(o, f); return; }
        push(o);
        int m = (lo + hi) / 2;
        upd(2 * o, lo, m, l, r, f); upd(2 * o + 1, m, hi, l, r, f);
        t[o] = op(t[2 * o], t[2 * o + 1]);
    }
    S qry(int o, int lo, int hi, int l, int r) {
        if (r <= lo || hi <= l) return e();
        if (l <= lo && hi <= r) return t[o];
        push(o);
        int m = (lo + hi) / 2;
        return op(qry(2 * o, lo, m, l, r), qry(2 * o + 1, m, hi, l, r));
    }
    void apply(int l, int r, F f) { upd(1, 0, n, l, r, f); }
    S query(int l, int r) { return qry(1, 0, n, l, r); }
    S get(int p) { return query(p, p + 1); }
    void set(int p, S v) { setp(1, 0, n, p, v); }
    void setp(int o, int lo, int hi, int p, S v) {
        if (hi - lo == 1) { t[o] = v; return; }
        push(o);
        int m = (lo + hi) / 2;
        if (p < m) setp(2 * o, lo, m, p, v); else setp(2 * o + 1, m, hi, p, v);
        t[o] = op(t[2 * o], t[2 * o + 1]);
    }
    // max_right: pred monotona (pred(e()) true). Devolve r tal que pred(prod[l,r))
    // e true e r e o maior possivel (n se vale ate o fim).
    template<class P> int max_right(int l, P pred) {
        S acc = e();
        return mr(1, 0, n, l, acc, pred);
    }
    template<class P> int mr(int o, int lo, int hi, int l, S& acc, P& pred) {
        if (hi <= l) return n;
        if (l <= lo) {
            S nw = op(acc, t[o]);
            if (pred(nw)) { acc = nw; return n; }
            if (hi - lo == 1) return lo; // esta folha quebra o predicado
        }
        push(o);
        int m = (lo + hi) / 2;
        int r = mr(2 * o, lo, m, l, acc, pred);
        if (r < n) return r;
        return mr(2 * o + 1, m, hi, l, acc, pred);
    }
};
/*LATEX_DESC_BEGIN***************************
-> **Segtree Lazy Generica (ACL)**
Update em intervalo aplicando tag F e query de intervalo com monoide S, com
tags que se compoem; inclui max_right por descida. 0-based, [l, r).

Complexidade: O(log n) por op; build O(n).
Uso:
  // edite S, F, op, e, mapping, comp, fid no topo
  LazySeg s(vector<S>);
  s.apply(l, r, f);        // [l, r)
  S q = s.query(l, r);
  s.set(p, v); s.get(p);
  int r = s.max_right(l, pred);  // maior r com pred(prod[l,r)), n no fim

* Sobre o codigo:
  t[o] guarda o monoide e z[o] a tag pendente. ap aplica mapping e comp;
  push propaga para os filhos. mr desce devolvendo o maior prefixo valido.

* Problemas e reducoes:
  + Range add + range sum/max.
  + Range assignment + range sum (com flag "tem tag" em F).
  + Range affine (a*x + b) + soma.
  + max_right: maior prefixo com predicado monotonico (ex.: soma <= limite).

Cuidados: S precisa carregar o tamanho (len) se mapping depender dele.
  comp(f, g) aplica g primeiro e depois f (f e a tag mais recente).
  Persistente com lazy: veja seg_persist.
Catalogo: Estruturas de dados (Lazy, descida).
Digitacao: 68 linhas | dificil. Atalho: ok.
*****************************LATEX_DESC_END*/
