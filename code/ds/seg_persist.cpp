// Segtree persistente (contagem) - k-esimo em [l,r] e contagem <= x
//
// O que faz: versao i = prefixo a[0..i] inserido numa segtree sobre os valores
//   comprimidos. Query em [l,r] = versao r - versao l-1 (no aditivo).
// Quando usar: Catalogo > Estruturas de dados (Segtree persistente = versoes
//   por prefixo; k-esimo menor em [l,r]; contar a_i <= x em [l,r] online;
//   Combinacoes: "k-esimo menor em [l, r]").
// Complexidade: build O(n log n) tempo e memoria; query O(log n).
// Uso: PST p(a) (vector<ll>, 0-based); p.kth(l,r,k) -> k-esimo menor (k=1 e o
//   menor) em a[l..r] inclusivo; p.cnt_le(l,r,x) -> #{i in [l,r] : a[i] <= x}.
// Cuidados: para persistencia com update de ponto generico use o mesmo
//   esquema (path copy: novo no por nivel). Para lazy persistente use tag
//   permanente sem push-down (query soma tags dos ancestrais).
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
