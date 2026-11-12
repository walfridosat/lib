// Vertice extremo de convexo numa direcao

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
  // sequencia de up e ciclica: up...up, down...down
  if (!up(n - 1) && !up(0)) {  // comeca em descida: busca o minimo da rotacao
    // h[0] pode estar no meio da descida
  }
  int lo = 0, hi = n;  // busca em [lo, hi) com wrap
  bool u0 = up(0);
  while (hi - lo > 1) {
    int m = (lo + hi) / 2;
    bool um = up(m);
    // posicao relativa de m em relacao ao inicio: decide pelo lado de dot
    ll d0 = dot(dir, h[0]), dm = dot(dir, h[m]);
    bool right;  // maximo esta em (m, hi)?
    if (u0) right = um || dm < d0;   // subindo de 0: decide pelo lado do maximo
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

/*LATEX_DESC_BEGIN***************************
-> **Vertice extremo de convexo numa direcao**
Dado poligono convexo CCW e direcao dir, devolve o indice do vertice que maximiza
dot(dir, v). Indices 0-based.

Complexidade: O(log n) por consulta
Uso:
  vector<P> h = hull(pts);         // CCW, estrito, n >= 3
  int i = extrVertex(h, P(a, b));  // maximiza a*x + b*y

* Sobre o codigo:
  up(i) indica se dot(dir, h[i+1]-h[i]) > 0 (a projecao sobe). Essa sequencia e ciclicamente
  um bloco de subidas seguido de um bloco de descidas. A busca binaria compara dot(dir, h[m])
  com dot(dir, h[0]) para decidir de que lado esta o maximo; no fim confere os vizinhos.

* Problemas e reducoes:
  + Maximizar a*x + b*y sobre um conjunto de pontos: hull + extrVertex.
  + Muitas consultas de direcao no mesmo hull (cada uma O(log n)).
  + Achar o vertice de suporte numa direcao (usado em calipers).
  + Minimizar a*x + b*y: chame com P(-a,-b).

Cuidados: h deve ser CCW e estritamente convexo (sem colineares), n >= 3. Em empate (aresta
  perpendicular a dir) devolve um dos dois vertices. dot em ll; coords ~1e9 cabem.
Catalogo: Geometria.
Digitacao: 38 linhas | dificil. Atalho: a variavel right e atribuida duas vezes seguidas;
  consolidar em uma unica expressao encurta a busca.
*****************************LATEX_DESC_END*/
