// Fecho convexo - monotone chain (versao simples)
using P = pair<int, int>;

int cross(const P &O, const P &A, const P &B) {
    return (A.first - O.first) * (B.second - O.second) - 
           (A.second - O.second) * (B.first - O.first);
}

vector<P> convexHull(vector<P> points) {
    if (points.size() <= 1) return points;

    sort(points.begin(), points.end());
    vector<P> hull;

    for (const auto &p : points) {
        while (hull.size() >= 2 && cross(hull[hull.size()-2], hull.back(), p) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }

    int lower_size = hull.size();
    for (int i = points.size() - 2; i >= 0; --i) {
        while ((int)hull.size() > lower_size && cross(hull[hull.size()-2], hull.back(), points[i]) <= 0)
            hull.pop_back();
        hull.push_back(points[i]);
    }

    hull.pop_back();
    return hull;
}
/*LATEX_DESC_BEGIN***************************
-> **Fecho convexo - monotone chain (versao simples)**
Devolve o hull em ordem anti-horaria, sem pontos colineares nas arestas, usando <= 0.
P = pair<int,int>; a mesma ideia vale para ll.

Complexidade: O(n log n); memoria O(n)
Uso:
  vector<P> h = convexHull(p);   // hull anti-horario

* Sobre o codigo:
  Ordena os pontos, monta a cadeia inferior e depois a superior com um laco while que remove
  quem faz curva a direita ou e colinear (cross <= 0). O ultimo ponto repete o primeiro e e
  removido no fim.

* Problemas e reducoes:
  + Fecho convexo de um conjunto de pontos.
  + Area do hull: aplique shoelace no resultado.
  + Base para calipers, Minkowski e diametro.
  + Ponto dentro do hull: use inConvex de polygon.cpp.

Cuidados: remova duplicatas antes (ou aceite hull degenerado). Para manter colineares troque
  <= 0 por < 0. Compare areas com cross em ll, nao em int (aqui cross e int). Prefira
  hull_andrew.cpp, que e a versao corrigida e com opcao de manter colineares.
Catalogo: Geometria.
Digitacao: 23 linhas | facil. Atalho: duplica hull_andrew.cpp; manter so a versao de la e
  apagar este arquivo.
*****************************LATEX_DESC_END*/
