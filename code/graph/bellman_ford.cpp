// Bellman-Ford (ciclo negativo, -infinito, ciclo explicito)
//
// O que faz: distancias com pesos negativos; marca vertices com dist -INF (alcancaveis
//   a partir de ciclo negativo); acha um ciclo negativo explicito em qualquer parte do grafo.
// Quando usar: Catalogo > Grafos ("Bellman-Ford em n passos detecta ciclo negativo",
//   "Ciclo negativo explicito", "Restricoes x_j - x_i <= c").
// Complexidade: O(n*m)
// Uso: edges = vector<EdgeBF>{u,v,w}, 0-based.
//   d = bellman(n, edges, s): d[v]=BF_INF (inalcancavel) ou BF_NINF (ciclo negativo no caminho).
//   cyc = neg_cycle(n, edges): vertices do ciclo em ordem (vazio se nao ha).
// Cuidados: INF/NINF sao sentinelas; pesos devem ser bem menores que INF.
//   Para SPFA com fila ver code/graph/spfa.cpp.
struct EdgeBF { int u, v; ll w; };
const ll BF_INF = LLONG_MAX / 4, BF_NINF = -BF_INF;

vector<ll> bellman(int n, const vector<EdgeBF>& e, int s) {
    vector<ll> d(n, BF_INF);
    d[s] = 0;
    for (int it = 0; it < n - 1; it++) {
        bool ch = false;
        for (auto& x : e)
            if (d[x.u] < BF_INF && d[x.u] + x.w < d[x.v]) d[x.v] = d[x.u] + x.w, ch = true;
        if (!ch) break;
    }
    // mais n rodadas: tudo que ainda relaxa (ou e alcancado por quem relaxa) vira -INF
    for (int it = 0; it < n; it++)
        for (auto& x : e) {
            if (d[x.u] == BF_INF) continue;
            if (d[x.u] == BF_NINF) d[x.v] = BF_NINF;
            else if (d[x.u] + x.w < d[x.v]) d[x.v] = BF_NINF;
        }
    return d;
}

// Acha ciclo negativo qualquer (dist inicial 0 em todos = super-fonte implicita).
vector<int> neg_cycle(int n, const vector<EdgeBF>& e) {
    vector<ll> d(n, 0);
    vector<int> p(n, -1);
    int x = -1;
    for (int it = 0; it < n; it++) {
        x = -1;
        for (auto& ed : e)
            if (d[ed.u] + ed.w < d[ed.v]) {
                d[ed.v] = d[ed.u] + ed.w; p[ed.v] = ed.u; x = ed.v;
            }
        if (x == -1) return {};
    }
    for (int i = 0; i < n; i++) x = p[x];   // anda n passos pelos pais: garante estar dentro do ciclo
    vector<int> cyc;
    for (int v = x;; v = p[v]) {
        cyc.push_back(v);
        if (v == x && cyc.size() > 1) break;
    }
    reverse(cyc.begin(), cyc.end());         // agora cyc.front()==cyc.back()
    cyc.pop_back();
    return cyc;                              // ciclo na ordem das arestas u->v
}
