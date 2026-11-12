// Sequencias de graus - Erdos-Gallai, Havel-Hakimi e arvore
bool isGraphic(vector<ll> d) {
    ll n = d.size(), s = 0; for (ll x : d) { if (x < 0 || x >= max(n, 1LL)) return n == 1 && x == 0 ? true : false; s += x; }
    if (s & 1) return false;
    sort(d.rbegin(), d.rend());
    vector<ll> pre(n + 1, 0); for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + d[i];
    for (ll k = 1; k <= n; k++) {
        ll rhs = k * (k - 1);
        for (ll i = k; i < n; i++) rhs += min(d[i], k);   // O(n^2) simples; troque por busca binaria se n grande
        if (pre[k] > rhs) return false;
    }
    return true;
}
// retorna true se construiu; edges recebe as arestas
bool havelHakimi(const vector<ll>& d, vector<pair<int, int>>& edges) {
    edges.clear();
    vector<pair<ll, int>> a;                        // (grau restante, id) dos vertices ainda ativos
    for (int i = 0; i < (int)d.size(); i++) a.push_back({d[i], i});
    while (!a.empty()) {
        sort(a.rbegin(), a.rend());                 // maior grau primeiro
        auto [k, v] = a[0]; a.erase(a.begin());     // remove o maior e liga aos k maiores seguintes
        if (k < 0 || k > (ll)a.size()) return false;
        for (int j = 0; j < k; j++) {
            if (a[j].first <= 0) return false;
            a[j].first--; edges.push_back({v, a[j].second});
        }
    }
    return true;
}
// arvore com graus d_i (equivalente a Prufer)
vector<pair<int, int>> treeFromDegrees(const vector<ll>& d) {
    int n = d.size(); vector<pair<int, int>> e;
    if (n == 1) return d[0] == 0 ? e : vector<pair<int, int>>{{-1, -1}};
    ll s = 0; for (ll x : d) { if (x < 1) return {{-1, -1}}; s += x; }
    if (s != 2LL * (n - 1)) return {{-1, -1}};       // sinal de impossivel: aresta {-1,-1}
    vector<int> leaves, inner;
    for (int i = 0; i < n; i++) (d[i] == 1 ? leaves : inner).push_back(i);
    vector<ll> rem(d.begin(), d.end());
    // encadeia internos e pendura folhas
    for (size_t i = 0; i + 1 < inner.size(); i++) e.push_back({inner[i], inner[i + 1]}), rem[inner[i]]--, rem[inner[i + 1]]--;
    size_t li = 0;
    for (int v : inner) while (rem[v] > 0) { e.push_back({v, leaves[li++]}); rem[v]--; }
    if (inner.empty()) e.push_back({leaves[0], leaves[1]});   // n=2
    return e;
}
/*LATEX_DESC_BEGIN***************************
-> **Sequencias de Graus**
isGraphic testa se d e grafica; havelHakimi constroi grafo simples com graus dados;
treeFromDegrees constroi arvore com graus dados.

Complexidade: Erdos-Gallai O(n log n); Havel-Hakimi O(n^2 log n) simples
Uso:
  bool ok = isGraphic(d);
  vector<pair<int,int>> e; bool ok = havelHakimi(d, e);  // arestas 0-based
  vector<pair<int,int>> t = treeFromDegrees(d);  // {-1,-1} se impossivel

* Sobre o codigo:
  Erdos-Gallai usa prefixos e confere o sum dos k maiores <= k(k-1) + sum min(d_i, k).
  Havel-Hakimi remove o maior grau e liga aos k maiores restantes.
  treeFromDegrees encadeia os internos e pendura folhas no grau restante.

* Problemas e reducoes:
  + Construir grafo simples com sequencia de graus dada.
  + Construir arvore com d_i dados: precisa sum(d) = 2(n-1) e todos >= 1.
  + Grafo bipartido com graus dados: use Gale-Ryser.

Cuidados: sem lacos nem multiarestas; n = 1 com d = 0 e arvore trivial;
  treeFromDegrees sinaliza impossivel com a aresta {-1,-1}.
Catalogo: Construtivos e interativos (Grafo com graus dados, Construir grafo com sequencia de graus, Construir arvore com graus dados)
Digitacao: 44 linhas | media.
*****************************LATEX_DESC_END*/
