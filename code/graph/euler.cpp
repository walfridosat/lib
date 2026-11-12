// Caminho/circuito euleriano (Hierholzer) - nao direcionado e direcionado
//
// O que faz: devolve a sequencia de vertices de um circuito/trilha que usa cada aresta
//   exatamente uma vez, ou vazio se nao existe.
// Quando usar: Catalogo > Grafos ("Euleriano -> graus pares; Hierholzer", "Euler em nao
//   direcionado/direcionado", "Sequencia de de Bruijn", cobertura de arestas por trilhas).
// Complexidade: O(n + m)
// Uso: vector<array<int,2>> E (arestas u,v), 0-based.
//   euler_und(n, E) -> vertices (tamanho m+1); euler_dir(n, E) idem (aresta u->v).
//   m == 0 => retorna {0}? Aqui retorna vazio se nao ha aresta (trate fora).
//   Para trilhas de arestas (ids) troque o push final de vertice por id.
// Cuidados: exige conexidade das arestas (checada pelo tamanho final == m+1).
//   Nao dirigido: 0 ou 2 vertices de grau impar (comeca num impar). Dirigido: in==out,
//   ou um com out-in=1 (inicio) e um com in-out=1. Self-loops ok.
//   Cobertura minima de arestas por trilhas = max(1, #impares/2) por componente.
vector<int> euler_und(int n, const vector<array<int,2>>& E) {
    int m = E.size();
    vector<vector<pair<int,int>>> g(n);
    vector<int> deg(n, 0);
    for (int i = 0; i < m; i++) {
        g[E[i][0]].push_back({E[i][1], i}); g[E[i][1]].push_back({E[i][0], i});
        deg[E[i][0]]++; deg[E[i][1]]++;
    }
    int start = -1, odd = 0;
    for (int v = 0; v < n; v++)
        if (deg[v] & 1) { odd++; if (start == -1) start = v; }   // trilha comeca num vertice impar
    if (odd != 0 && odd != 2) return {};
    if (start == -1) for (int v = 0; v < n; v++) if (deg[v]) { start = v; break; }
    if (start == -1) return {};
    vector<char> used(m, 0);
    vector<int> it(n, 0), st = {start}, path;
    while (!st.empty()) {
        int u = st.back();
        while (it[u] < (int)g[u].size() && used[g[u][it[u]].second]) it[u]++;
        if (it[u] == (int)g[u].size()) { path.push_back(u); st.pop_back(); }
        else {
            auto [v, id] = g[u][it[u]++];
            used[id] = 1; st.push_back(v);
        }
    }
    if ((int)path.size() != m + 1) return {};
    reverse(path.begin(), path.end());
    return path;
}

vector<int> euler_dir(int n, const vector<array<int,2>>& E) {
    int m = E.size();
    vector<vector<int>> g(n);
    vector<int> in(n, 0), out(n, 0);
    for (auto& e : E) g[e[0]].push_back(e[1]), out[e[0]]++, in[e[1]]++;
    int start = -1, s_cnt = 0, e_cnt = 0;
    for (int v = 0; v < n; v++) {
        if (out[v] - in[v] == 1) s_cnt++, start = v;
        else if (in[v] - out[v] == 1) e_cnt++;
        else if (in[v] != out[v]) return {};
    }
    if (!((s_cnt == 0 && e_cnt == 0) || (s_cnt == 1 && e_cnt == 1))) return {};
    if (start == -1) for (int v = 0; v < n; v++) if (out[v]) { start = v; break; }
    if (start == -1) return {};
    vector<int> st = {start}, path, it(n, 0);
    while (!st.empty()) {
        int u = st.back();
        if (it[u] == (int)g[u].size()) { path.push_back(u); st.pop_back(); }
        else st.push_back(g[u][it[u]++]);
    }
    if ((int)path.size() != m + 1) return {};
    reverse(path.begin(), path.end());
    return path;
}
