// Mediana em janela - dois multisets e custo |x - mediana|
struct MedianSet {
    multiset<ll> lo, hi;      // lo = metade menor (ceil(n/2)); hi = maior
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
/*LATEX_DESC_BEGIN***************************
-> **Mediana em Janela**
Mantem a mediana e a soma |x - mediana| de um multiconjunto com inserir/remover.

Complexidade: O(log n) por operacao
Uso:
  MedianSet m; m.add(x); m.rem(x);
  ll med = m.median(); ll c = m.cost();
  vector<ll> cs = slidingMedianCost(a, k);

* Sobre o codigo:
  lo guarda a metade menor (ceil(n/2)) e hi a maior; slo/shi sao as somas.
  bal reequilibra os dois multisets; cost usa a mediana e as somas.

* Problemas e reducoes:
  + Custo de igualar uma janela a mediana: slidingMedianCost.
  + Mediana de cada janela de tamanho k.
  + Tornar consecutivos: use b_i = a_i - i antes.

Cuidados: rem exige x presente; mediana inferior (posicao (n-1)/2);
  somas em ll.
Catalogo: Arrays e guloso (Mediana, Mediana dinamica, Tornar consecutivos)
Digitacao: 32 linhas | media.
*****************************LATEX_DESC_END*/
