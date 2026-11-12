// Miller-Rabin deterministico (64 bits)
//
// O que faz: testa primalidade de n < 2^64 de forma exata.
// Quando usar: Catalogo > Teoria dos numeros (fatorar ate 1e18; primalidade
//   de numeros grandes). Base de pollard_rho.cpp.
// Complexidade: O(12 log n) mulmods.
// Uso: is_prime(n) -> bool. mulmod/powmod tambem sao uteis sozinhos.
// Cuidados: se colar junto com pollard_rho.cpp apague a duplicata (mesmos nomes).
//   Colide com `is_prime` do sieve.cpp (vector<bool>): renomeie um dos dois.
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
    // 12 primeiras bases valem para n < 3.3e24 (todo 64 bits)
    for (ull a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        ull x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool ok = false;
        for (int r = 1; r < s && !ok; r++) { x = mulmod(x, x, n); ok = (x == n - 1); }
        if (!ok) return false; // a e testemunha de composto
    }
    return true;
}
