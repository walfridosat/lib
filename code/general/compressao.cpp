// Compressao de coordenadas
//
// O que faz: mapeia valores arbitrarios para 0..k-1 preservando a ordem.
// Quando usar: BIT/segtree/DSU sobre valores grandes, sweep, contagem de inversoes. Catalogo > Arrays e guloso
// Complexidade: O(n log n) construir, O(log n) por consulta
// Uso: Comp<ll> c(v);  c.id(x) -> indice de x (0-based);  c.val(i) -> valor;  c.size();
//      c.lb(x) = quantos valores distintos < x (serve para x que nao esta no conjunto); c.ub(x) = quantos <= x.
//      compress(a): substitui a[i] pelo rank e devolve o vetor de valores distintos.
// Cuidados: id(x) exige x presente (use lb se nao tiver certeza). add() so vale antes de build().
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
