typedef long long ll;

// Padrao = prefixo fixo + sufixo de w don't cares.
// Representa o bloco [lo, hi], com lo multiplo de size = 2^w.
struct Pattern {
    ll lo;    // menor numero do bloco (os w bits baixos sao 0)
    ll hi;    // maior numero do bloco (os w bits baixos sao 1)
    ll size;  // quantidade de numeros no bloco, 2^w
    int w;    // quantidade de don't cares

    // bit da coluna i: 0 ou 1 se for fixo, -1 se for don't care
    int bit(int i) const { return i < w ? -1 : int(lo >> i & 1); }
    // prefixo fixo, descartando os k bits mais baixos (use k >= w)
    ll prefix(int k) const { return lo >> k; }
};

// Quebra [l, r] (inclusivo) em O(log) padroes disjuntos, em ordem crescente.
vector<Pattern> decompose(ll l, ll r) {
    vector<Pattern> res;
    while (l <= r) {
        int w = 0;
        // cresce o bloco enquanto continuar alinhado em l e cabendo ate r
        while ((l & ((2LL << w) - 1)) == 0 && l + (2LL << w) - 1 <= r) w++;
        ll size = 1LL << w;
        res.push_back({l, l + size - 1, size, w});
        l += size;
    }
    return res;
}
