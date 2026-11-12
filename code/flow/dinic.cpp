// Dinic (fluxo maximo) + recuperacao do corte minimo
//
// O que faz: fluxo maximo s->t; depois do flow() recupera o lado S do corte minimo
//   e o fluxo passando em cada aresta.
// Quando usar: "emparelhamento, cobertura, atribuir", Menger (caminhos disjuntos = corte),
//   corte minimo em grid, closure/project selection (Catalogo > Grafos, Otimizacao).
// Complexidade: O(V^2 E) geral; O(E*min(V^(2/3),E^(1/2))) cap. unitaria;
//   O(E sqrt V) em bipartido unitario.
// Uso: Dinic d(n); int id=d.add(u,v,cap[,rcap]); ll f=d.flow(s,t);
//   vector<bool> S=d.cut(s) (true = lado de s, valido apos flow);
//   d.flowOn(id) = fluxo na aresta id. Vertices 0-indexed. Nao-direcionada: add(u,v,c,c).
// Cuidados: INF grande mas sem estourar (use ~1e18 so em cap de aresta isolada; somas
//   de INF estouram). Para vertex-cut divida v em in->out cap 1.
struct Dinic {
    struct E { int to; ll cap, orig; };
    int n; vector<E> e; vector<vector<int>> g; vector<int> lvl, it;
    Dinic(int n) : n(n), g(n), lvl(n), it(n) {}
    int add(int u, int v, ll c, ll rc = 0) {
        e.push_back({v, c, c}); g[u].push_back(e.size() - 1);
        e.push_back({u, rc, rc}); g[v].push_back(e.size() - 1);
        return e.size() - 2;
    }
    bool bfs(int s, int t) {
        fill(lvl.begin(), lvl.end(), -1); lvl[s] = 0;
        queue<int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int id : g[u]) if (e[id].cap > 0 && lvl[e[id].to] < 0)
                lvl[e[id].to] = lvl[u] + 1, q.push(e[id].to);
        }
        return lvl[t] >= 0;
    }
    ll dfs(int u, int t, ll f) {
        if (u == t) return f;
        for (int &i = it[u]; i < (int)g[u].size(); i++) {
            int id = g[u][i], v = e[id].to;
            if (e[id].cap > 0 && lvl[v] == lvl[u] + 1) {
                ll r = dfs(v, t, min(f, e[id].cap));
                if (r > 0) { e[id].cap -= r; e[id ^ 1].cap += r; return r; }
            }
        }
        return 0;
    }
    ll flow(int s, int t) {
        ll tot = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (ll f = dfs(s, t, LLONG_MAX)) tot += f;
        }
        return tot;
    }
    // lado S do corte minimo: vertices alcancaveis de s no residual
    vector<bool> cut(int s) {
        vector<bool> vis(n, false); vis[s] = true;
        queue<int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int id : g[u]) if (e[id].cap > 0 && !vis[e[id].to])
                vis[e[id].to] = true, q.push(e[id].to);
        }
        return vis;
    }
    ll flowOn(int id) { return e[id].orig - e[id].cap; } // fluxo na aresta id (direta)
};
