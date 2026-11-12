// DP em bitmask: TSP, atribuicao e particao em subconjuntos
//
// O que faz: (1) tsp: menor ciclo hamiltoniano, dp[mask][ultimo]. (2) assign_mask: custo minimo de atribuir n itens
//   a n posicoes, dp[mask] com posicao = popcount(mask). (3) partition3: dp[mask] = melhor particao de mask em grupos
//   com custo g[sub] (3^n, fixando o menor bit).
// Quando usar: Catalogo > DP > "TSP / hamiltoniano", "Permutacoes como mascara", "Subconjuntos de mascara, 3^n", n <= 20 / 16-18.
// Complexidade: tsp O(2^n n^2); assign_mask O(2^n n); partition3 O(3^n).
// Uso: tsp(d) com d[i][j] matriz n x n (0-based, ciclo comeca em 0); assign_mask(c) com c[item][pos];
//   partition3(n, g) com g de tamanho 2^n (g[0] ignorado), retorna dp[(1<<n)-1].
// Cuidados: TINF = 1e18 (cuidado ao somar). tsp usa n*2^n ll (n=20: 160MB; use int se couber).
//   Para caminho (nao ciclo) troque o fecho final por min sobre ultimo sem voltar.
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
    vector<ll> dp(1<<n, TINF); dp[0] = 0;                    // mask = itens ja colocados nas posicoes 0..popcount-1
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
