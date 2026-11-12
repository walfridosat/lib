// Compressao de coordenadas - valores arbitrarios para ranks 0..k-1
template<class T> struct Comp {
    vector<T> v;
    Comp(vector<T> a = {}) : v(a) { build(); }
    void add(T x) { v.push_back(x); }
    void build() { sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end()); }
    int id(T x) const { return lower_bound(v.begin(), v.end(), x) - v.begin(); }
    int lb(T x) const { return lower_bound(v.begin(), v.end(), x) - v.begin(); }
    int ub(T x) const { return upper_bound(v.begin(), v.end(), x) - v.begin(); }
    T val(int i) const { return v[i]; }
    int size() const { return v.size(); }
};
template<class T> vector<T> compress(vector<T>& a) {
    vector<T> s = a; sort(s.begin(), s.end()); s.erase(unique(s.begin(), s.end()), s.end());
    for (auto& x : a) x = lower_bound(s.begin(), s.end(), x) - s.begin();
    return s;
}
/*LATEX_DESC_BEGIN***************************
-> **Compressao de Coordenadas**
Mapeia valores arbitrarios para 0..k-1 preservando a ordem (0-indexed).

Complexidade: O(n log n) para construir; O(log n) por consulta
Uso:
  Comp<ll> c(v); int i = c.id(x); T val = c.val(i); int k = c.size();
  c.lb(x) -> quantos valores distintos < x; c.ub(x) -> quantos <= x
  vector<T> vals = compress(a);  // troca a[i] pelo rank, devolve os distintos

* Sobre o codigo:
  Comp guarda os valores ordenados e unicos; busca binaria da o rank.
  add(x) so pode ser usado antes de build(); compress reordena o vetor in-place.

* Problemas e reducoes:
  + BIT/segtree/DSU sobre valores grandes: comprima antes de indexar.
  + Contar inversoes e sweep com coordenadas grandes.
  + Fenwick de frequencia: id(x) e o indice da posicao.

Cuidados: id(x) exige x presente (use lb se nao tiver certeza); add() so vale antes de build().
Catalogo: Arrays e guloso
Digitacao: 16 linhas | facil.
*****************************LATEX_DESC_END*/
