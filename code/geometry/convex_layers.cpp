// Camadas convexas (convex layers / onion peeling) e frente de Pareto 2D
//
// O que faz: layer[i] = indice da camada do ponto i (0 = fecho externo); repete o fecho
//   removendo os pontos extremos. Tambem: frente de Pareto (pontos nao dominados).
// Quando usar: Catalogo > Geometria (convex layers, "retirar pontos extremos repetidamente",
//   dominancia/frente de Pareto).
// Complexidade: layers O(n * L * ... ) ~ O(n^2 log n) pior caso (simples); pareto O(n log n).
// Uso: vector<int> L = convexLayers(pts) (vector<pair<ll,ll>>); pareto(pts) -> indices dos
//   pontos tais que nenhum outro tem x>= e y>= (maximo em ambos), com um dos > estrito.
// Cuidados: pontos colineares na borda do hull ficam na MESMA camada (mantidos no hull);
//   duplicatas entram na mesma camada do original.

typedef pair<ll, ll> pll;
ll crs(pll a, pll b, pll c) {
  return (b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first);
}

vector<int> convexLayers(const vector<pll> &pts) {
  int n = pts.size();
  vector<int> layer(n, -1), rest(n);
  iota(rest.begin(), rest.end(), 0);
  for (int L = 0; !rest.empty(); L++) {
    sort(rest.begin(), rest.end(), [&](int a, int b) { return pts[a] < pts[b]; });
    vector<int> h;  // hull mantendo colineares (pop so se cross < 0)
    int m = rest.size();
    if (m <= 2) {
      for (int i : rest) layer[i] = L;
      break;
    }
    vector<int> hh(2 * m);
    int k = 0;
    for (int t = 0; t < m; t++) {
      while (k >= 2 && crs(pts[hh[k - 2]], pts[hh[k - 1]], pts[rest[t]]) < 0) k--;
      hh[k++] = rest[t];
    }
    for (int t = m - 2, lo = k + 1; t >= 0; t--) {
      while (k >= lo && crs(pts[hh[k - 2]], pts[hh[k - 1]], pts[rest[t]]) < 0) k--;
      hh[k++] = rest[t];
    }
    for (int i = 0; i < k; i++) layer[hh[i]] = L;
    vector<int> nr;
    for (int i : rest) if (layer[i] < 0) nr.push_back(i);
    rest = nr;
  }
  return layer;
}

// frente de Pareto (maximizar x e y): indices dos pontos nao dominados
vector<int> pareto(const vector<pll> &p) {
  int n = p.size();
  vector<int> id(n), r;
  iota(id.begin(), id.end(), 0);
  sort(id.begin(), id.end(), [&](int a, int b) { return p[a] != p[b] ? p[a] > p[b] : a < b; });
  ll bestY = LLONG_MIN;
  for (int i : id) {  // x decrescente; fica se y >= maior y ja visto (empates mantidos)
    if (p[i].second >= bestY) {
      // se igual a um ponto visto em x maior com mesmo y, e dominado: exige x igual
      bool dom = false;
      if (!r.empty() && p[r.back()].second == p[i].second && p[r.back()].first > p[i].first) dom = true;
      if (!dom) r.push_back(i);
      bestY = max(bestY, p[i].second);
    }
  }
  return r;
}
