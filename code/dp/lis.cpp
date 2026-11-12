// LIS em O(n log n)
//
// O que faz: tamanho da maior subsequencia estritamente crescente.
// Quando usar: Catalogo > DP (LIS). LIS, LDS (rode no reverso), paciencia.
// Complexidade: O(n log n) tempo, O(n) memoria.
// Uso: lis(a) -> tamanho da LIS de a (0-based). Para nao decrescente use upper_bound.
// Cuidados: lower_bound = estritamente crescente; upper_bound = nao decrescente.
ll lis(const vector<ll>& a) {
    vector<ll> t;
    for (ll x : a) {
        auto it = lower_bound(t.begin(), t.end(), x);
        if (it == t.end()) t.push_back(x);
        else *it = x;
    }
    return t.size();
}
