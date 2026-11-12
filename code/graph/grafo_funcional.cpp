// Grafo funcional - ciclos e k-esimo sucessor
struct FuncGraph {
    int n, LOG;
    vector<int> f, root, depth, pos, cyc_len, cyc_id;
    vector<char> in_cyc;
    vector<vector<int>> cycles, up;
    FuncGraph(const vector<int>& f_) : n(f_.size()), f(f_) {
        LOG = 1; while ((1 << LOG) < n) LOG++;
        in_cyc.assign(n, 0); pos.assign(n, -1); cyc_id.assign(n, -1);
        // peeling por grau de entrada; sobra o ciclo
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
        // ordem inversa da remocao: f[u] ja resolvido
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
/*LATEX_DESC_BEGIN***************************
-> **Grafo funcional - ciclos e k-esimo sucessor**
Cada vertice tem exatamente uma aresta de saida. Acha os ciclos e, para cada
vertice, guarda id/posicao/tamanho do ciclo, depth e o vertice de entrada
(root). kth(u, k) da o k-esimo sucessor de u (k ate 1e18). 0-based.

Complexidade: build O(n log n); kth O(log n)
Uso:
  FuncGraph F(f);              // f[i] = destino de i
  int v = F.kth(u, k);
  // F.root[u], F.depth[u], F.cyc_len[u], F.in_cyc[u], F.pos[u]
  // F.pos so e valido quando F.in_cyc[u]

* Sobre o codigo:
  Peeling por grau de entrada remove arvores; o que sobra sao os ciclos.
  Processa em ordem inversa da remocao para achar root/depth. up[j] e binary
  lifting para a parte da arvore; kth divide entre subir a arvore e andar no
  ciclo por modulo.

* Problemas e reducoes:
  + Simulacao "apos k passos": kth em O(log n).
  + Permutacao como grafo funcional: ciclos e posicoes.
  + Distancia ate o ciclo: depth; entrada no ciclo: root.
  + Distancia u -> v quando v esta no ciclo: componha a mao.
  + Somas de k passos com pesos: guarde sum[j][u] junto de up[j][u].
  + Contagem de vertices que chegam em cada ciclo: agregue root/cyc_id.

Cuidados: depth < n, entao LOG = ceil(log2 n) niveis bastam. Pesos exigem uma
  tabela de somas paralela; k e ll.
Catalogo: Grafos (grafo funcional, permutacao, simulacao apos k passos).
Digitacao: 48 linhas | dificil.
*****************************LATEX_DESC_END*/
