// Floor sum (algoritmo tipo Euclides)
//
// O que faz: floor_sum = sum_{i=0}^{n-1} floor((a*i+b)/m) exato (cabe em ll se
//   o resultado couber). floor_sum3 devolve (sum f, sum i*f, sum f^2) mod MOD
//   com i = 0..n (inclusive).
// Quando usar: Catalogo > Teoria dos numeros (floor sum; pontos de rede sob
//   reta; sum (a*i+b) mod m = sum(a*i+b) - m*floor_sum; contar ax+by<=n).
// Complexidade: O(log m).
// Uso: floor_sum(n,m,a,b) com n>=0,m>=1, a,b quaisquer (negativos ok).
//   floor_sum3(n,a,b,c) -> {f,g,h} para floor((a*i+b)/c), i=0..n, mod MOD.
// Cuidados: floor_sum usa unsigned: resultado deve caber em ull. Em floor_sum3
//   a, b, c < 2^62 ok (operacoes mod MOD). c>=1.
typedef unsigned long long ull;
ull fs_unsigned(ull n, ull m, ull a, ull b) {
    ull ans = 0;
    while (true) {
        if (a >= m) { ans += n * (n - 1) / 2 * (a / m); a %= m; }
        if (b >= m) { ans += n * (b / m); b %= m; }
        ull y = a * n + b;
        if (y < m) break;
        n = y / m; b = y % m;
        swap(m, a); // troca papeis
    }
    return ans;
}
ll floor_sum(ll n, ll m, ll a, ll b) {
    ull ans = 0;
    if (a < 0) { // leva a para [0,m)
        ll a2 = ((a % m) + m) % m;
        ans -= (ull)(n * (n - 1) / 2) * ((a2 - a) / m);
        a = a2;
    }
    if (b < 0) {
        ll b2 = ((b % m) + m) % m;
        ans -= (ull)n * ((b2 - b) / m);
        b = b2;
    }
    return (ll)(ans + fs_unsigned(n, m, a, b));
}
// versao com soma de i*f e f^2 (recursao classica), tudo mod MOD
const ll MODF = 998244353, I2 = (MODF + 1) / 2, I6 = 166374059; // inverso de 6 mod 998244353
struct FGH { ll f, g, h; };
FGH floor_sum3(ll n, ll a, ll b, ll c) { // i = 0..n
    ll N = n % MODF, N1 = (n + 1) % MODF;
    ll s1 = N * N1 % MODF * I2 % MODF;                 // n(n+1)/2
    ll s2 = N * N1 % MODF * ((2 * n + 1) % MODF) % MODF * I6 % MODF; // n(n+1)(2n+1)/6
    if (a == 0) {
        ll bc = (b / c) % MODF;
        return {N1 * bc % MODF, bc * s1 % MODF, N1 * bc % MODF * bc % MODF};
    }
    if (a >= c || b >= c) {
        FGH t = floor_sum3(n, a % c, b % c, c);
        ll ac = (a / c) % MODF, bc = (b / c) % MODF;
        FGH r;
        r.f = (s1 * ac + N1 * bc + t.f) % MODF;
        r.g = (ac * s2 + bc * s1 + t.g) % MODF;
        r.h = (ac * ac % MODF * s2 + bc * bc % MODF * N1 + ac * bc % MODF * N % MODF * N1
               + t.h + 2 * bc % MODF * t.f + 2 * ac % MODF * t.g) % MODF;
        return r;
    }
    ll m = (ll)(((__int128)a * n + b) / c);
    if (m == 0) return {0, 0, 0};
    FGH t = floor_sum3(m - 1, c, c - b - 1, a);
    ll M = m % MODF, r;
    FGH res;
    res.f = ((N * M - t.f) % MODF + MODF) % MODF;
    res.g = (((M * N % MODF * N1 - t.h - t.f) % MODF + MODF) % MODF) * I2 % MODF;
    r = (N * M % MODF * ((M + 1) % MODF) - 2 * t.g - 2 * t.f - res.f) % MODF;
    res.h = (r % MODF + MODF) % MODF;
    return res;
}
