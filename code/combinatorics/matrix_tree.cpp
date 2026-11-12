// Matrix-Tree (Kirchhoff), determinante mod p e mod composto
//
// O que faz: det de matriz mod primo (Gauss) e mod qualquer m (eliminacao tipo
//   Euclides, sem inverso); # arvores geradoras (multigrafo, pesos) e
//   # arborescencias (dirigido, raiz escolhida); # circuitos eulerianos (BEST).
// Quando usar: "Catalogo > Combinatoria" (Matrix-Tree; BEST theorem; Determinantes
//   uteis). Tambem sobre n <= ~400. Grid grande/planar: Kasteleyn (nao incluso).
// Complexidade: O(n^3) (Euclides: O(n^3 log m)).
// Uso: det_mod(a, p) (p primo; a vetor<vector<ll>>), det_euclid(a, m) (m qualquer),
//   spanning_trees(n, arestas {u,v[,w]}, m) , arborescences(n, arestas {u->v}, raiz, m),
//   euler_circuits(n, arestas dirigidas) (grafo conexo c/ in=out em todo vertice).
//   Vertices 0-based. Resultado mod MT (primo) ou m dado.
// Cuidados: det_mod usa pivot != 0 e troca de linhas (sinal). Laplaciano usa
//   remocao da linha/coluna da raiz. BEST: circuitos contados como ciclos sem
//   ponto inicial; multiplica por (deg-1)! de cada vertice (precisa fact local).
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
// det mod m qualquer: Euclides entre linhas (so usa divisao inteira)
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
// # arvores geradoras (soma dos produtos de pesos) de multigrafo nao dirigido
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
// # arborescencias com raiz r (arestas u->v apontam para longe da raiz); Laplaciano de grau de entrada
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
// BEST: circuitos eulerianos (sem ponto inicial) = t_w(G) * prod (deg(v)-1)!
ll euler_circuits(int n, const vector<MEdge>& E) {
    vector<int> deg(n, 0);
    for (auto& e : E) deg[e.u]++;
    ll res = arborescences(n, E, 0, MT); // t_w para qualquer raiz w (aqui 0), arestas de entrada na raiz irrelevantes
    // Obs: usa arborescencia "para longe da raiz"; em grafo euleriano o numero coincide com o de "para a raiz".
    for (int v = 0; v < n; v++) {
        if (!deg[v]) continue;
        for (int i = 2; i < deg[v]; i++) res = res * i % MT; // (deg-1)!
    }
    return res;
}
