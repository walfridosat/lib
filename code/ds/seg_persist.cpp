// Segtree persistente - k-esimo e contagem em [l,r]
struct PST {
    int n, m; vector<ll> vs; vector<int> L, R, C, root;
    int newnode(int l, int r, int c) { L.push_back(l); R.push_back(r); C.push_back(c); return L.size() - 1; }
    int ins(int o, int lo, int hi, int p) { // cria copia do no o com +1 em p
        int u = newnode(L[o], R[o], C[o] + 1);
        if (hi - lo > 1) {
            int mid = (lo + hi) / 2;
            if (p < mid) { int c = ins(L[o], lo, mid, p); L[u] = c; }
            else { int c = ins(R[o], mid, hi, p); R[u] = c; }
        }
        return u;
    }
    PST(const vector<ll>& a) : n(a.size()) {
        vs = a; sort(vs.begin(), vs.end()); vs.erase(unique(vs.begin(), vs.end()), vs.end());
        m = vs.size();
        newnode(0, 0, 0); // no 0 = vazio (filhos apontam para si)
        root.push_back(0); // root[0] = versao vazia; root[i+1] = apos inserir a[i]
        for (int i = 0; i < n; i++) {
            int p = lower_bound(vs.begin(), vs.end(), a[i]) - vs.begin();
            root.push_back(ins(root.back(), 0, m, p));
        }
    }
    ll kth(int l, int r, int k) {
        int u = root[r + 1], v = root[l], lo = 0, hi = m;
        while (hi - lo > 1) {
            int mid = (lo + hi) / 2, c = C[L[u]] - C[L[v]];
            if (k <= c) { u = L[u]; v = L[v]; hi = mid; }
            else { k -= c; u = R[u]; v = R[v]; lo = mid; }
        }
        return vs[lo];
    }
    int cnt_le(int l, int r, ll x) {
        int p = upper_bound(vs.begin(), vs.end(), x) - vs.begin(); // #valores comprimidos <= x
        if (p == 0) return 0;
        // conta posicoes < p
        int u = root[r + 1], v = root[l], lo = 0, hi = m, res = 0;
        while (hi - lo > 1) {
            int mid = (lo + hi) / 2;
            if (p >= mid) { res += C[L[u]] - C[L[v]]; u = R[u]; v = R[v]; lo = mid; }
            else { u = L[u]; v = L[v]; hi = mid; }
        }
        // folha lo: vale se lo < p
        if (lo < p) res += C[u] - C[v];
        return res;
    }
};
/*LATEX_DESC_BEGIN***************************
-> **Segtree Persistente**
Versao i = prefixo a[0..i] inserido numa segtree sobre os valores comprimidos.
Query em [l,r] = versao r - versao l-1 (o no e aditivo). 0-based.

Complexidade: build O(n log n) tempo e memoria; query O(log n).
Uso:
  PST p(a);                       // vector<ll>, 0-based
  ll x = p.kth(l, r, k);          // k-esimo menor (k = 1 e o menor)
  int c = p.cnt_le(l, r, x);      // #{i in [l,r] : a[i] <= x}

* Sobre o codigo:
  ins copia o caminho do no (path copy) somando 1 em p; root[i+1] e a versao
  apos inserir a[i]. A query compara duas raizes e desce pelas contagens de
  zeros para achar o k-esimo.

* Problemas e reducoes:
  + k-esimo menor em [l, r] inclusivo.
  + Contar a_i <= x em [l, r].
  + Mediana e quantis de subarray.
  + Versoes por prefixo para consultas em intervalos.

Cuidados: para update de ponto generico use o mesmo path copy. Para lazy
  persistente use tag permanente sem push-down (some tags dos ancestrais).
  Intervalo de kth/cnt_le e inclusivo [l, r].
Catalogo: Estruturas de dados (Segtree persistente).
Digitacao: 46 linhas | media. Atalho: ok.
*****************************LATEX_DESC_END*/
