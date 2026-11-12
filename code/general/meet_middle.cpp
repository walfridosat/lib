// Meet in the middle (subconjuntos, n <= 40)
//
// O que faz: gera somas das duas metades e combina com ordenacao + two pointers.
//            countSubsetsLE: nº de subconjuntos com soma <= S; closestSubset: maior soma <= S; countSubsetsEq: soma == S.
// Quando usar: n <= 40 com valores grandes (DP na soma inviavel). Catalogo > Arrays e guloso (Meet in the middle)
// Complexidade: O(2^(n/2) * n/2) (geracao ordenada por merge: O(2^(n/2)))
// Uso: vector<ll> a (qualquer sinal);  countSubsetsLE(a, S), closestSubset(a, S), countSubsetsEq(a, S).
// Cuidados: o subconjunto vazio conta. Para xor use o mesmo esqueleto trocando + por ^ (ver code/bits/xor_basis.cpp
//           se n grande e valores pequenos). 3^(n/2) se cada item tem 3 escolhas.
// gera todas as somas dos subconjuntos de a[l, r), ordenadas (merge incremental)
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
// maior soma <= S (LLONG_MIN se nenhuma, ex.: todos > S e S < 0)
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
