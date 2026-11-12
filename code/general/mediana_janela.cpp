// Mediana dinamica em janela deslizante (dois multisets)
//
// O que faz: mantem mediana e soma |a_i - mediana| de um multiconjunto com inserir/remover.
// Quando usar: "custo de igualar elementos a mediana em janela", "mediana de cada janela de tamanho k".
//              Catalogo > Arrays e guloso (Mediana, Mediana dinamica, Tornar consecutivos)
// Complexidade: O(log n) por operacao
// Uso: MedianSet m; m.add(x); m.rem(x); m.median() (mediana inferior); m.cost() = sum |x - mediana|.
//      slidingMedianCost(a, k) -> vetor com o custo de cada janela de tamanho k.
// Cuidados: rem exige x presente; mediana inferior (elemento de posicao (n-1)/2 em ordem). Para progressao +1
//           use b_i = a_i - i antes. Somas em ll.
struct MedianSet {
    multiset<ll> lo, hi;      // lo guarda a metade menor (tamanho = ceil(n/2)), hi a maior
    ll slo = 0, shi = 0;
    void bal() {
        while (lo.size() > hi.size() + 1) { auto it = prev(lo.end()); slo -= *it; shi += *it; hi.insert(*it); lo.erase(it); }
        while (lo.size() < hi.size()) { auto it = hi.begin(); shi -= *it; slo += *it; lo.insert(*it); hi.erase(it); }
    }
    void add(ll x) {
        if (lo.empty() || x <= *prev(lo.end())) lo.insert(x), slo += x; else hi.insert(x), shi += x;
        bal();
    }
    void rem(ll x) {
        auto it = lo.find(x);
        if (it != lo.end()) lo.erase(it), slo -= x;
        else hi.erase(hi.find(x)), shi -= x;
        bal();
    }
    ll median() const { return *prev(lo.end()); }
    ll cost() const {                 // sum |x - med|
        ll m = median();
        return m * (ll)lo.size() - slo + shi - m * (ll)hi.size();
    }
};
vector<ll> slidingMedianCost(const vector<ll>& a, int k) {
    MedianSet m; vector<ll> res;
    for (int i = 0; i < (int)a.size(); i++) {
        m.add(a[i]);
        if (i >= k) m.rem(a[i - k]);
        if (i >= k - 1) res.push_back(m.cost());
    }
    return res;
}
