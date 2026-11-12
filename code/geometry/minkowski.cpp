// Soma de Minkowski de poligonos convexos

struct P {
  ll x, y;
  P(ll x = 0, ll y = 0) : x(x), y(y) {}
  P operator+(P o) const { return P(x + o.x, y + o.y); }
  P operator-(P o) const { return P(x - o.x, y - o.y); }
  bool operator<(P o) const { return y != o.y ? y < o.y : x < o.x; }  // menor y, depois x
};
ll cross(P a, P b) { return a.x * b.y - a.y * b.x; }

void reorder(vector<P> &g) {  // comeca pelo vertice mais baixo
  rotate(g.begin(), min_element(g.begin(), g.end()), g.end());
}

vector<P> minkowski(vector<P> A, vector<P> B) {
  reorder(A), reorder(B);
  int n = A.size(), m = B.size();
  A.push_back(A[0]), A.push_back(A[1]);  // sentinelas ciclicas
  B.push_back(B[0]), B.push_back(B[1]);
  vector<P> r;
  int i = 0, j = 0;
  while (i < n || j < m) {
    r.push_back(A[i] + B[j]);
    ll c = cross(A[i + 1] - A[i], B[j + 1] - B[j]);  // compara angulo das arestas
    if (c >= 0 && i < n) i++;
    if (c <= 0 && j < m) j++;
  }
  return r;
}

vector<P> negPoly(vector<P> g) {  // -g (rotacao de 180 graus: continua CCW)
  for (auto &p : g) p = P(-p.x, -p.y);
  return g;
}

// origem dentro/borda do convexo CCW? O(n)
bool originIn(const vector<P> &c) {
  int n = c.size();
  for (int i = 0; i < n; i++)
    if (cross(c[(i + 1) % n] - c[i], P(0, 0) - c[i]) < 0) return false;
  return true;
}
// A e B (convexos CCW) se intersectam (inclui toque)?
bool convexInter(const vector<P> &A, const vector<P> &B) {
  vector<P> c = minkowski(A, negPoly(B));
  if (c.size() < 3) {  // degenerado (pontos/segmentos): nao tratado aqui
    return false;
  }
  return originIn(c);
}

/*LATEX_DESC_BEGIN***************************
-> **Soma de Minkowski de poligonos convexos**
A + B = {a + b}, devolvido como poligono convexo CCW. Tambem testa se dois convexos se
intersectam (origem dentro de A + (-B)).

Complexidade: O(n + m)
Uso:
  vector<P> c = minkowski(A, B);   // A e B em ordem CCW, qualquer ponto inicial
  vector<P> nb = negPoly(B);       // -B (continua CCW)
  bool inter = convexInter(A, B);  // inclui toque

* Sobre o codigo:
  reorder poe o vertice mais baixo primeiro e duplica dois sentinelas. Os dois ponteiros i,j
  percorrem as arestas; cross das arestas decide qual avanca (empate avanca os dois), o que
  mantem a ordem angular. originIn testa se a origem esta a esquerda de todas as arestas.

* Problemas e reducoes:
  + Soma de Minkowski de dois convexos.
  + Colisao de dois convexos por translacao: A + (-B) contem a origem.
  + Intersecao de dois poligonos convexos: convexInter.
  + Zonotopo / soma de segmentos e translacoes.
  + Diferenca de Minkowski: minkowski(A, negPoly(B)).

Cuidados: entrada deve estar em CCW. Pode gerar vertices colineares; a funcao nao remove.
  Poligonos com >= 1 vertice; convexInter com resultado degenerado (< 3 vertices) devolve
  false sem tratar o caso.
Catalogo: Geometria.
Digitacao: 45 linhas | media. Atalho: negPoly, originIn e convexInter sao parte opcional;
  separar em arquivo proprio deixa o minkowski puro bem menor.
*****************************LATEX_DESC_END*/
