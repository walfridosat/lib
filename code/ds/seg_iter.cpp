// Segtree iterativa (bottom-up) com monoide generico (nao comutativo ok)
//
// O que faz: update pontual e query de intervalo com qualquer operacao
//   associativa (soma, min, gcd, composicao de funcoes, matriz, hash...).
// Quando usar: Catalogo > Estruturas de dados (Segtree nao comutativa,
//   iterativa bottom-up, no como monoide). Sem update em intervalo.
// Complexidade: build O(n), update/query O(log n). 2-3x mais rapida que recursiva.
// Uso: Seg<T,F> s(n, id, f);  // T tipo, id = elemento neutro, f(a,b)
//   C++17 deduz: Seg s(n, (ll)0, [](ll a, ll b){return a+b;});
//   s.set(p, v) (0-based, substitui); s.query(l, r) intervalo [l, r) meio-aberto;
//   s.t[p+n] le a folha p. Build em O(n): preencha s.t[n+i], chame s.build().
// Cuidados: f(a,b) deve ser na ORDEM esquerda->direita. query vazia (l>=r)
//   devolve id. Nos maiores (struct): ver code/ds/seg_nodes.cpp.
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
