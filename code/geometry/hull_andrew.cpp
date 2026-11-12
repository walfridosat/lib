// Fecho convexo - Andrew monotone chain

struct P {
  ll x, y;
  P(ll x = 0, ll y = 0) : x(x), y(y) {}
  P operator-(P o) const { return P(x - o.x, y - o.y); }
  bool operator<(P o) const { return x != o.x ? x < o.x : y < o.y; }
  bool operator==(P o) const { return x == o.x && y == o.y; }
};
ll cross(P a, P b) { return a.x * b.y - a.y * b.x; }
ll cr(P a, P b, P c) { return cross(b - a, c - a); }

vector<P> hull(vector<P> p, bool keepCol = false) {
  sort(p.begin(), p.end());
  p.erase(unique(p.begin(), p.end()), p.end());
  int n = p.size();
  if (n <= 2) return p;
  bool allCol = true;
  for (int i = 2; i < n; i++) if (cr(p[0], p[1], p[i]) != 0) { allCol = false; break; }
  if (allCol) return keepCol ? p : vector<P>{p[0], p[n - 1]};
  vector<P> h(2 * n);
  int k = 0;
  // pop se virar a direita ou colinear
  auto bad = [&](ll c) { return c < 0 || (!keepCol && c == 0); };
  for (int i = 0; i < n; i++) {  // cadeia inferior
    while (k >= 2 && bad(cr(h[k - 2], h[k - 1], p[i]))) k--;
    h[k++] = p[i];
  }
  for (int i = n - 2, t = k + 1; i >= 0; i--) {  // cadeia superior
    while (k >= t && bad(cr(h[k - 2], h[k - 1], p[i]))) k--;
    h[k++] = p[i];
  }
  h.resize(k - 1);  // ultimo ponto repete o primeiro
  return h;
}

/*LATEX_DESC_BEGIN***************************
-> **Fecho convexo - Andrew monotone chain**
Devolve os vertices do hull em ordem anti-horaria, comecando pelo menor (x,y). Opcao de
manter ou remover colineares na borda.

Complexidade: O(n log n)
Uso:
  vector<P> h = hull(pts);         // sem colineares (so vertices)
  vector<P> h2 = hull(pts, true);  // mantem colineares na borda
  // 1 ponto se todos iguais; 2 pontos se todos colineares (sem keep)

* Sobre o codigo:
  Ordena e remove duplicatas. Caso todos colineares, devolve extremos ou todos. Senao monta a
  cadeia inferior e a superior; bad(c) remove curva a direita (c < 0) e, se keepCol == false,
  tambem colineares (c == 0). O ultimo ponto repete o primeiro e e removido.

* Problemas e reducoes:
  + Fecho convexo de um conjunto de pontos.
  + Maximo de funcao linear: hull + extrVertex (convex_extreme.cpp).
  + Base para calipers, Minkowski e diametro.
  + Area do hull e ponto em poligono convexo (inConvex, polygon.cpp).

Cuidados: duplicatas sao removidas. Cross em ll; coords ate ~1e9 dao ate 4e18, no limite.
  Prefira esta versao a convexhull.cpp (antiga, com bug de tipo).
Catalogo: Geometria.
Digitacao: 32 linhas | media. Atalho: as duas cadeias repetem o mesmo while; extrair um
  helper de cadeia reutilizado para inferior e superior.
*****************************LATEX_DESC_END*/
