// Pilha monotonica - proximo maior/menor, contribuicao, histograma

// nxt[i] = primeiro j > i com a[j] > a[i], ou n
vector<int> nextGreater(const vector<ll>& a) {
    int n = a.size(); vector<int> nxt(n, n); vector<int> st;
    for (int i = 0; i < n; i++) {
        while (!st.empty() && a[st.back()] < a[i]) nxt[st.back()] = i, st.pop_back();
        st.push_back(i);
    }
    return nxt;
}
// prv[i] = ultimo j < i com a[j] >= a[i], ou -1
vector<int> prevGreaterEq(const vector<ll>& a) {
    int n = a.size(); vector<int> prv(n, -1); vector<int> st;
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && a[st.back()] <= a[i]) prv[st.back()] = i, st.pop_back();
        st.push_back(i);
    }
    return prv;
}
// i e maximo de (prv[i], nxt[i]); esquerda >=, direita >
ll sumMax(const vector<ll>& a) {
    int n = a.size(); auto nx = nextGreater(a); auto pv = prevGreaterEq(a); ll ans = 0;
    for (int i = 0; i < n; i++) ans += a[i] * (ll)(i - pv[i]) * (nx[i] - i);
    return ans;
}
ll sumMin(const vector<ll>& a) {
    vector<ll> b(a.size()); for (size_t i = 0; i < a.size(); i++) b[i] = -a[i];
    return -sumMax(b);
}

// maior retangulo em histograma (area), h[i] >= 0
ll largestRect(const vector<ll>& h) {
    int n = h.size(); vector<int> st; ll best = 0;
    for (int i = 0; i <= n; i++) {
        ll cur = i < n ? h[i] : -1;    // sentinela -1 esvazia a pilha no fim
        while (!st.empty() && h[st.back()] >= cur) {
            ll H = h[st.back()]; st.pop_back();
            int L = st.empty() ? -1 : st.back();
            best = max(best, H * (i - L - 1));
        }
        st.push_back(i);
    }
    return best;
}
// maior submatriz de 1s: histograma por linha
ll largestOnes(const vector<vector<int>>& g) {
    if (g.empty()) return 0;
    int m = g[0].size(); vector<ll> h(m, 0); ll best = 0;
    for (auto& row : g) {
        for (int j = 0; j < m; j++) h[j] = row[j] ? h[j] + 1 : 0;
        best = max(best, largestRect(h));
    }
    return best;
}
// remove n-k; menor lexicografica de tamanho k
vector<ll> minSubseqLex(const vector<ll>& a, int k) {
    int n = a.size(), rem = n - k; vector<ll> st;
    for (int i = 0; i < n; i++) {
        while (rem > 0 && !st.empty() && st.back() > a[i]) st.pop_back(), rem--;
        st.push_back(a[i]);
    }
    st.resize(k);
    return st;
}
/*LATEX_DESC_BEGIN***************************
-> **Pilha Monotonica**
Proximo/anterior maior e menor; soma de max/min de todos os subarrays; maior retangulo
em histograma e em matriz 0/1; menor subsequencia lexicografica de tamanho k.

Complexidade: O(n) cada
Uso:
  auto nx = nextGreater(a);      // nxt[i] = j > i com a[j] > a[i], ou n
  auto pv = prevGreaterEq(a);    // prv[i] = j < i com a[j] >= a[i], ou -1
  ll smax = sumMax(a), smin = sumMin(a);
  ll r = largestRect(h); ll o = largestOnes(grid);
  vector<ll> s = minSubseqLex(a, k);

* Sobre o codigo:
  nextGreater/prevGreaterEq mantem pilha de indices e desempilham quando o novo e maior.
  sumMax usa (i - prv[i]) * (nxt[i] - i) como numero de subarrays em que a[i] e maximo.
  largestRect usa sentinela -1 no fim; largestOnes roda por linha.
  minSubseqLex remove n-k elementos enquanto o topo e maior.

* Problemas e reducoes:
  + Proximo maior/menor elemento.
  + Soma de max/min sobre todos os subarrays: sumMax/sumMin.
  + Maior retangulo em histograma e maior submatriz de 1s.
  + Remover k digitos: minSubseqLex.

Cuidados: empates! Um lado estrito (>) e o outro nao estrito (>=), senao conta
  subarrays em dobro; sumMax pode estourar ll com n e valores grandes.
Catalogo: Arrays e guloso (Pilha monotonica, Contribuicao com empates, Maior submatriz de 1s, Menor subsequencia lexicografica)
Digitacao: 62 linhas | media.
*****************************LATEX_DESC_END*/
