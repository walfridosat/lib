// Lucas e Kummer
//
// O que faz: C(n,k) mod p para p primo PEQUENO (p ate ~1e6) e n,k ate 1e18;
//   v_p(C(n,k)) por Kummer (numero de vai-uns ao somar k e n-k na base p).
// Quando usar: "Catalogo > Combinatoria" (Lucas para C(n,k) mod p pequeno; Kummer).
//   Se o modulo e composto/potencia de primo veja binom_general.cpp.
// Complexidade: pre-calc O(p); consulta O(log_p n).
// Uso: Lucas L(p); L.C(n,k). kummer(n,k,p) (devolve -1 se C=0).
// Cuidados: p tem de ser primo. Pre-calculo ocupa 2 arrays de tamanho p.
struct Lucas {
    ll p; vector<ll> f, fi;
    ll pw(ll b, ll e) { ll r = 1; b %= p; for (; e; e >>= 1, b = b * b % p) if (e & 1) r = r * b % p; return r; }
    Lucas(ll p_) : p(p_), f(p_), fi(p_) {
        f[0] = 1; for (ll i = 1; i < p; i++) f[i] = f[i-1] * i % p;
        fi[p-1] = pw(f[p-1], p - 2);
        for (ll i = p - 1; i > 0; i--) fi[i-1] = fi[i] * i % p;
    }
    ll small(ll n, ll k) { return k < 0 || k > n ? 0 : f[n] * fi[k] % p * fi[n-k] % p; }
    ll C(ll n, ll k) { // produto dos binomiais dos digitos na base p
        if (k < 0 || k > n) return 0;
        ll r = 1;
        while (n || k) {
            r = r * small(n % p, k % p) % p;
            if (!r) return 0;
            n /= p; k /= p;
        }
        return r;
    }
};
// expoente de p em C(n,k) = numero de vai-uns em k + (n-k) na base p
ll kummer(ll n, ll k, ll p) {
    if (k < 0 || k > n) return -1;
    ll c = 0, carry = 0, a = k, b = n - k;
    while (a || b || carry) {
        ll s = a % p + b % p + carry;
        carry = s >= p; c += carry;
        a /= p; b /= p;
    }
    return c;
}
