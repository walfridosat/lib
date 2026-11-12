// Pontes, articulacoes e componentes 2-aresta-conexas (bridge tree)
//
// O que faz: acha pontes e vertices de articulacao; rotula 2-aresta-conexas; monta a
//   arvore de pontes (bridge tree); conta pares desconectados ao remover cada vertice.
// Quando usar: Catalogo > Grafos ("Pontes e articulacoes -> arvore de componentes 2-aresta-
//   conexas", "Condensacao por pontes", "Articulacao != ponte para multiarestas",
//   "Contar pares desconectados ao remover vertice v", orientacao de Robbins).
// Complexidade: O(n + m)
// Uso: Bridges b(n); b.add(u,v) (devolve id da aresta); b.build();
//   b.is_bridge[id], b.is_art[v], b.cc[v] (id da 2ecc), b.C, b.tree (adj da bridge tree),
//   b.sep[v] = pares nao ordenados {a,b} (a,b != v, mesma comp. de v) que ficam
//   desconectados ao remover v. 0-based.
//   Minimo de arestas p/ tornar 2-aresta-conexo = ceil(folhas/2) na bridge tree (se C>1).
// Cuidados: DFS recursiva (profundidade n): para n ~1e6 aumente a pilha ou reescreva.
//   Multiarestas: compara-se id da aresta pai, nao o vertice pai. Raiz e articulacao so
//   com >= 2 filhos na DFS. Grafo pode ser desconexo.
struct Bridges {
    int n, timer = 0, C = 0, csz = 0;
    vector<array<int,2>> E;
    vector<vector<pair<int,int>>> g;
    vector<int> tin, low, cc, sub;
    vector<char> is_bridge, is_art;
    vector<vector<int>> tree;
    vector<ll> sep;
    Bridges(int n) : n(n), g(n) {}
    int add(int u, int v) {
        int id = E.size(); E.push_back({u, v});
        g[u].push_back({v, id}); g[v].push_back({u, id});
        return id;
    }
    void dfs(int u, int pe) {
        tin[u] = low[u] = timer++;
        sub[u] = 1;
        int ch = 0; ll sumsz = 0, sq = 0; bool art = false;
        for (auto [v, id] : g[u]) {
            if (id == pe) continue;
            if (tin[v] != -1) low[u] = min(low[u], tin[v]);   // aresta de retorno
            else {
                dfs(v, id); ch++;
                sub[u] += sub[v];
                low[u] = min(low[u], low[v]);
                if (low[v] > tin[u]) is_bridge[id] = 1;
                if (low[v] >= tin[u]) {                      // v fica pendurado em u
                    sumsz += sub[v]; sq += (ll)sub[v] * sub[v];
                    if (pe != -1) art = true;
                }
            }
        }
        if (pe == -1 && ch >= 2) art = true;
        is_art[u] = art;
        // csz = tamanho da componente conexa de u (preenchido antes da dfs da raiz)
        ll tot = csz - 1, rest = tot - sumsz;                // rest = lado de cima de u
        sep[u] = (tot * tot - sq - rest * rest) / 2;
    }
    void build() {
        tin.assign(n, -1); low.assign(n, 0); sub.assign(n, 0);
        is_bridge.assign(E.size(), 0); is_art.assign(n, 0); sep.assign(n, 0);
        vector<char> mk(n, 0);
        for (int r = 0; r < n; r++) if (tin[r] == -1) {
            // tamanho da componente (varredura simples)
            vector<int> st = {r};
            mk[r] = 1; csz = 0;
            while (!st.empty()) {
                int u = st.back(); st.pop_back(); csz++;
                for (auto [v, id] : g[u]) if (!mk[v]) mk[v] = 1, st.push_back(v);
            }
            dfs(r, -1);
        }
        cc.assign(n, -1); C = 0;
        for (int r = 0; r < n; r++) if (cc[r] == -1) {
            vector<int> st = {r}; cc[r] = C;
            while (!st.empty()) {
                int u = st.back(); st.pop_back();
                for (auto [v, id] : g[u]) if (!is_bridge[id] && cc[v] == -1) cc[v] = C, st.push_back(v);
            }
            C++;
        }
        tree.assign(C, {});
        for (int id = 0; id < (int)E.size(); id++) if (is_bridge[id]) {
            tree[cc[E[id][0]]].push_back(cc[E[id][1]]);
            tree[cc[E[id][1]]].push_back(cc[E[id][0]]);
        }
    }
};
