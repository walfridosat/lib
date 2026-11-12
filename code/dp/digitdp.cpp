// Digit DP (soma dos digitos de 0..k)
//
// O que faz: conta/otimiza sobre os digitos de 0..k com estado (posicao, soma, tight);
//            aqui retorna a soma das somas de digitos de 0 ate k.
// Quando usar: Catalogo > DP (DP de digitos). Gatilhos: "quantos numeros <= k com ...",
//            "soma dos digitos", propriedades que dependem dos digitos decimais.
// Complexidade: O(digitos * estados * 10); digitos <= 19 para ll.
// Uso: ll ans = solve(k); chame solve uma vez por limite (memset a cada chamada).
// Cuidados: limite[19] cabe ll (19 digitos); ajuste o segundo estado (aqui soma <= 170);
//            digitDP devolve a soma, nao a contagem; para contar troque o retorno para 1.
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

/*********************
Digit DP - Sum of Digits

Solve(K)  ->  Retorna a soma dos dígitos de todo número X tal que: 0 <= X <= K
dp[D][S][f]  ->  D: Quantidade de dígitos; S: Soma dos dígitos; f: Flag que indica o limite.
int limite[D] -> Guarda os dígitos de K.

Complexity: O(D^2 * B^2)  (B = Base = 10)
*********************/