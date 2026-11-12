// Dinic - fluxo maximo / corte minimo
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
    vector<bool> cut(int s) { // lado S: alcancaveis de s no residual
        vector<bool> vis(n, false); vis[s] = true;
        queue<int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int id : g[u]) if (e[id].cap > 0 && !vis[e[id].to])
                vis[e[id].to] = true, q.push(e[id].to);
        }
        return vis;
    }
    ll flowOn(int id) { return e[id].orig - e[id].cap; }
};
/*LATEX_DESC_BEGIN***************************
-> **Dinic - Max Flow / Min Cut**
Fluxo maximo s->t por niveis (BFS) + fluxo bloqueante (DFS com ponteiro).
Vertices 0-indexed.

Complexidade: O(V^2 E) geral | O(E sqrt V) bipartido com cap 1
Uso:
  Dinic d(n); int id = d.add(u, v, cap[, rcap]);  // nao-direcionada: add(u,v,c,c)
  ll f = d.flow(s, t);
  d.cut(s)[u]  -> u esta no lado de s do corte minimo (chame apos flow)
  d.flowOn(id) -> fluxo passando na aresta id

* Sobre o codigo:
  e[] guarda cada aresta e a reversa lado a lado: a reversa de id e id ^ 1.
  bfs calcula lvl[] (distancia no residual); dfs so anda de lvl k para k + 1.
  it[u] = proxima aresta de u ainda util; nunca volta, o que garante a complexidade.

* Problemas e reducoes:
  + Corte minimo = fluxo maximo; lado S = alcancaveis de s no residual.
  + Caminhos disjuntos em arestas: cap 1 (Menger). Em vertices: v vira v_in -> v_out cap 1.
  + Matching bipartido: s -> esquerda, direita -> t, tudo cap 1.
  + Bipartido: cobertura minima de vertices = matching (Konig); independente maximo = n - matching.
  + Cobertura de DAG por caminhos disjuntos = n - matching em (u_out, v_in);
    com fecho transitivo vira a maior anticadeia (Dilworth).
  + Project selection / closure: s -> projeto (lucro), maquina -> t (custo),
    dependencia com cap INF; resposta = soma dos lucros - flow.
  + Atribuicao com limites (pessoas x tarefas): camadas s -> A -> B -> t.

Cuidados: somar varios INF estoura ll; dfs recursiva (profundidade <= V).
Catalogo: Grafos (fluxo/corte), Otimizacao.
Digitacao: 50 linhas | media. Atalho: cut(s) e dispensavel, apos flow() o lado S
  e exatamente lvl[u] >= 0 (a ultima bfs falhou e marcou os alcancaveis de s).
*****************************LATEX_DESC_END*/
