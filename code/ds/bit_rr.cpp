// BIT range-update range-query - duas BITs
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
/*LATEX_DESC_BEGIN***************************
-> **BIT range-update range-query**
Soma em intervalo de v (add em [l,r]) e soma de intervalo, com duas BITs
sobre o array de diferencas. Indexacao 1-based.

Complexidade: O(log n) por operacao; memoria O(n).
Uso:
  BITRR b(n); b.add(l, r, v); b.query(l, r); b.pre(i);
  Valores iniciais: chame add(i, i, a[i]) para cada i (ou monte a diferenca).

* Sobre o codigo:
  d[i] = a[i]-a[i-1]; b1 acumula d e b2 acumula d*(i-1).
  pre(i) = B1(i)*i - B2(i), onde Bk(i) e a soma da BIT correspondente.

* Problemas e reducoes:
  + Add em intervalo e soma em intervalo (range add range sum 1D).
  + Euler tour: update em subarvore e soma em subarvore.
  + Diferencas de segunda ordem para somas de prefixo.

Cuidados: overflow de ll em v*i se v ~1e18; add(l,r,..) com r+1 = n+1 e ok.
Catalogo: Estruturas de dados.
Digitacao: 15 linhas | media.
*****************************LATEX_DESC_END*/
