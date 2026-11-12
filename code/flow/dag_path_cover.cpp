// Cobertura minima de caminhos em DAG - disjuntos em vertices ou com repeticao
vector<vector<int>> dagPathCover(int n, vector<pair<int,int>> edges, bool repeat) {
    const int MAXB = 2048;
    if (repeat) { // fecho transitivo: ordem topologica + bitset
        vector<vector<int>> adj(n); vector<int> deg(n, 0), ord;
        for (auto [u, v] : edges) adj[u].push_back(v), deg[v]++;
        for (int i = 0; i < n; i++) if (!deg[i]) ord.push_back(i);
        for (int k = 0; k < (int)ord.size(); k++)
            for (int v : adj[ord[k]]) if (!--deg[v]) ord.push_back(v);
        vector<bitset<MAXB>> reach(n);
        for (int k = n - 1; k >= 0; k--) {
            int u = ord[k];
            for (int v : adj[u]) reach[u] |= reach[v], reach[u][v] = 1;
        }
        edges.clear();
        for (int u = 0; u < n; u++) for (int v = 0; v < n; v++) if (reach[u][v]) edges.push_back({u, v});
    }
    // matching bipartido (out-copy -> in-copy) por Kuhn
    vector<vector<int>> g(n); vector<int> mr(n, -1), ml(n, -1), vis(n, 0);
    for (auto [u, v] : edges) g[u].push_back(v);
    function<bool(int)> dfs = [&](int u) {
        vis[u] = 1;
        for (int v : g[u]) if (mr[v] < 0 || (!vis[mr[v]] && dfs(mr[v]))) { ml[u] = v; mr[v] = u; return true; }
        return false;
    };
    for (int u = 0; u < n; u++) { fill(vis.begin(), vis.end(), 0); dfs(u); }
    vector<vector<int>> res;
    for (int u = 0; u < n; u++) if (mr[u] < 0) { // inicio de caminho
        vector<int> p;
        for (int x = u; x >= 0; x = ml[x]) p.push_back(x);
        res.push_back(p);
    }
    return res;
}
/*LATEX_DESC_BEGIN***************************
-> **Cobertura minima de caminhos em DAG**
Minimo de caminhos que cobrem todos os vertices de um DAG, com reconstrucao.
repeat=true permite caminhos que compartilham vertices (usa fecho transitivo).
0-indexed.

Complexidade: O(E sqrt V) no matching (+ O(V^3/64) bitset para o fecho).
Uso:
  auto paths = dagPathCover(n, edges, false); // edges: pares (u,v), u -> v
  paths.size() = minimo; paths[i] = vertices do i-esimo caminho em ordem.
  repeat = true: fecho transitivo antes (bitset, ate MAXB vertices).

* Sobre o codigo:
  Reduz a cobertura de caminhos a matching bipartido: a copia out de u liga a
  copia in de v para cada aresta u -> v; resposta = n - matching. Cada vertice
  sem par de entrada inicia um caminho, seguido por ml[]. Com repeat, o fecho
  transitivo transforma "caminho que pode repetir" em caminho disjunto.

* Problemas e reducoes:
  + Cobertura minima de DAG por caminhos disjuntos em vertices: modelo acima;
    resposta = n - matching; caminhos reconstruidos por ml[].
  + Cobertura com vertices repetidos: feche transitivamente e use o mesmo
    modelo; equivale ao minimo de caminhos no DAG original.
  + Dilworth / maior anticadeia em poset: arestas do poset (i < j) com fecho
    transitivo; anticadeia maxima = n - matching.
  + Decomposicao minima de poset em cadeias: mesmo matching; cada caminho e
    uma cadeia; tamanho = n - matching.
  + Particionar sequencia no minimo de subsequencias crescentes: poset com
    i < j e a[i] <= a[j]; matching no bipartido das comparacoes.
  + Minimo de cadeias para cobrir um poset (largura = anticadeia maxima).
  + Escalonamento com precedencias: minimo de sequencias encadeadas que
    executam todas as tarefas = n - matching no grafo de precedencias.
  + DAG coberto por um unico caminho: matching = n - 1.
  + Cobertura de um subconjunto: remova os demais vertices do universo e
    aplique o mesmo modelo.

Cuidados: o grafo DEVE ser DAG (sem ciclos). Resposta = n - matching.
  repeat: bitset MAXB = 2048, ajuste para n maior. 0-indexed.
Catalogo: Grafos (cobertura minima de caminhos em DAG, Dilworth).
Digitacao: 33 linhas | media. Atalho: o matching interno repete o codigo de
  kuhn.cpp; poderia incluir kuhn.cpp e chamar a struct.
*****************************LATEX_DESC_END*/
