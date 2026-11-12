// Fecho maximo / selecao de projetos (closure) via corte minimo
//
// O que faz: escolhe conjunto S de itens maximizando soma dos lucros p[i] (podem ser
//   negativos = custo), com dependencias "escolher i exige escolher j".
// Quando usar: "projetos x ferramentas", "lucro - custo com dependencias", segmentacao,
//   Catalogo > Grafos ("Selecao com custo de par", "Maximo closure"), Otimizacao >
//   "Fecho maximo", "Binario submodular".
// Complexidade: um Dinic em n+2 vertices.
// Uso: Closure c(n); c.profit(i,p); c.need(i,j) /* i exige j */;
//   ll best=c.solve(); vector<bool> pick = c.chosen;
//   Resposta = soma dos lucros positivos - corte minimo.
// Cuidados: bonus de par ("ganha w se escolher a E b") -> vertice aux com lucro +w que
//   exige a e b. Custo de par que so existe se ambos escolhidos idem com lucro -c nao
//   funciona direto; reveja o modelo (termos binarios so por corte se submodulares,
//   Catalogo > Otimizacao). INF = 1e15; soma dos lucros deve caber em ll.
struct Closure {
    int n; ll sum = 0; vector<ll> p; vector<pair<int,int>> dep; vector<bool> chosen;
    Closure(int n) : n(n), p(n, 0) {}
    void profit(int i, ll v) { p[i] = v; }
    void need(int i, int j) { dep.push_back({i, j}); }
    // Dinic compacto
    struct E { int to; ll cap; };
    vector<E> e; vector<vector<int>> g; vector<int> lvl, it;
    void ae(int u, int v, ll c) {
        e.push_back({v, c}); g[u].push_back(e.size() - 1);
        e.push_back({u, 0}); g[v].push_back(e.size() - 1);
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
    ll solve() {
        const ll INF = 1e15; int S = n, T = n + 1;
        g.assign(n + 2, {}); lvl.assign(n + 2, 0); it.assign(n + 2, 0); e.clear();
        for (int i = 0; i < n; i++) {
            if (p[i] > 0) ae(S, i, p[i]), sum += p[i];
            else if (p[i] < 0) ae(i, T, -p[i]);
        }
        for (auto [i, j] : dep) ae(i, j, INF); // i escolhido => j escolhido
        ll cut = 0;
        while (bfs(S, T)) { fill(it.begin(), it.end(), 0); while (ll f = dfs(S, T, LLONG_MAX)) cut += f; }
        // escolhidos = alcancaveis de S no residual
        chosen.assign(n, false);
        vector<int> st = {S}; vector<bool> vis(n + 2, false); vis[S] = true;
        while (!st.empty()) {
            int u = st.back(); st.pop_back();
            for (int id : g[u]) if (e[id].cap > 0 && !vis[e[id].to]) vis[e[id].to] = true, st.push_back(e[id].to);
        }
        for (int i = 0; i < n; i++) chosen[i] = vis[i];
        return sum - cut;
    }
};
