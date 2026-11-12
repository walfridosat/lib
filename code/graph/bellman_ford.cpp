// Bellman-Ford - pesos negativos e ciclo
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
    // n rodadas extra propagam BF_NINF
    for (int it = 0; it < n; it++)
        for (auto& x : e) {
            if (d[x.u] == BF_INF) continue;
            if (d[x.u] == BF_NINF) d[x.v] = BF_NINF;
            else if (d[x.u] + x.w < d[x.v]) d[x.v] = BF_NINF;
        }
    return d;
}

// ciclo negativo qualquer; d=0: super-fonte
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
    for (int i = 0; i < n; i++) x = p[x];   // n passos pelos pais: entra no ciclo
    vector<int> cyc;
    for (int v = x;; v = p[v]) {
        cyc.push_back(v);
        if (v == x && cyc.size() > 1) break;
    }
    reverse(cyc.begin(), cyc.end());         // agora cyc.front()==cyc.back()
    cyc.pop_back();
    return cyc;                              // ciclo na ordem das arestas u->v
}
/*LATEX_DESC_BEGIN***************************
-> **Bellman-Ford - pesos negativos e ciclo negativo**
Distancias de fonte unica com pesos negativos; marca -infinito o que e
alcancavel a partir de ciclo negativo e extrai um ciclo negativo explicito.

Complexidade: O(n*m)
Uso:
  vector<EdgeBF> e = {{u, v, w}, ...};  // 0-based
  vector<ll> d = bellman(n, e, s);      // BF_INF = inalcancavel, BF_NINF = -inf
  vector<int> cyc = neg_cycle(n, e);    // vazio se nao ha ciclo negativo

* Sobre o codigo:
  Relaxa todas as arestas n-1 vezes. Mais n rodadas propagam BF_NINF por quem
  ainda relaxa. neg_cycle parte de d=0 em todos (super-fonte implicita), guarda
  pais e sobe n passos para garantir um vertice dentro do ciclo.

* Problemas e reducoes:
  + Sistema x_j - x_i <= c: aresta i -> j de peso c; viavel sse nao ha ciclo
    negativo, e d satisfaz as restricoes.
  + Ciclo negativo explicito: use neg_cycle para recuperar os vertices.
  + Arbitragem de moedas: peso = -log(taxa); ciclo negativo = lucro.
  + Johnson/MCMF: potenciais h obtidos por Bellman-Ford de super-fonte.
  + Vertices afetados por ciclo negativo: d[v] == BF_NINF.

Cuidados: INF/NINF sao sentinelas; use pesos bem menores que BF_INF para nao
  estourar ll. Para fila use SPFA (code/graph/spfa.cpp).
Catalogo: Grafos (Bellman-Ford, ciclo negativo, restricoes).
Digitacao: 43 linhas | media. Atalho: bellman e neg_cycle repetem o laco de relaxamento.
*****************************LATEX_DESC_END*/
