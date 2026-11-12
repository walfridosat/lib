// Vertice extremo de poligono convexo numa direcao (busca binaria O(log n))
//
// O que faz: dado poligono convexo CCW e direcao dir, devolve o indice do vertice que maximiza
//   dot(dir, v). Serve para "max a*x + b*y sobre o hull" com muitas consultas.
// Quando usar: Catalogo > Geometria (fecho convexo = max de funcao linear; queries de direcao
//   -> busca binaria no hull).
// Complexidade: O(log n) por consulta.
// Uso: vector<P> h = hull(pts) (CCW, estrito, n >= 3); int i = extrVertex(h, P(a,b));
// Cuidados: h CCW estritamente convexo. Se houver empate (aresta perpendicular a dir)
//   devolve um dos dois vertices. Valores: dot em ll (coords ~1e9 ok).

struct P {
  ll x, y;
  P(ll x = 0, ll y = 0) : x(x), y(y) {}
  P operator-(P o) const { return P(x - o.x, y - o.y); }
};
ll dot(P a, P b) { return a.x * b.x + a.y * b.y; }
ll cross(P a, P b) { return a.x * b.y - a.y * b.x; }

int extrVertex(const vector<P> &h, P dir) {
  int n = h.size();
  // sinal de dot(dir, h[i+1]-h[i]): >0 sobe, <0 desce
  auto up = [&](int i) { return dot(dir, h[(i + 1) % n] - h[i % n]) > 0; };
  // varia: o vetor aresta gira CCW; a sequencia de "up" e ciclicamente [up...up, down...down] (ou rotacao).
  if (!up(n - 1) && !up(0)) {  // comeca em descida: busca o minimo da rotacao
    // h[0] pode estar no meio da descida; procuramos o ponto onde passa a subir e depois desce
  }
  int lo = 0, hi = n;  // busca em [lo, hi): predicado "up" com cuidado de wrap
  bool u0 = up(0);
  while (hi - lo > 1) {
    int m = (lo + hi) / 2;
    bool um = up(m);
    // posicao relativa de m em relacao ao inicio: decide pelo lado de dot
    ll d0 = dot(dir, h[0]), dm = dot(dir, h[m]);
    bool right;  // maximo esta em (m, hi)?
    if (u0) right = um || dm < d0;   // subindo de 0: se m ainda sobe, ou ja desceu abaixo de d0 (maximo antes)
    else right = !um && dm > d0;     // descendo de 0: maximo so apos o fundo
    // reinterpreta: right = maximo esta a direita de m
    if (u0) right = um && dm >= d0;  // so se m ainda esta subindo a partir de 0
    else right = (!um && dm > d0) || (um && dm >= d0) ? true : false;
    if (right) lo = m; else hi = m;
  }
  // lo e candidato; verifica vizinhos por seguranca
  int best = lo;
  for (int d = -1; d <= 1; d++) {
    int i = ((lo + d) % n + n) % n;
    if (dot(dir, h[i]) > dot(dir, h[best])) best = i;
  }
  return best;
}
