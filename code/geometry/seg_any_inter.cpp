// Existe interseção entre n segmentos? (Shamos-Hoey, sweep + set)
//
// O que faz: acha um par de segmentos que se intersectam (inclui toque), ou {-1,-1}.
// Quando usar: Catalogo > Geometria (sweep line + set, "algum par de segmentos se cruza?").
// Complexidade: O(n log n).
// Uso: vector<Seg> s; s[i] = {Pd(x1,y1), Pd(x2,y2), i}; auto r = anyInter(s) -> par de ids ou {-1,-1}.
// Cuidados: EPS = 1e-9 com double (coords inteiras pequenas ok). Segmentos verticais e pontos
//   sao tratados pela comparacao em y no x corrente. O comparador depende do x da varredura
//   (guardado em max dos minimos). Segmentos degenerados (ponto) sao aceitos.

const double EPS = 1e-9;
struct Pd { double x, y; };
struct Seg {
  Pd p, q;
  int id;
  double gety(double x) const {
    if (fabs(p.x - q.x) < EPS) return p.y;  // vertical: usa o ponto de baixo (p.y <= q.y apos normalizar)
    return p.y + (q.y - p.y) * (x - p.x) / (q.x - p.x);
  }
};
bool inter1d(double a, double b, double c, double d) {
  if (a > b) swap(a, b);
  if (c > d) swap(c, d);
  return max(a, c) <= min(b, d) + EPS;
}
double vec(Pd a, Pd b, Pd c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }
int sgnd(double x) { return (x > EPS) - (x < -EPS); }
bool segsInter(const Seg &a, const Seg &b) {
  return inter1d(a.p.x, a.q.x, b.p.x, b.q.x) && inter1d(a.p.y, a.q.y, b.p.y, b.q.y) &&
         sgnd(vec(a.p, a.q, b.p)) * sgnd(vec(a.p, a.q, b.q)) <= 0 &&
         sgnd(vec(b.p, b.q, a.p)) * sgnd(vec(b.p, b.q, a.q)) <= 0;
}
bool operator<(const Seg &a, const Seg &b) {
  double x = max(min(a.p.x, a.q.x), min(b.p.x, b.q.x));
  return a.gety(x) < b.gety(x) - EPS;
}

pair<int, int> anyInter(vector<Seg> a) {
  int n = a.size();
  for (auto &s : a)
    if (s.p.x > s.q.x || (fabs(s.p.x - s.q.x) < EPS && s.p.y > s.q.y)) swap(s.p, s.q);
  vector<array<double, 3>> ev;  // (x, tipo, indice): abre (+1) antes de fecha (-1) no mesmo x
  for (int i = 0; i < n; i++) {
    ev.push_back({a[i].p.x, -1, (double)i});
    ev.push_back({a[i].q.x, +1, (double)i});
  }
  sort(ev.begin(), ev.end());
  set<Seg> s;
  vector<set<Seg>::iterator> where(n);
  for (auto &e : ev) {
    int i = (int)e[2];
    if (e[1] < 0) {  // abre
      auto nxt = s.lower_bound(a[i]);
      auto prv = nxt;
      if (nxt != s.end() && segsInter(*nxt, a[i])) return {nxt->id, a[i].id};
      if (nxt != s.begin() && segsInter(*--prv, a[i])) return {prv->id, a[i].id};
      where[i] = s.insert(nxt, a[i]);
    } else {  // fecha: checa os vizinhos que passam a ser adjacentes
      auto nxt = next(where[i]), prv = where[i];
      if (nxt != s.end() && prv != s.begin() && segsInter(*nxt, *--prv)) return {prv->id, nxt->id};
      s.erase(where[i]);
    }
  }
  return {-1, -1};
}
