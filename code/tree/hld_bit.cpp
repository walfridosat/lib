// HLD com BIT range-add / range-sum (soma e add em caminho e subarvore)
//
// O que faz: add x em todos os vertices de um caminho / subarvore e soma sobre
//   caminho / subarvore, usando dois Fenwicks (add em intervalo, soma em intervalo).
// Quando usar: "adicione x no caminho, some caminho" (Catalogo > Arvores,
//   "HLD offline com 2 Fenwicks"). Mais leve que segtree lazy.
// Complexidade: O(log^2 n) por caminho, O(log n) por subarvore.
// Uso: HLDBit h(g, raiz); h.path_add(u,v,x); h.path_sum(u,v); h.sub_add(v,x);
//   h.sub_sum(v); h.pt_add(v,x). Valores iniciais 0. 0-based.
// Cuidados: valores nos vertices. Para arestas guarde no filho e exclua o LCA
//   (use pos[lca]+1 no ultimo trecho). Overflow: ll.
struct HLDBit {
    int n;
    vector<int> par, dep, sz, heavy, head, pos;
    vector<ll> b1, b2;                       // BIT range-add range-sum
    HLDBit(const vector<vector<int>>& g, int r = 0) : n(g.size()), par(n, -1), dep(n, 0), sz(n, 1), heavy(n, -1), head(n), pos(n), b1(n + 2), b2(n + 2) {
        vector<int> pre = {r};
        for (int i = 0; i < (int)pre.size(); i++) {
            int v = pre[i];
            for (int w : g[v]) if (w != par[v]) { par[w] = v; dep[w] = dep[v] + 1; pre.push_back(w); }
        }
        for (int i = n - 1; i > 0; i--) sz[par[pre[i]]] += sz[pre[i]];
        for (int i = n - 1; i > 0; i--) { int v = pre[i], p = par[v]; if (heavy[p] < 0 || sz[v] > sz[heavy[p]]) heavy[p] = v; }
        int t = 0; vector<int> st = {r}; head[r] = r;
        while (!st.empty()) {
            int v = st.back(); st.pop_back(); pos[v] = t++;
            for (int w : g[v]) if (w != par[v] && w != heavy[v]) { head[w] = w; st.push_back(w); }
            if (heavy[v] >= 0) { head[heavy[v]] = head[v]; st.push_back(heavy[v]); }
        }
    }
    void upd(int i, ll x) { ll y = x * (i - 1); for (int j = i; j <= n; j += j & -j) b1[j] += x, b2[j] += y; }
    ll pre(int i) { ll s = 0, s2 = 0; for (int j = i; j > 0; j -= j & -j) s += b1[j], s2 += b2[j]; return s * i - s2; }
    void add(int l, int r, ll x) { upd(l + 1, x); upd(r + 2, -x); }       // posicoes 0-based [l,r]
    ll sum(int l, int r) { return pre(r + 1) - pre(l); }
    void pt_add(int v, ll x) { add(pos[v], pos[v], x); }
    void sub_add(int v, ll x) { add(pos[v], pos[v] + sz[v] - 1, x); }
    ll sub_sum(int v) { return sum(pos[v], pos[v] + sz[v] - 1); }
    void path_add(int u, int v, ll x) {
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            add(pos[head[u]], pos[u], x); u = par[head[u]];
        }
        if (pos[u] > pos[v]) swap(u, v);
        add(pos[u], pos[v], x);
    }
    ll path_sum(int u, int v) {
        ll s = 0;
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            s += sum(pos[head[u]], pos[u]); u = par[head[u]];
        }
        if (pos[u] > pos[v]) swap(u, v);
        return s + sum(pos[u], pos[v]);
    }
};
