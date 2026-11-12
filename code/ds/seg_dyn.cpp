// Segtree dinamica - soma, k-esimo e merge
struct SegDyn {
    ll U; vector<int> L, R; vector<ll> C;
    SegDyn(ll U) : U(U) { L.push_back(0); R.push_back(0); C.push_back(0); } // no 0 = nulo
    int nn() { L.push_back(0); R.push_back(0); C.push_back(0); return L.size() - 1; }
    int add(int o, ll p, ll v) { return add(o, 0, U, p, v); }
    int add(int o, ll lo, ll hi, ll p, ll v) {
        if (!o) o = nn();
        C[o] += v;
        if (hi - lo > 1) {
            ll m = lo + (hi - lo) / 2;
            if (p < m) { int c = add(L[o], lo, m, p, v); L[o] = c; }
            else { int c = add(R[o], m, hi, p, v); R[o] = c; }
        }
        return o;
    }
    ll sum(int o, ll l, ll r) { return sum(o, 0, U, l, r); }
    ll sum(int o, ll lo, ll hi, ll l, ll r) {
        if (!o || r <= lo || hi <= l) return 0;
        if (l <= lo && hi <= r) return C[o];
        ll m = lo + (hi - lo) / 2;
        return sum(L[o], lo, m, l, r) + sum(R[o], m, hi, l, r);
    }
    ll kth(int o, ll k) { // exige 1 <= k <= C[o]
        ll lo = 0, hi = U;
        while (hi - lo > 1) {
            ll m = lo + (hi - lo) / 2;
            if (C[L[o]] >= k) { o = L[o]; hi = m; }
            else { k -= C[L[o]]; o = R[o]; lo = m; }
        }
        return lo;
    }
    int merge(int a, int b) { return merge(a, b, 0, U); }
    int merge(int a, int b, ll lo, ll hi) {
        if (!a || !b) return a ^ b;
        C[a] += C[b]; // folha: soma; senao reconstroi dos filhos abaixo
        if (hi - lo > 1) {
            ll m = lo + (hi - lo) / 2;
            int x = merge(L[a], L[b], lo, m); L[a] = x;
            int y = merge(R[a], R[b], m, hi); R[a] = y;
        }
        return a;
    }
};
/*LATEX_DESC_BEGIN***************************
-> **Segtree Dinamica**
Segtree sobre [0, U) enorme (ate 1e18) com nos criados sob demanda. Update de
ponto (soma), soma de intervalo, k-esimo e merge destrutivo. 0-based.

Complexidade: O(log U) por op; memoria O(q log U); merge amortizado O(nos).
Uso:
  SegDyn s(U); int root = 0;
  root = s.add(root, pos, v);   // precisa reatribuir se estava vazia
  ll sum = s.sum(root, l, r);   // [l, r)
  int p = s.kth(root, k);       // menor pos com soma[0..pos] >= k
  root = s.merge(ra, rb);       // ra e rb nao valem depois

* Sobre o codigo:
  Pool L/R/C com no 0 nulo; add cria o caminho ate a folha e soma v. sum
  decompoe o intervalo. kth desce comparando C[L[o]] com k. merge soma as
  contagens e liga os filhos, reaproveitando a arvore a.

* Problemas e reducoes:
  + Multiconjunto sobre valores ate 1e9/1e18 sem comprimir.
  + Merge de segtrees para small-to-large e DP em subarvore.
  + K-esimo e soma de intervalo online.
  + Contar valores em [l,r] em arvores que se unem.

Cuidados: reserve s.L/s.R/s.C se q for grande. kth exige valores >= 0.
Catalogo: Estruturas de dados (Segtree dinamica/esparsa, merge).
Digitacao: 43 linhas | media. Atalho: ok.
*****************************LATEX_DESC_END*/
