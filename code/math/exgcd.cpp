// Euclides estendido, diofantina e inverso modular
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) { x = 1; y = 0; return a; }
    ll g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}
ll inv_mod(ll a, ll m) {
    ll x, y; a %= m; if (a < 0) a += m;
    if (exgcd(a, m, x, y) != 1) return -1;
    return (x % m + m) % m;
}
typedef __int128 LL;
LL fdiv(LL a, LL b) { return a / b - ((a % b != 0) && ((a < 0) != (b < 0))); } // piso
LL cdiv(LL a, LL b) { return -fdiv(-a, b); } // teto
bool dioph(ll a, ll b, ll c, ll &x, ll &y, ll &g) {
    if (a == 0 && b == 0) { x = y = 0; g = 0; return c == 0; }
    ll u, v; g = exgcd(llabs(a), llabs(b), u, v);
    if (c % g) return false;
    LL k = c / g;
    x = (ll)((LL)u * (a < 0 ? -1 : 1) * k); // pode ser grande; ok se |c|*|b|/g cabe em ll
    y = (ll)((LL)v * (b < 0 ? -1 : 1) * k);
    return true;
}
ll count_dioph(ll a, ll b, ll c, ll x1, ll x2, ll y1, ll y2) {
    if (x1 > x2 || y1 > y2) return 0;
    if (a == 0 && b == 0) return c == 0 ? (ll)(x2 - x1 + 1) * (y2 - y1 + 1) : 0;
    if (a == 0) { // b*y = c
        if (c % b) return 0;
        ll y = c / b; return (y1 <= y && y <= y2) ? x2 - x1 + 1 : 0;
    }
    if (b == 0) {
        if (c % a) return 0;
        ll x = c / a; return (x1 <= x && x <= x2) ? y2 - y1 + 1 : 0;
    }
    ll u, v; ll g = exgcd(llabs(a), llabs(b), u, v);
    if (c % g) return 0;
    LL x0 = (LL)u * (a < 0 ? -1 : 1) * (c / g), y0 = (LL)v * (b < 0 ? -1 : 1) * (c / g);
    LL A = a / g, B = b / g; // x = x0 + k*B, y = y0 - k*A
    LL lo = -((LL)1 << 120), hi = ((LL)1 << 120); // intervalo de k
    auto cut = [&](LL l, LL h, LL d) { // l <= k*d <= h
        if (d > 0) { lo = max(lo, cdiv(l, d)); hi = min(hi, fdiv(h, d)); }
        else { lo = max(lo, cdiv(h, d)); hi = min(hi, fdiv(l, d)); }
    };
    cut(x1 - x0, x2 - x0, B);
    cut(y0 - y2, y0 - y1, A);
    return hi >= lo ? (ll)(hi - lo + 1) : 0;
}
/*LATEX_DESC_BEGIN***************************
-> **Euclides estendido, diofantina e inverso**
Resolve a*x + b*y = c, conta solucoes em uma caixa e calcula inverso modular para m qualquer (coprimo).

Complexidade: O(log).
Uso:
  ll g = exgcd(a, b, x, y);                    // a*x + b*y = g
  bool ok = dioph(a, b, c, x, y, g);           // uma solucao
  ll cnt = count_dioph(a, b, c, x1, x2, y1, y2);
  ll iv = inv_mod(a, m);                       // -1 se gcd != 1

* Sobre o codigo:
  exgcd recursivo devolve g e coeficientes de Bezout. dioph multiplica uma
  solucao base por c/g. count_dioph escreve x = x0 + k*B, y = y0 - k*A e
  intersecta os intervalos de k usando fdiv/cdiv (piso e teto exatos).

* Problemas e reducoes:
  + Equacao linear a*x + b*y = c -> dioph; existe solucao sse g | c.
  + Inverso modular com modulo nao primo -> inv_mod.
  + Congruencia a*x = b (mod m) -> dividir por g = gcd(a, m).
  + Contar solucoes inteiras de a*x + b*y = c em uma caixa -> count_dioph.
  + Pontos inteiros sobre uma reta dentro de um retangulo -> count_dioph.
  + Passo de CRT: resolver x = r + m*k (mod m2) -> exgcd.
  + Combinar duas progressoes aritmeticas -> dioph.

Cuidados: intermediarios em __int128 (|c| ate ~1e18 ok); a = 0 ou b = 0
  tratados; a solucao de dioph pode ser grande (ate ~|c|), confira o intervalo
  antes de multiplicar de novo.
Catalogo: Teoria dos numeros.
Digitacao: 47 linhas | media. Atalho: dioph e count_dioph repetem a solucao base; extraia helper.
*****************************LATEX_DESC_END*/
