// Rotating calipers: diametro, largura minima, retangulo envolvente de menor area
//
// O que faz: sobre um fecho convexo CCW (de hull_andrew.cpp) acha o par mais distante,
//   a menor largura (distancia entre retas suporte paralelas) e a menor area de retangulo
//   envolvente (com lado colinear a uma aresta do hull).
// Quando usar: Catalogo > Geometria (pontos extremos, maior distancia, calipers, menor caixa).
// Complexidade: O(h) apos o hull.
// Uso: vector<P> h = hull(pts);  diameter2(h) -> maior dist^2 (ll);
//      width2(h) -> (largura^2) em long double; minRectArea(h) -> area em long double.
// Cuidados: h CCW sem colineares (h.size()==1 ou 2 tratados). Diametro usa inteiros (exato);
//   largura/retangulo usam long double.

struct P {
  ll x, y;
  P(ll x = 0, ll y = 0) : x(x), y(y) {}
  P operator-(P o) const { return P(x - o.x, y - o.y); }
};
ll cross(P a, P b) { return a.x * b.y - a.y * b.x; }
ll dot(P a, P b) { return a.x * b.x + a.y * b.y; }
ll norm2(P a) { return dot(a, a); }

ll diameter2(const vector<P> &h) {
  int n = h.size();
  if (n == 1) return 0;
  if (n == 2) return norm2(h[0] - h[1]);
  ll best = 0;
  for (int i = 0, j = 1; i < n; i++) {
    P e = h[(i + 1) % n] - h[i];
    // avanca j enquanto o ponto j+1 esta mais longe da aresta i
    while (cross(e, h[(j + 1) % n] - h[j]) > 0) j = (j + 1) % n;
    best = max(best, max(norm2(h[i] - h[j]), norm2(h[(i + 1) % n] - h[j])));
  }
  return best;
}

long double width2(const vector<P> &h) {
  int n = h.size();
  if (n <= 2) return 0;
  long double best = 1e30L;
  for (int i = 0, j = 1; i < n; i++) {
    P e = h[(i + 1) % n] - h[i];
    while (cross(e, h[(j + 1) % n] - h[i]) > cross(e, h[j] - h[i])) j = (j + 1) % n;
    long double c = cross(e, h[j] - h[i]);  // altura * |e|
    best = min(best, c * c / norm2(e));
  }
  return best;
}

long double minRectArea(const vector<P> &h) {
  int n = h.size();
  if (n <= 2) return 0;
  long double best = 1e30L;
  int r = 1, t = 1, l = 1;  // ponteiros: extremo na direcao e, no topo, e no oposto
  for (int i = 0; i < n; i++) {
    P e = h[(i + 1) % n] - h[i];
    while (dot(e, h[(r + 1) % n] - h[r]) > 0) r = (r + 1) % n;          // max projecao em e
    if (i == 0) t = r;
    while (cross(e, h[(t + 1) % n] - h[t]) > 0) t = (t + 1) % n;        // max altura
    if (i == 0) l = t;
    while (dot(e, h[(l + 1) % n] - h[l]) < 0) l = (l + 1) % n;          // min projecao em e
    long double w = dot(e, h[r] - h[l]);        // largura * |e|
    long double hh = cross(e, h[t] - h[i]);     // altura * |e|
    best = min(best, w * hh / norm2(e));
  }
  return best;
}
