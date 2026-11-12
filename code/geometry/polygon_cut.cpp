// Corte de poligono por semiplano (Sutherland-Hodgman)

struct Pd {
  long double x, y;
  Pd(long double x = 0, long double y = 0) : x(x), y(y) {}
  Pd operator+(Pd o) const { return Pd(x + o.x, y + o.y); }
  Pd operator-(Pd o) const { return Pd(x - o.x, y - o.y); }
  Pd operator*(long double k) const { return Pd(x * k, y * k); }
};
long double cross(Pd a, Pd b) { return a.x * b.y - a.y * b.x; }

vector<Pd> cutPoly(const vector<Pd> &g, Pd a, Pd b) {
  const long double E = 1e-12L;
  vector<Pd> r;
  int n = g.size();
  for (int i = 0; i < n; i++) {
    Pd p = g[i], q = g[(i + 1) % n];
    long double sp = cross(b - a, p - a), sq = cross(b - a, q - a);  // lado de p e q
    if (sp >= -E) r.push_back(p);                                    // p dentro
    if ((sp > E && sq < -E) || (sp < -E && sq > E))                  // aresta cruza a reta
      r.push_back(p + (q - p) * (sp / (sp - sq)));
  }
  return r;
}

long double polyArea(const vector<Pd> &g) {  // area (nao sinalizada)
  long double s = 0;
  for (int i = 0, n = g.size(); i < n; i++) s += cross(g[i], g[(i + 1) % n]);
  return fabsl(s) / 2;
}

/*LATEX_DESC_BEGIN***************************
-> **Corte de poligono por semiplano (Sutherland-Hodgman)**
Devolve a parte do poligono que fica a esquerda (ou sobre) da reta orientada a -> b.

Complexidade: O(n) por corte
Uso:
  vector<Pd> g;
  g = cutPoly(g, a, b);           // mantem o lado esquerdo de a->b
  long double ar = polyArea(g);   // area nao sinalizada
  // HPI simples: comece com uma caixa grande e corte por cada semiplano (O(n*m))

* Sobre o codigo:
  Para cada aresta p->q, sp e sq sao os lados de p e q. Mantem p se sp >= -E e adiciona o
  ponto de cruzamento quando os sinais sao opostos (sem contar toque). Resultado vazio =>
  vetor vazio.

* Problemas e reducoes:
  + Recorte de poligono por uma reta/semiplano.
  + HPI incremental com caixa grande.
  + Kernel de um poligono por cortes sucessivos.
  + Area da parte recortada: polyArea.

Cuidados: funciona para poligono convexo (resultado convexo); em nao convexo pode gerar
  arestas degeneradas sobre a reta. E = 1e-12; coordenadas reais. Nao fecha o poligono
  duplicando o primeiro vertice (as funcoes usam (i+1)%n).
Catalogo: Geometria.
Digitacao: 26 linhas | facil. Atalho: ok.
*****************************LATEX_DESC_END*/
