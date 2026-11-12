// CRT geral (modulos nao coprimos) e Garner
//
// O que faz: crt_merge combina x=a1 (m1) e x=a2 (m2) em x=r (lcm); crt_all
//   combina varias; garner reconstroi x mod M a partir de residuos em modulos
//   primos entre si (sem bigint).
// Quando usar: Catalogo > Teoria dos numeros (sistema de congruencias; CRT com
//   modulos nao coprimos; Garner para NTT de 3 primos / resposta mod qualquer).
// Complexidade: crt_merge O(log); garner O(k^2 log).
// Uso: bool crt_merge(r,m,a2,m2) atualiza (r,m) in place; false se sem solucao
//   (ou lcm > ~9e18). crt_all(a,m,&r,&M) -> bool. Resultado r em [0,M).
//   garner(r,m,M): vetores de residuos/modulos (m[i] < 2^31, coprimos 2 a 2).
// Cuidados: comece com r=0,m=1. m>=1. Se lcm estourar ll, crt_merge devolve
//   false (nao distingue de sem solucao: ajuste se precisar).
typedef __int128 LL;
ll exg(ll a, ll b, ll &x, ll &y) {
    if (!b) { x = 1; y = 0; return a; }
    ll g = exg(b, a % b, y, x); y -= a / b * x; return g;
}
bool crt_merge(ll &r, ll &m, ll a2, ll m2) {
    ll x, y, g = exg(m, m2, x, y);
    ll d = a2 - r;
    if (d % g) return false; // sem solucao
    ll m2g = m2 / g;
    // k = (d/g) * inv(m/g) mod (m2/g);  x = r + m*k
    LL k = (LL)(d / g % m2g) * (x % m2g) % m2g;
    if (k < 0) k += m2g;
    LL L = (LL)m / g * m2; // novo modulo
    if (L > (LL)4e18) return false;
    LL nr = ((LL)r + (LL)m * k) % L; if (nr < 0) nr += L;
    r = (ll)nr; m = (ll)L;
    return true;
}
bool crt_all(const vector<ll> &a, const vector<ll> &m, ll &r, ll &M) {
    r = 0; M = 1;
    for (size_t i = 0; i < a.size(); i++) {
        ll ai = ((a[i] % m[i]) + m[i]) % m[i];
        if (!crt_merge(r, M, ai, m[i])) return false;
    }
    return true;
}
// Garner: x = sum t[i] * prod_{j<i} m[j]; devolve x mod M
ll garner(const vector<ll> &r, const vector<ll> &m, ll M) {
    int k = r.size();
    vector<ll> t(k);
    for (int i = 0; i < k; i++) {
        t[i] = r[i] % m[i];
        for (int j = 0; j < i; j++) { // t[i] = (t[i]-t[j]) * inv(m[j]) mod m[i]
            ll x, y; exg(m[j] % m[i], m[i], x, y); x = (x % m[i] + m[i]) % m[i];
            t[i] = ((t[i] - t[j]) % m[i] + m[i]) % m[i] * x % m[i];
        }
    }
    ll res = 0, pr = 1 % M;
    for (int i = 0; i < k; i++) {
        res = (res + (LL)t[i] % M * pr) % M;
        pr = (LL)pr * (m[i] % M) % M;
    }
    return res;
}
