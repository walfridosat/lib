// Circulo minimo envolvente (Welzl iterativo) e circuncentro
//
// O que faz: menor circulo contendo todos os pontos. Retorna centro e raio.
// Quando usar: Catalogo > Geometria (circulo minimo, circuncentro).
// Complexidade: O(n) esperado (apos embaralhar).
// Uso: auto c = minCircle(pts); c.first = centro (Pd), c.second = raio.
//   circumcenter(a,b,c) devolve o centro do circulo por 3 pontos (nao colineares).
// Cuidados: embaralha internamente (mt19937 fixo). EPS relativo; coords reais.

struct Pd {
  long double x, y;
  Pd(long double x = 0, long double y = 0) : x(x), y(y) {}
  Pd operator+(Pd o) const { return Pd(x + o.x, y + o.y); }
  Pd operator-(Pd o) const { return Pd(x - o.x, y - o.y); }
  Pd operator*(long double k) const { return Pd(x * k, y * k); }
};
long double cross(Pd a, Pd b) { return a.x * b.y - a.y * b.x; }
long double dot(Pd a, Pd b) { return a.x * b.x + a.y * b.y; }
long double dist(Pd a, Pd b) { return sqrtl(dot(a - b, a - b)); }

Pd circumcenter(Pd a, Pd b, Pd c) {
  b = b - a, c = c - a;  // resolve com a na origem
  long double d = 2 * cross(b, c);
  return a + Pd((c.y * dot(b, b) - b.y * dot(c, c)) / d,
                (b.x * dot(c, c) - c.x * dot(b, b)) / d);
}

pair<Pd, long double> minCircle(vector<Pd> p) {
  mt19937 rng(12345);
  shuffle(p.begin(), p.end(), rng);
  const long double E = 1e-9L;
  Pd c = p[0];
  long double r = 0;
  int n = p.size();
  for (int i = 1; i < n; i++) {
    if (dist(c, p[i]) <= r + E) continue;
    c = p[i], r = 0;                       // p[i] na fronteira
    for (int j = 0; j < i; j++) {
      if (dist(c, p[j]) <= r + E) continue;
      c = (p[i] + p[j]) * 0.5L, r = dist(p[i], p[j]) / 2;  // p[i], p[j] na fronteira
      for (int k = 0; k < j; k++) {
        if (dist(c, p[k]) <= r + E) continue;
        c = circumcenter(p[i], p[j], p[k]);   // tres pontos na fronteira
        r = dist(c, p[i]);
      }
    }
  }
  return {c, r};
}
