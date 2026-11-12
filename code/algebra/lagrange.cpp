// Lagrange em pontos consecutivos (0..d)
const ll MOD = 1000000007;
ll pw(ll b, ll e) {
    ll r = 1; b %= MOD; if (b < 0) b += MOD;
    for (; e; e >>= 1, b = b * b % MOD) if (e & 1) r = r * b % MOD;
    return r;
}
ll lagrange(const vector<ll>& y, ll n) {
    int d = (int)y.size() - 1;
    if (n >= 0 && n <= d) return y[n] % MOD;
    n %= MOD; if (n < 0) n += MOD;
    vector<ll> pre(d + 2, 1), suf(d + 2, 1), fi(d + 1), f(d + 1, 1);
    for (int i = 1; i <= d; i++) f[i] = f[i - 1] * i % MOD;
    fi[d] = pw(f[d], MOD - 2);
    for (int i = d; i > 0; i--) fi[i - 1] = fi[i] * i % MOD;
    for (int i = 0; i <= d; i++) pre[i + 1] = pre[i] * ((n - i + MOD) % MOD) % MOD;      // prod_{j<=i}(n-j)
    for (int i = d; i >= 0; i--) suf[i] = suf[i + 1] * ((n - i + MOD) % MOD) % MOD;      // prod_{j>=i}(n-j)
    ll res = 0;
    for (int i = 0; i <= d; i++) {
        ll t = y[i] % MOD * pre[i] % MOD * suf[i + 1] % MOD * fi[i] % MOD * fi[d - i] % MOD;
        if ((d - i) & 1) t = (MOD - t) % MOD; // sinal (-1)^(d-i)
        res = (res + t) % MOD;
    }
    return res;
}
/*LATEX_DESC_BEGIN***************************
-> **Interpolacao de Lagrange em pontos consecutivos**
Dado y[i] = P(i) para i = 0..d (P de grau <= d), calcula P(n) para n qualquer,
0-based.

Complexidade: O(d), sem inverso por termo (prefixos/sufixos de prod(n-j)).
Uso:
  vector<ll> y = {P(0), ..., P(d)};
  ll r = lagrange(y, n);

* Sobre o codigo:
  Usa a formula de Lagrange com denominador i! * (d-i)! * (-1)^(d-i) e os
  produtos prefixo/sufixo de (n-j). Fatoriais e inversos sao pre-calculados,
  entao cada termo e O(1). Se n <= d, devolve y[n] direto.

* Problemas e reducoes:
  + "n ate 1e18 mas a resposta parece polinomial": calcule d+2 valores por
    brute e interpole.
  + DP cuja resposta e polinomio em n (grau d -> d+1 pontos).
  + Soma de potencias (ver code/algebra/power_sum.cpp).

Cuidados: MOD primo e d < MOD. Para pontos nao consecutivos use interpolate de
  code/algebra/poly.cpp ou o O(n^2) classico. Se f(n) = sum_{i<=n} g(i) com g
  de grau d, f tem grau d+1: passe d+2 pontos.
Catalogo: Algebra, polinomios e FFT (Lagrange em pontos consecutivos).
Digitacao: 24 linhas | media.
*****************************LATEX_DESC_END*/
