// Heavy-Light Decomposition + segtree sobre monoide (caminho e subarvore)
//
// O que faz: decompoe a arvore em cadeias pesadas; vertices numerados em ordem de
//   DFS com filho pesado primeiro, entao cada cadeia E cada subarvore sao
//   intervalos contiguos de pos[]. HLDSeg<M> guarda um monoide em pos[] e
//   responde query de caminho (ate nao comutativo), subarvore e update pontual.
// Quando usar: queries/updates de caminho ou subarvore com updates
//   (Catalogo > Arvores, "HLD com segtree", "HLD: query nao comutativa",
//   "Arvore com updates em aresta" -> peso da aresta no filho).
// Complexidade: build O(n); caminho O(log^2 n); subarvore O(log n); LCA O(log n).
// Uso: HLD h(g, raiz);  h.lca(u,v);  h.pos[v], h.sz[v], h.head[v], h.par[v], h.dep[v].
//   Monoide M: typedef T; static T id(); static T op(T a,T b); static T rev(T a)
//   (rev inverte o sentido do segmento; identidade se op e comutativa).
//   HLDSeg<M> s(h, valores_por_vertice);
//   s.set(v, x); s.path(u,v,edges): valor do caminho u->v NA ORDEM u...v;
//   edges=true -> valores nas arestas guardados no filho (exclui o LCA);
//   s.subtree(v, edges).   0-based.
// Cuidados: para update de intervalo/lazy use pos[] com uma segtree lazy de ds/.
//   Sem recursao (DFS por pilha). Para path em ordem u->v o rev e necessario.
struct HLD {
    int n;
    vector<int> par, dep, sz, heavy, head, pos, ord;
    HLD(const vector<vector<int>>& g, int r = 0) : n(g.size()), par(n, -1), dep(n, 0), sz(n, 1), heavy(n, -1), head(n), pos(n), ord(n) {
        vector<int> pre = {r};
        for (int i = 0; i < (int)pre.size(); i++) {
            int v = pre[i];
            for (int w : g[v]) if (w != par[v]) { par[w] = v; dep[w] = dep[v] + 1; pre.push_back(w); }
        }
        for (int i = n - 1; i > 0; i--) {   // tamanhos de baixo para cima
            int v = pre[i]; sz[par[v]] += sz[v];
        }
        for (int i = n - 1; i > 0; i--) {
            int v = pre[i], p = par[v];
            if (heavy[p] < 0 || sz[v] > sz[heavy[p]]) heavy[p] = v;
        }
        int t = 0;
        vector<int> st = {r}; head[r] = r;
        while (!st.empty()) {               // preordem: filho pesado e o ultimo empilhado (sai primeiro)
            int v = st.back(); st.pop_back();
            pos[v] = t; ord[t++] = v;
            for (int w : g[v]) if (w != par[v] && w != heavy[v]) { head[w] = w; st.push_back(w); }
            if (heavy[v] >= 0) { head[heavy[v]] = head[v]; st.push_back(heavy[v]); }
        }
    }
    int lca(int u, int v) const {
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            u = par[head[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
    int dist(int u, int v) const { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
};

// exemplo de monoide: soma (comutativa)
struct MSum { typedef ll T; static T id() { return 0; } static T op(T a, T b) { return a + b; } static T rev(T a) { return a; } };
// exemplo de monoide: maximo
struct MMax { typedef ll T; static T id() { return LLONG_MIN; } static T op(T a, T b) { return max(a, b); } static T rev(T a) { return a; } };

template<class M> struct HLDSeg {
    typedef typename M::T T;
    const HLD& h; int n; vector<T> t;
    HLDSeg(const HLD& h_, const vector<T>& a) : h(h_), n(h_.n), t(2 * h_.n, M::id()) {
        for (int v = 0; v < n; v++) t[n + h.pos[v]] = a[v];
        for (int i = n - 1; i > 0; i--) t[i] = M::op(t[2*i], t[2*i+1]);
    }
    void set(int v, T x) {
        int i = h.pos[v] + n; t[i] = x;
        for (i >>= 1; i; i >>= 1) t[i] = M::op(t[2*i], t[2*i+1]);
    }
    T get(int v) const { return t[h.pos[v] + n]; }
    T seg(int l, int r) const {            // [l, r] em posicoes, ordem crescente de pos
        T a = M::id(), b = M::id();
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) a = M::op(a, t[l++]);
            if (r & 1) b = M::op(t[--r], b);
        }
        return M::op(a, b);
    }
    T subtree(int v, bool edges = false) const {
        int l = h.pos[v] + (edges ? 1 : 0), r = h.pos[v] + h.sz[v] - 1;
        return l > r ? M::id() : seg(l, r);
    }
    T path(int u, int v, bool edges = false) const {
        T L = M::id(), R = M::id();        // L: lado de u (ordem u->cima), R: lado de v (ordem cima->v)
        while (h.head[u] != h.head[v]) {
            if (h.dep[h.head[u]] >= h.dep[h.head[v]]) {
                L = M::op(L, M::rev(seg(h.pos[h.head[u]], h.pos[u]))); u = h.par[h.head[u]];
            } else {
                R = M::op(seg(h.pos[h.head[v]], h.pos[v]), R); v = h.par[h.head[v]];
            }
        }
        // mesma cadeia: o mais fundo tem pos maior
        if (h.pos[u] >= h.pos[v]) {
            int l = h.pos[v] + (edges ? 1 : 0);
            if (l <= h.pos[u]) L = M::op(L, M::rev(seg(l, h.pos[u])));
        } else {
            int l = h.pos[u] + (edges ? 1 : 0);
            if (l <= h.pos[v]) R = M::op(seg(l, h.pos[v]), R);
        }
        return M::op(L, R);
    }
};
