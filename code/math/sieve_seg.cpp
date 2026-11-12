// Crivo segmentado (primos e phi em [L, R])
//
// O que faz: primos em [L,R] e phi de cada numero do intervalo, usando so os
//   primos <= sqrt(R).
// Quando usar: Catalogo > Teoria dos numeros (crivo segmentado; R ate ~1e12
//   e R-L ate ~1e7).
// Complexidade: O(sqrt(R) + (R-L) log log R).
// Uso: seg_primes(L,R) devolve vector<ll> dos primos em [L,R].
//   seg_phi(L,R) devolve ph[i-L] para i em [L,R].
//   Para fatorar, copie o corpo de seg_phi (rem[x] guarda o que sobrou).
// Cuidados: L>=1. O 1 nao e primo (tratado). Primos ate sqrt(R) gerados aqui.
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
