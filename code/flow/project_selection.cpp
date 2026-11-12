// Fecho maximo / selecao de projetos (closure) via corte minimo
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
/*LATEX_DESC_BEGIN***************************
-> **Fecho maximo / selecao de projetos (closure)**
Escolhe um conjunto S de itens maximizando a soma dos lucros p[i] (custos sao
negativos), com dependencias "escolher i exige escolher j". 0-indexed.

Complexidade: um Dinic em n + 2 vertices.
Uso:
  Closure c(n); c.profit(i, p); c.need(i, j); // i exige j
  ll best = c.solve(); vector<bool> pick = c.chosen;
  Resposta = soma dos lucros positivos - corte minimo.

* Sobre o codigo:
  Rede: s -> i com cap p[i] quando p[i] > 0; i -> t com cap -p[i] quando
  p[i] < 0; i -> j com INF para cada dependencia. O corte minimo paga os
  projetos abandonados e os custos dos escolhidos; o lado de s no residual
  e o conjunto escolhido.

* Problemas e reducoes:
  + Fecho de peso maximo em grafo dirigido: s -> v (w > 0), v -> t (-w se
    w < 0), arestas originais cap INF; resposta = soma dos positivos -
    corte.
  + Project selection: projetos com lucro, maquinas/ferramentas com custo,
    projeto -> ferramenta cap INF; compre as ferramentas do lado de s.
  + Dependencia "i exige j": aresta i -> j com INF; se i e escolhido, j fica
    do lado de s.
  + Cursos com pre-requisitos: lucro = creditos, custo = esforco; fecho.
  + Bonus de par ("ganha w se escolher a e b"): vertice auxiliar com lucro w
    e arestas INF para a e para b; so recebe o bonus se ambos entrarem.
  + Penalidade/custo de escolher: p[i] negativo vira i -> t com cap -p[i].
  + Conjunto fechado para tras (ideal) de peso maximo em um DAG.
  + Maximizar receita com custos fixos de infraestrutura compartilhada:
    cada item tem lucro, cada infraestrutura tem custo e e exigida por itens.
  + Verificar se um conjunto e fechado: toda aresta de i em S leva a j em S.
  + Caso sem dependencias: cada item com lucro positivo entra; com lucro
    negativo fica fora; o corte reproduz isso.

Cuidados: bonus de par ("ganha w se escolher a E b") -> vertice auxiliar com
  lucro +w que exige a e b. Custo de par que so existe se ambos escolhidos
  nao funciona direto (termos binarios so por corte se submodulares).
  INF = 1e15; soma dos lucros deve caber em ll.
Catalogo: Grafos (selecao com custo de par, maximo closure), Otimizacao
  (fecho maximo, binario submodular).
Digitacao: 54 linhas | media. Atalho: o Dinic interno duplica dinic.cpp;
  poderia incluir dinic.cpp e reusar a struct.
*****************************LATEX_DESC_END*/
