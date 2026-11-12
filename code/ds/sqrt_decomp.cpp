// Sqrt decomposition (exemplo: add em intervalo + contar >= x em intervalo)
//
// O que faz: blocos de tamanho B; cada bloco guarda copia ordenada e um lazy
//   de soma. Update: bloco inteiro mexe so no lazy; bloco parcial reconstroi.
// Quando usar: Catalogo > Estruturas de dados (Sqrt decomposition quando a
//   operacao nao e associativa/estranha; bloco com array ordenado para
//   "contar >= x"; reconstrucao periodica). Use como TEMPLATE: troque o
//   que cada bloco guarda (bitset, tabela de contagem, funcao de pulo).
// Complexidade: update O(B log B + n/B); query O(B + (n/B) log B).
//   B ~ sqrt(n log n) na pratica; teste por experimento.
// Uso: Sqrt s(a); s.add(l, r, v) [l,r) 0-based; s.count_ge(l, r, x).
// Cuidados: sempre rebuild(b) apos mexer em elementos soltos do bloco b.
//   Para "Holes" (pular ate sair do bloco): guarde nxt[i], cnt[i] por bloco
//   e recompute o bloco no update (ideia igual, nao incluida).
struct Sqrt {
    int n, B, nb; vector<ll> a, lz; vector<vector<ll>> srt;
    Sqrt(const vector<ll>& v) : n(v.size()), a(v) {
        B = max(1, (int)sqrt((double)n * 8)); nb = (n + B - 1) / B;
        lz.assign(nb, 0); srt.resize(nb);
        for (int b = 0; b < nb; b++) rebuild(b);
    }
    void rebuild(int b) {
        int l = b * B, r = min(n, l + B);
        srt[b].assign(a.begin() + l, a.begin() + r);
        sort(srt[b].begin(), srt[b].end());
    }
    void add(int l, int r, ll v) { // [l, r)
        if (l >= r) return;
        int bl = l / B, br = (r - 1) / B;
        if (bl == br) { for (int i = l; i < r; i++) a[i] += v; rebuild(bl); return; }
        for (int i = l; i < (bl + 1) * B; i++) a[i] += v;
        rebuild(bl);
        for (int b = bl + 1; b < br; b++) lz[b] += v;
        for (int i = br * B; i < r; i++) a[i] += v;
        rebuild(br);
    }
    int count_ge(int l, int r, ll x) {
        if (l >= r) return 0;
        int bl = l / B, br = (r - 1) / B, res = 0;
        if (bl == br) { for (int i = l; i < r; i++) res += a[i] + lz[bl] >= x; return res; }
        for (int i = l; i < (bl + 1) * B; i++) res += a[i] + lz[bl] >= x;
        for (int b = bl + 1; b < br; b++) // valores do bloco + lz >= x  <=>  valor >= x - lz
            res += srt[b].end() - lower_bound(srt[b].begin(), srt[b].end(), x - lz[b]);
        for (int i = br * B; i < r; i++) res += a[i] + lz[br] >= x;
        return res;
    }
};
