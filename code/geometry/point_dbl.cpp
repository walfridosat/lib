// Ponto e vetor em long double com primitivas

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
// intersecao das retas ab e cd; false se paralelas
bool lineInter(Pd a, Pd b, Pd c, Pd d, Pd &out) {
  ld den = cross(b - a, d - c);
  if (sg(den) == 0) return false;
  out = a + (b - a) * (cross(c - a, d - c) / den);
  return true;
}
// segmentos: cruzamento proprio em 1 ponto
bool segInter(Pd a, Pd b, Pd c, Pd d, Pd &out) {
  ld oa = cr(c, d, a), ob = cr(c, d, b), oc = cr(a, b, c), od = cr(a, b, d);
  if (sg(oa) * sg(ob) < 0 && sg(oc) * sg(od) < 0) {
    out = (a * ob - b * oa) / (ob - oa);
    return true;
  }
  return false;  // toque/colinear: trate a parte
}

/*LATEX_DESC_BEGIN***************************
-> **Ponto e vetor em long double com primitivas**
Struct Pd com operadores, rotacao, projecao, reflexao, intersecao de retas, distancia
ponto-reta/segmento e angulo orientado. Use quando as coordenadas nao forem inteiras.

Complexidade: O(1) por operacao
Uso:
  Pd a(1.5, 2), b(3, 4);
  ld c = cross(a, b);
  Pd r = rot(a, ang), pr = proj(p, a, b), rf = refl(p, a, b);
  bool ok = lineInter(a, b, c, d, out);  // false se paralelas
  ld ds = distPointSeg(p, a, b);

* Sobre o codigo:
  sg e eq comparam com EPS relativo. perp gira 90 graus; unit normaliza; rot usa cos/sin.
  proj projeta na reta ab; refl reflete pela reta; lineInter resolve o sistema por cross.
  segInter so detecta cruzamento proprio de um ponto.

* Problemas e reducoes:
  + Primitivas de geometria com coordenadas reais.
  + Distancia ponto-reta e ponto-segmento.
  + Rotacao, projecao e reflexao de pontos.
  + Intersecao de retas (e de segmentos com cruzamento proprio).
  + Angulo orientado entre dois vetores.

Cuidados: EPS = 1e-9; compare com eq(a,b) e sg(x), nunca com ==. Faca clamp em acos/asin para
  [-1,1] e use sqrtl(max(0,x)). segInter nao trata toque nem colineares: para isso use
  point_int.cpp (se inteiro) ou trate a parte. Coordenadas muito grandes podem estourar a
  precisao relativa do EPS.
Catalogo: Geometria.
Digitacao: 51 linhas | media. Atalho: cross/dot/norm2/len/cr se repetem em circles,
  half_plane e min_circle; centralizar esse bloco num unico arquivo base.
*****************************LATEX_DESC_END*/
