// mint: struct de inteiro modular
//
// O que faz: aritmetica mod MOD (primo) com operadores, pow e inverso.
// Quando usar: Catalogo > Teoria dos numeros e divisores (aritmetica modular).
//   Qualquer contagem/DP mod 1e9+7 ou 998244353; evita esquecer %.
// Complexidade: O(1) por operacao; inv e pow O(log MOD).
// Uso: mint a = 5, b = a.pow(10) / 3; cout << a; cin >> a;
//   Compara com == e !=. mint(-1) funciona (normaliza).
// Cuidados: MOD precisa ser primo para operator/ e inv. Para MOD diferente
//   mude a constante (ou use mint dinamico: troque MOD por variavel static).
//   Divisao por 0 mod p da resultado 0 silenciosamente.
const int MOD = 998244353; // ou 1000000007
struct mint {
    int v;
    mint(ll x = 0) { v = x % MOD; if (v < 0) v += MOD; }
    mint pow(ll e) const {
        mint r = 1, b = *this;
        for (; e; e >>= 1, b *= b) if (e & 1) r *= b;
        return r;
    }
    mint inv() const { return pow(MOD - 2); }
    mint &operator+=(const mint &o) { v += o.v; if (v >= MOD) v -= MOD; return *this; }
    mint &operator-=(const mint &o) { v -= o.v; if (v < 0) v += MOD; return *this; }
    mint &operator*=(const mint &o) { v = (ll)v * o.v % MOD; return *this; }
    mint &operator/=(const mint &o) { return *this *= o.inv(); }
    friend mint operator+(mint a, const mint &b) { return a += b; }
    friend mint operator-(mint a, const mint &b) { return a -= b; }
    friend mint operator*(mint a, const mint &b) { return a *= b; }
    friend mint operator/(mint a, const mint &b) { return a /= b; }
    mint operator-() const { return mint(-v); }
    bool operator==(const mint &o) const { return v == o.v; }
    bool operator!=(const mint &o) const { return v != o.v; }
    friend ostream &operator<<(ostream &os, const mint &a) { return os << a.v; }
    friend istream &operator>>(istream &is, mint &a) { ll x; is >> x; a = mint(x); return is; }
};
