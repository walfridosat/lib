// DP em bitmask - TSP, atribuicao e particao
const ll TINF = (ll)1e18;
ll tsp(const vector<vector<ll>>& d){
    int n = d.size();
    if(n == 1) return 0;
    vector<vector<ll>> dp(1<<n, vector<ll>(n, TINF));
    dp[1][0] = 0;                                            // comeca em 0
    for(int m = 1; m < (1<<n); m += 2)                       // so mascaras que contem o vertice 0
        for(int u = 0; u < n; u++){
            if(dp[m][u] >= TINF) continue;
            for(int v = 1; v < n; v++) if(!(m>>v&1))
                dp[m|1<<v][v] = min(dp[m|1<<v][v], dp[m][u] + d[u][v]);
        }
    ll ans = TINF;
    for(int u = 1; u < n; u++) if(dp[(1<<n)-1][u] < TINF) ans = min(ans, dp[(1<<n)-1][u] + d[u][0]);
    return ans;
}
ll assign_mask(const vector<vector<ll>>& c){                 // c[item][posicao], n x n
    int n = c.size();
    vector<ll> dp(1<<n, TINF); dp[0] = 0;                    // itens ja colocados nas posicoes 0..popcount-1
    for(int m = 0; m < (1<<n); m++){
        if(dp[m] >= TINF) continue;
        int p = __builtin_popcount(m);                       // proxima posicao
        for(int i = 0; i < n; i++) if(!(m>>i&1))
            dp[m|1<<i] = min(dp[m|1<<i], dp[m] + c[i][p]);
    }
    return dp[(1<<n)-1];
}
ll partition3(int n, const vector<ll>& g){                   // g[sub] = custo do grupo sub (sub != 0)
    vector<ll> dp(1<<n, TINF); dp[0] = 0;
    for(int m = 1; m < (1<<n); m++){
        int low = m & -m;                                    // grupo sempre contem o menor bit
        for(int s = m; s; s = (s-1) & m){
            if(!(s & low)) continue;
            if(dp[m^s] < TINF) dp[m] = min(dp[m], dp[m^s] + g[s]);
        }
    }
    return dp[(1<<n)-1];
}
/*LATEX_DESC_BEGIN***************************
-> **DP em bitmask: TSP, atribuicao e particao**
(1) tsp: menor ciclo hamiltoniano, dp[mask][ultimo]. (2) assign_mask: custo
minimo de atribuir n itens a n posicoes. (3) partition3: melhor particao de
mask em grupos com custo g[sub], fixando o menor bit. 0-based.

Complexidade: tsp O(2^n n^2); assign_mask O(2^n n); partition3 O(3^n).
Uso:
  ll a = tsp(d);                 // d[i][j] matriz n x n, ciclo comeca em 0
  ll b = assign_mask(c);         // c[item][posicao]
  ll e = partition3(n, g);       // g tem tamanho 2^n, g[0] ignorado

* Sobre o codigo:
  tsp so percorre mascaras que contem o vertice 0 e fecha o ciclo no fim.
  assign_mask usa popcount(mask) como proxima posicao a preencher.
  partition3 itera subconjuntos s de mask que contem o menor bit, evitando
  contar a mesma particao varias vezes.

* Problemas e reducoes:
  + Caixeiro viajante com n <= 20 (ciclo ou caminho).
  + Atribuicao de tarefas a posicoes (custo minimo).
  + Particionar um conjunto em grupos com custo por grupo.
  + Cobertura por subconjuntos e coloracao em grafo pequeno.

Cuidados: TINF = 1e18 (cuidado ao somar). tsp usa n*2^n ll (n=20: 160MB; use
  int se couber). Para caminho (nao ciclo), troque o fecho final por min sobre
  o ultimo sem voltar.
Catalogo: DP > TSP / permutacoes como mascara / subconjuntos de mascara 3^n.
Digitacao: 38 linhas | media.
*****************************LATEX_DESC_END*/
