// Lucas e Kummer - C(n,k) mod p pequeno
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
// v_p(C(n,k)) por Kummer
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
/*LATEX_DESC_BEGIN***************************
-> **Lucas e Kummer**
C(n,k) mod p para p primo pequeno e n,k ate 1e18; v_p(C(n,k)) por Kummer.

Complexidade: pre-calculo O(p); consulta O(log_p n).
Uso:
  Lucas L(p);
  ll c = L.C(n, k);
  ll v = kummer(n, k, p);       // -1 se C = 0

* Sobre o codigo:
  Lucas pre-calcula fatoriais e inversos ate p-1 e multiplica os binomiais
  dos digitos de n e k na base p. Kummer conta os vai-uns ao somar k e n-k.

* Problemas e reducoes:
  + C(n,k) mod p com p pequeno e n grande -> Lucas.
  + Decidir se p divide C(n,k) -> kummer > 0.
  + Expoente de p em C(n,k) -> kummer.
  + C(n,k) mod p^e -> binom_general.cpp.
  + Coeficientes de (1+x)^n mod p -> L.C(n,k).
  + Contar caminhos mod p pequeno -> Lucas.

Cuidados: p tem de ser primo; o pre-calculo ocupa 2 arrays de tamanho p;
  se o modulo e composto ou potencia de primo use binom_general.cpp.
Catalogo: Combinatoria.
Digitacao: 31 linhas | facil. Atalho: pw local duplica outros arquivos; use pw_mod.
*****************************LATEX_DESC_END*/
