// Two pointers - janela monotonica, k distintos, max-min

// conta subarrays nao ruins; menor l valido nao decresce
template<class F> ll countGood(int n, F bad) {
    ll ans = 0; int l = 0;
    for (int r = 0; r < n; r++) {
        while (l <= r && bad(l, r)) l++;   // se l > r a janela e vazia
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

// subarrays com max - min <= K (deques)
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
/*LATEX_DESC_BEGIN***************************
-> **Two Pointers / Janela Deslizante**
Conta subarrays bons quando a propriedade e monotonica; "no maximo k distintos"
(exactK = atMostK(k) - atMostK(k-1)); janela com max - min <= K.

Complexidade: O(n) (ou O(n log n) se bad() for pesado)
Uso:
  ll c = countGood(n, bad);   // bad(l, r) diz se [l, r] e RUIM; precisa ser monotonica
  ll a1 = atMostK(a, k), a2 = exactK(a, k);
  ll m = countMaxMinLE(a, K);

* Sobre o codigo:
  countGood para cada r avanca l enquanto a janela for ruim e soma r - l + 1.
  atMostK usa map de frequencias; exactK subtrai as duas contagens.
  countMaxMinLE mantem deques monotonos do maximo e do minimo.

* Problemas e reducoes:
  + Subarray com soma <= S com valores >= 0.
  + No maximo k valores distintos; exatamente k distintos.
  + Subarrays com max - min <= K.

Cuidados: two pointers NAO vale com negativos (use prefixos + BIT);
  a contagem pode estourar int (use ll).
Catalogo: Arrays e guloso (Two pointers / janela, Exatamente k distintos, Janela com max-min)
Digitacao: 38 linhas | media.
*****************************LATEX_DESC_END*/
