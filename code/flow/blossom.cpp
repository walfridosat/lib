// Blossom - matching maximo em grafo geral
struct Blossom {
    int n; vector<vector<int>> g; vector<int> mt, p, base, q; vector<char> used, bl;
    Blossom(int n) : n(n), g(n), mt(n, -1), p(n), base(n), q(n), used(n), bl(n) {}
    void add(int u, int v) { if (u != v) g[u].push_back(v), g[v].push_back(u); }
    int lca(int a, int b) {
        vector<char> u(n, 0);
        for (;;) { a = base[a]; u[a] = 1; if (mt[a] < 0) break; a = p[mt[a]]; }
        for (;;) { b = base[b]; if (u[b]) return b; b = p[mt[b]]; }
    }
    void markPath(int v, int b, int ch) { // marca o caminho ate a base b do blossom
        while (base[v] != b) {
            bl[base[v]] = bl[base[mt[v]]] = 1;
            p[v] = ch; ch = mt[v]; v = p[mt[v]];
        }
    }
    int findPath(int root) { // BFS alternada; devolve o fim livre do caminho aumentante
        fill(used.begin(), used.end(), 0); fill(p.begin(), p.end(), -1);
        for (int i = 0; i < n; i++) base[i] = i;
        used[root] = 1; int qh = 0, qt = 0; q[qt++] = root;
        while (qh < qt) {
            int v = q[qh++];
            for (int to : g[v]) {
                if (base[v] == base[to] || mt[v] == to) continue;
                if (to == root || (mt[to] >= 0 && p[mt[to]] >= 0)) { // acha blossom
                    int cb = lca(v, to);
                    fill(bl.begin(), bl.end(), 0);
                    markPath(v, cb, to); markPath(to, cb, v);
                    for (int i = 0; i < n; i++) if (bl[base[i]]) {
                        base[i] = cb;
                        if (!used[i]) used[i] = 1, q[qt++] = i;
                    }
                } else if (p[to] < 0) {
                    p[to] = v;
                    if (mt[to] < 0) return to;
                    used[mt[to]] = 1; q[qt++] = mt[to];
                }
            }
        }
        return -1;
    }
    int solve() {
        for (int i = 0; i < n; i++) if (mt[i] < 0) // init guloso
            for (int to : g[i]) if (mt[to] < 0) { mt[to] = i; mt[i] = to; break; }
        for (int i = 0; i < n; i++) if (mt[i] < 0) {
            int v = findPath(i);
            while (v >= 0) { int pv = p[v], ppv = mt[pv]; mt[v] = pv; mt[pv] = v; v = ppv; }
        }
        int r = 0;
        for (int i = 0; i < n; i++) if (mt[i] > i) r++;
        return r;
    }
};
/*LATEX_DESC_BEGIN***************************
-> **Blossom (Edmonds) - matching maximo geral**
Matching de cardinalidade maxima em grafo nao direcionado qualquer, encolhendo
ciclos impares (blossoms). Vertices 0-indexed.

Complexidade: O(V^3) (V buscas, cada O(V^2)); ok para V ~ 500..1000.
Uso:
  Blossom b(n); b.add(u, v); int m = b.solve();
  b.mt[v] -> par de v (ou -1). Auto-lacos e arestas duplicadas sao tolerados.

* Sobre o codigo:
  findPath faz BFS alternada a partir de uma raiz livre. Ao achar aresta entre
  vertices de mesma paridade, lca acha a base do blossom e markPath contrai o
  ciclo ajustando base[]. solve() inicializa guloso e aumenta por caminhos.

* Problemas e reducoes:
  + Matching maximo em grafo geral: vertices = objetos, arestas = pares
    compativeis; resposta = solve(), pares em mt[].
  + Matching perfeito (1-fator): mesmo modelo; existe sse solve()*2 == n.
  + Dominos em tabuleiro com buracos: vertices = casas livres, arestas entre
    casas vizinhas; matching perfeito = cobertura completa por dominos.
  + Maximo de dominos sem sobrepor: mesmo modelo, resposta = matching maximo.
  + Maximo de pares disjuntos (pessoas/robos compativeis): idem item 1.
  + Cobertura minima por arestas (sem vertices isolados): mesmo grafo;
    resposta = n - solve() (pegue o matching e cubra o resto).
  + Emparelhamento perfeito dentro de um conjunto T (so arestas internas):
    remova vertices fora de T e teste matching perfeito no subgrafo induzido.
  + Matching com aresta (u,v) forcada: remova u e v, some 1 ao matching do
    restante; existe matching de tamanho k com (u,v) sse isso da k.

Cuidados: auto-lacos ignorados (v == to); arestas duplicadas ok. Sem recursao.
  0-indexed.
Catalogo: Grafos (matching geral, Tutte-Berge).
Digitacao: 52 linhas | dificil. Atalho: lca e markPath poderiam virar uma
  contrai() unica, ao custo de ficar mais dificil de depurar.
*****************************LATEX_DESC_END*/
