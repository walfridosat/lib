// Divide and conquer optimization (D&C DP)
const ll DCINF = (ll)4e18;
ll S_dc[100005];                       // prefix sums (exemplo de custo)
ll C(int j, int i){ ll s = S_dc[i]-S_dc[j]; return s*s; }  // custo do bloco (j,i]
vector<ll> dcprv, dccur;
// dccur[l..r], opt em [ol,orr]
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
// n elementos, K camadas; retorna dp[K][n]
ll dc_opt(int n, int K){
    dcprv.assign(n+1, DCINF); dcprv[0] = 0;       // camada 0: so o prefixo vazio
    for(int k = 1; k <= K; k++){
        dccur.assign(n+1, DCINF);
        dc_solve(1, n, 0, n-1);
        dcprv = dccur;
    }
    return dcprv[n];
}
/*LATEX_DESC_BEGIN***************************
-> **Divide and conquer optimization (D&C DP)**
Calcula dp[k][i] = min_{j<i} dp[k-1][j] + C(j,i) para k = 1..K quando
opt(i) (o melhor j) e monotono em i.

Complexidade: O(K * n log n) chamadas de C; C deve ser O(1) (prefix sums).
Uso:
  ll ans = dc_opt(n, K);   // divide n elementos em K blocos nao vazios
  // no exemplo, C(j,i) = (S[i] - S[j])^2

* Sobre o codigo:
  dc_solve(l, r, ol, orr) calcula a camada atual no intervalo [l,r] sabendo que
  o otimo esta em [ol,orr]. Acha opt(mid) por busca linear, aplica a mesma ideia
  em [l,mid-1] com [ol,best] e em [mid+1,r] com [best,orr]. dcprv/dccur sao as
  camadas anterior/atual.

* Problemas e reducoes:
  + Dividir array em K blocos com custo de intervalo e minimizar a soma.
  + DP com custo C(j,i) que satisfaz a desigualdade do quadrangulo (Monge).
  + Custo = soma de pares dentro do bloco, com prefix sums.

Cuidados: verifique a condicao de Monge por brute force; se C nao for O(1),
  use ponteiros tipo Mo. INF = 4e18 e testado antes de somar. Para dp 1D/1D
  (mesma camada) isto NAO serve: use CDQ ou pilha de candidatos.
Catalogo: DP > D&C DP / desigualdade do quadrangulo (Monge).
Digitacao: 26 linhas | media.
*****************************LATEX_DESC_END*/
