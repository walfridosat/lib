// Contar pares (u<v) com dist(u,v) <= K via centroide (arestas ponderadas >= 0)
//
// O que faz: para cada centroide junta as distancias da componente, conta pares com
//   soma <= K por two pointers (ordenado) e subtrai os pares da mesma subarvore filha.
// Quando usar: "caminhos com soma de peso <= K", "comprimento = k" (troque a contagem)
//   (Catalogo > Arvores, "Contar caminhos ... via centroide").
// Complexidade: O(n log^2 n).
// Uso: ll r = count_paths_le(g, K); g[v] = vector<pair<int,int>> (vizinho, peso). 0-based.
//   Para comprimento EXATO k use, no lugar de cnt(), contagem por valor: map/vetor de
//   frequencias (cnt[d]) e some freq[k - d].
// Cuidados: pares nao ordenados, u != v. Iterativo. Peso negativo nao pode (sem
//   problema para a contagem, mas dist por soma e o que se pede).
static ll cnt_le(vector<ll>& a, ll K) {       // pares i<j com a[i]+a[j] <= K
    sort(a.begin(), a.end());
    ll r = 0; int j = (int)a.size() - 1;
    for (int i = 0; i < (int)a.size(); i++) {
        while (j >= 0 && a[i] + a[j] > K) j--;
        r += j + 1;
        if (j >= i) r--;                       // tirou o par (i,i)
    }
    return r / 2;
}
ll count_paths_le(const vector<vector<pair<int,int>>>& g, ll K) {
    int n = g.size();
    vector<char> dead(n, 0);
    vector<int> sz(n), par(n), ord;
    vector<ll> dd(n);
    ll ans = 0;
    vector<int> st = {0};
    while (!st.empty()) {
        int s = st.back(); st.pop_back();
        ord.assign(1, s); par[s] = -1;
        for (int i = 0; i < (int)ord.size(); i++) {
            int v = ord[i]; sz[v] = 1;
            for (auto [w, _] : g[v]) if (!dead[w] && w != par[v]) par[w] = v, ord.push_back(w);
        }
        for (int i = ord.size() - 1; i > 0; i--) sz[par[ord[i]]] += sz[ord[i]];
        int c = s, tot = ord.size();
        while (true) {
            bool mv = false;
            for (auto [w, _] : g[c]) if (!dead[w] && w != par[c] && sz[w] * 2 > tot) { c = w; mv = true; break; }
            if (!mv) break;
        }
        dead[c] = 1;
        vector<ll> all = {0};
        for (auto [w, wt] : g[c]) if (!dead[w]) {
            vector<ll> sub;
            ord.assign(1, w); par[w] = c; dd[w] = wt;
            for (int i = 0; i < (int)ord.size(); i++) {
                int v = ord[i]; sub.push_back(dd[v]);
                for (auto [x, xw] : g[v]) if (!dead[x] && x != par[v]) par[x] = v, dd[x] = dd[v] + xw, ord.push_back(x);
            }
            ans -= cnt_le(sub, K);             // pares dentro da mesma subarvore (contados em 'all')
            all.insert(all.end(), sub.begin(), sub.end());
            st.push_back(w);
        }
        ans += cnt_le(all, K);
    }
    return ans;
}
