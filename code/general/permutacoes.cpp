// Geracao de permutacoes - backtracking de todas as n!
void backtrack(vector<ll>& nums, vector<bool>& used, vector<ll>& current, vector<vector<ll>>& result) {
    if (current.size() == nums.size()) {
        result.push_back(current);
        return;
    }

    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            used[i] = true;
            current.push_back(nums[i]);

            backtrack(nums, used, current, result);

            current.pop_back();
            used[i] = false;
        }
    }
}

vector<vector<ll>> generatePermutations(vector<ll>& nums) {
    vector<vector<ll>> result;
    vector<ll> current;
    vector<bool> used(nums.size(), false);
    backtrack(nums, used, current, result);
    return result;
}
/*LATEX_DESC_BEGIN***************************
-> **Geracao de Permutacoes**
generatePermutations(a) devolve todas as permutacoes dos n elementos na ordem
lexicografica dos indices.

Complexidade: O(n! * n) tempo e memoria (todas guardadas)
Uso:
  auto ps = generatePermutations(a);  // a e copiado

* Sobre o codigo:
  backtrack marca used[], empilha o elemento, recursa e desfaz.

* Problemas e reducoes:
  + Brute force com n <= 8-9: gerar todas as permutacoes.

Cuidados: nao trata elementos repetidos (deduplique com set ou exija distintos);
  para n grande apenas conte ou itere sob demanda em vez de guardar tudo.
Catalogo: Construtivos e interativos (brute force pequeno)
Digitacao: 23 linhas | facil.
*****************************LATEX_DESC_END*/
