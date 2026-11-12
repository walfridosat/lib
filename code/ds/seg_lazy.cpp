// Segtree com lazy generica (estilo ACL) + descida max_right
//
// O que faz: update em intervalo (aplica tag F) e query de intervalo (monoide S),
//   com tags que se compoem. Tambem max_right: maior r com pred(prod[l,r)) true.
// Quando usar: Catalogo > Estruturas de dados (Lazy para update em
//   intervalo, no como monoide de funcoes, descida na segtree).
//   Exemplos: add+soma, add+max, atribuicao+soma, afim+soma.
// Complexidade: O(log n) por op; build O(n).
// Uso: edite S/F/op/e/mapping/comp/fid no topo (exemplo: add em intervalo,
//   soma). LazySeg s(vector<S>); s.apply(l,r,f) [l,r) 0-based; s.query(l,r);
//   s.set(p,v); s.get(p); s.max_right(l, pred) -> indice r (n se vai ate o fim).
// Cuidados: S precisa carregar o tamanho (len) se mapping depende dele.
//   comp(f,g) = aplicar g PRIMEIRO e depois f (f mais recente). Para
//   atribuicao use flag "tem tag" em F. Persistente com lazy: ver seg_persist.
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
