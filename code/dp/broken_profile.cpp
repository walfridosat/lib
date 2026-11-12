// Broken profile (plug DP) - ladrilhar grade com dominos
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
            } else if(filled){                                   // ja coberta por domino de cima/horizontal
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
/*LATEX_DESC_BEGIN***************************
-> **Broken profile (plug DP) - ladrilhar grade com dominos**
Conta mod BP_MOD os ladrilhamentos de uma grade n x m com dominos 1x2 e celulas
bloqueadas '#'. Processa celula a celula; a mascara de m bits e a fronteira.

Complexidade: O(n * m * 2^m).
Uso:
  ll ans = count_tilings(g);   // g: vetor de strings, '.' livre, '#' bloqueada

* Sobre o codigo:
  dp[mask] conta as formas de preencher as celulas ja processadas, onde o bit j
  indica se a celula da fronteira na coluna j ja esta coberta. Ao processar (i,j),
  o bit j passa a significar (i+1,j). Celula bloqueada exige bit j livre; celula
  livre e nao coberta pode receber domino vertical (i+1,j) ou horizontal (i,j+1).

* Problemas e reducoes:
  + Contar ladrilhamentos com dominos 1x2 em grade com obstaculos.
  + Contar emparelhamentos perfeitos de grade bipartida por colunas.
  + Trocar as transicoes da o mesmo esqueleto para independentes ou coloracao.

Cuidados: use a menor dimensao como m (m <= ~12-15); a mascara tem 2^m estados.
  Para outro problema, so troque as transicoes.
Catalogo: DP > Broken profile (plug DP simples).
Digitacao: 25 linhas | media.
*****************************LATEX_DESC_END*/
