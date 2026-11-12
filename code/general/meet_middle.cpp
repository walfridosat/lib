// Meet in the middle - subconjuntos com n <= 40
// somas de a[l,r) ordenadas por merge incremental
vector<ll> allSums(const vector<ll>& a, int l, int r) {
    vector<ll> s = {0};
    for (int i = l; i < r; i++) {
        vector<ll> t(s.size()), u; for (size_t j = 0; j < s.size(); j++) t[j] = s[j] + a[i];
        u.resize(s.size() * 2);
        merge(s.begin(), s.end(), t.begin(), t.end(), u.begin());   // s e t ja ordenados
        s.swap(u);
    }
    return s;
}
ll countSubsetsLE(const vector<ll>& a, ll S) {
    int n = a.size(), h = n / 2;
    auto A = allSums(a, 0, h), B = allSums(a, h, n);
    ll ans = 0; int j = B.size();
    for (ll x : A) {                       // A crescente => limite em B decrescente
        while (j > 0 && x + B[j - 1] > S) j--;
        ans += j;
    }
    return ans;
}
ll countSubsetsEq(const vector<ll>& a, ll S) {
    int n = a.size(), h = n / 2;
    auto A = allSums(a, 0, h), B = allSums(a, h, n);
    ll ans = 0;
    for (ll x : A) ans += upper_bound(B.begin(), B.end(), S - x) - lower_bound(B.begin(), B.end(), S - x);
    return ans;
}
// maior soma <= S (LLONG_MIN se nenhuma)
ll closestSubset(const vector<ll>& a, ll S) {
    int n = a.size(), h = n / 2;
    auto A = allSums(a, 0, h), B = allSums(a, h, n);
    ll best = LLONG_MIN;
    for (ll x : A) {
        auto it = upper_bound(B.begin(), B.end(), S - x);
        if (it != B.begin()) best = max(best, x + *prev(it));
    }
    return best;
}
/*LATEX_DESC_BEGIN***************************
-> **Meet in the Middle**
Gera as somas das duas metades e combina com ordenacao e two pointers.
  countSubsetsLE: numero de subconjuntos com soma <= S
  closestSubset: maior soma <= S
  countSubsetsEq: numero de subconjuntos com soma == S

Complexidade: O(2^(n/2) * n/2); geracao ordenada por merge O(2^(n/2))
Uso:
  ll c = countSubsetsLE(a, S); ll best = closestSubset(a, S);
  ll e = countSubsetsEq(a, S);   // a pode ter qualquer sinal

* Sobre o codigo:
  allSums gera as somas de a[l, r) ja ordenadas por merge incremental.
  A crescente permite limite decrescente em B; Eq usa lower/upper_bound.

* Problemas e reducoes:
  + Contar subconjuntos com soma <= S (n <= 40, valores grandes).
  + Maior soma <= S e soma exatamente S.
  + Xor: mesmo esqueleto trocando + por ^.

Cuidados: o subconjunto vazio conta; para 3 escolhas por item o custo e 3^(n/2).
Catalogo: Arrays e guloso (Meet in the middle)
Digitacao: 39 linhas | media.
*****************************LATEX_DESC_END*/
