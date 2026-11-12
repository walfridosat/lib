// Segtree dinamica (esparsa) lazy - indices em [lo, hi] ate 1e9 / 1e18, nos criados sob demanda
template<class Node, class Tag> struct DSeg {
    ll lo, hi; vector<Node> t; vector<Tag> z; vector<array<int, 2>> c;
    DSeg(ll lo, ll hi) : lo(lo), hi(hi) { nw(), nw(); }  // 0 = nulo, 1 = raiz
    int nw() { t.emplace_back(), z.emplace_back(), c.push_back({0, 0}); return t.size() - 1; }
    void ap(int p, ll l, ll r, const Tag& g) { t[p].apply(g, l, r); z[p] += g; }
    void push(int p, ll l, ll r) {
        ll m = l + (r - l) / 2;
        for (int k : {0, 1}) if (!c[p][k]) { int x = nw(); c[p][k] = x; } // nw() realoca c
        ap(c[p][0], l, m, z[p]), ap(c[p][1], m + 1, r, z[p]), z[p] = Tag();
    }
    void upd(ll a, ll b, const Tag& g) { upd(a, b, g, 1, lo, hi); }
    void upd(ll a, ll b, const Tag& g, int p, ll l, ll r) {
        if (b < l || r < a) return;
        if (a <= l && r <= b) { ap(p, l, r, g); return; }
        push(p, l, r);
        ll m = l + (r - l) / 2;
        upd(a, b, g, c[p][0], l, m), upd(a, b, g, c[p][1], m + 1, r);
        t[p] = t[c[p][0]] + t[c[p][1]];
    }
    Node qry(ll a, ll b) { return qry(a, b, 1, lo, hi); }
    Node qry(ll a, ll b, int p, ll l, ll r) {
        if (b < l || r < a) return Node();
        if (a <= l && r <= b) return t[p];
        push(p, l, r);
        ll m = l + (r - l) / 2;
        return qry(a, b, c[p][0], l, m) + qry(a, b, c[p][1], m + 1, r);
    }
};
// Node e Tag: os mesmos de code/segtree/seg_lazy.cpp. Ponto: upd(i, i, Tag).
// IMPORTANTE: no recem-criado vale Node(); ele precisa representar o valor INICIAL do trecho
// (ex.: soma de zeros = 0). Se o inicial for outro (ex.: min de zeros), crie em nw() com Node(0)
// e trate a identidade do merge so em qry (retorne um Node "vazio" separado).

/* BEGIN first
    // walk down global: menor indice i com f(prefixo lo..i) verdadeiro (f monotona); hi+1 se nao ha
    // uso: Node acc; ll i = s.first([&](const Node& x) { return x.s >= k; }, acc, 1, s.lo, s.hi);
    template<class F> ll first(F f, Node& acc, int p, ll l, ll r) {
        if (!f(acc + t[p])) { acc = acc + t[p]; return r + 1; }
        if (l == r) return l;
        push(p, l, r);
        ll m = l + (r - l) / 2;
        ll x = first(f, acc, c[p][0], l, m);
        return x <= m ? x : first(f, acc, c[p][1], m + 1, r);
    }
END first */
/*LATEX_DESC_BEGIN***************************
-> **Segtree dinamica (esparsa) com lazy**
Mesma interface da LSeg, mas os indices vao de lo a hi (ate ~1e18) e os nos so existem onde
houve update/query. Bom quando nao da (ou e chato) comprimir coordenadas, ou e online.

Complexidade: O(log(hi - lo)) por operacao | memoria ~ 4 * Q * log(hi - lo) nos
Uso:
  DSeg<Node, Tag> s(0, 1e9);
  s.upd(a, b, Tag{...});  Node x = s.qry(a, b);

* Sobre o codigo:
  c[p] = filhos (0 = nulo). push cria os dois filhos se faltarem, entao todo no visitado
  tem filhos validos. m = l + (r - l) / 2 funciona com indices negativos e ate 1e18.
  "int x = nw(); c[p][k] = x;" em duas linhas de proposito: nw() faz push_back em c e a
  referencia c[p] poderia ficar invalida se fosse c[p][k] = nw().

* Problemas e reducoes:
  + Range add / range sum com coordenadas ate 1e9 e queries online (sem comprimir).
  + Contar pontos/valores em [x, y] com insercoes online: Tag add em ponto, Node soma.
  + Pintar intervalos enormes e contar o que esta pintado: Tag assign, Node (qtd pintada).
  + Primeira posicao livre >= x num dominio grande: Node com "qtd ocupada" + snippet first.
  + Quando der para ler tudo antes: prefira comprimir + LSeg (mais rapido, menos memoria).

Cuidados: memoria. Faca t.reserve / z.reserve / c.reserve(4 * Q * 31) para evitar realocacoes.
  Sem lazy (so point update), a mesma estrutura serve: Tag com += do valor e apply no ponto.
Catalogo: Estruturas de dados e queries.
Digitacao: 30 linhas | media.
*****************************LATEX_DESC_END*/
