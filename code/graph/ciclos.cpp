// Deteccao de ciclos: orientado, nao orientado, girth (menor ciclo nao ponderado)
//
// O que faz: find_cycle_dir devolve um ciclo orientado; find_cycle_und um ciclo simples
//   em grafo nao orientado (multiarestas contam como ciclo de tamanho 2); girth devolve o
//   comprimento do menor ciclo nao orientado.
// Quando usar: Catalogo > Grafos ("Ciclos (deteccao, menor ciclo)", "Ciclo minimo em grafo
//   nao pesado (girth)", "Ciclo unico (m=n) -> pseudofloresta").
//   Ciclo negativo: code/graph/bellman_ford.cpp. Ciclo de peso minimo: floyd.cpp.
// Complexidade: dir/und O(n+m); girth O(n*m)
// Uso: find_cycle_dir(n, g) / find_cycle_und(n, E) -> vertices do ciclo (vazio se nao ha).
//   girth(n, E) -> INT_MAX se floresta. E = vector<array<int,2>> arestas, g = adj orientada.
// Cuidados: DFS recursiva em find_cycle_dir (profundidade n). Em girth o candidato
//   d[u]+d[v]+1 para aresta fora da arvore BFS e exato quando minimizado sobre todas as raizes.
vector<int> find_cycle_dir(int n, const vector<vector<int>>& g) {
    vector<int> col(n, 0), par(n, -1), cyc;
    function<bool(int)> dfs = [&](int u) {
        col[u] = 1;
        for (int v : g[u]) {
            if (col[v] == 0) { par[v] = u; if (dfs(v)) return true; }
            else if (col[v] == 1) {              // aresta de retorno u -> v
                for (int x = u; x != v; x = par[x]) cyc.push_back(x);
                cyc.push_back(v);
                reverse(cyc.begin(), cyc.end());
                return true;
            }
        }
        col[u] = 2;
        return false;
    };
    for (int r = 0; r < n; r++) if (col[r] == 0 && dfs(r)) return cyc;
    return {};
}

vector<int> find_cycle_und(int n, const vector<array<int,2>>& E) {
    vector<vector<pair<int,int>>> g(n);
    for (int i = 0; i < (int)E.size(); i++) {
        g[E[i][0]].push_back({E[i][1], i}); g[E[i][1]].push_back({E[i][0], i});
    }
    vector<int> dep(n, -1), par(n, -1), pe(n, -1), cyc;
    function<bool(int)> dfs = [&](int u) {
        for (auto [v, id] : g[u]) {
            if (id == pe[u]) continue;
            if (dep[v] == -1) {
                dep[v] = dep[u] + 1; par[v] = u; pe[v] = id;
                if (dfs(v)) return true;
            } else if (dep[v] < dep[u]) {        // retorno para ancestral
                for (int x = u; x != v; x = par[x]) cyc.push_back(x);
                cyc.push_back(v);
                return true;
            }
        }
        return false;
    };
    for (int r = 0; r < n; r++) if (dep[r] == -1) { dep[r] = 0; if (dfs(r)) return cyc; }
    return {};
}

int girth(int n, const vector<array<int,2>>& E) {
    vector<vector<pair<int,int>>> g(n);
    for (int i = 0; i < (int)E.size(); i++) {
        g[E[i][0]].push_back({E[i][1], i}); g[E[i][1]].push_back({E[i][0], i});
    }
    int best = INT_MAX;
    for (int s = 0; s < n; s++) {
        vector<int> d(n, -1), pe(n, -1);
        queue<int> q; q.push(s); d[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto [v, id] : g[u]) {
                if (id == pe[u]) continue;
                if (d[v] == -1) d[v] = d[u] + 1, pe[v] = id, q.push(v);
                else best = min(best, d[u] + d[v] + 1);
            }
        }
    }
    return best;
}
