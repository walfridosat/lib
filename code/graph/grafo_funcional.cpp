// Grafo funcional (cada vertice tem exatamente uma aresta de saida)
//
// O que faz: acha os ciclos, e para cada vertice: se esta no ciclo, id do ciclo, posicao,
//   tamanho, distancia ate o ciclo (depth) e o vertice de entrada no ciclo (root).
//   kth(u, k) devolve o k-esimo sucessor de u (k ate 1e18).
// Quando usar: Catalogo > Grafos ("Grafo funcional", "Permutacao como grafo funcional",
//   "Grafos funcionais com pesos"), simulacoes "apos k passos".
// Complexidade: build O(n log n); kth O(log n)
// Uso: FuncGraph F(f) com f[i] = destino de i (0-based). F.kth(u,k); F.root[u], F.depth[u],
//   F.cyc_len[u] (tamanho do ciclo ao qual u chega), F.in_cyc[u], F.pos[u] (posicao no
//   ciclo, so para in_cyc). Distancia u->v se v no ciclo, etc.: compose a mao.
//   Para somas de k passos com pesos, guarde sum[j][u] junto de up[j][u] (binary lifting).
// Cuidados: depth < n, entao ate LOG=ceil(log2 n) niveis bastam na parte da arvore.
struct FuncGraph {
    int n, LOG;
    vector<int> f, root, depth, pos, cyc_len, cyc_id;
    vector<char> in_cyc;
    vector<vector<int>> cycles, up;
    FuncGraph(const vector<int>& f_) : n(f_.size()), f(f_) {
        LOG = 1; while ((1 << LOG) < n) LOG++;
        in_cyc.assign(n, 0); pos.assign(n, -1); cyc_id.assign(n, -1);
        // peeling por grau de entrada: o que sobra e ciclo
        vector<int> indeg(n, 0);
        for (int i = 0; i < n; i++) indeg[f[i]]++;
        vector<int> q;
        for (int i = 0; i < n; i++) if (!indeg[i]) q.push_back(i);
        vector<char> removed(n, 0);
        for (int h = 0; h < (int)q.size(); h++) {
            int u = q[h]; removed[u] = 1;
            if (--indeg[f[u]] == 0) q.push_back(f[u]);
        }
        for (int i = 0; i < n; i++) if (!removed[i] && !in_cyc[i]) {
            cycles.push_back({});
            int c = cycles.size() - 1;
            for (int v = i; !in_cyc[v]; v = f[v]) {
                in_cyc[v] = 1; pos[v] = cycles[c].size(); cyc_id[v] = c; cycles[c].push_back(v);
            }
        }
        root.assign(n, -1); depth.assign(n, 0); cyc_len.assign(n, 0);
        for (int i = 0; i < n; i++) if (in_cyc[i]) root[i] = i, cyc_len[i] = cycles[cyc_id[i]].size();
        // processa em ordem inversa da remocao: f[u] ja resolvido
        for (int h = (int)q.size() - 1; h >= 0; h--) {
            int u = q[h];
            root[u] = root[f[u]]; depth[u] = depth[f[u]] + 1;
            cyc_len[u] = cyc_len[f[u]]; cyc_id[u] = cyc_id[f[u]];
        }
        up.assign(LOG, vector<int>(n));
        up[0] = f;
        for (int j = 1; j < LOG; j++)
            for (int i = 0; i < n; i++) up[j][i] = up[j - 1][up[j - 1][i]];
    }
    int kth(int u, ll k) {
        if (k < depth[u]) {                       // ainda na parte da arvore
            for (int j = 0; j < LOG; j++) if (k >> j & 1) u = up[j][u];
            return u;
        }
        k -= depth[u];
        int r = root[u], L = cyc_len[u];
        return cycles[cyc_id[u]][(pos[r] + k % L) % L];
    }
};
