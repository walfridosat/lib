// Segtree generica - point update, range query (so escreva o Node)
template<class Node> struct Seg {
    int n; vector<Node> t;
    Seg(int n) : n(n), t(4 * n) {}
    template<class T> Seg(const vector<T>& v) : Seg(v.size()) { build(v, 1, 0, n - 1); }
    template<class T> void build(const vector<T>& v, int p, int l, int r) {
        if (l == r) { t[p] = Node(v[l]); return; }
        int m = (l + r) / 2;
        build(v, 2 * p, l, m), build(v, 2 * p + 1, m + 1, r);
        t[p] = t[2 * p] + t[2 * p + 1];
    }
    template<class V> void upd(int i, V v, int p = 1, int l = 0, int r = -1) {
        if (r < 0) r = n - 1;
        if (l == r) { t[p].apply(v); return; }
        int m = (l + r) / 2;
        if (i <= m) upd(i, v, 2 * p, l, m); else upd(i, v, 2 * p + 1, m + 1, r);
        t[p] = t[2 * p] + t[2 * p + 1];
    }
    Node qry(int a, int b, int p = 1, int l = 0, int r = -1) {
        if (r < 0) r = n - 1;
        if (b < l || r < a) return Node();
        if (a <= l && r <= b) return t[p];
        int m = (l + r) / 2;
        return qry(a, b, 2 * p, l, m) + qry(a, b, 2 * p + 1, m + 1, r);
    }
    // cole aqui os snippets de baixo, se precisar
};

// ---------- Nodes prontos (escolha um e escreva ANTES da Seg) ----------
/*
struct Node {                       // soma, update = atribuir
    ll s = 0;                       // Node() = identidade do merge
    Node(ll v = 0) : s(v) {}
    void apply(ll v) { s = v; }     // point add: s += v
};
Node operator+(Node a, Node b) { return Node(a.s + b.s); }

struct Node {                       // minimo + quantas vezes aparece
    ll mn = LLONG_MAX; int c = 0;
    Node() {}
    Node(ll v) : mn(v), c(1) {}
    void apply(ll v) { mn = v, c = 1; }
};
Node operator+(Node a, Node b) {
    if (a.mn != b.mn) return a.mn < b.mn ? a : b;
    a.c += b.c; return a;
}

struct Node {                       // subarray de soma maxima (Kadane na seg)
    ll s = 0, pre = 0, suf = 0, best = 0; bool e = true;  // e = vazio
    Node() {}
    Node(ll v) : s(v), pre(v), suf(v), best(v), e(false) {}
    void apply(ll v) { *this = Node(v); }
};
Node operator+(Node a, Node b) {
    if (a.e || b.e) return a.e ? b : a;
    Node r; r.e = false; r.s = a.s + b.s;
    r.pre = max(a.pre, a.s + b.pre); r.suf = max(b.suf, b.s + a.suf);
    r.best = max({a.best, b.best, a.suf + b.pre}); return r;
}
*/

// ---------- Snippets (cole DENTRO da struct) ----------
/* BEGIN first
    // walk down: menor r >= a com f(a..r) verdadeiro (f monotona em r); -1 se nao ha
    // uso: Node acc; s.first(a, [&](const Node& x) { return x.s >= k; }, acc);
    template<class F> int first(int a, F f, Node& acc, int p = 1, int l = 0, int r = -1) {
        if (r < 0) r = n - 1;
        if (r < a) return -1;
        if (a <= l && !f(acc + t[p])) { acc = acc + t[p]; return -1; }
        if (l == r) return l;
        int m = (l + r) / 2;
        int x = first(a, f, acc, 2 * p, l, m);
        return x != -1 ? x : first(a, f, acc, 2 * p + 1, m + 1, r);
    }
END first */
/* BEGIN kth
    // k-esima posicao (1-based) com valor 1, numa seg de soma de 0/1; supoe k <= total
    int kth(ll k, int p = 1, int l = 0, int r = -1) {
        if (r < 0) r = n - 1;
        if (l == r) return l;
        int m = (l + r) / 2;
        if (t[2 * p].s >= k) return kth(k, 2 * p, l, m);
        return kth(k - t[2 * p].s, 2 * p + 1, m + 1, r);
    }
END kth */
/*LATEX_DESC_BEGIN***************************
-> **Segtree generica (point update / range query)**
Voce so escreve o Node; a estrutura e sempre a mesma. 0-indexed, intervalos fechados [a, b].

Complexidade: build O(n) | upd O(log n) | qry O(log n)
Uso:
  Seg<Node> s(n);  ou  Seg<Node> s(vetor);   // Node(v) constroi a folha
  s.upd(i, v);          // chama t[folha].apply(v)
  Node x = s.qry(a, b);

* Sobre o codigo:
  Node precisa de: Node() = identidade do merge; Node(v) = folha; apply(v) = update na folha;
  e a funcao livre operator+(Node, Node) = merge (pode ser nao comutativo: esquerda + direita).
  Os parametros (p, l, r) tem default, entao nao ha funcoes publicas "wrapper" para digitar.

* Problemas e reducoes:
  + Soma/min/max/gcd em intervalo com updates pontuais: Node com o agregado.
  + Min + contagem do min, max + indice: Node com dois campos.
  + Subarray de soma maxima em intervalo: Node Kadane (s, pre, suf, best).
  + Primeira posicao >= a com prefixo >= k / primeiro elemento > x: snippet first (walk down).
  + k-esimo elemento presente (ordered set com valores pequenos): seg de 0/1 + snippet kth.
  + Hash de string com updates: Node (hash, tamanho), merge = h1 * B^len2 + h2.
  + Composicao de funcoes / matrizes 2x2 em intervalo: Node = funcao, merge nao comutativo.

Cuidados: merge nao comutativo: a ordem do + e esquerda, direita. Node() TEM de ser identidade.
  Se so uma Seg no codigo, pode trocar template<class Node> pelo tipo direto.
Catalogo: Estruturas de dados e queries.
Digitacao: 27 linhas | facil. Para soma/min puros, code/ds/seg_iter.cpp e ainda menor.
*****************************LATEX_DESC_END*/
