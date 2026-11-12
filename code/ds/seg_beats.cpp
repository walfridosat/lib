// Segtree beats - chmin e add em range, soma e max
struct Beats {
    const ll NEG = LLONG_MIN / 4;
    int n; vector<ll> mx_, se, sm, lm, lo_; vector<int> cnt;
    Beats(const vector<ll>& a) : n(a.size()), mx_(4 * n), se(4 * n), sm(4 * n), lm(4 * n, 0), lo_(4 * n, 0), cnt(4 * n) {
        build(1, 0, n, a);
    }
    void pull(int o) {
        int l = 2 * o, r = 2 * o + 1;
        sm[o] = sm[l] + sm[r];
        if (mx_[l] > mx_[r]) { mx_[o] = mx_[l]; cnt[o] = cnt[l]; se[o] = max(se[l], mx_[r]); }
        else if (mx_[l] < mx_[r]) { mx_[o] = mx_[r]; cnt[o] = cnt[r]; se[o] = max(mx_[l], se[r]); }
        else { mx_[o] = mx_[l]; cnt[o] = cnt[l] + cnt[r]; se[o] = max(se[l], se[r]); }
    }
    void build(int o, int lo, int hi, const vector<ll>& a) {
        if (hi - lo == 1) { mx_[o] = sm[o] = a[lo]; se[o] = NEG; cnt[o] = 1; return; }
        int m = (lo + hi) / 2;
        build(2 * o, lo, m, a); build(2 * o + 1, m, hi, a);
        pull(o);
    }
    // soma am nos maximos e ao nos demais do no o (len = tamanho do no)
    void ap(int o, int len, ll am, ll ao) {
        sm[o] += am * cnt[o] + ao * (len - cnt[o]);
        mx_[o] += am;
        if (se[o] != NEG) se[o] += ao;
        lm[o] += am; lo_[o] += ao;
    }
    void push(int o, int lo, int hi) {
        int m = (lo + hi) / 2;
        ll M = max(mx_[2 * o], mx_[2 * o + 1]); // max dos filhos ANTES de aplicar a tag
        for (int c = 2 * o; c <= 2 * o + 1; c++) {
            int len = (c == 2 * o) ? m - lo : hi - m;
            if (mx_[c] == M) ap(c, len, lm[o], lo_[o]); else ap(c, len, lo_[o], lo_[o]);
        }
        lm[o] = lo_[o] = 0;
    }
    void chmin(int o, int lo, int hi, int l, int r, ll x) {
        if (r <= lo || hi <= l || mx_[o] <= x) return;
        if (l <= lo && hi <= r && se[o] < x) { ap(o, hi - lo, x - mx_[o], 0); return; }
        push(o, lo, hi);
        int m = (lo + hi) / 2;
        chmin(2 * o, lo, m, l, r, x); chmin(2 * o + 1, m, hi, l, r, x);
        pull(o);
    }
    void add(int o, int lo, int hi, int l, int r, ll v) {
        if (r <= lo || hi <= l) return;
        if (l <= lo && hi <= r) { ap(o, hi - lo, v, v); return; }
        push(o, lo, hi);
        int m = (lo + hi) / 2;
        add(2 * o, lo, m, l, r, v); add(2 * o + 1, m, hi, l, r, v);
        pull(o);
    }
    ll qs(int o, int lo, int hi, int l, int r) {
        if (r <= lo || hi <= l) return 0;
        if (l <= lo && hi <= r) return sm[o];
        push(o, lo, hi);
        int m = (lo + hi) / 2;
        return qs(2 * o, lo, m, l, r) + qs(2 * o + 1, m, hi, l, r);
    }
    ll qm(int o, int lo, int hi, int l, int r) {
        if (r <= lo || hi <= l) return NEG;
        if (l <= lo && hi <= r) return mx_[o];
        push(o, lo, hi);
        int m = (lo + hi) / 2;
        return max(qm(2 * o, lo, m, l, r), qm(2 * o + 1, m, hi, l, r));
    }
    void chmin(int l, int r, ll x) { chmin(1, 0, n, l, r, x); }
    void add(int l, int r, ll v) { add(1, 0, n, l, r, v); }
    ll sum(int l, int r) { return qs(1, 0, n, l, r); }
    ll mx(int l, int r) { return qm(1, 0, n, l, r); }
};
/*LATEX_DESC_BEGIN***************************
-> **Segtree Beats**
Range chmin: a[i] = min(a[i], x) em [l,r); range add: a[i] += v; consulta soma
e maximo em [l,r). Guarda max, segundo max estrito e quantidade de maximos.

Complexidade: amortizado O(log n) por chmin sem add; O(log^2 n) com add.
Uso:
  Beats b(a);              // vector<ll>, 0-based
  b.chmin(l, r, x);        // a[i] = min(a[i], x), intervalo [l, r)
  b.add(l, r, v);
  ll s = b.sum(l, r); ll m = b.mx(l, r);

* Sobre o codigo:
  ap aplica em lote: os maximos recebem am e o resto recebe ao. push usa o max
  dos filhos antes da tag para decidir quem e "maximo". chmin so desce quando o
  segundo maximo nao permite aplicar em bloco.

* Problemas e reducoes:
  + Range chmin mantendo soma e maximo (cortar valores acima de x).
  + Range add + range chmin + soma/max combinados.
  + chmax: negue os valores, aplique chmin e negue de volta.
  + "Nivelar" alturas por chmin (water filling / cortar picos).

Cuidados: tags separadas para maximos (lm) e demais (lo). Para chmin e chmax
  juntos precisa guardar tambem min e segundo min (nao incluido).
Catalogo: Estruturas de dados (Segtree beats).
Digitacao: 70 linhas | dificil. Atalho: ok.
*****************************LATEX_DESC_END*/
