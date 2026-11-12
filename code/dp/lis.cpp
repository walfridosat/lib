// LIS em O(n log n)
ll lis(const vector<ll>& a) {
    vector<ll> t;
    for (ll x : a) {
        auto it = lower_bound(t.begin(), t.end(), x);
        if (it == t.end()) t.push_back(x);
        else *it = x;
    }
    return t.size();
}
/*LATEX_DESC_BEGIN***************************
-> **LIS em O(n log n)**
Tamanho da maior subsequencia estritamente crescente de a, 0-based.

Complexidade: O(n log n) tempo, O(n) memoria.
Uso:
  ll k = lis(a);

* Sobre o codigo:
  t[i] guarda o menor final possivel de uma subsequencia crescente de tamanho
  i+1. Para cada x, lower_bound acha a primeira posicao com t >= x e troca.
  O tamanho final de t e a LIS.

* Problemas e reducoes:
  + Maior subsequencia crescente (LIS).
  + LDS: rode no array revertido.
  + Paciencia e ordenacao por um criterio com desempate no outro.
  + Cobertura minima por sequencias nao crescentes (Dilworth).

Cuidados: lower_bound = estritamente crescente; upper_bound = nao decrescente.
Catalogo: DP (LIS).
Digitacao: 9 linhas | facil.
*****************************LATEX_DESC_END*/
