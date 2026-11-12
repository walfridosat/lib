// Euleriano - Hierholzer
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
/*LATEX_DESC_BEGIN***************************
-> **Euleriano - trilha/circuito (Hierholzer)**
Devolve a sequencia de vertices de um circuito/trilha que usa cada aresta
exatamente uma vez, ou vazio se nao existe. E = vector<array<int,2>> u,v; 0-based.

Complexidade: O(n + m)
Uso:
  vector<int> p = euler_und(n, E);   // nao direcionado, arestas u-v
  vector<int> p = euler_dir(n, E);   // direcionado, arestas u->v
  // p tem tamanho m+1; vazio se nao ha trilha (m==0 tambem devolve vazio)
  // para ids de aresta, troque o push final de vertice por id

* Sobre o codigo:
  Hierholzer com pilha e iterador it[u]: desce consumindo arestas, e ao travar
  desempilha gravando o vertice; no fim o caminho e invertido.
  Graus: nao dirigido aceita 0 ou 2 impares (comeca num impar); dirigido exige
  0 ou 1 vertice com out-in=1 e 0 ou 1 com in-out=1. O tamanho final m+1
  confirma a conexidade das arestas.

* Problemas e reducoes:
  + Circuito euleriano: todos os graus pares (dirigido: in == out).
  + Trilha euleriana: 0 ou 2 impares (dirigido: um inicio e um fim).
  + Sequencia de de Bruijn: trilha euleriana no grafo de k-1 uplas.
  + Cobertura minima por trilhas: max(1, #impares/2) por componente.
  + Rota com cada aresta uma vez: decomponha em trilhas eulerianas.

Cuidados: exige conexidade das arestas (checada por tamanho == m+1). Self-loops
  ok. Sem arestas retorna vazio, nao {0}. Para multigrafo use ids de aresta.
Catalogo: Grafos (euleriano, Hierholzer, de Bruijn, trilhas).
Digitacao: 53 linhas | media. Atalho: euler_und e euler_dir compartilham todo
  o laco de pilha/iterador; una com uma flag.
*****************************LATEX_DESC_END*/
