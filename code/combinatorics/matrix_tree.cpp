// Matrix-Tree, determinantes e circuitos eulerianos
const ll MT = 998244353;
ll mt_pw(ll b, ll e, ll m) { ll r = 1 % m; b %= m; if (b < 0) b += m; for (; e > 0; e >>= 1, b = b * b % m) if (e & 1) r = r * b % m; return r; }
ll det_mod(vector<vector<ll>> a, ll p = MT) { // p primo
    int n = a.size(); ll d = 1;
    for (auto& r : a) for (auto& x : r) x = ((x % p) + p) % p;
    for (int c = 0; c < n; c++) {
        int pv = -1;
        for (int i = c; i < n; i++) if (a[i][c]) { pv = i; break; }
        if (pv < 0) return 0;
        if (pv != c) { swap(a[pv], a[c]); d = (p - d) % p; }
        d = d * a[c][c] % p;
        ll iv = mt_pw(a[c][c], p - 2, p);
        for (int i = c + 1; i < n; i++) if (a[i][c]) {
            ll f = a[i][c] * iv % p;
            for (int j = c; j < n; j++) a[i][j] = ((a[i][j] - f * a[c][j]) % p + p) % p;
        }
    }
    return d;
}
// det mod m qualquer: Euclides entre linhas
ll det_euclid(vector<vector<ll>> a, ll m) {
    int n = a.size(); ll d = 1 % m;
    for (auto& r : a) for (auto& x : r) x = ((x % m) + m) % m;
    for (int c = 0; c < n; c++) {
        for (int i = c + 1; i < n; i++) {
            while (a[i][c]) {
                ll t = a[c][c] / a[i][c];
                for (int j = c; j < n; j++) a[c][j] = ((a[c][j] - t * a[i][j]) % m + m) % m;
                swap(a[c], a[i]); d = (m - d) % m;
            }
        }
        d = d * a[c][c] % m;
        if (!d) return 0;
    }
    return d;
}
struct MEdge { int u, v; ll w; };
// arvores geradoras de multigrafo nao dirigido
ll spanning_trees(int n, const vector<MEdge>& E, ll m = MT, bool prime = true) {
    if (n == 1) return 1 % m;
    vector<vector<ll>> L(n, vector<ll>(n, 0));
    for (auto& e : E) {
        if (e.u == e.v) continue; // lacos nao contam
        L[e.u][e.u] += e.w; L[e.v][e.v] += e.w; L[e.u][e.v] -= e.w; L[e.v][e.u] -= e.w;
        for (int x : {e.u, e.v}) for (int y : {e.u, e.v}) L[x][y] %= m;
    }
    vector<vector<ll>> M(n - 1, vector<ll>(n - 1));
    for (int i = 0; i < n - 1; i++) for (int j = 0; j < n - 1; j++) M[i][j] = L[i][j]; // remove ultima linha/coluna
    return prime ? det_mod(M, m) : det_euclid(M, m);
}
// arborescencias com raiz r (grau de entrada)
ll arborescences(int n, const vector<MEdge>& E, int r, ll m = MT, bool prime = true) {
    if (n == 1) return 1 % m;
    vector<vector<ll>> L(n, vector<ll>(n, 0));
    for (auto& e : E) {
        if (e.u == e.v) continue;
        L[e.v][e.v] = (L[e.v][e.v] + e.w) % m;           // grau de entrada
        L[e.u][e.v] = ((L[e.u][e.v] - e.w) % m + m) % m;  // -A[u][v]
    }
    vector<vector<ll>> M;
    for (int i = 0; i < n; i++) if (i != r) {
        vector<ll> row;
        for (int j = 0; j < n; j++) if (j != r) row.push_back(L[i][j]);
        M.push_back(row);
    }
    return prime ? det_mod(M, m) : det_euclid(M, m);
}
// BEST: circuitos eulerianos sem ponto inicial
ll euler_circuits(int n, const vector<MEdge>& E) {
    vector<int> deg(n, 0);
    for (auto& e : E) deg[e.u]++;
    ll res = arborescences(n, E, 0, MT); // t_w independe da raiz
    // em grafo euleriano os dois sentidos coincidem
    for (int v = 0; v < n; v++) {
        if (!deg[v]) continue;
        for (int i = 2; i < deg[v]; i++) res = res * i % MT; // (deg-1)!
    }
    return res;
}
/*LATEX_DESC_BEGIN***************************
-> **Matrix-Tree, determinantes e BEST**
Determinante mod primo ou composto, arvores geradoras, arborescencias e circuitos eulerianos.

Complexidade: O(n^3); det_euclid O(n^3 log m).
Uso:
  ll d = det_mod(a, p);                 // p primo
  ll e = det_euclid(a, m);              // m qualquer
  ll st = spanning_trees(n, E, m);
  ll ar = arborescences(n, E, r, m);
  ll ec = euler_circuits(n, E);

* Sobre o codigo:
  det_mod faz Gauss com inverso (p primo); det_euclid troca linhas por
  subtracoes inteiras, sem inverso. spanning_trees monta o Laplaciano e
  remove a ultima linha/coluna. arborescences usa o Laplaciano de grau de
  entrada e remove a raiz. euler_circuits multiplica por (deg-1)!.

* Problemas e reducoes:
  + Numero de arvores geradoras de um grafo (com pesos) -> spanning_trees.
  + Numero de arborescencias com raiz r -> arborescences.
  + Determinante de matriz mod primo -> det_mod.
  + Determinante mod composto (sem inverso) -> det_euclid.
  + Circuitos eulerianos de grafo dirigido -> euler_circuits (BEST).
  + Contar arvores de um multigrafo -> spanning_trees com pesos.
  + Matrix-Tree para grafos com arestas paralelas -> somar pesos.

Cuidados: det_mod usa pivot != 0 e troca de linhas (sinal); o Laplaciano
  remove a linha/coluna da raiz; BEST conta ciclos sem ponto inicial e precisa
  do fatorial local (deg-1)!.
Catalogo: Combinatoria.
Digitacao: 79 linhas | dificil. Atalho: det_mod e lgv_det sao iguais; mantenha uma copia.
*****************************LATEX_DESC_END*/
