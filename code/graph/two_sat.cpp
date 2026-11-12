// 2-SAT
//
// O que faz: decide satisfatibilidade de clausulas de 2 literais e devolve uma atribuicao.
// Quando usar: Catalogo > Grafos ("Restricoes booleanas de 2 variaveis -> 2-SAT",
//   "2-SAT com cardinalidade no maximo uma de k", "2-SAT com escolha de 2 opcoes por item",
//   2-SAT binaria/incremental).
// Complexidade: O(n + clausulas)
// Uso: TwoSat ts(n);  variaveis 0..n-1, literal (x, true) = x verdadeiro.
//   ts.add_or(x,vx, y,vy)   : (x==vx) OU (y==vy)
//   ts.imply(x,vx, y,vy)    : (x==vx) => (y==vy)
//   ts.set(x,v)             : x == v  (forcado)
//   ts.at_most_one(vector<int> vars) : no maximo um verdadeiro (O(k) clausulas, aux vars:
//                                      crie ts com folga: n + soma dos k)
//   bool ok = ts.solve(); ts.val[x] = atribuicao.
// Cuidados: at_most_one cria variaveis novas (ts.n cresce) - chame ANTES de solve e use
//   val so para os indices originais. "Variavel forcada": x forcado a true se x==false
//   leva a contradicao (rode solve com set(x,false)); menor lexicografica: tente fixar
//   x=false e resolver de novo (O(n*(n+m))). Ordem das comps: Tarjan => comp menor = depois
//   na ordem topologica; x verdadeiro se comp[x] < comp[!x].
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
