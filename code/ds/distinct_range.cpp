// Distintos em intervalo (offline, sweep por r + BIT)
//
// O que faz: para cada query [l,r] devolve (a) quantidade de valores
//   distintos e (b) soma dos valores distintos.
// Quando usar: Catalogo > Estruturas de dados ("Distintos em [l,r]",
//   "Distintos em intervalo, versao com soma"; distintos em subarvore via
//   Euler tour).
// Complexidade: O((n + q) log n).
// Uso: vector<pair<ll,ll>> r = distinct_range(a, qs); a 0-based, qs com
//   pares (l,r) 0-based inclusivos; r[i] = {qtd distintos, soma distintos}.
// Cuidados: valores quaisquer (comprime internamente). Soma pode ser ll.
vector<pair<ll, ll>> distinct_range(const vector<ll>& a, const vector<pair<int, int>>& qs) {
    int n = a.size(), q = qs.size();
    vector<ll> vs(a); sort(vs.begin(), vs.end()); vs.erase(unique(vs.begin(), vs.end()), vs.end());
    vector<int> last(vs.size(), -1);
    vector<vector<int>> byr(n);
    for (int i = 0; i < q; i++) byr[qs[i].second].push_back(i);
    vector<ll> c(n + 1, 0), s(n + 1, 0); // duas BITs (contagem, soma)
    auto upd = [&](int i, ll dc, ll ds) { for (i++; i <= n; i += i & -i) { c[i] += dc; s[i] += ds; } };
    auto pre = [&](int i, ll& rc, ll& rs) { rc = rs = 0; for (i++; i > 0; i -= i & -i) { rc += c[i]; rs += s[i]; } };
    vector<pair<ll, ll>> res(q);
    for (int i = 0; i < n; i++) {
        int k = lower_bound(vs.begin(), vs.end(), a[i]) - vs.begin();
        if (last[k] >= 0) upd(last[k], -1, -a[i]); // apaga ocorrencia anterior
        upd(i, 1, a[i]); last[k] = i;              // so a ultima ocorrencia conta
        for (int id : byr[i]) {
            ll c1, s1, c0, s0;
            pre(i, c1, s1); pre(qs[id].first - 1, c0, s0);
            res[id] = {c1 - c0, s1 - s0};
        }
    }
    return res;
}
