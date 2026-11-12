// Kruskal - arvore geradora minima
struct KEdge {
    ll w; int u, v;
    bool operator<(const KEdge& o) const { return w < o.w; }
};

pair<ll, bool> kruskal(int n, vector<KEdge> edges) {
    sort(edges.begin(), edges.end());
    vector<int> par(n);
    iota(par.begin(), par.end(), 0);
    function<int(int)> find = [&](int u) {
        return par[u] == u ? u : par[u] = find(par[u]);
    };
    ll cost = 0;
    int cnt = 0;
    for (const auto& e : edges) {
        int a = find(e.u), b = find(e.v);
        if (a != b) {
            par[a] = b;
            cost += e.w;
            cnt++;
        }
    }
    return {cost, cnt == n - 1};
}
/*LATEX_DESC_BEGIN***************************
-> **Kruskal - arvore geradora minima**
Calcula a MST de um grafo nao direcionado e diz se ele e conexo. 0-based.
Arestas como KEdge{w, u, v}; use ll no custo.

Complexidade: O(m log m) tempo (ordenacao), O(n + m) memoria
Uso:
  auto [custo, conexo] = kruskal(n, edges);
  // conexo == false se a MST nao usa n-1 arestas

* Sobre o codigo:
  Ordena as arestas por peso e une com DSU (find com compressao) sempre que
  as pontas estao em componentes diferentes. Conta as arestas aceitas.

* Problemas e reducoes:
  + MST de grafo nao direcionado.
  + Gargalo minimax: a MST minimiza a maior aresta entre dois vertices.
  + Componentes por limiar de peso: processe arestas em ordem e pare no limiar.
  + Floresta geradora minima: o mesmo codigo sem exigir conexidade.
  + Aresta obrigatoria/proibida: rode Kruskal com ela fixada ou removida.

Cuidados: MST nao e unica com pesos iguais. Ordem {w,u,v} importa no sort.
  Para segunda MST e preciso LCA sobre a MST (nao implementado aqui).
Catalogo: Grafos (MST/Kruskal, gargalo minimax, componentes por peso).
Digitacao: 23 linhas | facil.
*****************************LATEX_DESC_END*/
