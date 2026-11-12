// mint - inteiro modular
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
/*LATEX_DESC_BEGIN***************************
-> **mint - inteiro modular**
Struct de aritmetica mod MOD com operadores, pow, inv, leitura e impressao.

Complexidade: O(1) por operacao; inv e pow O(log MOD).
Uso:
  mint a = 5, b = a.pow(10) / 3;
  cin >> a; cout << a;
  a == b, a != b;

* Sobre o codigo:
  v sempre em [0, MOD). Os operadores += e -= ajustam com uma soma/subtracao.
  pow e exponenciacao binaria; inv usa Fermat, logo MOD precisa ser primo.

* Problemas e reducoes:
  + Contagens e DP mod 1e9+7 ou 998244353 -> mint.
  + Coeficientes de polinomios mod p -> mint.
  + Probabilidades como fracao mod p -> mint.
  + Evitar esquecer % em expressoes longas -> mint.

Cuidados: MOD precisa ser primo para / e inv; para outro MOD mude a constante
  (ou troque MOD por variavel static). Divisao por 0 mod p da 0 silenciosamente.
Catalogo: Teoria dos numeros e divisores.
Digitacao: 24 linhas | facil. Atalho: operator!= pode ser !(a == b).
*****************************LATEX_DESC_END*/
