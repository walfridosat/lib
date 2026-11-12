// Miller-Rabin deterministico (64 bits)
typedef unsigned long long ull;
ull mulmod(ull a, ull b, ull m) { return (__uint128_t)a * b % m; }
ull powmod(ull a, ull e, ull m) {
    ull r = 1 % m; a %= m;
    for (; e; e >>= 1, a = mulmod(a, a, m)) if (e & 1) r = mulmod(r, a, m);
    return r;
}
bool is_prime(ull n) {
    if (n < 2) return false;
    for (ull p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
        if (n % p == 0) return n == p;
    ull d = n - 1; int s = __builtin_ctzll(d); d >>= s; // n-1 = d * 2^s
    // 12 bases bastam para n < 2^64
    for (ull a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        ull x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool ok = false;
        for (int r = 1; r < s && !ok; r++) { x = mulmod(x, x, n); ok = (x == n - 1); }
        if (!ok) return false; // a e testemunha de composto
    }
    return true;
}
/*LATEX_DESC_BEGIN***************************
-> **Miller-Rabin deterministico (64 bits)**
Testa primalidade de n < 2^64 de forma exata com 12 bases.

Complexidade: O(12 log n) mulmods.
Uso:
  bool p = is_prime(n);
  ull r = powmod(a, e, m);       // uteis sozinhos
  ull x = mulmod(a, b, m);

* Sobre o codigo:
  Escreve n-1 = d * 2^s e testa a^d e seus quadrados para 12 bases.
  As 12 primeiras bases cobrem todo n < 2^64. mulmod usa __uint128_t.

* Problemas e reducoes:
  + Primalidade de numeros ate 1e18 -> is_prime.
  + Verificar se um divisor de Pollard rho e primo -> is_prime.
  + Exponenciacao modular em ull -> powmod.
  + Base para fatoracao (pollard_rho) -> is_prime.
  + Checar se um numero e potencia de primo -> is_prime nos candidatos.

Cuidados: se colar junto com pollard_rho.cpp, apague a duplicata (mesmos nomes).
  Colide com is_prime do sieve.cpp (vector<bool>): renomeie um.
Catalogo: Teoria dos numeros.
Digitacao: 22 linhas | facil. Atalho: a lista de bases aparece duas vezes; guarde em array.
*****************************LATEX_DESC_END*/
