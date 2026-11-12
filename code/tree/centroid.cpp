// Centroid decomposition (arvore de centroides + distancias por nivel)
//
// O que faz: constroi a arvore de centroides (altura <= log n). Para cada vertice v
//   guarda cpar[v] (pai na arvore de centroides), lvl[v] e dist[v][l] = distancia de v ao
//   seu ancestral centroide de nivel l. Inclui o exemplo "vertice marcado mais proximo".
// Quando usar: caminhos com condicao, "distancia ao marcado mais proximo", soma de
//   distancias a marcados (Catalogo > Arvores, "Centroid tree").
// Complexidade: build O(n log n), update/query O(log n), memoria O(n log n).
// Uso: Centroid c(g)  com g[v] = vector<pair<int,int>> (vizinho, peso) -- peso 1 se nao ha.
//   c.cpar[v] (-1 na raiz), c.lvl[v], c.d[v][l].
//   Nearest N(c): N.mark(v); N.query(v) = menor dist a um marcado (INF se nenhum).
//   Para soma de dist a marcados: mantenha cnt[a], sum[a], sumpar[a] (soma das dist ao pai
//   centroide) e some em cada ancestral a de v: sum[a] + cnt[a]*d[v][lvl[a]] - (sumpar[ch] +
//   cnt[ch]*d[v][lvl[a]]) para o filho ch no caminho (evita contar duas vezes).
// Cuidados: 0-based, arestas (viz, peso). Iterativo (sem recursao). Dist em ll.
struct Centroid {
    int n;
    vector<int> cpar, lvl;
    vector<vector<ll>> d;                  // d[v][l], l = 0..lvl[v]
    Centroid(const vector<vector<pair<int,int>>>& g) : n(g.size()), cpar(n, -1), lvl(n, 0), d(n) {
        vector<char> dead(n, 0);
        vector<int> sz(n), par(n), ord;
        vector<array<int,3>> st = {{0, -1, 0}};      // (qualquer vertice da componente, centroide pai, nivel)
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
