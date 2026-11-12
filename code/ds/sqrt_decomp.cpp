// Sqrt decomposition - add em range e contar >= x
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
/*LATEX_DESC_BEGIN***************************
-> **Sqrt Decomposition**
Blocos de tamanho B; cada bloco guarda copia ordenada e lazy de soma. Update
de range: bloco inteiro mexe so no lazy; bloco parcial reconstroi. 0-based.

Complexidade: update O(B log B + n/B); query O(B + (n/B) log B).
  B ~ sqrt(n log n) na pratica; teste por experimento.
Uso:
  Sqrt s(a);
  s.add(l, r, v);            // [l, r)
  int c = s.count_ge(l, r, x);

* Sobre o codigo:
  a guarda os valores crus, lz a soma pendente por bloco e srt a copia
  ordenada. rebuild(b) reordena o bloco. count_ge usa lower_bound em x - lz[b]
  nos blocos inteiros e testa a[i] + lz nos pedacos das pontas.

* Problemas e reducoes:
  + Range add + contar valores >= x em range.
  + Operacoes nao associativas ou estranhas: trate por bloco.
  + Manter informacao ordenada por bloco (bitset, contagem, pulo).
  + Reconstrucao periodica de estruturas.

Cuidados: sempre rebuild(b) apos mexer em elementos soltos do bloco b.
  Para "Holes" guarde nxt[i], cnt[i] por bloco e reconstrua no update.
Catalogo: Estruturas de dados (Sqrt decomposition).
Digitacao: 33 linhas | media. Atalho: ok.
*****************************LATEX_DESC_END*/
