// Circulos - intersecoes, tangentes e areas

typedef long double ld;
const ld EPS = 1e-9L;
const ld PI = acosl(-1);
struct Pd {
  ld x, y;
  Pd(ld x = 0, ld y = 0) : x(x), y(y) {}
  Pd operator+(Pd o) const { return Pd(x + o.x, y + o.y); }
  Pd operator-(Pd o) const { return Pd(x - o.x, y - o.y); }
  Pd operator*(ld k) const { return Pd(x * k, y * k); }
  Pd operator/(ld k) const { return Pd(x / k, y / k); }
};
ld cross(Pd a, Pd b) { return a.x * b.y - a.y * b.x; }
ld dot(Pd a, Pd b) { return a.x * b.x + a.y * b.y; }
ld len(Pd a) { return sqrtl(dot(a, a)); }
Pd perp(Pd a) { return Pd(-a.y, a.x); }
Pd rot(Pd a, ld t) { return Pd(a.x * cosl(t) - a.y * sinl(t), a.x * sinl(t) + a.y * cosl(t)); }
ld sq(ld x) { return x * x; }
ld sqrtp(ld x) { return sqrtl(max((ld)0, x)); }
struct C { Pd c; ld r; };

vector<Pd> circleLine(C o, Pd a, Pd b) {
  Pd d = b - a;
  Pd f = a + d * (dot(o.c - a, d) / dot(d, d));  // pe da perpendicular do centro
  ld h2 = sq(o.r) - dot(f - o.c, f - o.c);
  if (h2 < -EPS) return {};
  if (h2 < EPS) return {f};
  Pd u = d / len(d) * sqrtl(h2);
  return {f - u, f + u};
}

vector<Pd> circleCircle(C a, C b) {
  Pd d = b.c - a.c;
  ld D = len(d);
  if (D < EPS) return {};                              // concentricos
  if (D > a.r + b.r + EPS || D < fabsl(a.r - b.r) - EPS) return {};
  ld x = (sq(D) + sq(a.r) - sq(b.r)) / (2 * D);        // distancia de a.c ao eixo radical
  ld h = sqrtp(sq(a.r) - sq(x));
  Pd m = a.c + d / D * x, n = perp(d) / D * h;
  if (h < EPS) return {m};
  return {m - n, m + n};
}

// tangencia do ponto p no circulo o (p fora)
vector<Pd> tangentsFrom(C o, Pd p) {
  Pd d = p - o.c;
  ld D2 = dot(d, d);
  if (D2 < sq(o.r) - EPS) return {};
  if (D2 < sq(o.r) + EPS) return {p};
  ld t = acosl(min((ld)1, o.r / sqrtl(D2)));  // angulo no centro entre d e o raio ao ponto
  Pd u = d / sqrtl(D2) * o.r;
  return {o.c + rot(u, t), o.c + rot(u, -t)};
}

// tangentes comuns: pares (ponto em a, ponto em b)
vector<pair<Pd, Pd>> commonTangents(C a, C b) {
  vector<pair<Pd, Pd>> res;
  Pd d = b.c - a.c;
  ld D2 = dot(d, d);
  if (D2 < EPS) return res;
  for (int s : {-1, 1}) {            // s=1 externas; s=-1 internas
    ld R = a.r - s * b.r;            // n unitaria com dot(n, d) = R
    ld h2 = D2 - sq(R);
    if (h2 < -EPS) continue;
    ld h = sqrtp(h2);
    for (int sg : {-1, 1}) {         // dois lados
      // normal unitaria n com dot(n, d) = R (do lado sg)
      Pd n = (d * R + perp(d) * (sg * h)) / D2;
      Pd pa = a.c + n * a.r;
      Pd pb = b.c + n * (s * b.r);   // externa: mesmo lado; interna: lado oposto
      res.push_back({pa, pb});
      if (h < EPS) break;            // tangente dupla
    }
  }
  return res;
}

// area sinalizada do triangulo (o,a,b)
ld triCircle(Pd a, Pd b, ld r) {  // centro na origem
  Pd d = b - a;
  ld A = dot(d, d), B = dot(a, d), Cc = dot(a, a) - r * r;
  ld disc = B * B - A * Cc;
  auto sector = [&](Pd p, Pd q) { return r * r * atan2l(cross(p, q), dot(p, q)) / 2; };
  if (A < EPS * EPS) return 0;
  if (disc <= 0) return sector(a, b);  // reta nao corta o circulo (ou tangente)
  ld s = sqrtl(disc);
  ld t1 = max((ld)0, (-B - s) / A), t2 = min((ld)1, (-B + s) / A);  // parte dentro em [0,1]
  if (t2 <= t1) return sector(a, b);   // segmento todo fora
  Pd p = a + d * t1, q = a + d * t2;
  return sector(a, p) + cross(p, q) / 2 + sector(q, b);
}
ld circlePolyArea(C o, const vector<Pd> &g) {
  ld s = 0;
  int n = g.size();
  for (int i = 0; i < n; i++) s += triCircle(g[i] - o.c, g[(i + 1) % n] - o.c, o.r);
  return fabsl(s);
}

// area da uniao (Green)
ld unionArea(vector<C> cs) {
  // remove circulos contidos em outros (e duplicatas)
  vector<C> v;
  for (int i = 0; i < (int)cs.size(); i++) {
    bool ok = cs[i].r > EPS;
    for (int j = 0; j < (int)cs.size() && ok; j++) {
      if (i == j) continue;
      ld D = len(cs[i].c - cs[j].c);
      if (D + cs[i].r <= cs[j].r + EPS && (cs[j].r > cs[i].r + EPS || j < i)) ok = false;
    }
    if (ok) v.push_back(cs[i]);
  }
  ld total = 0;
  int n = v.size();
  for (int i = 0; i < n; i++) {
    vector<pair<ld, ld>> iv;  // arcos cobertos [lo, hi] em [0, 2pi]
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      Pd d = v[j].c - v[i].c;
      ld D = len(d);
      if (D >= v[i].r + v[j].r - EPS) continue;  // disjuntos
      ld base = atan2l(d.y, d.x);
      ld w = acosl(max((ld)-1, min((ld)1, (sq(v[i].r) + sq(D) - sq(v[j].r)) / (2 * v[i].r * D))));
      ld lo = base - w, hi = base + w;
      while (lo < 0) lo += 2 * PI, hi += 2 * PI;
      while (lo >= 2 * PI) lo -= 2 * PI, hi -= 2 * PI;
      if (hi > 2 * PI) iv.push_back({lo, 2 * PI}), iv.push_back({0, hi - 2 * PI});
      else iv.push_back({lo, hi});
    }
    sort(iv.begin(), iv.end());
    ld cur = 0;  // percorre arcos livres [cur, lo]
    auto arc = [&](ld a, ld b) {  // Green do arco a..b do circulo i
      if (b <= a) return;
      Pd c = v[i].c; ld r = v[i].r;
      total += r * r * (b - a) / 2 +
               (c.x * r * (sinl(b) - sinl(a)) - c.y * r * (cosl(b) - cosl(a))) / 2 * 1;
    };
    for (auto &p : iv) {
      if (p.first > cur) arc(cur, p.first);
      cur = max(cur, p.second);
    }
    arc(cur, 2 * PI);
  }
  return total;
}

/*LATEX_DESC_BEGIN***************************
-> **Circulos - intersecoes, tangentes e areas**
Circunferencia-reta, circunferencia-circunferencia, tangentes de ponto e comuns, area de
intersecao com poligono (Green) e area da uniao de circulos. Coordenadas reais.

Complexidade: intersecao O(1); circlePolyArea O(n); unionArea O(n^2 log n)
Uso:
  struct C { Pd c; ld r; };
  vector<Pd> p = circleLine(c, a, b);      // 0, 1 ou 2 pontos
  vector<Pd> q = circleCircle(c1, c2);     // vazio se disjuntos/contidos; 1 ou 2
  vector<Pd> t = tangentsFrom(c, p);       // p externo ao circulo
  vector<pair<Pd,Pd>> ct = commonTangents(c1, c2);  // ate 4 pares
  ld a = circlePolyArea(c, poly);
  ld u = unionArea(vector<C>);

* Sobre o codigo:
  circleLine projeta o centro na reta e corta por h2 = r^2 - dist^2. circleCircle usa o eixo
  radical. commonTangents testa s = +1 (externas, R = r1 - r2) e s = -1 (internas, R = r1 + r2).
  triCircle soma setor + triangulo pela formula de Green. unionArea remove circulos contidos,
  projeta os arcos cobertos como intervalos angulares e soma os arcos livres.

* Problemas e reducoes:
  + Tangentes comuns a dois circulos: commonTangents (ate 4).
  + Tangentes de um ponto externo: tangentsFrom.
  + Area de poligono intersectado por um circulo: circlePolyArea.
  + Area da uniao de discos: unionArea.
  + Intersecao de uma circunferencia com uma reta: circleLine.
  + Pontos de tangencia para construcoes de retas e circulos tangentes.

Cuidados: EPS = 1e-9; sempre faca clamp em sqrt/acos/asin (sqrtp e min/max ja fazem).
  Circulos identicos: circleCircle devolve vazio; unionArea remove duplicatas e contidos.
  Coordenadas grandes com long double ainda podem acumular erro em unionArea.
Catalogo: Geometria.
Digitacao: 137 linhas | dificil. Atalho: o bloco Pd/cross/dot/len/perp/rot repete
  point_dbl.cpp; incluir aquele arquivo e apagar o bloco encurta bastante.
*****************************LATEX_DESC_END*/
