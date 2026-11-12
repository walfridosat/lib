// Geometria 3D - primitivas e fecho convexo incremental

typedef double db;
struct P3 {
  db x, y, z;
  P3(db x = 0, db y = 0, db z = 0) : x(x), y(y), z(z) {}
  P3 operator+(P3 o) const { return P3(x + o.x, y + o.y, z + o.z); }
  P3 operator-(P3 o) const { return P3(x - o.x, y - o.y, z - o.z); }
  P3 operator*(db k) const { return P3(x * k, y * k, z * k); }
};
P3 cross(P3 a, P3 b) { return P3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
db dot(P3 a, P3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
db len(P3 a) { return sqrt(dot(a, a)); }

// 6 * volume sinalizado do tetraedro (a,b,c,d)
db vol6(P3 a, P3 b, P3 c, P3 d) { return dot(b - a, cross(c - a, d - a)); }
db distPlane(P3 p, P3 a, P3 b, P3 c) {  // distancia de p ao plano abc
  P3 n = cross(b - a, c - a);
  return fabs(dot(n, p - a)) / len(n);
}
// reta p + t*d com o plano abc; false se paralela
bool linePlane(P3 p, P3 d, P3 a, P3 b, P3 c, P3 &out) {
  P3 n = cross(b - a, c - a);
  db den = dot(n, d);
  if (fabs(den) < 1e-12) return false;
  out = p + d * (dot(n, a - p) / den);
  return true;
}

// ---- fecho convexo 3D (estilo KACTL) ----
struct PR {  // as 2 faces adjacentes a uma aresta dirigida
  int a = -1, b = -1;
  void ins(int x) { (a == -1 ? a : b) = x; }
  void rem(int x) { (a == x ? a : b) = -1; }
  int cnt() { return (a != -1) + (b != -1); }
};
struct F { P3 q; int a, b, c; };  // q = normal (para fora), a,b,c vertices

vector<F> hull3d(const vector<P3> &A) {
  int n = A.size();
  vector<vector<PR>> E(n, vector<PR>(n));
  vector<F> FS;
  auto mf = [&](int i, int j, int k, int l) {  // cria face (i,j,k), l = ponto do lado de dentro
    P3 q = cross(A[j] - A[i], A[k] - A[i]);
    if (dot(q, A[l]) > dot(q, A[i])) q = q * -1;
    F f{q, i, j, k};
    E[f.a][f.b].ins(k); E[f.a][f.c].ins(j); E[f.b][f.c].ins(i);
    FS.push_back(f);
  };
  for (int i = 0; i < 4; i++) for (int j = i + 1; j < 4; j++) for (int k = j + 1; k < 4; k++)
    mf(i, j, k, 6 - i - j - k);  // tetraedro inicial
  for (int i = 4; i < n; i++) {
    for (int j = 0; j < (int)FS.size(); j++) {
      F f = FS[j];
      if (dot(f.q, A[i]) > dot(f.q, A[f.a])) {  // face visivel de i: remove
        E[f.a][f.b].rem(f.c); E[f.a][f.c].rem(f.b); E[f.b][f.c].rem(f.a);
        swap(FS[j--], FS.back());
        FS.pop_back();
      }
    }
    int nw = FS.size();
    for (int j = 0; j < nw; j++) {  // fecha o "buraco" com faces novas ligando a i
      F f = FS[j];
      if (E[f.a][f.b].cnt() != 2) mf(f.a, f.b, i, f.c);
      if (E[f.a][f.c].cnt() != 2) mf(f.a, f.c, i, f.b);
      if (E[f.b][f.c].cnt() != 2) mf(f.b, f.c, i, f.a);
    }
  }
  for (F &it : FS)  // orienta CCW visto de fora
    if (dot(cross(A[it.b] - A[it.a], A[it.c] - A[it.a]), it.q) <= 0) swap(it.c, it.b);
  return FS;
}

/*LATEX_DESC_BEGIN***************************
-> **Geometria 3D - primitivas e fecho convexo incremental**
Struct P3 com cross/dot, volume de tetraedro por produto misto, distancia ponto-plano,
intersecao reta-plano e hull 3D como faces triangulares orientadas para fora.

Complexidade: hull3d O(n^2)
Uso:
  P3 a(x,y,z);
  P3 n = cross(a, b); db d = dot(a, b);
  db v6 = vol6(a, b, c, d);                 // 6 * volume sinalizado
  db dp = distPlane(p, a, b, c);
  bool ok = linePlane(p, d, a, b, c, out);  // reta p + t*d, false se paralela
  vector<F> fs = hull3d(pts);               // F tem a,b,c e normal q

* Sobre o codigo:
  vol6 = dot(b-a, cross(c-a, d-a)). O hull comeca com o tetraedro dos 4 primeiros pontos;
  para cada ponto novo remove as faces visiveis e fecha o buraco com faces ligando ao ponto.
  E[a][b] guarda as duas faces adjacentes a aresta dirigida a->b.

* Problemas e reducoes:
  + Volume de tetraedro/poliedro: produto misto / 6.
  + Area da superficie do hull: sum |q|/2.
  + Volume do hull: sum vol6(O, a, b, c)/6 em torno de qualquer ponto.
  + Distancia de ponto a plano e intersecao reta-plano.
  + Fecho convexo 3D / triangulacao de faces.

Cuidados: hull3d exige n >= 4 e SEM 4 pontos coplanares no inicio (posicao geral). Faces
  coplanares podem gerar triangulacao arbitraria, sem erro se nao houver duplicatas; pontos
  duplicados quebram. Use double com EPS ou inteiros exatos. Volume/area do hull podem perder
  precisao com double.
Catalogo: Geometria.
Digitacao: 67 linhas | dificil. Atalho: PR pode virar array<int,2> com helpers estaticos,
  eliminando os metodos ins/rem/cnt.
*****************************LATEX_DESC_END*/
