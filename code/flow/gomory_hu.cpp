// Gomory-Hu (Gusfield) - corte minimo entre todos os pares
struct GomoryHu {
    struct E { int to; ll cap, orig; };
    int n; vector<E> e; vector<vector<int>> g; vector<int> lvl, it, par; vector<ll> w;
    GomoryHu(int n) : n(n), g(n), lvl(n), it(n), par(n, 0), w(n, 0) {}
    void add(int u, int v, ll c) {
        e.push_back({v, c, c}); g[u].push_back(e.size() - 1);
        e.push_back({u, c, c}); g[v].push_back(e.size() - 1);
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
    void build() {
        for (int i = 1; i < n; i++) {
            for (auto &x : e) x.cap = x.orig; // restaura capacidades
            ll f = 0;
            while (bfs(i, par[i])) { fill(it.begin(), it.end(), 0); while (ll r = dfs(i, par[i], LLONG_MAX)) f += r; }
            w[i] = f; // apos o ultimo bfs, lvl>=0 marca o lado de i do corte
            for (int j = i + 1; j < n; j++) if (lvl[j] >= 0 && par[j] == par[i]) par[j] = i;
        }
    }
    vector<vector<ll>> mincuts() { // O(n^2): mincut de todos os pares via arvore
        vector<vector<ll>> r(n, vector<ll>(n, LLONG_MAX));
        // processa na ordem em que par[i] ja esta ligado: i entra ligado a par[i]
        // (par[i] < i nao vale sempre); usa DFS a partir de cada raiz
        vector<vector<pair<int,ll>>> adj(n);
        for (int i = 1; i < n; i++) adj[i].push_back({par[i], w[i]}), adj[par[i]].push_back({i, w[i]});
        for (int s = 0; s < n; s++) {
            vector<int> st = {s}; vector<int> pr(n, -1); pr[s] = s;
            while (!st.empty()) {
                int u = st.back(); st.pop_back();
                for (auto [v, c] : adj[u]) if (pr[v] < 0) {
                    pr[v] = u; r[s][v] = min(r[s][u], c); st.push_back(v);
                }
            }
        }
        return r;
    }
};
/*LATEX_DESC_BEGIN***************************
-> **Gomory-Hu (Gusfield) - min cut entre todos os pares**
Grafo nao direcionado com capacidades; constroi uma arvore com n - 1 arestas
em que o corte minimo (fluxo maximo) entre u e v e o menor peso no caminho
u-v. 0-indexed.

Complexidade: n - 1 fluxos (Dinic).
Uso:
  GomoryHu gh(n); gh.add(u, v, c); gh.build();
  gh.par[i], gh.w[i] -> aresta i--par[i] de peso w[i] (i >= 1; 0 e raiz);
  auto mc = gh.mincuts(); // matriz n x n de min cuts.

* Sobre o codigo:
  Para cada i >= 1 restaura as capacidades e calcula o fluxo maximo entre i e
  par[i]. O valor vira w[i]; o lado de i no residual (lvl >= 0) reparenta os
  vertices j > i que ainda apontavam para par[i]. mincuts sobe a arvore com
  DFS guardando o minimo das arestas no caminho.

* Problemas e reducoes:
  + Corte minimo entre todos os pares: monte a arvore; mincut(u, v) = minimo
    das arestas no caminho u-v da arvore.
  + Par com maior corte minimo: maximize mincut(u, v) sobre todos os pares,
    usando a matriz ou o caminho na arvore.
  + Corte minimo global (menor aresta de corte): menor peso entre as n - 1
    arestas da arvore (n >= 2).
  + Conectividade de arestas (edge connectivity): igual ao corte minimo
    global; a arvore da o valor sem testar pares.
  + Quantos pares tem mincut >= k: conte pares cujo caminho na arvore tem
    todas as arestas >= k.
  + Separar um vertice u de ao menos um vertice de S: minimo de mincut(u, v)
    sobre v em S.
  + Fluxo maximo entre todos os pares: mesma resposta do corte, pois o grafo
    e nao direcionado (max flow = min cut).
  + Min cuts de um vertice para todos os outros: a linha correspondente de
    mincuts() traz os n valores em O(n).
  + Testar se o mincut de um par e exatamente K: caminho na arvore e menor
    aresta.

Cuidados: grafo NAO direcionado apenas. A arvore e flow-equivalent (valores
  corretos por caminho); os cortes em si nao sao necessariamente os da arvore.
  0-indexed.
Catalogo: Otimizacao (corte minimo global), Grafos.
Digitacao: 56 linhas | dificil. Atalho: o Dinic interno duplica dinic.cpp;
  poderia incluir dinic.cpp e reusar a struct.
*****************************LATEX_DESC_END*/
