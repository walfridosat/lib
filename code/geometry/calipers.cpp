// Rotating calipers - diametro, largura e caixa minima

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
  int r = 1, t = 1, l = 1;  // r, t, l: extremos nas direcoes e, perp e -e
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

/*LATEX_DESC_BEGIN***************************
-> **Rotating calipers - diametro, largura e caixa minima**
Sobre o fecho convexo CCW (de hull_andrew.cpp), acha o par mais distante, a menor largura
(distancia entre retas suporte paralelas) e a menor area de retangulo envolvente.

Complexidade: O(h) apos o hull
Uso:
  vector<P> h = hull(pts);         // CCW, sem colineares
  ll d2 = diameter2(h);            // maior distancia^2 (exato, ll)
  long double w2 = width2(h);      // largura^2
  long double a = minRectArea(h);  // menor area de retangulo

* Sobre o codigo:
  Para cada aresta i do hull, um ponteiro j avanca enquanto a area/altura da aresta ate j
  cresce. diameter2 usa norm2; width2 usa cross(e, h[j]-h[i]), que e altura*|e|; minRectArea
  mantem tres ponteiros: projecao maxima (r), altura maxima (t) e projecao minima (l).

* Problemas e reducoes:
  + Diametro de um conjunto de pontos: hull + diameter2.
  + Par de pontos mais distante em O(n log n) total (ordenacao inclusa).
  + Menor largura de um poligono convexo: width2.
  + Menor retangulo envolvente (com lado colinear a uma aresta): minRectArea.
  + Calipers tambem serve para antipodal points e giro de arestas.

Cuidados: h deve ser CCW e estritamente convexo (sem colineares); h.size() 1 ou 2 e tratado.
  Diametro usa inteiros (exato; cuidado com overflow de ll em |e|^2); largura e retangulo usam
  long double e podem perder precisao em coordenadas muito grandes.
Catalogo: Geometria.
Digitacao: 51 linhas | dificil. Atalho: os tres lacos repetem o mesmo avanco de ponteiro
  antipodal; extrair um helper e reusar em diameter2/width2/minRectArea.
*****************************LATEX_DESC_END*/
