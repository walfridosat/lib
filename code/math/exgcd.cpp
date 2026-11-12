// Euclides estendido, diofantina linear, contagem de solucoes em caixa
//
// O que faz: exgcd; resolve a*x + b*y = c; conta solucoes com x em [x1,x2] e
//   y em [y1,y2]; inverso modular para m qualquer (coprimo).
// Quando usar: Catalogo > Teoria dos numeros (equacao linear ax+by=c, todas as
//   solucoes x=x0+k*b/g, y=y0-k*a/g; inverso mod nao primo).
// Complexidade: O(log).
// Uso: exgcd(a,b,x,y) -> g com a*x+b*y=g (a,b>=0).
//   dioph(a,b,c,x,y,g) -> false se nao ha solucao; senao uma solucao (x,y).
//   count_dioph(a,b,c,x1,x2,y1,y2) -> numero de solucoes inteiras na caixa.
//   inv_mod(a,m) -> inverso de a mod m (-1 se gcd != 1).
// Cuidados: valores intermediarios em __int128 (|c| ate ~1e18 ok). Casos
//   a=0 ou b=0 tratados. Solucao devolvida por dioph pode ser grande
//   (ate ~|c|); confira o intervalo antes de multiplicar de novo.
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
