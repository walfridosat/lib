// Raiz quadrada modular (Tonelli-Shanks) e simbolo de Jacobi
//
// O que faz: x com x^2 = a (mod p), p primo; Jacobi (a/n) em O(log).
// Quando usar: Catalogo > Teoria dos numeros (raiz quadrada mod p, criterio
//   de Euler, Legendre/Jacobi; x^2 = -1 mod p).
// Complexidade: O(log^2 p).
// Uso: sqrt_mod(a,p) -> uma raiz r (a outra e p-r) ou -1 se a nao e residuo.
//   jacobi(a,n) -> -1,0,1 (n impar positivo). Para mod composto: fatore e
//   use CRT (crt.cpp); 2^omega solucoes.
// Cuidados: p=2 tratado. a=0 devolve 0. p ate ~1e18 (usa __int128).
typedef __int128 LL;
ll pmod(ll b, ll e, ll m) {
    ll r = 1 % m; b %= m;
    for (; e; e >>= 1, b = (LL)b * b % m) if (e & 1) r = (LL)r * b % m;
    return r;
}
int jacobi(ll a, ll n) {
    a %= n; if (a < 0) a += n;
    int r = 1;
    while (a) {
        while (a % 2 == 0) { // (2/n) = -1 se n = 3,5 mod 8
            a /= 2;
            if (n % 8 == 3 || n % 8 == 5) r = -r;
        }
        swap(a, n); // reciprocidade quadratica
        if (a % 4 == 3 && n % 4 == 3) r = -r;
        a %= n;
    }
    return n == 1 ? r : 0;
}
ll sqrt_mod(ll a, ll p) {
    a %= p; if (a < 0) a += p;
    if (a == 0) return 0;
    if (p == 2) return a;
    if (pmod(a, (p - 1) / 2, p) != 1) return -1; // Euler
    if (p % 4 == 3) return pmod(a, (p + 1) / 4, p);
    ll q = p - 1; int s = 0;
    while (q % 2 == 0) q /= 2, s++; // p-1 = q * 2^s
    ll z = 2;
    while (pmod(z, (p - 1) / 2, p) != p - 1) z++; // nao residuo
    ll c = pmod(z, q, p), x = pmod(a, (q + 1) / 2, p), t = pmod(a, q, p);
    int m = s;
    while (t != 1) {
        int i = 0; ll tt = t;
        while (tt != 1) tt = (LL)tt * tt % p, i++; // menor i com t^(2^i)=1
        ll b = c;
        for (int j = 0; j < m - i - 1; j++) b = (LL)b * b % p;
        x = (LL)x * b % p; c = (LL)b * b % p; t = (LL)t * c % p; m = i;
    }
    return x;
}
