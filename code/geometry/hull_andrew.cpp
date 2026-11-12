// Fecho convexo (Andrew monotone chain) - versao correta
//
// O que faz: devolve os vertices do fecho convexo em ordem anti-horaria, comecando pelo
//   menor (x,y). Opcao de manter ou remover pontos colineares na borda.
// Quando usar: Catalogo > Geometria (fecho convexo, pontos extremos, max de funcao linear,
//   base de calipers/Minkowski/diametro).
// Complexidade: O(n log n).
// Uso: vector<P> h = hull(pts);          // sem colineares (so vertices)
//      vector<P> h = hull(pts, true);    // mantem colineares na borda
//   Retorna 1 ponto se todos iguais, 2 pontos se todos colineares (sem keep).
// Cuidados: duplicatas sao removidas; cross em ll (coords ate ~1e9). Ver convexhull.cpp
//   (versao antiga com bug de tipo) - use esta.

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
  // pop quando virar a direita (cross<0) ou colinear (cross==0, se nao mantemos colineares)
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
