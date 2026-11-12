// Inversoes - merge sort e minimo de trocas adjacentes
ll mergeCount(vector<ll>& a, vector<ll>& tmp, int l, int r) {   // ordena a[l, r)
    if (r - l < 2) return 0;
    int m = (l + r) / 2;
    ll c = mergeCount(a, tmp, l, m) + mergeCount(a, tmp, m, r);
    int i = l, j = m, k = l;
    while (i < m || j < r) {
        if (j == r || (i < m && a[i] <= a[j])) tmp[k++] = a[i++];
        else { c += m - i; tmp[k++] = a[j++]; }   // a[j] menor que todos os restantes da esquerda
    }
    copy(tmp.begin() + l, tmp.begin() + r, a.begin() + l);
    return c;
}
ll countInv(vector<ll> a) {
    vector<ll> tmp(a.size());
    return mergeCount(a, tmp, 0, a.size());
}
// mapeia a k-esima ocorrencia de A para a de B
ll minAdjSwaps(const vector<ll>& A, const vector<ll>& B) {
    int n = A.size(); if ((int)B.size() != n) return -1;
    map<ll, vector<int>> pos;
    for (int i = n - 1; i >= 0; i--) pos[B[i]].push_back(i);   // pop_back da a menor posicao primeiro
    vector<ll> p(n);
    for (int i = 0; i < n; i++) {
        auto it = pos.find(A[i]);
        if (it == pos.end() || it->second.empty()) return -1;
        p[i] = it->second.back(); it->second.pop_back();
    }
    return countInv(p);
}
/*LATEX_DESC_BEGIN***************************
-> **Contagem de Inversoes**
Numero de pares i < j com a[i] > a[j]; minimo de trocas adjacentes para A virar B.

Complexidade: O(n log n)
Uso:
  ll inv = countInv(a);              // nao altera a
  ll sw = minAdjSwaps(A, B);         // -1 se nao sao multiconjuntos iguais

* Sobre o codigo:
  mergeCount divide, conta e ordena; quando a[j] entra, conta m - i.
  minAdjSwaps mapeia a k-esima ocorrencia de cada valor de A para a de B e conta inversoes.

* Problemas e reducoes:
  + Minimo de swaps adjacentes para ordenar: countInv.
  + Transformar A em B por swaps adjacentes: minAdjSwaps.
  + Contar pares i < j com condicao (adapte a comparacao no merge).

Cuidados: inversoes estritas; para nao estritas troque > por >= no merge;
  o resultado pode chegar a n^2/2 (use ll).
Catalogo: Arrays e guloso (Contar pares i<j, Minimo de trocas adjacentes de A para B)
Digitacao: 29 linhas | media.
*****************************LATEX_DESC_END*/
