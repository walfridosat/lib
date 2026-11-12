// Contagens diversas - hook, grafos, torneios, permanente
// Requer: code/combinatorics/binom_mod.cpp (cole antes).
ll hook_syt(const vector<int>& lam) { // lam decrescente; n!/prod hooks
    int n = 0; for (int x : lam) n += x;
    int rows = lam.size(); ll den = 1;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < lam[i]; j++) {
            int arm = lam[i] - j - 1, leg = 0;
            for (int r = i + 1; r < rows && lam[r] > j; r++) leg++;
            den = den * (arm + leg + 1) % MOD;
        }
    return fact[n] * pw(den, MOD - 2) % MOD;
}
ll forest_orderings(const vector<int>& sz, int n) { // # rotulacoes com pai < filho
    ll den = 1; for (int s : sz) den = den * s % MOD;
    return fact[n] * pw(den, MOD - 2) % MOD;
}
bool erdos_gallai(vector<ll> d) {
    sort(d.rbegin(), d.rend());
    int n = d.size(); ll tot = 0;
    for (ll x : d) { if (x < 0 || x >= n) return false; tot += x; }
    if (tot & 1) return false;
    ll pre = 0;
    for (int k = 1; k <= n; k++) {
        pre += d[k-1];
        ll rhs = (ll)k * (k - 1);
        for (int i = k; i < n; i++) rhs += min<ll>(d[i], k);
        if (pre > rhs) return false;
    }
    return true;
}
// Gale-Ryser: matriz 0/1 com somas a e b?
bool gale_ryser(vector<ll> a, vector<ll> b) {
    ll sa = 0, sb = 0; for (ll x : a) sa += x; for (ll x : b) sb += x;
    if (sa != sb) return false;
    sort(a.rbegin(), a.rend());
    int n = b.size();
    for (ll x : a) if (x > n) return false;
    sort(b.rbegin(), b.rend());
    ll pb = 0; // sum_{i<=k} b_i <= sum_j min(a_j, k)
    for (int k = 1; k <= n; k++) {
        pb += b[k-1]; ll rhs = 0;
        for (ll x : a) rhs += min<ll>(x, k);
        if (pb > rhs) return false;
    }
    return true;
}
bool landau(vector<ll> s) { // placares de torneio (Landau)
    sort(s.begin(), s.end());
    ll pre = 0; int n = s.size();
    for (int k = 1; k <= n; k++) { pre += s[k-1]; if (pre < (ll)k * (k - 1) / 2) return false; }
    return pre == (ll)n * (n - 1) / 2;
}
ll tournament_3cycles(const vector<ll>& out) { // C(n,3) - sum C(out_v,2)
    ll n = out.size(), r = n * (n - 1) * (n - 2) / 6;
    for (ll o : out) r -= o * (o - 1) / 2;
    return r;
}
ll forbidden_perms(int n, const vector<ll>& r) { // sum (-1)^k r_k (n-k)!
    ll s = 0;
    for (int k = 0; k <= n && k < (int)r.size(); k++) {
        ll t = r[k] % MOD * fact[n - k] % MOD;
        s += (k & 1) ? MOD - t : t;
    }
    return s % MOD;
}
// permanente 0/1: Ryser com Gray code
ll permanent01(const vector<vector<int>>& a) {
    int n = a.size(); vector<ll> rs(n, 0);
    ll tot = 0; unsigned g = 0;
    for (unsigned i = 1; i < (1u << n); i++) {
        int j = __builtin_ctz(i);              // coluna que muda no Gray code
        g ^= 1u << j;
        int sgn = (g >> j & 1) ? 1 : -1;
        for (int r = 0; r < n; r++) rs[r] += sgn * a[r][j];
        ll prod = 1;
        for (int r = 0; r < n && prod; r++) prod *= rs[r];
        tot += ((n - __builtin_popcount(g)) & 1) ? -prod : prod;
    }
    return tot;
}
/*LATEX_DESC_BEGIN***************************
-> **Contagens diversas (hook, grafos, torneios, permanente)**
Hook length, extensoes de floresta, Erdos-Gallai, Gale-Ryser, Landau, posicoes proibidas e permanente 0/1.

Complexidade: hook O(n); EG O(n log n); Ryser O(2^n n).
Uso:
  ll h = hook_syt(lambda);
  ll fo = forest_orderings(sz, n);
  bool eg = erdos_gallai(d), gr = gale_ryser(a, b), la = landau(s);
  ll t3 = tournament_3cycles(out);
  ll fp = forbidden_perms(n, r);        // r[k] = # k torres proibidas
  ll pm = permanent01(a);               // n <= ~25

* Sobre o codigo:
  hook_syt divide n! pelo produto dos hooks. forest_orderings divide por
  prod sz. Erdos-Gallai/Gale-Ryser/Landau testam as desigualdades classicas.
  forbidden_perms faz inclusao-exclusao com r_k. permanent01 usa Ryser com
  Gray code, somando produtos de somas de colunas.

* Problemas e reducoes:
  + Numero de tabelas de Young de forma lambda -> hook_syt.
  + Ordenacoes lineares compativeis com uma floresta -> forest_orderings.
  + Saber se uma sequencia de graus realiza um grafo simples -> erdos_gallai.
  + Saber se somas de linha/coluna realizam matriz 0/1 -> gale_ryser.
  + Saber se placares realizam um torneio -> landau.
  + Numero de 3-ciclos de um torneio -> tournament_3cycles.
  + Permutacoes que evitam posicoes proibidas -> forbidden_perms.
  + Permanente de matriz 0/1 (matching perfeito contado) -> permanent01.

Cuidados: Erdos-Gallai exige soma par; ordena internamente (decrescente).
  permanent01 e mod 2^64 em unsigned e exato so se o resultado < 2^63.
Catalogo: Combinatoria.
Digitacao: 79 linhas | dificil. Atalho: erdos_gallai e gale_ryser repetem somas parciais; helper comum.
*****************************LATEX_DESC_END*/
