// Binomial modulo composto qualquer (e potencia de primo)
//
// O que faz: C(n,k) mod m para m arbitrario, n,k ate 1e18. Fatora m=prod p^e,
//   calcula C mod p^e (tira os fatores p do fatorial; tabela do produto das
//   unidades mod p^e) e junta por CRT.
// Quando usar: "Catalogo > Combinatoria" (binomial mod composto / mod p^e, Lucas generalizado).
// Complexidade: construcao O(sum p^e); consulta O(#primos * log n * log).
// Uso: BinomMod B(m); B.C(n,k).
// Cuidados: memoria ~ sum p^e (cada p^e ate ~1e7); se m for primo grande
//   (1e9) use binom_mod.cpp. Produtos usam ll: m < 3e9 e suficiente.
struct BinomMod {
    ll m;
    vector<ll> P, E, PE; // primo, expoente, p^e
    vector<vector<ll>> tab; // tab[i][x] = produto dos j<=x com p nao dividindo j, mod p^e
    static ll egcd(ll a, ll b, ll &x, ll &y) {
        if (!b) { x = 1; y = 0; return a; }
        ll g = egcd(b, a % b, y, x); y -= a / b * x; return g;
    }
    static ll inv(ll a, ll mod) { // a coprimo com mod
        ll x, y; egcd(a % mod, mod, x, y); return (x % mod + mod) % mod;
    }
    BinomMod(ll m_) : m(m_) {
        ll t = m;
        for (ll p = 2; p * p <= t; p++) if (t % p == 0) {
            ll e = 0, q = 1; while (t % p == 0) t /= p, e++, q *= p;
            P.push_back(p); E.push_back(e); PE.push_back(q);
        }
        if (t > 1) P.push_back(t), E.push_back(1), PE.push_back(t);
        for (size_t i = 0; i < P.size(); i++) {
            vector<ll> v(PE[i]);
            v[0] = 1 % PE[i];
            for (ll x = 1; x < PE[i]; x++) v[x] = v[x-1] * (x % P[i] ? x : 1) % PE[i];
            tab.push_back(v);
        }
    }
    ll pwq(ll b, ll e, ll q) { ll r = 1 % q; for (; e; e >>= 1, b = b * b % q) if (e & 1) r = r * b % q; return r; }
    // n! sem os fatores p, mod p^e (i = indice do primo)
    ll fct(ll n, int i) {
        ll p = P[i], q = PE[i], r = 1;
        while (n) {
            r = r * tab[i][n % q] % q;                    // resto do bloco incompleto
            r = r * pwq(tab[i][q-1], n / q, q) % q;       // blocos completos de tamanho q
            n /= p;                                       // multiplos de p: (n/p)! recursivo
        }
        return r;
    }
    ll vp(ll n, ll p) { ll c = 0; while (n) n /= p, c += n; return c; } // Legendre
    ll C(ll n, ll k) {
        if (k < 0 || k > n || m == 1) return 0;
        ll res = 0, mod = 1; // CRT incremental
        for (size_t i = 0; i < P.size(); i++) {
            ll p = P[i], q = PE[i];
            ll v = vp(n, p) - vp(k, p) - vp(n - k, p);
            ll r;
            if (v >= E[i]) r = 0;
            else {
                r = fct(n, i) * inv(fct(k, i) * fct(n - k, i) % q, q) % q;
                for (ll j = 0; j < v; j++) r = r * p % q;
            }
            // x = res + mod * t  com  x == r (mod q)
            ll t = ((r - res) % q + q) % q * inv(mod % q, q) % q;
            res += mod * t; mod *= q;
        }
        return res % m;
    }
};
