// Floyd-Warshall (distancias, ciclo negativo, caminho, ciclo minimo)
//
// O que faz: todos-os-pares em O(n^3). floyd(): trata ciclo negativo (-INF) e guarda
//   proximo vertice para reconstruir caminho. min_cycle_w(): ciclo de peso minimo.
// Quando usar: Catalogo > Grafos ("Floyd como fecho de qualquer semianel", "Floyd com
//   ciclo minimo", "adicao incremental de vertices"). n <= ~400-500.
// Complexidade: O(n^3)
// Uso: d[i][j] = peso (FL_INF se nao ha aresta), d[i][i]=0. floyd(d, nxt);
//   depois d[i][j]==FL_INF inalcancavel, ==FL_NINF se passa por ciclo negativo.
//   path(nxt,i,j) devolve vertices (so use se d[i][j] finito). 0-based.
// Cuidados: a ordem k externo e essencial. Troque min/+ por or/and (fecho transitivo)
//   ou max/min (gargalo). "Remova vertices na ordem e some distancias": inverta a ordem
//   e adicione o vertice k como intermediario por vez (o laco k ja faz isso).
const ll FL_INF = LLONG_MAX / 4, FL_NINF = -FL_INF;

void floyd(vector<vector<ll>>& d, vector<vector<int>>& nxt) {
    int n = d.size();
    nxt.assign(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) if (d[i][j] < FL_INF) nxt[i][j] = j;
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++) if (d[i][k] < FL_INF)
            for (int j = 0; j < n; j++) if (d[k][j] < FL_INF)
                if (d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = max(FL_NINF, d[i][k] + d[k][j]);
                    nxt[i][j] = nxt[i][k];
                }
    // propaga -INF: se k esta em ciclo negativo e existe i->k e k->j
    for (int k = 0; k < n; k++) if (d[k][k] < 0)
        for (int i = 0; i < n; i++) if (d[i][k] < FL_INF)
            for (int j = 0; j < n; j++) if (d[k][j] < FL_INF) d[i][j] = FL_NINF;
}

vector<int> path(const vector<vector<int>>& nxt, int i, int j) {
    vector<int> p = {i};
    while (i != j) { i = nxt[i][j]; p.push_back(i); }
    return p;
}

// Ciclo de peso minimo em grafo orientado, pesos >= 0 (sem self-loop).
// w[i][j]=FL_INF se nao ha aresta. Para cada k: menor ciclo cujo maior indice e k
// = min d[i][j] + w[j][k] + w[k][i], com d usando so intermediarios < k.
ll min_cycle_w(const vector<vector<ll>>& w) {
    int n = w.size();
    vector<vector<ll>> d = w;
    for (int i = 0; i < n; i++) d[i][i] = 0;
    ll best = FL_INF;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < k; i++)
            for (int j = 0; j < k; j++)
                if (d[i][j] < FL_INF && w[j][k] < FL_INF && w[k][i] < FL_INF)
                    best = min(best, d[i][j] + w[j][k] + w[k][i]);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (d[i][k] < FL_INF && d[k][j] < FL_INF) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    }
    return best;   // FL_INF se aciclico
}
