// Gulosos com heap e arrependimento
//
// O que faz: (1) jobs com prazo e lucro (1 unidade cada); (2) comprar/vender acoes com arrependimento;
//            (3) k elementos nao adjacentes de soma maxima; (4) tornar array nao decrescente com min sum |a_i - b_i|;
//            (5) ordem de Smith (min sum w*C) e EDF (min atraso maximo).
// Quando usar: "escolher o melhor disponivel, desfazer se vale a pena". Catalogo > Arrays e guloso
//              (Heap guloso, Scheduling, Jobs com prazo e lucro, Acoes, k nao adjacentes, slope trick)
// Complexidade: O(n log n)
// Uso: 0-based. jobsProfit(vector<pair<ll,ll>> (prazo, lucro)) -> lucro maximo (cada job leva 1 unidade, prazo>=1: executa em t em [1, prazo]).
//      stocks(prices) -> lucro maximo com no maximo uma acao em maos por vez (stock II): soma das diferencas positivas adjacentes.
//      kNonAdjacent(a, k) -> soma maxima de k elementos sem dois adjacentes (-INF se k > (n+1)/2).
//      makeNonDecreasing(a, strict) -> min sum |a_i - b_i| com b nao decrescente (ou estritamente crescente).
//      smithOrder(t, w) -> permutacao de jobs que minimiza sum w_i*C_i. edfOrder(d) -> ordem por prazo.
// Cuidados: compare t_i*w_j < t_j*w_i sem dividir; no k nao adjacente o valor -INF marca borda; resultado em ll.

// jobs (prazo, lucro): ordena por prazo; heap de lucros; se tamanho > prazo, remove o menor
ll jobsProfit(vector<pair<ll, ll>> jobs) {
    sort(jobs.begin(), jobs.end());
    priority_queue<ll, vector<ll>, greater<ll>> pq; ll s = 0;
    for (auto& [d, p] : jobs) {
        pq.push(p); s += p;
        if ((ll)pq.size() > d) s -= pq.top(), pq.pop();
    }
    return s;
}
// acoes: uma acao em maos por vez (stock II). Some as diferencas positivas adjacentes.
// Ex.: [0,1,4,7] -> 7; [3,1,4,1,5,9] -> 11. Nao use heap: a versao com dois pushes superconta.
ll stocks(const vector<ll>& pr) {
    ll prof = 0;
    for (size_t i = 1; i < pr.size(); i++) prof += max(0LL, pr[i] - pr[i - 1]);
    return prof;
}
// k nao adjacentes: lista ligada + heap; ao escolher i, funde (l, i, r) num no de valor v_l + v_r - v_i
ll kNonAdjacent(const vector<ll>& a, int k) {
    const ll NEG = -(ll)4e18 / 4;
    int n = a.size(); if (k > (n + 1) / 2) return NEG;
    vector<ll> v(a); vector<int> L(n), R(n); vector<bool> dead(n, false);
    for (int i = 0; i < n; i++) L[i] = i - 1, R[i] = i + 1 < n ? i + 1 : -1;
    priority_queue<pair<ll, int>> pq; for (int i = 0; i < n; i++) pq.push({v[i], i});
    ll ans = 0;
    while (k--) {
        while (dead[pq.top().second] || pq.top().first != v[pq.top().second]) pq.pop();
        auto [val, i] = pq.top(); pq.pop(); ans += val;
        int l = L[i], r = R[i];
        // se falta vizinho, o no fundido recebe -inf (nunca sera escolhido)
        ll nv = (l >= 0 && r >= 0) ? v[l] + v[r] - v[i] : NEG;
        v[i] = nv;
        if (l >= 0) { dead[l] = true; L[i] = L[l]; if (L[l] >= 0) R[L[l]] = i; }
        else L[i] = -1;
        if (r >= 0) { dead[r] = true; R[i] = R[r]; if (R[r] >= 0) L[R[r]] = i; }
        else R[i] = -1;
        pq.push({v[i], i});
    }
    return ans;
}
// slope trick simples: custo minimo para tornar a nao decrescente (b_i inteiros livres)
ll makeNonDecreasing(vector<ll> a, bool strict = false) {
    if (strict) for (size_t i = 0; i < a.size(); i++) a[i] -= i;   // estritamente crescente => nao decrescente em a_i - i
    priority_queue<ll> pq; ll ans = 0;
    for (ll x : a) {
        pq.push(x);
        if (pq.top() > x) ans += pq.top() - x, pq.pop(), pq.push(x);
    }
    return ans;
}
// regra de Smith: ordena por t/w crescente (cross-multiplication, desempate por indice)
vector<int> smithOrder(const vector<ll>& t, const vector<ll>& w) {
    vector<int> o(t.size()); iota(o.begin(), o.end(), 0);
    sort(o.begin(), o.end(), [&](int i, int j) {
        __int128 l = (__int128)t[i] * w[j], r = (__int128)t[j] * w[i];
        return l != r ? l < r : i < j;
    });
    return o;
}
// EDF: minimiza o atraso maximo (ordenar por prazo)
vector<int> edfOrder(const vector<ll>& d) {
    vector<int> o(d.size()); iota(o.begin(), o.end(), 0);
    sort(o.begin(), o.end(), [&](int i, int j) { return d[i] != d[j] ? d[i] < d[j] : i < j; });
    return o;
}
