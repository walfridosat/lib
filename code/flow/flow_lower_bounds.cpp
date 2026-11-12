// Fluxo com limites inferiores - circulacao viavel e fluxo maximo
struct FlowLB {
    struct E { int to; ll cap; };
    int n, SS, TT; vector<E> e; vector<vector<int>> g; vector<int> lvl, it;
    vector<ll> exc; vector<array<ll,3>> ed; vector<int> eid; // ed: u,v,low
    FlowLB(int n) : n(n), SS(n), TT(n + 1), g(n + 2), lvl(n + 2), it(n + 2), exc(n + 2, 0) {}
    int _add(int u, int v, ll c) {
        e.push_back({v, c}); g[u].push_back(e.size() - 1);
        e.push_back({u, 0}); g[v].push_back(e.size() - 1);
        return e.size() - 2;
    }
    int add(int u, int v, ll low, ll high) {
        ed.push_back({u, v, low}); eid.push_back(_add(u, v, high - low));
        exc[v] += low; exc[u] -= low; // excesso: o que chega a mais do que sai
        return ed.size() - 1;
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
    ll dinic(int s, int t) {
        ll tot = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (ll f = dfs(s, t, LLONG_MAX)) tot += f;
        }
        return tot;
    }
    bool feasible() { // liga SS/TT conforme exc e satura
        ll need = 0;
        for (int v = 0; v < n; v++) {
            if (exc[v] > 0) _add(SS, v, exc[v]), need += exc[v];
            else if (exc[v] < 0) _add(v, TT, -exc[v]);
        }
        return dinic(SS, TT) == need;
    }
    bool circulation() { return feasible(); }
    ll maxflow(int s, int t) {
        const ll INF = 1e18;
        int ts = _add(t, s, INF); // fecha circulacao
        if (!feasible()) return -1;
        ll base = e[ts ^ 1].cap; // fluxo t->s ja enviado = valor atual s->t
        e[ts].cap = e[ts ^ 1].cap = 0; // remove a aresta t->s
        return base + dinic(s, t);
    }
    ll flowOn(int id) { return ed[id][2] + e[eid[id] ^ 1].cap; }
};
/*LATEX_DESC_BEGIN***************************
-> **Fluxo com limites inferiores**
Circulacao viavel e fluxo maximo s -> t com low <= f <= high em cada aresta;
recupera o fluxo por aresta. 0-indexed.

Complexidade: um ou dois Dinic (ver code/flow/dinic.cpp).
Uso:
  FlowLB f(n); int id = f.add(u, v, low, high);
  bool ok = f.circulation();   // existe circulacao viavel?
  ll r = f.maxflow(s, t);      // -1 se inviavel; senao o fluxo maximo total
  f.flowOn(id) -> fluxo na aresta id (inclui o low)
  Use UMA das duas (circulation ou maxflow) por objeto.

* Sobre o codigo:
  Cada aresta vira cap high - low; low entra em exc[] (excesso do destino menos
  da origem). feasible cria SS -> v para exc > 0 e v -> TT para exc < 0 e
  satura. maxflow fecha a circulacao com t -> s INF, mede o fluxo ja enviado
  em e[ts^1].cap (base) e depois remove essa aresta e aumenta s -> t.

* Problemas e reducoes:
  + Circulacao viavel com l <= f <= u: cap u - l; exc no destino/origem;
    SS -> v (exc > 0), v -> TT (exc < 0), T -> S com INF; viavel sse
    maxflow(SS, TT) satura toda a demanda.
  + Fluxo maximo s -> t com limites inferiores: igual ao anterior com a aresta
    T -> S INF; depois remova-a e some o fluxo base a um Dinic(s, t).
  + Fluxo minimo s -> t com limites: ache o viavel e rode Dinic(t, s) no
    residual sem a aresta T -> S; minimo = base - fluxo(t -> s).
  + Demanda fixa em vertice (b[v] = entra - sai exigido): aresta de/para um
    vertice extra com low = high, ou some b[v] em exc antes de feasible.
  + Cada aresta deve carregar pelo menos l: mesma reducao do primeiro item.
  + Arredondamento de matriz: linhas -> colunas com cap [floor(a), ceil(a)];
    somas de linha e coluna viram limites; viavel da o arredondamento.
  + Turnos com minimo por aresta: demandas viram lower bounds nas arestas de
    cobertura e a circulacao viavel decide a escala.
  + Multiplas fontes/sumidouros com limites: ligue super-fonte e
    super-sumidouro com cap INF e rode o fluxo maximo com limites.
  + Verificar um fluxo dado: compare flowOn(id) com [low, high] e a
    conservacao nos vertices.
  + Lower bounds so em algumas arestas: low = 0 nas demais e a mesma
    construcao.

Cuidados: INF = 1e18 na aresta t -> s; fluxo total pode somar muitas arestas,
  use ll. Chame circulation() ou maxflow() uma unica vez por objeto.
Catalogo: Grafos (circulacao com demandas, fluxo com limites inferiores),
  Otimizacao (fluxo com limites inferiores).
Digitacao: 63 linhas | media. Atalho: o Dinic interno duplica dinic.cpp;
  poderia incluir dinic.cpp e reusar a struct.
*****************************LATEX_DESC_END*/
