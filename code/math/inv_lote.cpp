// Inversos modulares em lote
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
// fatoriais e inversos ate n (mod p primo > n)
vector<ll> fact_tab, ifact_tab;
void build_fact(int n, ll p) {
    fact_tab.assign(n + 1, 1); ifact_tab.assign(n + 1, 1);
    for (int i = 1; i <= n; i++) fact_tab[i] = fact_tab[i - 1] * i % p;
    ifact_tab[n] = pw_mod(fact_tab[n], p - 2, p);
    for (int i = n; i > 0; i--) ifact_tab[i - 1] = ifact_tab[i] * i % p;
}
/*LATEX_DESC_BEGIN***************************
-> **Inversos modulares em lote**
Calcula inv[1..n] em O(n), inversos de um vetor com um unico pow e fatoriais com inversos.

Complexidade: O(n) + um pow O(log p).
Uso:
  vector<ll> inv = inv_upto(n, p);             // p primo > n
  vector<ll> r = batch_inv(v, p);              // v[i] != 0 mod p
  build_fact(n, p);                            // fact_tab, ifact_tab

* Sobre o codigo:
  inv_upto usa inv[i] = -(p/i) * inv[p % i] mod p. batch_inv faz prefixos,
  inverte o produto total com um pow e desfaz de tras para frente.
  build_fact calcula o fatorial e, com um pow, o inverso do fatorial de n.

* Problemas e reducoes:
  + Inversos de todos os numeros ate n mod p -> inv_upto.
  + Inverso de varios elementos com um so pow -> batch_inv.
  + Preparar fatorial e inverso do fatorial para binomiais -> build_fact.
  + Dividir muitos valores por um mesmo denominador -> batch_inv.
  + Pre-calcular produtos de prefixo e suas inversas -> batch_inv.

Cuidados: p primo (usa Fermat); elementos 0 mod p quebram batch_inv;
  p > n para inv_upto.
Catalogo: Teoria dos numeros.
Digitacao: 29 linhas | facil. Atalho: fact_tab/ifact_tab podem ser locais de binom_mod.cpp.
*****************************LATEX_DESC_END*/
