// Digit DP - soma dos digitos de 0..k
ll dp[2][19][171]; // soma maxima de digitos de um ll e 170
 
int limite[19];
ll digitDP(int idx, int sum, bool flag){
    if(idx < 0) return sum;
    if(~dp[flag][idx][sum]) return dp[flag][idx][sum];

    dp[flag][idx][sum] = 0; 
	int lm = flag ? limite[idx] : 9;
 
    for(int i=0; i<=lm; i++)
        dp[flag][idx][sum] += digitDP(idx-1, sum+i, (flag && i == lm));
 
    return dp[flag][idx][sum];
}

ll solve(ll k){
    memset(dp, -1, sizeof dp);
	
	int sz=0;
	while(k){
		limite[sz++] = k % 10LL;
		k /= 10LL;
	}

 	return digitDP(sz-1, 0, true);
}

/*LATEX_DESC_BEGIN***************************
-> **Digit DP - soma dos digitos**
Conta/otimiza sobre os digitos de 0..k com estado (posicao, soma, tight);
esta versao retorna a soma das somas de digitos de 0 ate k, 0-based.

Complexidade: O(digitos * estados * 10); digitos <= 19 para ll.
Uso:
  ll ans = solve(k);   // uma chamada por limite (memset acontece dentro)

* Sobre o codigo:
  dp[flag][idx][sum] = soma para os digitos restantes, onde flag indica se o
  prefixo esta colado em k. limite[] guarda os digitos de k. digitDP soma as
  transicoes e usa -1 como "nao calculado". Para contar em vez de somar,
  troque o retorno base de sum para 1.

* Problemas e reducoes:
  + Soma dos digitos de 0..k.
  + Contar numeros <= k com uma propriedade dos digitos (troque o estado).
  + Intervalo [l,r]: solve(r) - solve(l-1).

Cuidados: limite[19] cabe ll; ajuste o segundo estado (aqui soma <= 170).
  digitDP devolve a soma, nao a contagem. O memset e obrigatorio a cada chamada.
Catalogo: DP (DP de digitos).
Digitacao: 20 linhas | media.
*****************************LATEX_DESC_END*/