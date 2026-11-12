// BIT (Fenwick) - soma, k-esimo e BIT de maximo
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

// BIT de maximo: update so cresce, query de prefixo
struct BITMax {
    int n; vector<ll> t;
    BITMax(int n = 0, ll neg = LLONG_MIN) : n(n), t(n + 1, neg) {}
    void upd(int i, ll v) { for (; i <= n; i += i & -i) t[i] = max(t[i], v); }
    ll pre(int i) { ll s = t[0]; for (; i > 0; i -= i & -i) s = max(s, t[i]); return s; }
};
/*LATEX_DESC_BEGIN***************************
-> **BIT (Fenwick) 1D**
Soma de prefixo/intervalo com update pontual, k-esimo por descida e BIT de
maximo. Indexacao 1-based.

Complexidade: add/pre O(log n); lower_bound O(log n); build O(n).
Uso:
  BIT b(n); b.add(i, v); b.pre(i); b.query(l, r);
  BIT b(vector<ll> a);          // a 0-based vira posicoes 1..n
  b.lower_bound(k) -> menor i com pre(i) >= k (n+1 se nao existe)
  Range-add + point-query: b.add(l,v); b.add(r+1,-v); valor em i = b.pre(i)
  k-esimo de multiconjunto: b.add(valor,1); b.lower_bound(k)
  Range-add + range-sum: code/ds/bit_rr.cpp; 2D: code/ds/bit2d.cpp
  BITMax: update so cresce (upd = max), query de prefixo (LIS ponderado)

* Sobre o codigo:
  t[i] cobre (i - lowbit(i), i]. O build soma os blocos em O(n).
  lower_bound desce os bits altos mantendo pos e o k restante.
  BITMax guarda maximos de prefixo e nao suporta diminuir valores.

* Problemas e reducoes:
  + Soma em intervalo com update pontual.
  + k-esimo menor de multiconjunto (lower_bound).
  + Contar inversoes (BIT de frequencia).
  + LIS ponderado e dominancia 2D com BITMax e valores comprimidos.
  + Range-add + point-query usando o array de diferencas.
  + Euler tour: soma/contagem em subarvore.

Cuidados: lower_bound exige valores >= 0 (monotonia); devolve n+1 se nao
  existe. add com i fora de [1,n] nao e checado (r+1 = n+1 e ok).
Catalogo: Estruturas de dados e queries.
Digitacao: 24 linhas | facil. Atalho: o build O(n) pode virar um laco de
  add O(n log n), que e mais curto.
*****************************LATEX_DESC_END*/
