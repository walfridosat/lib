// SOS DP recursivo (soma sobre submascaras)
//
// O que faz: gen_submask(b, mask) = soma de F[s] para todas as submascaras s de mask
//            considerando os bits 0..b (com memoizacao).
// Quando usar: Catalogo > Bits e XOR (SOS). Para a versao iterativa O(B*2^B) e mais
//            rapida/segura, use o laco padrao do catalogo (para cada bit, para cada mask).
// Complexidade: O(B * 2^B) estados; memoria O(B * 2^B) (aqui 21 * 2^21 ll ~ 350 MB).
// Uso: preencha F[0..(1<<B)-1], memset(dp, -1, sizeof dp) e chame gen_submask(B-1, mask).
// Cuidados: SEMPRE memset dp para -1 antes (o codigo nao inicializa); reduza MAXN ao B real;
//            a recursao inclui a propria submask (F[mask]); para excluir, subtraia F[mask].
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

