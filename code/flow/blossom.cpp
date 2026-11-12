// Blossom (Edmonds) - emparelhamento maximo em grafo geral
//
// O que faz: matching maximo em grafo nao bipartido, encolhendo ciclos impares (blossoms).
// Quando usar: "pareie jogadores/vertices" em grafo qualquer (Catalogo > Grafos
//   "Matching geral"; tamanho do maximo: Tutte-Berge). Em arvore basta guloso de folhas.
// Complexidade: O(V^3) (V buscas, cada O(V^2)); ok para V ~ 500..1000.
// Uso: Blossom b(n); b.add(u,v); int m=b.solve(); b.mt[v] = par de v (ou -1). 0-indexed.
// Cuidados: auto-lacos ignorados (v==to). Arestas duplicadas ok.
struct Blossom {
    int n; vector<vector<int>> g; vector<int> mt, p, base, q; vector<char> used, bl;
    Blossom(int n) : n(n), g(n), mt(n, -1), p(n), base(n), q(n), used(n), bl(n) {}
    void add(int u, int v) { if (u != v) g[u].push_back(v), g[v].push_back(u); }
    int lca(int a, int b) {
        vector<char> u(n, 0);
        for (;;) { a = base[a]; u[a] = 1; if (mt[a] < 0) break; a = p[mt[a]]; }
        for (;;) { b = base[b]; if (u[b]) return b; b = p[mt[b]]; }
    }
    void markPath(int v, int b, int ch) { // marca o caminho ate a base b do blossom
        while (base[v] != b) {
            bl[base[v]] = bl[base[mt[v]]] = 1;
            p[v] = ch; ch = mt[v]; v = p[mt[v]];
        }
    }
    int findPath(int root) { // BFS alternada; devolve o fim livre do caminho aumentante
        fill(used.begin(), used.end(), 0); fill(p.begin(), p.end(), -1);
        for (int i = 0; i < n; i++) base[i] = i;
        used[root] = 1; int qh = 0, qt = 0; q[qt++] = root;
        while (qh < qt) {
            int v = q[qh++];
            for (int to : g[v]) {
                if (base[v] == base[to] || mt[v] == to) continue;
                if (to == root || (mt[to] >= 0 && p[mt[to]] >= 0)) { // acha blossom
                    int cb = lca(v, to);
                    fill(bl.begin(), bl.end(), 0);
                    markPath(v, cb, to); markPath(to, cb, v);
                    for (int i = 0; i < n; i++) if (bl[base[i]]) {
                        base[i] = cb;
                        if (!used[i]) used[i] = 1, q[qt++] = i;
                    }
                } else if (p[to] < 0) {
                    p[to] = v;
                    if (mt[to] < 0) return to;
                    used[mt[to]] = 1; q[qt++] = mt[to];
                }
            }
        }
        return -1;
    }
    int solve() {
        for (int i = 0; i < n; i++) if (mt[i] < 0) // init guloso
            for (int to : g[i]) if (mt[to] < 0) { mt[to] = i; mt[i] = to; break; }
        for (int i = 0; i < n; i++) if (mt[i] < 0) {
            int v = findPath(i);
            while (v >= 0) { int pv = p[v], ppv = mt[pv]; mt[v] = pv; mt[pv] = v; v = ppv; }
        }
        int r = 0;
        for (int i = 0; i < n; i++) if (mt[i] > i) r++;
        return r;
    }
};
