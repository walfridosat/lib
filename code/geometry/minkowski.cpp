// Soma de Minkowski de poligonos convexos
//
// O que faz: A + B = {a+b}. Retorna o poligono convexo (CCW). Tambem testa interseção de dois
//   convexos (origem em A + (-B)).
// Quando usar: Catalogo > Geometria (Minkowski, colisao por translacao, zonotopo, distancia
//   entre convexos).
// Complexidade: O(n + m).
// Uso: vector<P> c = minkowski(A, B);  A, B em ordem CCW (qualquer ponto inicial).
//   Para A - B: negue as coordenadas de B (continua CCW apos reverter? ver negPoly).
//   Colisao: convexosInter(A,B) usa inConvex-like generico O(n+m) por area (veja abaixo).
// Cuidados: pode gerar vertices colineares; nao remove. Poligonos com >=1 vertice.

struct P {
  ll x, y;
  P(ll x = 0, ll y = 0) : x(x), y(y) {}
  P operator+(P o) const { return P(x + o.x, y + o.y); }
  P operator-(P o) const { return P(x - o.x, y - o.y); }
  bool operator<(P o) const { return y != o.y ? y < o.y : x < o.x; }  // menor y, depois x
};
ll cross(P a, P b) { return a.x * b.y - a.y * b.x; }

void reorder(vector<P> &g) {  // comeca pelo vertice mais baixo (e mais a esquerda)
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

// origem dentro (ou na borda) do convexo CCW c (pode ter colineares)? O(n)
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
