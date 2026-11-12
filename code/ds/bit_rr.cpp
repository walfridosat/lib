// BIT range-update range-query
//
// O que faz: soma em intervalo de v (add em [l,r]) e soma de intervalo,
//   com duas BITs sobre o array de diferencas.
// Quando usar: Catalogo > Estruturas de dados (BIT range-update
//   range-query); update/query em subarvore via Euler tour.
// Complexidade: O(log n) por operacao, memoria O(n).
// Uso: 1-based. BITRR b(n); b.add(l,r,v); b.query(l,r); b.pre(i).
//   Valores iniciais: chame add(i,i,a[i]) para cada i (ou monte a diferenca).
// Cuidados: overflow de ll em v*i se v ~1e18; add(l,r,..) com r+1=n+1 e ok.
struct BITRR {
    int n; vector<ll> b1, b2;
    BITRR(int n = 0) : n(n), b1(n + 2, 0), b2(n + 2, 0) {}
    void upd(int i, ll v) { // diferenca d[i] += v
        ll w = v * (i - 1);
        for (int j = i; j <= n; j += j & -j) { b1[j] += v; b2[j] += w; }
    }
    void add(int l, int r, ll v) { upd(l, v); upd(r + 1, -v); }
    ll pre(int i) { // soma de a[1..i] = B1(i)*i - B2(i)
        ll s1 = 0, s2 = 0;
        for (int j = i; j > 0; j -= j & -j) { s1 += b1[j]; s2 += b2[j]; }
        return s1 * i - s2;
    }
    ll query(int l, int r) { return pre(r) - pre(l - 1); }
};
