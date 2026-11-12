// SOS DP recursivo - soma sobre submascaras
const ll MAXN = 21;
ll F[1<<MAXN]; //guarda a resposta pra uma submask
ll dp[MAXN][1<<MAXN];

ll gen_submask(int b , int curmask) {
    if(b < 0) {
        return F[curmask];
    }

    if(dp[b][curmask] != -1) return dp[b][curmask];

    ll ans = 0;
    if(curmask&(1ll << b)) {  
        ans += gen_submask(b-1 , curmask); //transicao pra o bit ligado
        ans += gen_submask(b-1 , curmask ^ (1ll << b)); //transicao pra o bit desligado
    }
    else {
        ans += gen_submask(b-1 , curmask); //transicao pra o bit desligado
    }
    return dp[b][curmask] = ans;
}
/*LATEX_DESC_BEGIN***************************
-> **SOS DP recursivo (soma sobre submascaras)**
gen_submask(b, mask) = soma de F[s] sobre as submascaras s de mask considerando
os bits 0..b, com memoizacao. Inclui a propria mask, 0-based.

Complexidade: O(B * 2^B) estados; memoria O(B * 2^B) (21 * 2^21 ll ~ 350MB).
Uso:
  preencha F[0 .. (1<<B)-1];
  memset(dp, -1, sizeof dp);
  ll r = gen_submask(B-1, mask);

* Sobre o codigo:
  Para cada bit b ligado em mask, a soma vem de duas chamadas: mantendo o bit
  ligado e desligando-o; se o bit esta desligado, so a transicao que o mantem.
  dp[b][mask] memoiza. A versao iterativa O(B*2^B) costuma ser mais rapida.

* Problemas e reducoes:
  + Soma de F sobre todas as submascaras de cada mask.
  + Convolucao OR/AND entre funcoes sobre mascaras.
  + Contar pares/ternos com condicao de bits.

Cuidados: SEMPRE memset dp para -1 antes (o codigo nao inicializa); reduza
  MAXN ao B real. A recursao inclui a propria submask; para excluir, subtraia
  F[mask].
Catalogo: Bits e XOR (SOS).
Digitacao: 18 linhas | media.
*****************************LATEX_DESC_END*/

