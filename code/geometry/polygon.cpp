// Poligonos: area, centroide, Pick, ponto em poligono (geral e convexo O(log n)), pontos de rede
//
// O que faz: area*2 sinalizada (shoelace), centroide, contagem de pontos de rede (Pick),
//   ponto em poligono qualquer O(n) e em convexo O(log n), pontos de rede no segmento e no circulo.
// Quando usar: Catalogo > Geometria (area/sinal, centroide, Teorema de Pick, ponto em poligono).
// Complexidade: area/Pick/inPoly O(n); inConvex O(log n); circleLattice O(r).
// Uso: vector<P> g (vertices em ordem, sem repetir o primeiro no fim).
//   area2(g) -> 2*area sinalizada (>0 anti-horario). centroid(g) -> (cx,cy) em long double.
//   pick(g,I,B): A2=|area2|; B = pontos de rede na borda; I = (A2 - B + 2)/2 interiores.
//   inPoly(g,q): 0 fora, 1 borda, 2 dentro. inConvex(g,q): idem, g CCW estritamente convexo (n>=3).
//   latticeOnSeg(a,b) = gcd+1. circleLattice(r) = #(x,y) inteiros com x^2+y^2<=r^2.
// Cuidados: guarde 2*area em inteiro. Poligono simples assumido. inConvex exige CCW e sem
//   vertices colineares (use hull() de hull_andrew.cpp).

struct P {
  ll x, y;
  P(ll x = 0, ll y = 0) : x(x), y(y) {}
  P operator-(P o) const { return P(x - o.x, y - o.y); }
  P operator+(P o) const { return P(x + o.x, y + o.y); }
};
ll cross(P a, P b) { return a.x * b.y - a.y * b.x; }
ll cr(P a, P b, P c) { return cross(b - a, c - a); }
int sgn(ll x) { return (x > 0) - (x < 0); }

ll area2(const vector<P> &g) {
  ll s = 0;
  for (int i = 0, n = g.size(); i < n; i++) s += cross(g[i], g[(i + 1) % n]);
  return s;
}

// centroide da regiao (nao dos vertices). Poligono com area != 0.
pair<long double, long double> centroid(const vector<P> &g) {
  long double cx = 0, cy = 0, a = 0;
  int n = g.size();
  for (int i = 0; i < n; i++) {
    P p = g[i], q = g[(i + 1) % n];
    long double c = cross(p, q);       // area sinalizada do triangulo (0,p,q) * 2
    cx += (p.x + q.x) * c;
    cy += (p.y + q.y) * c;
    a += c;
  }
  return {cx / (3 * a), cy / (3 * a)};  // 6A = 3 * (2A)
}

// Pick: B = pontos de rede na borda, I = pontos de rede estritamente dentro
void pick(const vector<P> &g, ll &I, ll &B) {
  B = 0;
  int n = g.size();
  for (int i = 0; i < n; i++) {
    P d = g[(i + 1) % n] - g[i];
    B += __gcd(llabs(d.x), llabs(d.y));
  }
  ll A2 = llabs(area2(g));
  I = (A2 - B + 2) / 2;  // A = I + B/2 - 1
}

ll latticeOnSeg(P a, P b) { return __gcd(llabs(a.x - b.x), llabs(a.y - b.y)) + 1; }

// ponto em poligono qualquer (simples). 0 fora, 1 borda, 2 dentro. Regra y_a <= y < y_b.
int inPoly(const vector<P> &g, P q) {
  int n = g.size(), cnt = 0;
  for (int i = 0; i < n; i++) {
    P a = g[i], b = g[(i + 1) % n];
    if (cr(a, b, q) == 0 && min(a.x, b.x) <= q.x && q.x <= max(a.x, b.x) &&
        min(a.y, b.y) <= q.y && q.y <= max(a.y, b.y))
      return 1;
    // raio para a direita de q cruza a aresta?
    if ((a.y <= q.y) != (b.y <= q.y)) {
      // q esta a esquerda do ponto de cruzamento <=> sinal de cr combinado com a direcao
      ll c = cr(a, b, q);
      if (b.y > a.y ? c > 0 : c < 0) cnt ^= 1;
    }
  }
  return cnt ? 2 : 0;
}

// ponto em poligono convexo CCW estrito, n>=3, O(log n). 0 fora, 1 borda, 2 dentro.
int inConvex(const vector<P> &g, P q) {
  int n = g.size();
  if (cr(g[0], g[1], q) < 0 || cr(g[0], g[n - 1], q) > 0) return 0;
  int l = 1, r = n - 1;  // acha o setor (g0, g[l], g[l+1]) que contem q
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (cr(g[0], g[m], q) >= 0) l = m; else r = m;
  }
  int c = sgn(cr(g[l], g[l + 1], q));
  if (c < 0) return 0;
  if (c == 0) return 1;
  if (l == 1 && cr(g[0], g[1], q) == 0) return 1;
  if (l == n - 2 && cr(g[0], g[n - 1], q) == 0) return 1;
  return 2;
}

// numero de pontos inteiros com x^2+y^2 <= r^2
ll circleLattice(ll r) {
  ll s = 0;
  for (ll x = -r; x <= r; x++) {
    ll y = (ll)sqrtl((long double)(r * r - x * x));
    while (y * y > r * r - x * x) y--;       // corrige erro de sqrt
    while ((y + 1) * (y + 1) <= r * r - x * x) y++;
    s += 2 * y + 1;
  }
  return s;
}
