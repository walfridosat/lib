// Sweep angular: contar pontos em semiplano e triangulos que contem a origem
//
// O que faz: ordena pontos por angulo em torno da origem (exato, com cross) e usa dois
//   ponteiros sobre grupos de mesma direcao para achar, para cada ponto i, quantos pontos j
//   estao estritamente a esquerda (cross(v_i, v_j) > 0, i.e. em (theta_i, theta_i + pi)).
//   Com isso: triangulos que contem a origem = C(n,3) - sum C(k_i, 2).
// Quando usar: Catalogo > Geometria (sweep angular, "triangulos que contem um ponto",
//   cobertura por intervalos angulares).
// Complexidade: O(n log n).
// Uso: vector<P> v (ja relativos a origem; nenhum igual a (0,0));
//   countLeft(v) -> k[i] (por indice original).
//   trianglesContainingOrigin(v): #triangulos com a origem ESTRITAMENTE dentro,
//     valido se nenhum par de pontos e colinear com a origem (nem mesma direcao nem oposta).
// Cuidados: coordenadas ate 1e9 (cross em ll). Para "contem o ponto Q": subtraia Q de todos.
//   Com colinearidades use countLeft e trate casos de borda a mao.

struct P {
  ll x, y;
  P(ll x = 0, ll y = 0) : x(x), y(y) {}
};
ll cross(P a, P b) { return a.x * b.y - a.y * b.x; }
int half(P p) { return (p.y > 0 || (p.y == 0 && p.x > 0)) ? 0 : 1; }
bool angLess(P a, P b) {  // so angulo (mesma direcao => equivalentes)
  if (half(a) != half(b)) return half(a) < half(b);
  return cross(a, b) > 0;
}

vector<ll> countLeft(const vector<P> &v) {
  int n = v.size();
  vector<int> id(n);
  iota(id.begin(), id.end(), 0);
  sort(id.begin(), id.end(), [&](int a, int b) { return angLess(v[a], v[b]); });
  // grupos de mesma direcao
  vector<P> d;
  vector<ll> c;
  vector<int> grp(n);
  for (int t = 0; t < n; t++) {
    int i = id[t];
    if (d.empty() || angLess(d.back(), v[i])) d.push_back(v[i]), c.push_back(0);
    c.back()++;
    grp[i] = d.size() - 1;
  }
  int m = d.size();
  vector<ll> pc(2 * m + 1, 0);  // soma de prefixos sobre o vetor duplicado
  for (int t = 0; t < 2 * m; t++) pc[t + 1] = pc[t] + c[t % m];
  vector<ll> left(m);
  int j = 0;
  for (int g = 0; g < m; g++) {
    j = max(j, g + 1);
    while (j < g + m && cross(d[g], d[j % m]) > 0) j++;  // grupos estritamente a esquerda
    left[g] = pc[j] - pc[g + 1];
  }
  vector<ll> k(n);
  for (int i = 0; i < n; i++) k[i] = left[grp[i]];
  return k;
}

ll trianglesContainingOrigin(const vector<P> &v) {
  ll n = v.size(), bad = 0;
  for (ll x : countLeft(v)) bad += x * (x - 1) / 2;  // triangulos "dentro de um semiplano" por vertice inicial
  return n * (n - 1) * (n - 2) / 6 - bad;
}
