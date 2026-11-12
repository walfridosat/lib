// Intersecao de semiplanos (HPI) O(n log n)

typedef long double ld;
const ld EPS = 1e-9L;
struct Pd {
  ld x, y;
  Pd(ld x = 0, ld y = 0) : x(x), y(y) {}
  Pd operator+(Pd o) const { return Pd(x + o.x, y + o.y); }
  Pd operator-(Pd o) const { return Pd(x - o.x, y - o.y); }
  Pd operator*(ld k) const { return Pd(x * k, y * k); }
};
ld cross(Pd a, Pd b) { return a.x * b.y - a.y * b.x; }
ld dot(Pd a, Pd b) { return a.x * b.x + a.y * b.y; }

struct HP {
  Pd p, d;  // ponto na reta e direcao; semiplano = esquerda
  ld ang;
  HP() {}
  HP(Pd p, Pd d) : p(p), d(d), ang(atan2l(d.y, d.x)) {}
  bool out(Pd r) const { return cross(d, r - p) < -EPS; }  // r estritamente fora?
};
Pd hpInter(const HP &s, const HP &t) {  // reta s com reta t (nao paralelas)
  // acha alpha tal que s.p + s.d*alpha esta na reta t
  ld al = -cross(t.d, s.p - t.p) / cross(t.d, s.d);
  return s.p + s.d * al;
}

vector<Pd> hpi(vector<HP> H) {
  sort(H.begin(), H.end(), [](const HP &a, const HP &b) { return a.ang < b.ang; });
  deque<HP> dq;
  for (auto &h : H) {
    // remove do fim/inicio quem ficou redundante por causa de h
    while (dq.size() > 1 && h.out(hpInter(dq[dq.size() - 1], dq[dq.size() - 2]))) dq.pop_back();
    while (dq.size() > 1 && h.out(hpInter(dq[0], dq[1]))) dq.pop_front();
    if (!dq.empty() && fabsl(cross(h.d, dq.back().d)) < EPS) {  // paralelas
      if (dot(h.d, dq.back().d) < 0) return {};  // direcoes opostas: vazio (ou faixa degenerada)
      if (h.out(dq.back().p)) dq.pop_back();     // h e mais restritivo: substitui
      else continue;                              // h e redundante
    }
    dq.push_back(h);
  }
  while (dq.size() > 2 && dq[0].out(hpInter(dq[dq.size() - 1], dq[dq.size() - 2]))) dq.pop_back();
  while (dq.size() > 2 && dq.back().out(hpInter(dq[0], dq[1]))) dq.pop_front();
  if (dq.size() < 3) return {};
  vector<Pd> r;
  for (size_t i = 0; i < dq.size(); i++) r.push_back(hpInter(dq[i], dq[(i + 1) % dq.size()]));
  return r;
}

/*LATEX_DESC_BEGIN***************************
-> **Intersecao de semiplanos (HPI) O(n log n)**
Devolve os vertices CCW do poligono convexo que e a intersecao dos semiplanos a esquerda
de cada reta p -> p + d.

Complexidade: O(n log n)
Uso:
  vector<HP> H;
  H.push_back(HP(Pd(px,py), Pd(dx,dy)));  // esquerda da reta p + t*d
  vector<Pd> poly = hpi(H);               // vazio se vazia/degenerada
  // regiao ilimitada: adicione 4 semiplanos de uma caixa grande (ex.: 1e9)

* Sobre o codigo:
  Ordena por angulo e mantem um deque. Ao inserir h, remove do fim e do inicio os semiplanos
  cuja intersecao ficou fora de h. Trata paralelas (direcoes opostas => vazio; mesma direcao
  => fica o mais restritivo). No fim, fecha o deque e calcula os vertices por intersecao.

* Problemas e reducoes:
  + Intersecao de semiplanos em geral.
  + Kernel de poligono estrelado: um semiplano por aresta, do lado interno.
  + Viabilidade de LP 2D / regiao factivel de restricoes lineares.
  + "Regiao onde todas as condicoes valem".
  + Recorte incremental: equivalente a aplicar cutPoly (polygon_cut.cpp) em sequencia.

Cuidados: EPS = 1e-9. Intersecao de area ~0 (ponto/segmento) pode sair vazia ou com < 3
  pontos. Coordenadas grandes (1e9) com long double ok. Para viabilidade exata com inteiros
  use fracoes (nao feito aqui).
Catalogo: Geometria.
Digitacao: 44 linhas | dificil. Atalho: hpInter e chamado 4 vezes com pares do deque;
  extrair a intersecao de duas arestas do deque em um helper.
*****************************LATEX_DESC_END*/
