// Gulosos com heap - jobs, acoes, k nao adjacentes, slope trick

// jobs: heap de lucros; remove o menor se passar do prazo
ll jobsProfit(vector<pair<ll, ll>> jobs) {
    sort(jobs.begin(), jobs.end());
    priority_queue<ll, vector<ll>, greater<ll>> pq; ll s = 0;
    for (auto& [d, p] : jobs) {
        pq.push(p); s += p;
        if ((ll)pq.size() > d) s -= pq.top(), pq.pop();
    }
    return s;
}
// stock II: soma diferencas positivas adjacentes
// Ex.: [0,1,4,7] -> 7; dois pushes supercontam
ll stocks(const vector<ll>& pr) {
    ll prof = 0;
    for (size_t i = 1; i < pr.size(); i++) prof += max(0LL, pr[i] - pr[i - 1]);
    return prof;
}
// lista ligada + heap; funde (l,i,r) em v_l + v_r - v_i
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
        // sem os dois vizinhos: valor -inf
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
// slope trick: b inteiro livre, nao decrescente
ll makeNonDecreasing(vector<ll> a, bool strict = false) {
    if (strict) for (size_t i = 0; i < a.size(); i++) a[i] -= i;   // estritamente crescente => nao decrescente em a_i - i
    priority_queue<ll> pq; ll ans = 0;
    for (ll x : a) {
        pq.push(x);
        if (pq.top() > x) ans += pq.top() - x, pq.pop(), pq.push(x);
    }
    return ans;
}
// Smith: t/w crescente; desempate por indice
vector<int> smithOrder(const vector<ll>& t, const vector<ll>& w) {
    vector<int> o(t.size()); iota(o.begin(), o.end(), 0);
    sort(o.begin(), o.end(), [&](int i, int j) {
        __int128 l = (__int128)t[i] * w[j], r = (__int128)t[j] * w[i];
        return l != r ? l < r : i < j;
    });
    return o;
}
// EDF: ordena por prazo
vector<int> edfOrder(const vector<ll>& d) {
    vector<int> o(d.size()); iota(o.begin(), o.end(), 0);
    sort(o.begin(), o.end(), [&](int i, int j) { return d[i] != d[j] ? d[i] < d[j] : i < j; });
    return o;
}
/*LATEX_DESC_BEGIN***************************
-> **Gulosos com Heap e Arrependimento**
Jobs com prazo e lucro; acoes; k elementos nao adjacentes de soma maxima;
tornar array nao decrescente com custo minimo; ordem de Smith e EDF.

Complexidade: O(n log n)
Uso:
  ll p = jobsProfit({{prazo, lucro}, ...});  // cada job leva 1 unidade
  ll s = stocks(prices);                     // stock II: uma acao por vez
  ll kbest = kNonAdjacent(a, k);             // -INF se k > (n+1)/2
  ll cost = makeNonDecreasing(a, strict);
  vector<int> o1 = smithOrder(t, w), o2 = edfOrder(d);

* Sobre o codigo:
  jobsProfit ordena por prazo e mantem heap dos lucros; se passar do prazo, tira o menor.
  stocks soma as diferencas positivas adjacentes (uma acao por vez).
  kNonAdjacent usa lista ligada e funde (l, i, r) em v_l + v_r - v_i.
  makeNonDecreasing e slope trick: heap com o topo ajustado a cada x.
  smithOrder compara t_i*w_j < t_j*w_i sem dividir.

* Problemas e reducoes:
  + Jobs com prazo e lucro, 1 unidade cada: jobsProfit.
  + Comprar e vender acoes (stock II, uma por vez): stocks.
  + k elementos nao adjacentes de soma maxima: kNonAdjacent.
  + Min sum |a_i - b_i| com b nao decrescente: makeNonDecreasing.
  + Min sum w_i*C_i: ordem de Smith; min atraso maximo: EDF.

Cuidados: compare t_i*w_j por produto (ou __int128); no k nao adjacente -INF marca
  borda; resultados em ll.
Catalogo: Arrays e guloso (Heap guloso, Scheduling, Jobs com prazo e lucro, Acoes, k nao adjacentes, slope trick)
Digitacao: 65 linhas | media.
*****************************LATEX_DESC_END*/
