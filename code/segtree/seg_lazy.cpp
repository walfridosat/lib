// Segtree lazy generica - range update, range query (so escreva Node e Tag)
template<class Node, class Tag> struct LSeg {
    int n; vector<Node> t; vector<Tag> z;
    LSeg(int n) : n(n), t(4 * n), z(4 * n) {}
    template<class T> LSeg(const vector<T>& v) : LSeg(v.size()) { build(v, 1, 0, n - 1); }
    template<class T> void build(const vector<T>& v, int p, int l, int r) {
        if (l == r) { t[p] = Node(v[l]); return; }
        int m = (l + r) / 2;
        build(v, 2 * p, l, m), build(v, 2 * p + 1, m + 1, r);
        t[p] = t[2 * p] + t[2 * p + 1];
    }
    void ap(int p, int l, int r, const Tag& g) { t[p].apply(g, l, r); z[p] += g; }
    void push(int p, int l, int r) {
        int m = (l + r) / 2;
        ap(2 * p, l, m, z[p]), ap(2 * p + 1, m + 1, r, z[p]), z[p] = Tag();
    }
    void upd(int a, int b, const Tag& g, int p = 1, int l = 0, int r = -1) {
        if (r < 0) r = n - 1;
        if (b < l || r < a) return;
        if (a <= l && r <= b) { ap(p, l, r, g); return; }
        push(p, l, r);
        int m = (l + r) / 2;
        upd(a, b, g, 2 * p, l, m), upd(a, b, g, 2 * p + 1, m + 1, r);
        t[p] = t[2 * p] + t[2 * p + 1];
    }
    Node qry(int a, int b, int p = 1, int l = 0, int r = -1) {
        if (r < 0) r = n - 1;
        if (b < l || r < a) return Node();
        if (a <= l && r <= b) return t[p];
        push(p, l, r);
        int m = (l + r) / 2;
        return qry(a, b, 2 * p, l, m) + qry(a, b, 2 * p + 1, m + 1, r);
    }
    // cole aqui os snippets de baixo, se precisar
};

// ---------- Node + Tag prontos (escreva ANTES da LSeg) ----------
/*
struct Tag { ll a = 0; void operator+=(const Tag& g) { a += g.a; } };   // range add
struct Node {                                                          // soma
    ll s = 0;
    Node(ll v = 0) : s(v) {}
    void apply(const Tag& g, int l, int r) { s += g.a * (r - l + 1); }
};
Node operator+(Node a, Node b) { return Node(a.s + b.s); }
// max em vez de soma: apply faz mx += g.a (sem o tamanho); Node() = -INF; merge = max.

struct Tag {                         // atribuir (set) + somar (add): x -> x + a, ou x -> c + a
    bool st = false; ll c = 0, a = 0;
    void operator+=(const Tag& g) {  // g vem DEPOIS
        if (g.st) st = true, c = g.c, a = g.a; else a += g.a;
    }
};
struct Node {
    ll s = 0;
    Node(ll v = 0) : s(v) {}
    void apply(const Tag& g, int l, int r) { s = (g.st ? g.c * (r - l + 1) : s) + g.a * (r - l + 1); }
};
Node operator+(Node a, Node b) { return Node(a.s + b.s); }

const ll MOD = 998244353;            // afim mod p: x -> x * m + a
struct Tag {
    ll m = 1, a = 0;
    void operator+=(const Tag& g) { a = (a * g.m + g.a) % MOD; m = m * g.m % MOD; }
};
struct Node {
    ll s = 0;
    Node(ll v = 0) : s(v % MOD) {}
    void apply(const Tag& g, int l, int r) { s = (s * g.m + g.a * (r - l + 1)) % MOD; }
};
Node operator+(Node a, Node b) { return Node((a.s + b.s) % MOD); }
*/

// ---------- Snippets (cole DENTRO da struct) ----------
/* BEGIN first
    // walk down: menor r >= a com f(a..r) verdadeiro (f monotona em r); -1 se nao ha
    // uso: Node acc; s.first(a, [&](const Node& x) { return x.s > k; }, acc);
    template<class F> int first(int a, F f, Node& acc, int p = 1, int l = 0, int r = -1) {
        if (r < 0) r = n - 1;
        if (r < a) return -1;
        if (a <= l && !f(acc + t[p])) { acc = acc + t[p]; return -1; }
        if (l == r) return l;
        push(p, l, r);
        int m = (l + r) / 2;
        int x = first(a, f, acc, 2 * p, l, m);
        return x != -1 ? x : first(a, f, acc, 2 * p + 1, m + 1, r);
    }
END first */
/* BEGIN pos
    // valor numa posicao (atalho de qry(i, i))
    Node get(int i) { return qry(i, i); }
END pos */
/*LATEX_DESC_BEGIN***************************
-> **Segtree lazy generica (range update / range query)**
Voce so escreve Node e Tag; a estrutura nao muda. 0-indexed, intervalos fechados [a, b].

Complexidade: build O(n) | upd O(log n) | qry O(log n)
Uso:
  LSeg<Node, Tag> s(n);  ou  LSeg<Node, Tag> s(vetor);
  s.upd(a, b, Tag{...});
  Node x = s.qry(a, b);

* Sobre o codigo:
  Tag() = "nao faz nada"; t1 += t2 compoe (t2 aplicado DEPOIS de t1).
  Node: Node() = identidade; Node(v) = folha; apply(tag, l, r) aplica a tag num no que cobre
  [l, r] (o tamanho r - l + 1 entra em somas); operator+ = merge.
  ap() aplica no no e acumula a tag; push() desce a tag para os filhos antes de descer.

* Problemas e reducoes:
  + Range add + range sum / min / max: Tag add.
  + Range assign + range sum, ou assign e add misturados: Tag com flag "st".
  + x -> m*x + a mod p (multiplica e soma em intervalo): Tag afim.
  + Inverter bits em intervalo (0/1): Node (qtd de 1, tamanho), Tag flip (xor 1).
  + Pintar intervalo e contar cores / segmentos: Tag assign, Node com cor das pontas.
  + Area da uniao de retangulos: sweep + Node (min, qtd do min) com Tag add.
  + Primeiro indice >= a com prefixo/valor que passa de k: snippet first (walk down com push).

Cuidados: a ordem em operator+= importa (g vem depois). Tag() precisa ser identidade de verdade.
  Max com add: apply nao multiplica pelo tamanho. Chmin/chmax em intervalo: ver ds/seg_beats.cpp.
Catalogo: Estruturas de dados e queries.
Digitacao: 33 linhas | facil/media. E a mesma Seg + ap/push; decore a diferenca.
*****************************LATEX_DESC_END*/
