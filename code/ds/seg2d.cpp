// Segtree de segtrees (2D online): update de ponto, soma em retangulo
//
// O que faz: camada externa iterativa em x, cada no externo tem uma segtree
//   dinamica em y. add(x,y,v) e soma no retangulo [x1,x2) x [y1,y2).
// Quando usar: Catalogo > Estruturas de dados (Segtree de segtrees, BIT 2D
//   com coordenadas grandes, contar pontos em retangulo online com updates).
//   Para estatico/offline prefira sweep + BIT (ver bit.cpp, bit2d.cpp).
// Complexidade: O(log N * log M) por op; memoria O(q log N log M) nos.
// Uso: Seg2D s(N, M);  // x em [0,N), y em [0,M), M ate 1e9+
//   s.add(x, y, v); s.query(x1, y1, x2, y2);  // [x1,x2) x [y1,y2)
// Cuidados: memoria pesada (cerca de 2*q*logN*logM nos de 16 bytes);
//   para max/min com updates de aumento so troque soma por max (nao invertivel).
struct Seg2D {
    int N; ll M;
    vector<int> rt;                // raiz da segtree em y de cada no externo
    vector<int> L, R; vector<ll> C; // pool de nos (0 = nulo)
    Seg2D(int N, ll M) : N(N), M(M), rt(2 * N, 0), L(1, 0), R(1, 0), C(1, 0) {}
    int addY(int o, ll lo, ll hi, ll p, ll v) {
        if (!o) { o = L.size(); L.push_back(0); R.push_back(0); C.push_back(0); }
        C[o] += v;
        if (hi - lo > 1) {
            ll m = lo + (hi - lo) / 2;
            if (p < m) { int c = addY(L[o], lo, m, p, v); L[o] = c; }
            else { int c = addY(R[o], m, hi, p, v); R[o] = c; }
        }
        return o;
    }
    ll sumY(int o, ll lo, ll hi, ll l, ll r) {
        if (!o || r <= lo || hi <= l) return 0;
        if (l <= lo && hi <= r) return C[o];
        ll m = lo + (hi - lo) / 2;
        return sumY(L[o], lo, m, l, r) + sumY(R[o], m, hi, l, r);
    }
    void add(int x, ll y, ll v) {
        for (x += N; x >= 1; x >>= 1) { int c = addY(rt[x], 0, M, y, v); rt[x] = c; }
    }
    ll query(int x1, ll y1, int x2, ll y2) {
        ll s = 0;
        for (int l = x1 + N, r = x2 + N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) s += sumY(rt[l++], 0, M, y1, y2);
            if (r & 1) s += sumY(rt[--r], 0, M, y1, y2);
        }
        return s;
    }
};
