// Ponto/vetor em ponto flutuante (long double) + primitivas
//
// O que faz: struct Pd com operadores, rotacao, projecao, reflexao, interseção de retas,
//   distancia ponto-reta/segmento, angulo orientado.
// Quando usar: Catalogo > Geometria (precisao: compare com eps, long double, clamp em acos/sqrt).
//   Use so quando as coordenadas nao forem inteiras (ver point_int.cpp).
// Complexidade: O(1) cada.
// Uso: Pd a(1.5,2); cross(a,b); rot(a, ang); proj(p, a, b); refl(p, a, b);
//   lineInter(a,b,c,d,out) devolve false se paralelas; distPointSeg(a,b,p).
// Cuidados: EPS = 1e-9; compare com eq(a,b) e sg(x), nunca ==. acos/asin: clamp em [-1,1];
//   sqrt: sqrtl(max(0,x)).

typedef long double ld;
const ld EPS = 1e-9L;
int sg(ld x) { return (x > EPS) - (x < -EPS); }
bool eq(ld a, ld b) { return fabsl(a - b) <= EPS * max((ld)1, max(fabsl(a), fabsl(b))); }

struct Pd {
  ld x, y;
  Pd(ld x = 0, ld y = 0) : x(x), y(y) {}
  Pd operator+(Pd o) const { return Pd(x + o.x, y + o.y); }
  Pd operator-(Pd o) const { return Pd(x - o.x, y - o.y); }
  Pd operator*(ld k) const { return Pd(x * k, y * k); }
  Pd operator/(ld k) const { return Pd(x / k, y / k); }
  bool operator<(Pd o) const { return sg(x - o.x) ? x < o.x : (sg(y - o.y) ? y < o.y : false); }
};
ld cross(Pd a, Pd b) { return a.x * b.y - a.y * b.x; }
ld dot(Pd a, Pd b) { return a.x * b.x + a.y * b.y; }
ld norm2(Pd a) { return dot(a, a); }
ld len(Pd a) { return sqrtl(norm2(a)); }
ld cr(Pd a, Pd b, Pd c) { return cross(b - a, c - a); }
Pd perp(Pd a) { return Pd(-a.y, a.x); }                 // rotaciona 90 graus anti-horario
Pd unit(Pd a) { return a / len(a); }
Pd rot(Pd a, ld ang) {                                  // rotaciona ang radianos anti-horario
  return Pd(a.x * cosl(ang) - a.y * sinl(ang), a.x * sinl(ang) + a.y * cosl(ang));
}
ld angle(Pd a, Pd b) { return atan2l(cross(a, b), dot(a, b)); }  // angulo orientado a->b em (-pi,pi]

Pd proj(Pd p, Pd a, Pd b) {                             // projecao de p na reta ab
  return a + (b - a) * (dot(p - a, b - a) / norm2(b - a));
}
Pd refl(Pd p, Pd a, Pd b) { return proj(p, a, b) * 2 - p; }  // reflexao de p pela reta ab
ld distPointLine(Pd p, Pd a, Pd b) { return fabsl(cross(b - a, p - a)) / len(b - a); }
ld distPointSeg(Pd p, Pd a, Pd b) {
  if (sg(norm2(b - a)) == 0) return len(p - a);
  ld t = dot(p - a, b - a) / norm2(b - a);
  t = max((ld)0, min((ld)1, t));                        // limita a [0,1]
  return len(p - (a + (b - a) * t));
}
// interseção das retas ab e cd; false se paralelas
bool lineInter(Pd a, Pd b, Pd c, Pd d, Pd &out) {
  ld den = cross(b - a, d - c);
  if (sg(den) == 0) return false;
  out = a + (b - a) * (cross(c - a, d - c) / den);
  return true;
}
// segmentos ab e cd: ponto de interseção unico (se cruzam em 1 ponto); false caso contrario
bool segInter(Pd a, Pd b, Pd c, Pd d, Pd &out) {
  ld oa = cr(c, d, a), ob = cr(c, d, b), oc = cr(a, b, c), od = cr(a, b, d);
  if (sg(oa) * sg(ob) < 0 && sg(oc) * sg(od) < 0) {
    out = (a * ob - b * oa) / (ob - oa);
    return true;
  }
  return false;  // toque/colinear: trate a parte (ver point_int.cpp se inteiro)
}
