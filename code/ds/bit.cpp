// BIT (Fenwick) 1D + busca binaria na BIT + BIT de maximo
//
// O que faz: soma de prefixo/intervalo com update pontual; lower_bound
//   (menor i com pre(i) >= k) em O(log n) por descida; construcao O(n).
// Quando usar: Catalogo > Estruturas de dados e queries (BIT, busca binaria
//   na BIT, k-esimo de multiconjunto, dominancia 2D, LIS ponderado).
// Complexidade: add/pre O(log n); lower_bound O(log n); build O(n).
// Uso: indexacao 1-based. BIT b(n); b.add(i,v); b.pre(i); b.query(l,r);
//   BIT b(vector<ll> a) (a 0-based vira posicoes 1..n).
//   Range-add + point-query: b.add(l,v); b.add(r+1,-v); valor em i = b.pre(i).
//   k-esimo de multiconjunto: add(valor,1); b.lower_bound(k) = k-esimo menor.
//   Range-add + range-sum: ver code/ds/bit_rr.cpp. 2D: code/ds/bit2d.cpp.
// Cuidados: lower_bound exige valores >= 0 (monotonia); devolve n+1 se
//   nao existe. add com i fora de [1,n] nao e checado (r+1 = n+1 e ok).
struct BIT {
    int n; vector<ll> t;
    BIT(int n = 0) : n(n), t(n + 1, 0) {}
    BIT(const vector<ll>& a) : n(a.size()), t(a.size() + 1, 0) {
        for (int i = 1; i <= n; i++) t[i] += a[i - 1];
        for (int i = 1; i <= n; i++) { int j = i + (i & -i); if (j <= n) t[j] += t[i]; }
    }
    void add(int i, ll v) { for (; i <= n; i += i & -i) t[i] += v; }
    ll pre(int i) { ll s = 0; for (; i > 0; i -= i & -i) s += t[i]; return s; }
    ll query(int l, int r) { return pre(r) - pre(l - 1); }
    int lower_bound(ll k) { // menor i com pre(i) >= k
        int pos = 0;
        for (int pw = 1 << (31 - __builtin_clz(max(n, 1))); pw; pw >>= 1)
            if (pos + pw <= n && t[pos + pw] < k) { pos += pw; k -= t[pos]; }
        return pos + 1;
    }
};

// BIT de maximo: so valores que AUMENTAM (upd = max com o existente) e
// query de PREFIXO. Ex.: LIS ponderado indexado por valor comprimido.
struct BITMax {
    int n; vector<ll> t;
    BITMax(int n = 0, ll neg = LLONG_MIN) : n(n), t(n + 1, neg) {}
    void upd(int i, ll v) { for (; i <= n; i += i & -i) t[i] = max(t[i], v); }
    ll pre(int i) { ll s = t[0]; for (; i > 0; i -= i & -i) s = max(s, t[i]); return s; }
};
