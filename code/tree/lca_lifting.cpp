// LCA - binary lifting e caminho
struct LCA {
    int n, LG;
    vector<vector<int>> up;
    vector<int> d;
    LCA(const vector<vector<int>>& g, int r = 0) : n(g.size()) {
        LG = 1; while ((1 << LG) < n) LG++;
        up.assign(LG, vector<int>(n, r));
        d.assign(n, 0);
        vector<int> st = {r};
        while (!st.empty()) {
            int v = st.back(); st.pop_back();
            for (int w : g[v]) if (w != up[0][v]) {
                up[0][w] = v; d[w] = d[v] + 1;
                // pai de v ja tem a tabela pronta
                for (int k = 1; k < LG; k++) up[k][w] = up[k-1][up[k-1][w]];
                st.push_back(w);
            }
        }
    }
    int kth(int u, ll k) const {          // k-esimo ancestral de u (k=0 -> u)
        if (k > d[u]) return -1;
        for (int b = 0; b < LG; b++) if (k >> b & 1) u = up[b][u];
        return u;
    }
    int lca(int u, int v) const {
        if (d[u] < d[v]) swap(u, v);
        u = kth(u, d[u] - d[v]);
        if (u == v) return u;
        for (int b = LG - 1; b >= 0; b--)
            if (up[b][u] != up[b][v]) u = up[b][u], v = up[b][v];
        return up[0][u];
    }
    int dist(int u, int v) const { return d[u] + d[v] - 2 * d[lca(u, v)]; }
    int on_path(int u, int v, int k) const { // k-esimo vertice do caminho; -1 se nao existe
        int l = lca(u, v), a = d[u] - d[l], b = d[v] - d[l];
        if (k > a + b) return -1;
        return k <= a ? kth(u, k) : kth(v, a + b - k);
    }
    template<class F> int top(int u, F f) const { // sobe enquanto f(ancestral) for verdadeiro
        for (int b = LG - 1; b >= 0; b--)
            if (f(up[b][u])) u = up[b][u];
        return u;
    }
};
/*LATEX_DESC_BEGIN***************************
-> **LCA com binary lifting**
Pre-processa o pai 2^k de cada vertice; responde LCA, distancia, k-esimo
ancestral e k-esimo vertice do caminho u->v. 0-based.

Complexidade: build O(n log n); query O(log n); memoria O(n log n)
Uso:
  LCA t(g, raiz);        // g = lista de adjacencia
  t.lca(u, v);  t.dist(u, v);
  t.kth(u, k);           // k-esimo ancestral (-1 se k > d[u])
  t.on_path(u, v, k);    // k-esimo vertice do caminho (k = 0 -> u)
  t.top(u, f);           // ancestral mais alto w com f(w) verdadeiro, f monotona

* Sobre o codigo:
  up[j][v] = 2^j-esimo ancestral; up[0][raiz] = raiz. Build iterativo com
  pilha: ao empilhar w, a tabela do pai ja esta pronta. lca sobe u ate a
  profundidade de v e depois desce juntos pelos saltos que divergem.

* Problemas e reducoes:
  + LCA e distancia em arvore (arestas unitarias).
  + k-esimo ancestral: kth.
  + k-esimo vertice do caminho u->v: on_path.
  + Primeiro ancestral que satisfaz predicado monotono: top (ex.: peso > X).
  + Distancia com pesos: mantenha pref[] em ll e use pref[u]+pref[v]-2*pref[lca].
  + Saltos 2^k em grafo funcional: mesma ideia de up[][].

Cuidados: up[0][raiz] = raiz (saltar alem da raiz fica na raiz). kth devolve
  -1 se k > d[u]. Pesos exigem distancia em ll separada. Iterativo.
Catalogo: Arvores (LCA, k-esimo ancestral, caminho).
Digitacao: 44 linhas | media. Atalho: dist e on_path reutilizam lca/kth.
*****************************LATEX_DESC_END*/
