// Codigo de Gray - mascaras mudando 1 bit por passo
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
/*LATEX_DESC_BEGIN***************************
-> **Codigo de Gray**
g(i) = i ^ (i >> 1) percorre as 2^n mascaras mudando um bit por passo; ungray inverte.
forEachSubsetSum atualiza a soma de cada subconjunto em O(1) por passo.

Complexidade: O(1) por passo; O(2^n) para enumerar tudo
Uso:
  ll g = gray(i); ll j = ungray(g);
  forEachSubsetSum(a, [&](ll mask, ll sum) { ... });  // n <= ~25

* Sobre o codigo:
  No passo i >= 1, o bit que muda e ctz(i); mask ^= 1 << bit.
  forEachSubsetSum soma a[bit] se o bit entrou e subtrai se saiu.

* Problemas e reducoes:
  + Enumerar subconjuntos atualizando soma/estado incrementalmente.
  + Hipercubo hamiltoniano e sequencias de Hanoi/aneis chineses.

Cuidados: a enumeracao usa 1LL << n; mask comeca em 0 e o bit alterado e ctz(i).
Catalogo: Construtivos (Gray code), Bits e XOR (Ordem de Gray)
Digitacao: 11 linhas | facil.
*****************************LATEX_DESC_END*/
