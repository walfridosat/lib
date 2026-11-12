// Push-relabel (highest label + gap) - fluxo maximo
//
// O que faz: fluxo maximo; alternativa ao Dinic em grafos densos / capacidades grandes.
// Quando usar: Catalogo > Grafos (fluxo); quando Dinic estoura tempo em grafo denso.
// Complexidade: O(V^2 sqrt E) pior caso; muito rapido na pratica.
// Uso: PushRelabel pr(n); pr.addEdge(u,v,cap[,rcap]); ll f=pr.calc(s,t);
//   pr.leftOfMinCut(v) = true se v esta do lado de s no corte minimo (apos calc).
// Cuidados: baseado no KACTL. Chamar calc uma unica vez por objeto. 0-indexed.
struct PushRelabel {
    struct Edge { int dest, back; ll f, c; };
    vector<vector<Edge>> g; vector<ll> ec; vector<Edge*> cur;
    vector<vector<int>> hs; vector<int> H;
    PushRelabel(int n) : g(n), ec(n), cur(n), hs(2 * n), H(n) {}
    void addEdge(int s, int t, ll cap, ll rcap = 0) {
        if (s == t) return;
        g[s].push_back({t, (int)g[t].size(), 0, cap});
        g[t].push_back({s, (int)g[s].size() - 1, 0, rcap});
    }
    void addFlow(Edge& e, ll f) {
        Edge &back = g[e.dest][e.back];
        if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
        e.f += f; e.c -= f; ec[e.dest] += f;
        back.f -= f; back.c += f; ec[back.dest] -= f;
    }
    ll calc(int s, int t) {
        int v = g.size(); H[s] = v; ec[t] = 1;
        vector<int> co(2 * v); co[0] = v - 1;
        for (int i = 0; i < v; i++) cur[i] = g[i].data();
        for (Edge& e : g[s]) addFlow(e, e.c);
        for (int hi = 0;;) {
            while (hs[hi].empty()) if (!hi--) return -ec[s];
            int u = hs[hi].back(); hs[hi].pop_back();
            while (ec[u] > 0) // descarrega u
                if (cur[u] == g[u].data() + g[u].size()) {
                    H[u] = 1e9; // relabel
                    for (Edge& e : g[u]) if (e.c && H[u] > H[e.dest] + 1)
                        H[u] = H[e.dest] + 1, cur[u] = &e;
                    if (++co[H[u]], !--co[hi] && hi < v) // gap
                        for (int i = 0; i < v; i++) if (hi < H[i] && H[i] < v)
                            --co[H[i]], H[i] = v + 1;
                    hi = H[u];
                } else if (cur[u]->c && H[u] == H[cur[u]->dest] + 1)
                    addFlow(*cur[u], min(ec[u], cur[u]->c));
                else ++cur[u];
        }
    }
    bool leftOfMinCut(int a) { return H[a] >= (int)g.size(); }
};
