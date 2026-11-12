// Tonelli-Shanks e simbolo de Jacobi
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
/*LATEX_DESC_BEGIN***************************
-> **Tonelli-Shanks e Jacobi**
Raiz quadrada modular mod p primo e simbolo de Jacobi em O(log).

Complexidade: O(log^2 p).
Uso:
  ll r = sqrt_mod(a, p);        // uma raiz; a outra e p-r; -1 se nao ha
  int j = jacobi(a, n);         // n impar positivo

* Sobre o codigo:
  sqrt_mod trata p = 2, a = 0 e p = 3 mod 4; no caso geral escreve p-1 = q*2^s,
  acha um nao residuo z e itera reduzindo t ate 1. jacobi aplica a
  reciprocidade quadratica removendo fatores 2.

* Problemas e reducoes:
  + Resolver x^2 = a (mod p) -> sqrt_mod.
  + x^2 = -1 mod p -> sqrt_mod(p-1, p).
  + Testar residuo quadratico (criterio de Euler) -> sqrt_mod != -1.
  + Resolver x^2 = a mod composto -> fatorar e juntar por CRT.
  + Calcular Legendre/Jacobi -> jacobi.
  + Pontos em conica mod p -> sqrt_mod.

Cuidados: p primo; p = 2 tratado; a = 0 devolve 0; sqrt_mod devolve so uma
  raiz (a outra e p-r); para mod composto fatore e use CRT (2^omega solucoes).
Catalogo: Teoria dos numeros.
Digitacao: 41 linhas | media. Atalho: pmod duplica pw/pw_mod de outros arquivos.
*****************************LATEX_DESC_END*/
