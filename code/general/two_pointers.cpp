// Two pointers / janela deslizante (templates)
//
// O que faz: (1) conta subarrays "bons" quando a propriedade e monotonica (encolher nunca piora);
//            (2) "no maximo k distintos" e "exatamente k distintos" = atMost(k) - atMost(k-1);
//            (3) janela com max - min <= K usando dois deques.
// Quando usar: "subarray com soma <= S (valores >= 0)", "no maximo k distintos", "max-min <= k".
//              Catalogo > Arrays e guloso (Two pointers / janela, Exatamente k distintos, Janela com max-min)
// Complexidade: O(n) (ou O(n log) se bad() for pesado)
// Uso: 0-based. countGood(n, bad): bad(l, r) deve dizer se a janela [l, r] e RUIM; precisa ser monotona
//      (se [l,r] e ruim, [l,r+1] e [l-1,r] tambem). Devolve o numero de subarrays bons.
//      atMostK(a, k), exactK(a, k) -> contagem de subarrays com <= k / exatamente k valores distintos.
//      countMaxMinLE(a, K) -> subarrays com max - min <= K.
// Cuidados: two pointers NAO vale com negativos (use prefixos + BIT). Contagem pode estourar int (use ll).

// Conta subarrays [l, r] nao ruins. Para cada r, o menor l valido e nao decrescente.
template<class F> ll countGood(int n, F bad) {
    ll ans = 0; int l = 0;
    for (int r = 0; r < n; r++) {
        while (l <= r && bad(l, r)) l++;   // se l > r a janela e vazia (nenhum subarray terminando em r)
        ans += r - l + 1;
    }
    return ans;
}

// subarrays com no maximo k valores distintos
ll atMostK(const vector<int>& a, int k) {
    if (k < 0) return 0;
    map<int, int> cnt; ll ans = 0; int l = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        cnt[a[r]]++;
        while ((int)cnt.size() > k) { if (--cnt[a[l]] == 0) cnt.erase(a[l]); l++; }
        ans += r - l + 1;
    }
    return ans;
}
ll exactK(const vector<int>& a, int k) { return atMostK(a, k) - atMostK(a, k - 1); }

// subarrays com max - min <= K (deques monotonicos de indices)
ll countMaxMinLE(const vector<ll>& a, ll K) {
    deque<int> mx, mn; ll ans = 0; int l = 0;
    for (int r = 0; r < (int)a.size(); r++) {
        while (!mx.empty() && a[mx.back()] <= a[r]) mx.pop_back();
        mx.push_back(r);
        while (!mn.empty() && a[mn.back()] >= a[r]) mn.pop_back();
        mn.push_back(r);
        while (a[mx.front()] - a[mn.front()] > K) {   // encolhe ate valer
            l++;
            if (mx.front() < l) mx.pop_front();
            if (mn.front() < l) mn.pop_front();
        }
        ans += r - l + 1;
    }
    return ans;
}
