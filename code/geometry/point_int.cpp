// Ponto inteiro e primitivas exatas

struct P {
  ll x, y;
  P(ll x = 0, ll y = 0) : x(x), y(y) {}
  P operator+(P o) const { return P(x + o.x, y + o.y); }
  P operator-(P o) const { return P(x - o.x, y - o.y); }
  P operator*(ll k) const { return P(x * k, y * k); }
  bool operator<(P o) const { return x != o.x ? x < o.x : y < o.y; }
  bool operator==(P o) const { return x == o.x && y == o.y; }
};
ll cross(P a, P b) { return a.x * b.y - a.y * b.x; }
ll dot(P a, P b) { return a.x * b.x + a.y * b.y; }
ll norm2(P a) { return dot(a, a); }
ll cr(P a, P b, P c) { return cross(b - a, c - a); }  // orientacao de a,b,c
int sgn(ll x) { return (x > 0) - (x < 0); }

// meio-plano: 0 para angulo em [0,pi), 1 para [pi,2pi)
int half(P p) { return (p.y > 0 || (p.y == 0 && p.x > 0)) ? 0 : 1; }
// comparador angular exato; empate: mais perto antes
bool angLess(P a, P b) {
  if (half(a) != half(b)) return half(a) < half(b);
  ll c = cross(a, b);
  if (c != 0) return c > 0;
  return norm2(a) < norm2(b);
}

// p esta no segmento ab (inclui extremos)?
bool onSeg(P a, P b, P p) {
  return cr(a, b, p) == 0 && min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
         min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

// se intersectam (inclui toque/colinear)
bool segInter(P a, P b, P c, P d) {
  int o1 = sgn(cr(a, b, c)), o2 = sgn(cr(a, b, d));
  int o3 = sgn(cr(c, d, a)), o4 = sgn(cr(c, d, b));
  if (o1 * o2 < 0 && o3 * o4 < 0) return true;  // cruzamento proprio
  return onSeg(a, b, c) || onSeg(a, b, d) || onSeg(c, d, a) || onSeg(c, d, b);
}

// distancia ponto p ao segmento ab (double)
double distPointSeg(P a, P b, P p) {
  if (a == b) return sqrt((double)norm2(p - a));
  ll t = dot(p - a, b - a), l = norm2(b - a);
  if (t <= 0) return sqrt((double)norm2(p - a));
  if (t >= l) return sqrt((double)norm2(p - b));
  return fabs((double)cross(b - a, p - a)) / sqrt((double)l);
}

// intersecao das retas ab e cd (nao paralelas: cross(b-a,d-c) != 0)
// ponto = a + (b-a)*t, t = cross(c-a, d-c)/cross(b-a, d-c)
pair<long double, long double> lineInter(P a, P b, P c, P d) {
  long double t = (long double)cross(c - a, d - c) / cross(b - a, d - c);
  return {a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t};
}

/*LATEX_DESC_BEGIN***************************
-> **Ponto inteiro e primitivas exatas**
Struct P (ll) com cross, dot, orientacao, ordenacao angular exata, intersecao de segmentos,
ponto em segmento, distancia ponto-segmento e intersecao de retas. Evita double por completo.

Complexidade: O(1) por operacao
Uso:
  P a(1,2), b(3,4);
  ll c = cross(a, b);          // cr(a,b,c) = cross(b-a, c-a)
  int s = sgn(x);              // -1, 0, 1
  bool i = segInter(a,b,c,d);  // inclui toque e colinear sobreposto
  bool on = onSeg(a, b, p);
  sort(v.begin(), v.end(), angLess);  // angulo em [0,2pi) a partir de +x
  auto q = lineInter(a, b, c, d);     // long double, retas nao paralelas

* Sobre o codigo:
  cr(a,b,c) = cross(b-a, c-a): > 0 anti-horario. angLess usa half (semiplano) e cross para
  ordenar sem float; empate de direcao desempata por norm2. segInter combina sinais opostos
  com onSeg para cobrir toque e sobreposicao.

* Problemas e reducoes:
  + Orientacao exata de tres pontos.
  + Intersecao de segmentos incluindo toque/colinear.
  + Ponto em segmento.
  + Ordenacao angular exata (comparador para sort).
  + Distancia ponto-segmento e intersecao de retas.

Cuidados: coords ate 1e9 => cross cabe em ll (ate ~4e18, perto do limite); para 1e18 use
  __int128. lineInter devolve long double e exige retas nao paralelas. distPointSeg usa
  double.
Catalogo: Geometria.
Digitacao: 49 linhas | facil. Atalho: distPointSeg e lineInter sao opcionais e podem sair;
  o resto e a base minima.
*****************************LATEX_DESC_END*/
