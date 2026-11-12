// Logaritmo discreto (BSGS) para modulo qualquer
//
// O que faz: menor x >= 0 com a^x = b (mod m), ou -1 se nao existe.
// Quando usar: Catalogo > Teoria dos numeros (BSGS, a^x = b mod m; gcd(a,m) != 1).
// Complexidade: O(sqrt(m)) com hash.
// Uso: dlog(a, b, m) -> x ou -1. m ate ~1e9 (produtos em ll; para m ate 1e18
//   troque * por mulmod __int128).
// Cuidados: m=1 devolve 0. Quando gcd(a,m) > 1 divide-se g dos dois lados
//   deslocando o expoente (variavel k). Ordem das operacoes importa: confira
//   add==b a cada passo (solucao pequena x < k).
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
    // agora gcd(a, m) = 1: add * a^x = b (mod m), resposta k + x
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
