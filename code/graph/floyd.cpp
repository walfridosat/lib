// Floyd-Warshall
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
    // propaga -INF por ciclo negativo em k
    for (int k = 0; k < n; k++) if (d[k][k] < 0)
        for (int i = 0; i < n; i++) if (d[i][k] < FL_INF)
            for (int j = 0; j < n; j++) if (d[k][j] < FL_INF) d[i][j] = FL_NINF;
}

vector<int> path(const vector<vector<int>>& nxt, int i, int j) {
    vector<int> p = {i};
    while (i != j) { i = nxt[i][j]; p.push_back(i); }
    return p;
}

// ciclo de peso minimo; pesos >= 0, sem self-loop
// FL_INF = sem aresta; maior indice do ciclo e k
// min d[i][j]+w[j][k]+w[k][i]; intermed. < k
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
/*LATEX_DESC_BEGIN***************************
-> **Floyd-Warshall - todos os pares**
Distancias entre todos os pares em O(n^3). Trata ciclo negativo (-INF) e
guarda o proximo vertice para reconstruir caminho; min_cycle_w acha o ciclo
de peso minimo. 0-based.

Complexidade: O(n^3); use n <= ~400-500
Uso:
  d[i][j] = peso (FL_INF se nao ha aresta), d[i][i] = 0;
  floyd(d, nxt);
  // d[i][j] == FL_INF inalcancavel; d[i][j] == FL_NINF passa por ciclo negativo
  vector<int> p = path(nxt, i, j);        // so se d[i][j] finito
  ll c = min_cycle_w(w);                  // FL_INF se aciclico

* Sobre o codigo:
  Laco k externo: k e o maior indice intermediario permitido. nxt[i][j] = j
  inicial e vira nxt[i][k] ao melhorar. Depois uma passada propaga FL_NINF
  por vertices em ciclo negativo. min_cycle_w usa d com intermediarios < k e
  fecha o ciclo por w[j][k] + w[k][i].

* Problemas e reducoes:
  + Todos os pares com n pequeno (mais simples que Johnson/Dijkstra).
  + Fecho transitivo: troque min/+ por or/and.
  + Gargalo/minimax: troque min/+ por max/min.
  + Ciclo negativo: d[i][i] < 0 e propagacao FL_NINF.
  + Ciclo de peso minimo orientado: min_cycle_w.
  + "Adicionar vertices e somar distancias": inverta a ordem; o laco k ja faz isso.

Cuidados: a ordem k externo e essencial. FL_INF/FL_NINF sao sentinelas; nao
  some pesos nelas. min_cycle_w supoe pesos >= 0 e sem self-loop.
Catalogo: Grafos (Floyd, fecho, ciclo minimo, adicao incremental).
Digitacao: 42 linhas | media.
*****************************LATEX_DESC_END*/
