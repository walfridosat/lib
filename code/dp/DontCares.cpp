// DontCares - quebra [l,r] em blocos de prefixo fixo
typedef long long ll;

struct Pattern {
    ll lo;    // menor numero do bloco (os w bits baixos sao 0)
    ll hi;    // maior numero do bloco (os w bits baixos sao 1)
    ll size;  // quantidade de numeros no bloco, 2^w
    int w;    // quantidade de don't cares

    // coluna i: 0/1 fixo, -1 don't care
    int bit(int i) const { return i < w ? -1 : int(lo >> i & 1); }
    // prefixo fixo, sem os k bits baixos (k >= w)
    ll prefix(int k) const { return lo >> k; }
};

// quebra [l,r] em O(log) padroes disjuntos
vector<Pattern> decompose(ll l, ll r) {
    vector<Pattern> res;
    while (l <= r) {
        int w = 0;
        // cresce enquanto alinhado em l e cabe ate r
        while ((l & ((2LL << w) - 1)) == 0 && l + (2LL << w) - 1 <= r) w++;
        ll size = 1LL << w;
        res.push_back({l, l + size - 1, size, w});
        l += size;
    }
    return res;
}
/*LATEX_DESC_BEGIN***************************
-> **DontCares - blocos com bits don't care**
Quebra um intervalo [l, r] inclusivo, 0-based, em O(log) blocos disjuntos, cada um
com prefixo fixo e w bits baixos variaveis (don't cares).

Complexidade: O(log(r-l)) blocos; decompose roda em O(log) por intervalo.
Uso:
  vector<Pattern> v = decompose(l, r);
  v[i].bit(k)     -> bit k do bloco: 0/1 fixo, -1 se don't care
  v[i].prefix(k)  -> prefixo fixo sem os k bits baixos (k >= w)
  v[i].lo, v[i].hi, v[i].size, v[i].w

* Sobre o codigo:
  Um bloco e [lo, hi] com lo multiplo de size = 2^w, ou seja, os w bits baixos
  sao livres. decompose cresce o bloco enquanto ele continua alinhado em l e cabe
  em r; cada passo e O(1) e o total e O(log). Os blocos saem em ordem crescente.

* Problemas e reducoes:
  + Somar uma funcao sobre [l, r] testando bits: quebre em blocos e some.
  + Contar numeros em [l, r] com um padrao de bits fixos.
  + Digit DP em intervalos: [l, r] = decompose(r) - decompose(l-1).

Cuidados: use 2LL no alinhamento para nao estourar int; ll sem sinal no shift.
Catalogo: DP > digit DP / padroes de bits.
Digitacao: 20 linhas | media.
*****************************LATEX_DESC_END*/
