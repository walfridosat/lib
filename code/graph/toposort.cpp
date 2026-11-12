// Ordenacao topologica - Kahn


vector<ll> topoSort(vector<vector<ll>> &adj) {
    ll n = adj.size();
    vector<ll> in_degree(n, 0);
    vector<ll> order;
    queue<ll> q;

    for (ll u = 0; u < n; u++) {
        for (ll v : adj[u]) {
            in_degree[v]++;
        }
    }

    for (ll i = 0; i < n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        ll v = q.front();
        q.pop();
        order.push_back(v);

        for (ll u : adj[v]) {
            in_degree[u]--;
            if (in_degree[u] == 0) {
                q.push(u);
            }
        }
    }

    if ((ll)order.size() != n) {
        cout<<"Ciclo"<<endl;
        return {};
    }
    return order;
}
/*LATEX_DESC_BEGIN***************************
-> **Ordenacao topologica - Kahn**
Devolve uma ordem topologica de um DAG; se sobrar vertice ha ciclo (o vetor
retornado tem tamanho < n). Grafo dirigido 0-indexado.

Complexidade: O(n + m) tempo, O(n) memoria
Uso:
  vector<ll> ord = topoSort(adj);
  if (ord.size() < adj.size()) tem ciclo;

* Sobre o codigo:
  Calcula in_degree de cada vertice, enfileira os de grau 0 e vai removendo.
  Se ao final a ordem nao tem n vertices, sobrou ciclo (e imprime "Ciclo").
  Para ordem lexicografica troque queue por priority_queue.

* Problemas e reducoes:
  + Ordem topologica de DAG / dependencias entre tarefas.
  + Deteccao de ciclo: tamanho da ordem < n.
  + DP em DAG na ordem topologica.
  + Menor ordem lexicografica: priority_queue no lugar da queue.
  + Ordem unica sse em todo passo ha no maximo um vertice de grau 0.

Cuidados: arestas duplicadas contam em dobro no grau (ok para Kahn, mas
  remova-as se a semantica exigir). Imprime "Ciclo" no cout quando ha ciclo.
Catalogo: Grafos (DAG, topologica, DP em DAG).
Digitacao: 32 linhas | facil. Atalho: use vector<int> no lugar de ll.
*****************************LATEX_DESC_END*/