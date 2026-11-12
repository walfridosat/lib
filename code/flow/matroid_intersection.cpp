// Interseccao de matroides (cardinalidade maxima e peso maximo)
//
// O que faz: maior conjunto S do universo {0..n-1} independente em DUAS matroides, via
//   caminhos aumentantes no grafo de trocas. Com pesos: maximiza o peso total (caminho
//   de custo minimo com menos arestas, SPFA).
// Quando usar: arvore geradora arco-iris (grafica ^ particao por cor), arborescencia
//   (grafica ^ in-grau<=1), matching bipartido (particao ^ particao), "floresta +
//   matching", escalonamento (Catalogo > Otimizacao: "Interseccao de matroides",
//   "Matroides do dia a dia", "Uniao de matroides").
// Complexidade: r augmentacoes, cada uma O(r*n) chamadas ao oraculo (+SPFA). Pequeno/medio.
// Uso: auto S = matroidInter(n, ind1, ind2[, w]);
//   ind1/ind2: bool f(const vector<int>& S) -> S e independente na matroide?
//   w[i] = peso (vazio = so cardinalidade maxima). Devolve os indices escolhidos.
//   Com pesos devolve o conjunto de MAIOR PESO (qualquer tamanho; pesos podem ser < 0).
//   Prontos: partOracle(cor, cap) e graphOracle(nVertices, arestas).
// Cuidados: o oraculo deve ser rapido (O(|S|)). Para max peso de tamanho fixo k, pegue
//   o k-esimo prefixo (veja comentario no codigo). 0-indexed.
typedef function<bool(const vector<int>&)> MOracle;
// matroide de particao: no maximo cap[c] elementos de cor c
MOracle partOracle(vector<int> color, vector<int> cap) {
    return [=](const vector<int>& S) {
        vector<int> cnt(cap.size(), 0);
        for (int x : S) if (++cnt[color[x]] > cap[color[x]]) return false;
        return true;
    };
}
// matroide grafica: conjunto de arestas sem ciclo (aresta i = (u,v))
MOracle graphOracle(int nv, vector<pair<int,int>> ed) {
    return [=](const vector<int>& S) {
        vector<int> p(nv); iota(p.begin(), p.end(), 0);
        function<int(int)> f = [&](int x) { return p[x] == x ? x : p[x] = f(p[x]); };
        for (int x : S) {
            int a = f(ed[x].first), b = f(ed[x].second);
            if (a == b) return false;
            p[a] = b;
        }
        return true;
    };
}
vector<int> matroidInter(int n, MOracle ind1, MOracle ind2, vector<ll> w = {}) {
    if (w.empty()) w.assign(n, 0);
    vector<char> in(n, 0); vector<int> best; ll curW = 0, bestW = 0; // best = conjunto vazio
    while (true) {
        vector<int> I, O;
        for (int i = 0; i < n; i++) (in[i] ? I : O).push_back(i);
        vector<vector<int>> adj(n); vector<char> src(n, 0), snk(n, 0);
        vector<int> T = I;
        for (int x : O) {
            T.push_back(x);
            src[x] = ind1(T); snk[x] = ind2(T); // I+x independente em M1 / M2
            T.pop_back();
        }
        for (int y : I) {
            vector<int> R; for (int z : I) if (z != y) R.push_back(z);
            for (int x : O) {
                R.push_back(x);
                if (ind1(R)) adj[y].push_back(x); // y -> x se I-y+x em M1
                if (ind2(R)) adj[x].push_back(y); // x -> y se I-y+x em M2
                R.pop_back();
            }
        }
        // SPFA: custo do vertice = -w (fora de I) ou +w (dentro); desempate: menos arestas
        const ll INF = LLONG_MAX / 4;
        vector<pair<ll,int>> d(n, {INF, 0}); vector<int> par(n, -1); vector<char> inq(n, 0);
        deque<int> q;
        for (int x : O) if (src[x]) { d[x] = {-w[x], 1}; q.push_back(x); inq[x] = 1; }
        while (!q.empty()) {
            int u = q.front(); q.pop_front(); inq[u] = 0;
            for (int v : adj[u]) {
                pair<ll,int> nd = {d[u].first + (in[v] ? w[v] : -w[v]), d[u].second + 1};
                if (nd < d[v]) { d[v] = nd; par[v] = u; if (!inq[v]) inq[v] = 1, q.push_back(v); }
            }
        }
        int e = -1;
        for (int x : O) if (snk[x] && d[x].first < INF && (e < 0 || d[x] < d[e])) e = x;
        if (e < 0) break;
        for (int v = e; v >= 0; v = par[v]) in[v] ^= 1; // troca ao longo do caminho
        curW -= d[e].first;
        if (curW >= bestW) { // >= para preferir o maior tamanho em empate
            bestW = curW; best.clear();
            for (int i = 0; i < n; i++) if (in[i]) best.push_back(i);
        }
    }
    return best;
}
