// Nos prontos para segtree - max subarray, parenteses, afim
const ll NINF = LLONG_MIN / 4;
struct MS { // max subarray nao vazio
    ll sum = 0, pre = NINF, suf = NINF, best = NINF; // neutro: best = -inf
    static MS leaf(ll x) { MS r; r.sum = r.pre = r.suf = r.best = x; return r; }
};
MS merge(const MS& a, const MS& b) {
    if (a.best == NINF) return b; // a e neutro
    if (b.best == NINF) return a;
    MS r;
    r.sum = a.sum + b.sum;
    r.pre = max(a.pre, a.sum + b.pre);
    r.suf = max(b.suf, b.sum + a.suf);
    r.best = max({a.best, b.best, a.suf + b.pre});
    return r;
}
struct BR { // parenteses: soma total e minimo prefixo (prefixo vazio conta 0)
    ll sum = 0, mn = 0;
    static BR leaf(char c) { BR r; r.sum = (c == '(' ? 1 : -1); r.mn = min(0LL, r.sum); return r; }
};
BR mergeBR(const BR& a, const BR& b) { BR r; r.sum = a.sum + b.sum; r.mn = min(a.mn, a.sum + b.mn); return r; }
const ll AMOD = 1e9 + 7;
struct Aff { // x -> a*x + b (mod AMOD); neutro = identidade
    ll a = 1, b = 0;
};
Aff compose(const Aff& f, const Aff& g) { // primeiro f, depois g
    return {g.a * f.a % AMOD, (g.a * f.b + g.b) % AMOD};
}
ll ap(const Aff& f, ll x) { return (f.a * x + f.b) % AMOD; }
/*LATEX_DESC_BEGIN***************************
-> **Nos Prontos para Segtree**
Structs de no + funcao de merge para usar com Seg (seg_iter.cpp) ou qualquer
segtree que combina filho esquerdo e direito.

Complexidade: O(1) por merge.
Uso:
  Seg s(n, MS(), [](MS a, MS b){ return merge(a, b); });
  s.set(i, MS::leaf(x)); s.query(l, r).best;  // maior subarray nao vazio
  // Parenteses:
  Seg t(n, BR(), mergeBR);  // leaf: BR::leaf('(' ou ')')
  // balanceado <=> q.sum == 0 && q.mn >= 0
  // Afim x -> a*x+b:
  // query devolve a composicao; aplique com ap(f, x).

* Sobre o codigo:
  MS guarda soma, melhor prefixo, sufixo e subarray; merge junta os dois
  filhos. BR guarda soma e menor prefixo. Aff guarda a, b e compose.

* Problemas e reducoes:
  + Maior soma de subarray (nao vazio) com update de ponto.
  + Parenteses balanceados em range: soma == 0 e menor prefixo >= 0.
  + Composicao de funcoes afins em range e aplicacao em x.
  + Modelar outras informacoes de no que se juntam de forma associativa.

Cuidados: o neutro deve ser o construtor padrao (MS(), BR(), Aff()). MS usa
  NINF para "vazio"; seguro para somas ate ~1e18.
Catalogo: Estruturas de dados.
Digitacao: 28 linhas | facil. Atalho: ok.
*****************************LATEX_DESC_END*/
