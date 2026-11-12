// Inversos modulares em lote
//
// O que faz: inv[1..n] mod p linear; inverso de um vetor arbitrario com um
//   unico pow; fatorial e inverso do fatorial.
// Quando usar: Catalogo > Teoria dos numeros (inverso em lote); pre-calculo de
//   binomiais (ver combinatorics).
// Complexidade: O(n) (+ um pow de O(log p)).
// Uso: inv_upto(n,p) -> vector inv com inv[i] = i^-1 mod p (p primo > n).
//   batch_inv(v,p) -> inversos de v[i] (todos nao nulos mod p).
// Cuidados: p primo (para o pow); elementos 0 mod p quebram batch_inv.
ll pw_mod(ll b, ll e, ll m) {
    ll r = 1 % m; b %= m;
    for (; e; e >>= 1, b = b * b % m) if (e & 1) r = r * b % m;
    return r;
}
vector<ll> inv_upto(int n, ll p) {
    vector<ll> inv(n + 1, 1);
    for (int i = 2; i <= n; i++) inv[i] = (p - (p / i) * inv[p % i] % p) % p;
    return inv;
}
vector<ll> batch_inv(const vector<ll> &v, ll p) {
    int n = v.size();
    vector<ll> pre(n + 1, 1), r(n);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] * (v[i] % p) % p;
    ll t = pw_mod(pre[n], p - 2, p); // inverso do produto total
    for (int i = n - 1; i >= 0; i--) {
        r[i] = t * pre[i] % p; // inverso de v[i]
        t = t * (v[i] % p) % p;
    }
    return r;
}
// fatoriais e inversos dos fatoriais ate n (mod p primo > n)
vector<ll> fact_tab, ifact_tab;
void build_fact(int n, ll p) {
    fact_tab.assign(n + 1, 1); ifact_tab.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) fact_tab[i] = fact_tab[i - 1] * i % p;
    ifact_tab[n] = pw_mod(fact_tab[n], p - 2, p);
    for (int i = n; i > 0; i--) ifact_tab[i - 1] = ifact_tab[i] * i % p;
}
