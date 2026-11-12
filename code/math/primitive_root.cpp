// phi, lambda de Carmichael, ordem multiplicativa, raiz primitiva
//
// O que faz: phi(n) e lambda(n) por trial division; ord_n(a); menor raiz
//   primitiva mod n (ou -1 se nao existe); numero de raizes = phi(phi(n)).
// Quando usar: Catalogo > Teoria dos numeros (ordem multiplicativa, raiz
//   primitiva, indice/log via raiz primitiva, ciclos de a^k mod n).
// Complexidade: O(sqrt n + log^2) por chamada.
// Uso: ord_mult(a,n) (gcd(a,n)=1), prim_root(n) (n ate ~1e12 ok).
//   a e potencia k-esima mod p sse a^((p-1)/gcd(k,p-1)) = 1.
// Cuidados: raiz primitiva existe so para n=1,2,4,p^k,2p^k. ord_mult nao
//   verifica coprimalidade. Para fatoracao grande troque trial_fact por
//   factorize (pollard_rho.cpp).
typedef __int128 LL;
ll pm(ll b, ll e, ll m) {
    ll r = 1 % m; b %= m;
    for (; e; e >>= 1, b = (LL)b * b % m) if (e & 1) r = (LL)r * b % m;
    return r;
}
vector<pair<ll, int>> trial_fact(ll n) {
    vector<pair<ll, int>> f;
    for (ll p = 2; p * p <= n; p++) if (n % p == 0) {
        int e = 0;
        while (n % p == 0) n /= p, e++;
        f.push_back({p, e});
    }
    if (n > 1) f.push_back({n, 1});
    return f;
}
ll phi_of(ll n) {
    ll r = n;
    for (auto [p, e] : trial_fact(n)) r -= r / p;
    return r;
}
ll carmichael(ll n) { // lambda(n): a^k mod n depende so de k mod lambda
    ll l = 1;
    for (auto [p, e] : trial_fact(n)) {
        ll t;
        if (p == 2) t = e == 1 ? 1 : e == 2 ? 2 : 1LL << (e - 2);
        else { t = p - 1; for (int i = 1; i < e; i++) t *= p; }
        l = l / __gcd(l, t) * t;
    }
    return l;
}
ll ord_mult(ll a, ll n) { // menor k>0 com a^k = 1 (mod n); gcd(a,n)=1
    ll o = phi_of(n);
    for (auto [q, e] : trial_fact(o))
        while (o % q == 0 && pm(a, o / q, n) == 1) o /= q;
    return o;
}
ll prim_root(ll n) { // menor raiz primitiva ou -1
    if (n == 1) return 0;
    if (n == 2) return 1;
    if (n == 4) return 3;
    // checa forma p^k ou 2p^k
    ll t = n % 2 == 0 ? n / 2 : n;
    if (t % 2 == 0) return -1;
    auto f = trial_fact(t);
    if (f.size() != 1) return -1;
    ll ph = phi_of(n);
    auto qs = trial_fact(ph);
    for (ll g = 2;; g++) {
        if (__gcd(g, n) != 1) continue;
        bool ok = true;
        for (auto [q, e] : qs) if (pm(g, ph / q, n) == 1) { ok = false; break; }
        if (ok) return g;
    }
}
