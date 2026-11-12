// Subconjuntos por mascara - todos os 2^n subconjuntos
vector<vector<ll>> subsets(vector<ll>& nums) {
    ll n = nums.size();
    vector<vector<ll>> subsets;
    
    ll totalSubsets = 1 << n; 
    
    for (ll mask = 0; mask < totalSubsets; ++mask) {
        vector<ll> subset;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                subset.push_back(nums[i]);
            }
        }
        subsets.push_back(subset);
    }
    
    return subsets;
}
/*LATEX_DESC_BEGIN***************************
-> **Geracao de Subconjuntos**
subsets(a) devolve os 2^n subconjuntos de a como vetores, preservando a ordem.

Complexidade: O(2^n * n) tempo e memoria
Uso:
  auto ss = subsets(a);  // a e copiado

* Sobre o codigo:
  Para cada mask de 0 a 2^n-1, inclui nums[i] quando o bit i esta ligado.

* Problemas e reducoes:
  + Brute force com n <= 20; para DP de mascara use o laco direto sem materializar.

Cuidados: n >= 31 estoura 1 << n e a memoria; para n grande conte ou itere sob demanda.
Catalogo: Construtivos e interativos (brute force pequeno)
Digitacao: 15 linhas | facil.
*****************************LATEX_DESC_END*/
