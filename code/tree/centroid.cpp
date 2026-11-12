// Centroid - decomposicao e distancias por nivel
struct Centroid {
    int n;
    vector<int> cpar, lvl;
    vector<vector<ll>> d;                  // d[v][l], l = 0..lvl[v]
    Centroid(const vector<vector<pair<int,int>>>& g) : n(g.size()), cpar(n, -1), lvl(n, 0), d(n) {
        vector<char> dead(n, 0);
        vector<int> sz(n), par(n), ord;
        vector<array<int,3>> st = {{0, -1, 0}};      // (vertice, centroide pai, nivel)
        while (!st.empty()) {
            auto [s, cp, l] = st.back(); st.pop_back();
            ord.assign(1, s); par[s] = -1;
            for (int i = 0; i < (int)ord.size(); i++) {      // BFS da componente
                int v = ord[i]; sz[v] = 1;
                for (auto [w, _] : g[v]) if (!dead[w] && w != par[v]) par[w] = v, ord.push_back(w);
            }
            for (int i = ord.size() - 1; i > 0; i--) sz[par[ord[i]]] += sz[ord[i]];
            int c = s, tot = ord.size();
            while (true) {                               // desce pelo filho com sz > tot/2
                bool mv = false;
                for (auto [w, _] : g[c]) if (!dead[w] && w != par[c] && sz[w] * 2 > tot) { c = w; mv = true; break; }
                if (!mv) break;
            }
            cpar[c] = cp; lvl[c] = l; dead[c] = 1;
            // distancias de todos da componente ate c
            ord.assign(1, c); par[c] = -1; d[c].resize(l + 1); d[c][l] = 0;
            for (int i = 0; i < (int)ord.size(); i++) {
                int v = ord[i];
                for (auto [w, wt] : g[v]) if (!dead[w] && w != par[v]) {
                    par[w] = v; d[w].resize(l + 1); d[w][l] = d[v][l] + wt; ord.push_back(w);
                }
            }
            for (auto [w, _] : g[c]) if (!dead[w]) st.push_back({w, c, l + 1});
        }
    }
};

// Exemplo: vertice marcado mais proximo (marcar e perguntar)
struct Nearest {
    const Centroid& c; vector<ll> best;
    static constexpr ll INF = LLONG_MAX / 4;
    Nearest(const Centroid& c_) : c(c_), best(c_.n, INF) {}
    void mark(int v) {
        for (int a = v; a != -1; a = c.cpar[a]) best[a] = min(best[a], c.d[v][c.lvl[a]]);
    }
    ll query(int v) const {
        ll r = INF;
        for (int a = v; a != -1; a = c.cpar[a]) r = min(r, c.d[v][c.lvl[a]] + best[a]);
        return r;
    }
};
/*LATEX_DESC_BEGIN***************************
-> **Centroid decomposition**
Constroi a arvore de centroides (altura <= log n). Para cada v guarda cpar[v]
(pai na arvore, -1 na raiz), lvl[v] e d[v][l] = distancia de v ao ancestral
centroide de nivel l. Inclui o exemplo "marcado mais proximo". 0-based.

Complexidade: build O(n log n); update/query O(log n); memoria O(n log n)
Uso:
  // g[v] = vector<pair<int,int>> (vizinho, peso); peso 1 se nao ha
  Centroid c(g);                 // c.cpar[v], c.lvl[v], c.d[v][l]
  Nearest N(c); N.mark(v); N.query(v);   // menor dist a marcado (INF se nenhum)
  // soma de dist a marcados: cnt[a], sum[a], sumpar[a] por centroide a; em cada
  // ancestral a de v some sum[a] + cnt[a]*d[v][lvl[a]] menos a parte do filho ch:
  // sumpar[ch] + cnt[ch]*d[v][lvl[a]]

* Sobre o codigo:
  Para cada componente, BFS calcula tamanhos, desce ate o centroide e o marca
  morto. Nivel l e atribuido na construcao; uma segunda BFS grava d[v][l] de
  todos os vertices da componente ate o centroide. Pilha explicita, sem recursao.

* Problemas e reducoes:
  + Distancia ao vertice marcado mais proximo: Nearest.
  + Soma de distancias a todos os marcados: cnt/sum/sumpar.
  + Caminhos que passam por um centroide (condicao de distancia): combine
    subarvores em cada centroide.
  + Contagem de caminhos com distancia <= K (centroid_paths).
  + Distancia entre u e v via ancestrais comuns na arvore de centroides.

Cuidados: arestas (vizinho, peso), dist em ll. Iterativo. Cada vertice aparece
  em O(log n) niveis, dai a memoria O(n log n).
Catalogo: Arvores (centroid tree, caminhos por centroide).
Digitacao: 49 linhas | dificil.
*****************************LATEX_DESC_END*/
