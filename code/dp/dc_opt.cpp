// Divide and conquer optimization (D&C DP)
//
// O que faz: calcula dp[k][i] = min_{j<i} dp[k-1][j] + C(j,i) para k=1..K quando opt(i) e monotono.
// Quando usar: Catalogo > DP > "D&C DP", "Desigualdade do quadrangulo (Monge)", "Custo C(j,i) = soma de pares".
// Complexidade: O(K * n log n) chamadas de C. C deve ser O(1) (prefix sums) ou ponteiros tipo Mo.
// Uso: defina C(j,i) = custo do segmento (j,i] (prefixos 0..n); dc_opt(n,K) retorna dp[K][n].
//   Exemplo abaixo: C = (S[i]-S[j])^2 com S = somas de prefixo. Dividir array em K blocos nao vazios.
// Cuidados: verifique a condicao de Monge com brute force. INF = 4e18 (testa antes de somar).
//   Para dp[i] que depende da MESMA camada (1D/1D) isto NAO serve: usar CDQ ou pilha de candidatos.
const ll DCINF = (ll)4e18;
ll S_dc[100005];                       // prefix sums (exemplo de custo)
ll C(int j, int i){ ll s = S_dc[i]-S_dc[j]; return s*s; }  // custo do bloco (j,i]
vector<ll> dcprv, dccur;
// calcula dccur[l..r] sabendo que opt esta em [ol,orr]
void dc_solve(int l, int r, int ol, int orr){
    if(l > r) return;
    int mid = (l+r)/2, best = -1; ll bv = DCINF;
    for(int j = ol; j <= min(mid-1, orr); j++){   // j < mid: bloco nao vazio
        if(dcprv[j] >= DCINF) continue;
        ll v = dcprv[j] + C(j, mid);
        if(v < bv){ bv = v; best = j; }
    }
    dccur[mid] = bv;
    if(best == -1) best = ol;                       // sem candidato valido: mantem janela
    dc_solve(l, mid-1, ol, best);
    dc_solve(mid+1, r, best, orr);
}
// n elementos (prefixos 0..n), K camadas; retorna dp[K][n]
ll dc_opt(int n, int K){
    dcprv.assign(n+1, DCINF); dcprv[0] = 0;       // camada 0: so o prefixo vazio
    for(int k = 1; k <= K; k++){
        dccur.assign(n+1, DCINF);
        dc_solve(1, n, 0, n-1);
        dcprv = dccur;
    }
    return dcprv[n];
}
