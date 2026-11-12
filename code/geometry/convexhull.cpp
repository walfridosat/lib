// Fecho convexo (monotone chain)
//
// O que faz: convexHull(pontos) devolve o hull em ordem anti-horaria, sem pontos
//            colineares nas arestas (usa <= 0 para remover colineares).
// Quando usar: Catalogo > Geometria (hull). Gatilhos: "fecho convexo", area do hull,
//            ponto dentro do hull, calipers, Minkowski.
// Complexidade: O(n log n) (ordenacao); memoria O(n).
// Uso: vector<P> h = convexHull(p); P = pair<int,int>; para ll use o mesmo codigo com ll.
// Cuidados: remova duplicatas se existirem (ou aceite hull degenerado); para manter
//            colineares troque <= 0 por < 0; compare areas com cross em ll, nao em int.
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