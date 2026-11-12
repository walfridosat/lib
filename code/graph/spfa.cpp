// SPFA - Bellman-Ford com fila, pesos negativos
const ll SPFA_INF = LLONG_MAX / 4;

bool spfa(int n, const vector<vector<pair<int,ll>>>& adj, int s, vector<ll>& d) {
    d.assign(n, SPFA_INF);
    vector<int> cnt(n, 0);
    vector<char> in(n, 0);
    queue<int> q;
    d[s] = 0; q.push(s); in[s] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop(); in[u] = 0;
        for (auto [v, w] : adj[u])
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) return false;   // ciclo negativo
                if (!in[v]) in[v] = 1, q.push(v);
            }
    }
    return true;
}
/*LATEX_DESC_BEGIN***************************
-> **SPFA - Bellman-Ford com fila**
Menor caminho com pesos negativos; detecta ciclo negativo alcancavel de s.
Adj 0-based: adj[u] = {(v,w)}.

Complexidade: O(n*m) pior caso, tipicamente O(m)
Uso:
  vector<ll> d;
  bool ok = spfa(n, adj, s, d);   // false se ha ciclo negativo
  // d[v] == SPFA_INF se inalcancavel

* Sobre o codigo:
  Fila com os vertices que melhoraram; in[] evita duplicatas. cnt[v] conta
  arestas do caminho; cnt[v] >= n indica ciclo negativo.

* Problemas e reducoes:
  + Caminhos minimos com pesos negativos e sem ciclo negativo.
  + Detectar ciclo negativo alcancavel de s (retorno false).
  + MCMF com SPFA quando nao ha custos negativos iniciais.
  + Grafo esparso aleatorio: costuma ser rapido na pratica.

Cuidados: apenas heuristica; testes anti-SPFA existem. Use Bellman-Ford ou
  Johnson quando precisar de pior caso garantido.
Catalogo: Grafos (SPFA, pesos negativos).
Digitacao: 19 linhas | facil.
*****************************LATEX_DESC_END*/
