// Sweep angular - conta pontos a esquerda e triangulos com a origem

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
  for (ll x : countLeft(v)) bad += x * (x - 1) / 2;  // triangulos dentro de um semiplano
  return n * (n - 1) * (n - 2) / 6 - bad;
}

/*LATEX_DESC_BEGIN***************************
-> **Sweep angular - pontos a esquerda e triangulos com a origem**
Para cada ponto i, conta quantos pontos j estao em (theta_i, theta_i + pi), ou seja
cross(v_i, v_j) > 0. Indices 0-based, vetores ja relativos a origem.

Complexidade: O(n log n)
Uso:
  vector<P> v;  // relativo a origem; nenhum ponto (0,0)
  vector<ll> k = countLeft(v);          // k[i] pelo indice original
  ll t = trianglesContainingOrigin(v);  // triangulos com a origem dentro

* Sobre o codigo:
  Ordena os indices por angulo exato (half + cross). Junta direcoes iguais em grupos d[] com
  contagem c[]; duplica o vetor de prefixos para o teste de dois ponteiros. left[g] = pontos
  estritamente a esquerda do grupo g. k[i] apenas copia left[grp[i]].

* Problemas e reducoes:
  + Triangulos que contem a origem: C(n,3) - sum C(k_i,2), com k_i de countLeft.
  + Triangulos que contem um ponto Q: subtraia Q de todos os pontos e use o mesmo.
  + Para cada ponto, contar pontos em um semiplano (angulo < pi): k[i] de countLeft.
  + Cobertura por intervalos angulares: os grupos ordenados dao os eventos de inicio/fim.

Cuidados: coordenadas ate 1e9 (cross em ll). trianglesContainingOrigin exige que nenhum par
  de pontos seja colinear com a origem (mesma direcao ou oposta); com colinearidades, use
  countLeft e trate as bordas a mao.
Catalogo: Geometria.
Digitacao: 44 linhas | media. Atalho: d, c e grp repetem a mesma informacao; da para agrupar
  em um unico vetor de grupos e mapear k no fim.
*****************************LATEX_DESC_END*/
