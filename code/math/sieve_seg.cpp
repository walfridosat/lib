// Crivo segmentado
vector<int> small_primes(ll lim) { // primos <= lim
    vector<char> c(lim + 1, 1); vector<int> p;
    for (ll i = 2; i <= lim; i++) if (c[i]) {
        p.push_back(i);
        for (ll j = i * i; j <= lim; j += i) c[j] = 0;
    }
    return p;
}
ll isqrt_ll(ll x) { // piso da raiz quadrada
    ll s = sqrtl((long double)x);
    while (s * s > x) s--;
    while ((s + 1) * (s + 1) <= x) s++;
    return s;
}
vector<ll> seg_primes(ll L, ll R) {
    if (L < 2) L = 2;
    vector<ll> res; if (L > R) return res;
    vector<char> c(R - L + 1, 1);
    for (ll p : small_primes(isqrt_ll(R))) {
        // comeca em p*p para nao apagar o proprio p
        for (ll j = max(p * p, (L + p - 1) / p * p); j <= R; j += p) c[j - L] = 0;
    }
    for (ll i = L; i <= R; i++) if (c[i - L]) res.push_back(i);
    return res;
}
vector<ll> seg_phi(ll L, ll R) { // phi de todo i em [L,R], L>=1
    vector<ll> rem(R - L + 1), ph(R - L + 1);
    for (ll i = L; i <= R; i++) rem[i - L] = i, ph[i - L] = i;
    for (ll p : small_primes(isqrt_ll(R))) {
        for (ll j = (L + p - 1) / p * p; j <= R; j += p) {
            ph[j - L] -= ph[j - L] / p; // phi *= (1 - 1/p)
            while (rem[j - L] % p == 0) rem[j - L] /= p;
        }
    }
    for (ll i = L; i <= R; i++) // sobrou um primo > sqrt(R)
        if (rem[i - L] > 1) ph[i - L] -= ph[i - L] / rem[i - L];
    return ph;
}
/*LATEX_DESC_BEGIN***************************
-> **Crivo segmentado**
Primos e phi em [L, R] usando apenas os primos <= sqrt(R).

Complexidade: O(sqrt(R) + (R-L) log log R).
Uso:
  vector<ll> ps = seg_primes(L, R);
  vector<ll> ph = seg_phi(L, R);     // ph[i-L] = phi(i)

* Sobre o codigo:
  small_primes gera os primos pequenos; seg_primes marca o intervalo comecando
  em max(p*p, ceil(L/p)*p). seg_phi multiplica por (1 - 1/p) e remove os
  fatores p de rem; o que sobra > 1 e um primo grande.

* Problemas e reducoes:
  + Primos em [L, R] com R ate 1e12 e R-L ate 1e7 -> seg_primes.
  + phi de todo i em um intervalo grande -> seg_phi.
  + Fatorar cada i de um intervalo -> copiar seg_phi e usar rem.
  + Contar primos em intervalo -> tamanho de seg_primes.
  + Somar phi em um intervalo -> seg_phi.
  + Buscar primos gemeos em [L, R] -> seg_primes.

Cuidados: L >= 1; 1 nao e primo (tratado); os primos ate sqrt(R) sao gerados
  aqui a cada chamada.
Catalogo: Teoria dos numeros.
Digitacao: 38 linhas | media. Atalho: small_primes pode vir de sieve.cpp.
*****************************LATEX_DESC_END*/
