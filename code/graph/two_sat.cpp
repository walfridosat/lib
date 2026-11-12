// 2-SAT - satisfatibilidade e atribuicao
struct TwoSat {
    int n;                      // numero de variaveis
    vector<vector<int>> g;      // no 2*x = x verdadeiro, 2*x+1 = x falso
    vector<int> val;
    TwoSat(int n = 0) : n(n), g(2 * n) {}
    int new_var() { g.push_back({}); g.push_back({}); return n++; }
    static int lit(int x, bool v) { return 2 * x + (v ? 0 : 1); }
    void add_or(int x, bool vx, int y, bool vy) {
        g[lit(x, !vx)].push_back(lit(y, vy));
        g[lit(y, !vy)].push_back(lit(x, vx));
    }
    void imply(int x, bool vx, int y, bool vy) { add_or(x, !vx, y, vy); }
    void set(int x, bool v) { add_or(x, v, x, v); }
    void at_most_one(const vector<int>& vs) {
        int k = vs.size();
        if (k <= 1) return;
        int prev = new_var();                       // p_i = x_0 | ... | x_i
        imply(vs[0], true, prev, true);
        for (int i = 1; i < k; i++) {
            int cur = new_var();
            imply(vs[i], true, cur, true);          // x_i => p_i
            imply(prev, true, cur, true);           // p_{i-1} => p_i
            imply(prev, true, vs[i], false);        // p_{i-1} => !x_i
            prev = cur;
        }
    }
    bool solve() {
        int N = 2 * n;
        vector<int> idx(N, -1), low(N, 0), comp(N, -1), st, it(N, 0), cs;
        vector<char> on(N, 0);
        int timer = 0, C = 0;
        for (int r = 0; r < N; r++) {
            if (idx[r] != -1) continue;
            cs.push_back(r); idx[r] = low[r] = timer++; st.push_back(r); on[r] = 1;
            while (!cs.empty()) {
                int u = cs.back();
                if (it[u] < (int)g[u].size()) {
                    int v = g[u][it[u]++];
                    if (idx[v] == -1) { idx[v] = low[v] = timer++; st.push_back(v); on[v] = 1; cs.push_back(v); }
                    else if (on[v]) low[u] = min(low[u], idx[v]);
                } else {
                    if (low[u] == idx[u]) {
                        while (true) {
                            int w = st.back(); st.pop_back(); on[w] = 0; comp[w] = C;
                            if (w == u) break;
                        }
                        C++;
                    }
                    cs.pop_back();
                    if (!cs.empty()) low[cs.back()] = min(low[cs.back()], low[u]);
                }
            }
        }
        val.assign(n, 0);
        for (int x = 0; x < n; x++) {
            if (comp[2 * x] == comp[2 * x + 1]) return false;
            val[x] = comp[2 * x] < comp[2 * x + 1];   // Tarjan: comp menor = mais "a frente"
        }
        return true;
    }
};
/*LATEX_DESC_BEGIN***************************
-> **2-SAT - satisfatibilidade e atribuicao**
Decide clausulas de 2 literais e devolve uma atribuicao. Variaveis 0..n-1;
literal (x, true) = x verdadeiro.

Complexidade: O(n + clausulas)
Uso:
  TwoSat ts(n);
  ts.add_or(x, vx, y, vy);    // (x==vx) OU (y==vy)
  ts.imply(x, vx, y, vy);     // (x==vx) => (y==vy)
  ts.set(x, v);               // x == v (forcado)
  ts.at_most_one(vars);       // no maximo um verdadeiro
  bool ok = ts.solve();       // ts.val[x] = atribuicao

* Sobre o codigo:
  No 2*x = x verdadeiro, 2*x+1 = x falso. add_or cria as duas implicacoes.
  at_most_one usa variaveis prefixo p_i = x_0 | ... | x_i, com O(k) clausulas.
  solve roda Tarjan nas 2n implicacoes; x e verdadeiro sse comp[2x] < comp[2x+1]
  (Tarjan numera sumidouros primeiro).

* Problemas e reducoes:
  + Restricoes booleanas de 2 variaveis: cada clausula vira add_or.
  + "No maximo um de k": at_most_one, O(k) clausulas com variaveis auxiliares.
  + "Exatamente um de k": at_most_one + ao menos um (OR de todos).
  + Escolha de 2 opcoes por item: variavel por item; proiba pares invalidos.
  + Variavel forcada: x e true sse set(x, false) for insatisfativel.
  + Menor atribuicao lexicografica: fixe x=false e rode solve de novo,
    O(n*(n+m)).
  + Busca binaria/incremental: re-rode solve apos adicionar clausulas.

Cuidados: at_most_one cria variaveis novas (n cresce); chame ANTES de solve e
  use val so para os indices originais. Ordem: Tarjan => comp menor = mais a
  frente. Se n for grande, at_most_one com n + soma dos k tem folga.
Catalogo: Grafos (2-SAT, cardinalidade no maximo um, escolha de 2 opcoes).
Digitacao: 61 linhas | dificil. Atalho: solve repete o Tarjan de scc_tarjan;
  extraia a funcao de SCC.
*****************************LATEX_DESC_END*/
