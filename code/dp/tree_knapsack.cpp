// Tree knapsack - merge O(n^2) e ordem DFS O(nK)
const ll TKNEG = (ll)-1e18;
vector<ll> tk_dfs_merge(int v, int p, const vector<vector<int>>& adj, const vector<ll>& a, int K){
    vector<ll> dp = {TKNEG, a[v]};                          // dp[j]: melhor com j vertices, v incluso
    for(int c : adj[v]) if(c != p){
        vector<ll> ch = tk_dfs_merge(c, v, adj, a, K);
        vector<ll> nd(min<int>(dp.size() + ch.size() - 1, K + 1), TKNEG);
        for(int i = 1; i < (int)dp.size(); i++){
            if(dp[i] == TKNEG) continue;
            nd[i] = max(nd[i], dp[i]);                      // nao pega nada do filho
            for(int j = 1; j < (int)ch.size() && i + j <= K; j++) if(ch[j] != TKNEG)
                nd[i+j] = max(nd[i+j], dp[i] + ch[j]);
        }
        dp = nd;
    }
    return dp;
}
vector<ll> tk_merge(const vector<vector<int>>& adj, const vector<ll>& a, int K){
    vector<ll> d = tk_dfs_merge(0, -1, adj, a, K), res(K+1, TKNEG);
    res[0] = 0;
    for(int j = 1; j <= K && j < (int)d.size(); j++) res[j] = d[j];
    return res;
}
// versao ordem DFS
vector<int> tk_ord, tk_out;
void tk_dfs(int v, int p, const vector<vector<int>>& adj){
    tk_ord.push_back(v);
    for(int c : adj[v]) if(c != p) tk_dfs(c, v, adj);
    tk_out.push_back(0);                                    // placeholder; ver abaixo
}
vector<ll> tk_dfs_order(const vector<vector<int>>& adj, const vector<ll>& a, int K){
    int n = adj.size();
    tk_ord.clear(); tk_out.clear();
    vector<int> tin(n), tout(n);
    int timer = 0;
    function<void(int,int)> dfs = [&](int v, int p){
        tin[v] = timer++; tk_ord.push_back(v);
        for(int c : adj[v]) if(c != p) dfs(c, v);
        tout[v] = timer;                                    // tout = primeiro indice fora da subarvore
    };
    dfs(0, -1);
    // f[i][j]: j escolhas a partir de i
    vector<vector<ll>> f(n + 1, vector<ll>(K + 1, TKNEG));
    f[n][0] = 0;
    for(int i = n - 1; i >= 0; i--){
        int v = tk_ord[i];
        for(int j = 0; j <= K; j++){
            ll best = f[tout[v]][j];                        // nao pega v: perde toda a subarvore
            if(j >= 1 && f[i+1][j-1] != TKNEG) best = max(best, f[i+1][j-1] + a[v]);   // pega v e continua
            f[i][j] = best;
        }
    }
    vector<ll> res(K + 1);
    for(int j = 0; j <= K; j++) res[j] = f[0][j];
    return res;
}
/*LATEX_DESC_BEGIN***************************
-> **Knapsack em arvore**
Escolher exatamente k vertices formando subarvore conexa que contem a raiz
(se pega v, pega o pai), maximizando a soma de a[v]. Raiz = 0, 0-based.

Complexidade: tk_merge O(n^2) (ou O(nK) cortando em min(sz,K)); tk_dfs_order O(n*K).
Uso:
  vector<ll> r1 = tk_merge(adj, a, K);       // r1[k] = melhor soma com k vertices
  vector<ll> r2 = tk_dfs_order(adj, a, K);   // mesma resposta

* Sobre o codigo:
  tk_merge funde os filhos com dp[v][j], limitando os lacos pelo tamanho de cada
  subarvore, o que da O(n^2) no total. tk_dfs_order usa a ordem DFS: pegar v
  leva a i+1; nao pegar salta para tout[v], o primeiro indice fora da subarvore.

* Problemas e reducoes:
  + Escolher k vertices conexos contendo a raiz.
  + Mochila em arvore com dependencia pai-filho.
  + Escolher um conjunto fechado para cima em uma arvore.

Cuidados: recursao profunda (n > 1e5 em cadeia estoura pilha: converta para
  iterativa). NEG = -1e18; res[0] = 0 e res[k] = -INF se impossivel.
Catalogo: DP > Arvore knapsack O(n^2) / DP sobre ordem DFS.
Digitacao: 53 linhas | media. Atalho: tk_dfs_merge pode ser reutilizado para
  K = n, e a versao DFS dispensa o merge.
*****************************LATEX_DESC_END*/
