// Min-cost max-flow simples com SPFA (aceita custos negativos sem ciclo negativo)
//
// O que faz: igual a mcmf.cpp, porem mais curto (bom para colar rapido, grafos pequenos).
// Quando usar: atribuicao pequena, k caminhos de custo minimo (Catalogo > Grafos).
// Complexidade: O(F * V * E) pior caso, rapido na pratica.
// Uso: MCMFS m(n); m.add(u,v,cap,cost); auto [f,c]=m.run(s,t[,lim]);
// Cuidados: sem ciclo negativo no grafo inicial; 0-indexed. Para grafos grandes use mcmf.cpp.
struct MCMFS {
    struct E { int to; ll cap, cost; };
    int n; vector<E> e; vector<vector<int>> g;
    MCMFS(int n) : n(n), g(n) {}
    void add(int u, int v, ll cap, ll cost) {
        e.push_back({v, cap, cost}); g[u].push_back(e.size() - 1);
        e.push_back({u, 0, -cost}); g[v].push_back(e.size() - 1);
    }
    pair<ll, ll> run(int s, int t, ll lim = LLONG_MAX) {
        const ll INF = LLONG_MAX / 4; ll F = 0, C = 0;
        while (F < lim) {
            vector<ll> d(n, INF); vector<int> pe(n, -1); vector<char> in(n, 0);
            deque<int> q; d[s] = 0; q.push_back(s);
            while (!q.empty()) {
                int u = q.front(); q.pop_front(); in[u] = 0;
                for (int id : g[u]) if (e[id].cap > 0 && d[u] + e[id].cost < d[e[id].to]) {
                    int v = e[id].to; d[v] = d[u] + e[id].cost; pe[v] = id;
                    if (!in[v]) in[v] = 1, q.push_back(v);
                }
            }
            if (d[t] >= INF) break;
            ll f = lim - F;
            for (int v = t; v != s; v = e[pe[v] ^ 1].to) f = min(f, e[pe[v]].cap);
            for (int v = t; v != s; v = e[pe[v] ^ 1].to) e[pe[v]].cap -= f, e[pe[v] ^ 1].cap += f;
            F += f; C += f * d[t];
        }
        return {F, C};
    }
};
