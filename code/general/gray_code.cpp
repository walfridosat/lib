// Codigo de Gray
//
// O que faz: g(i) = i ^ (i>>1) percorre todas as mascaras mudando 1 bit por passo; inversa; enumeracao de subset sums em O(1)/passo.
// Quando usar: percorrer 2^n subconjuntos atualizando soma/estado incrementalmente; hipercubo hamiltoniano; Hanoi/aneis chineses.
//              Catalogo > Construtivos (Gray code), Bits e XOR (Ordem de Gray)
// Complexidade: O(1) por passo
// Uso: gray(i); ungray(g); em loop: for i in 1..2^n-1: bit = __builtin_ctz(i) e o bit que mudou de g(i-1) para g(i).
//      forEachSubsetSum(a, f): chama f(mask, soma) para os 2^n subconjuntos (n <= ~25).
// Cuidados: o bit alterado do passo i (i>=1) e ctz(i); mask comeca em 0.
ll gray(ll i) { return i ^ (i >> 1); }
ll ungray(ll g) { ll i = 0; for (; g; g >>= 1) i ^= g; return i; }   // inversa: prefixo xor dos bits
template<class F> void forEachSubsetSum(const vector<ll>& a, F f) {
    int n = a.size(); ll mask = 0, sum = 0; f(mask, sum);
    for (ll i = 1; i < (1LL << n); i++) {
        int b = __builtin_ctzll(i);
        mask ^= 1LL << b;
        if (mask >> b & 1) sum += a[b]; else sum -= a[b];   // entrou ou saiu o elemento b
        f(mask, sum);
    }
}
