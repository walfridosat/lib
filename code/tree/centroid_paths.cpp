// Centroide - contar pares com distancia <= K
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
            ans -= cnt_le(sub, K);             // pares da mesma subarvore (ja em all)
            all.insert(all.end(), sub.begin(), sub.end());
            st.push_back(w);
        }
        ans += cnt_le(all, K);
    }
    return ans;
}
/*LATEX_DESC_BEGIN***************************
-> **Contar pares com dist(u,v) <= K (centroide)**
Para cada centroide junta as distancias da componente, conta pares com soma
<= K por two pointers sobre o vetor ordenado e subtrai os pares da mesma
subarvore filha. Arestas ponderadas >= 0, 0-based.

Complexidade: O(n log^2 n)
Uso:
  // g[v] = vector<pair<int,int>> (vizinho, peso)
  ll r = count_paths_le(g, K);   // pares nao ordenados u < v
  // para comprimento EXATO k troque cnt_le por frequencias e some freq[k-d]

* Sobre o codigo:
  Mesma decomposicao por centroides de centroid.cpp. Em cada centroide:
  all = distancias da componente ate ele; para cada filho, subtrai cnt_le(sub)
  e depois soma cnt_le(all), evitando contar duas vezes pares da mesma subarvore.
  cnt_le ordena e usa dois ponteiros.

* Problemas e reducoes:
  + Pares com distancia <= K / soma de pesos <= K: count_paths_le.
  + Pares com distancia exata k: frequencias no lugar de two pointers.
  + Numero de caminhos que passam por cada centroide: combine subarvores.
  + Menor/maior distancia entre pares: adapte a comparacao.

Cuidados: pares nao ordenados, u != v. Peso negativo invalida a soma como
  distancia. Iterativo, sem recursao.
Catalogo: Arvores (contar caminhos via centroide).
Digitacao: 48 linhas | dificil. Atalho: a decomposicao por centroides repete
  centroid.cpp; extraia um helper comum.
*****************************LATEX_DESC_END*/
