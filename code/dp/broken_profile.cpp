// Broken profile DP (plug DP simples): ladrilhar grade com dominos
//
// O que faz: conta (mod) o numero de ladrilhamentos de uma grade n x m com dominos 1x2, com celulas bloqueadas '#'.
//   Processa celula a celula; mascara de m bits = "quais celulas da fronteira ja estao preenchidas".
// Quando usar: Catalogo > DP > "Broken profile (plug DP simples)", grid com m <= ~12-15, ladrilhos, independentes em grade.
// Complexidade: O(n * m * 2^m).
// Uso: count_tilings(g) com g vetor de strings ('.' livre, '#' bloqueada); m = largura (a menor dimensao!). Retorna mod BP_MOD.
// Cuidados: bit j da mascara na celula (i,j) = "celula (i,j) ja coberta"; ao processar, o bit passa a significar
//   "celula (i+1,j) coberta". Para outro problema (independentes, cores) so troque as transicoes.
const ll BP_MOD = 998244353;
ll count_tilings(const vector<string>& g){
    int n = g.size(), m = g[0].size();
    vector<ll> dp(1<<m, 0), nd(1<<m);
    dp[0] = 1;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++){
        fill(nd.begin(), nd.end(), 0);
        for(int mask = 0; mask < (1<<m); mask++){
            ll v = dp[mask]; if(!v) continue;
            bool filled = mask >> j & 1;
            if(g[i][j] == '#'){                                  // bloqueada: nao pode estar coberta
                if(!filled) nd[mask] = (nd[mask] + v) % BP_MOD;
            } else if(filled){                                   // ja coberta por domino vertical de cima/horizontal
                nd[mask ^ (1<<j)] = (nd[mask ^ (1<<j)] + v) % BP_MOD;
            } else {
                // vertical: cobre (i,j) e (i+1,j)
                if(i+1 < n && g[i+1][j] == '.')
                    nd[mask | (1<<j)] = (nd[mask | (1<<j)] + v) % BP_MOD;
                // horizontal: cobre (i,j) e (i,j+1)
                if(j+1 < m && g[i][j+1] == '.' && !(mask >> (j+1) & 1))
                    nd[mask | (1<<(j+1))] = (nd[mask | (1<<(j+1))] + v) % BP_MOD;
            }
        }
        swap(dp, nd);
    }
    return dp[0];
}
