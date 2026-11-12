// BSGS - logaritmo discreto (a^x = b mod m)
ll dlog(ll a, ll b, ll m) {
    a %= m; b %= m;
    if (b == 1 % m) return 0;
    ll k = 0, add = 1 % m, g;
    while ((g = __gcd(a, m)) > 1) {
        if (b % g) return -1;
        b /= g; m /= g; k++;
        add = add * (a / g) % m;
        if (add == b) return k;
    }
    // gcd(a, m) = 1: add * a^x = b (mod m)
    ll n = (ll)sqrtl((long double)m) + 1;
    unordered_map<ll, ll> tb; tb.reserve(n * 2);
    ll cur = b;
    for (ll j = 0; j < n; j++) { // b * a^j; guarda o maior j de cada valor
        tb[cur] = j;
        cur = cur * a % m;
    }
    ll an = 1;
    for (ll i = 0; i < n; i++) an = an * a % m;
    cur = add;
    for (ll i = 1; i <= n + 1; i++) { // add * a^(i*n) = b * a^j  ->  x = i*n - j
        cur = cur * an % m;
        auto it = tb.find(cur);
        if (it != tb.end()) return i * n - it->second + k;
    }
    return -1;
}
/*LATEX_DESC_BEGIN***************************
-> **BSGS - logaritmo discreto**
Menor x >= 0 com a^x = b (mod m), ou -1 se nao existe. m pode ser composto.

Complexidade: O(sqrt(m)) com hash.
Uso:
  ll x = dlog(a, b, m);  // -1 se nao existe; m = 1 devolve 0

* Sobre o codigo:
  Primeiro tira g = gcd(a, m) dos dois lados, acumulando em add = a^k / g^k
  o deslocamento k do expoente; se add == b, a resposta pequena e k.
  Com gcd(a, m) = 1, guarda b*a^j para j < n = sqrt(m) e varre add*a^(i*n);
  a resposta e i*n - j + k. Produtos em ll; para m ate 1e18 use mulmod.

* Problemas e reducoes:
  + Resolver a^x = b (mod m) com m qualquer -> dlog(a, b, m).
  + Caso classico gcd(a, m) = 1 -> mesma chamada (k = 0).
  + Descobrir expoente x tal que a^x = b mod p (p primo) -> BSGS.
  + Menor x com a^x = b -> BSGS devolve o menor.
  + Logaritmo discreto em grupo ciclico gerado por a -> BSGS.

Cuidados: m = 1 devolve 0; confira add == b a cada passo (x < k);
  produtos em ll; para m grande troque * por mulmod __int128.
Catalogo: Teoria dos numeros.
Digitacao: 28 linhas | media.
*****************************LATEX_DESC_END*/
