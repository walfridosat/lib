// Sequencia de de Bruijn - toda string de tamanho n sobre k simbolos
vector<int> deBruijn(int k, int n) {
    vector<int> a(k * n, 0), seq;
    function<void(int, int)> db = [&](int t, int p) {
        if (t > n) { if (n % p == 0) for (int i = 1; i <= p; i++) seq.push_back(a[i]); }
        else {
            a[t] = a[t - p]; db(t + 1, p);
            for (int j = a[t - p] + 1; j < k; j++) a[t] = j, db(t + 1, t);
        }
    };
    db(1, 1);
    return seq;
}
/*LATEX_DESC_BEGIN***************************
-> **Sequencia de de Bruijn**
Vetor ciclico de tamanho k^n com toda string de tamanho n sobre {0..k-1} exatamente
uma vez. Para string linear, use s + os primeiros n-1 elementos (k^n + n - 1).

Complexidade: O(k^n)
Uso:
  vector<int> s = deBruijn(k, n);  // ciclico

* Sobre o codigo:
  Algoritmo FKM: gera as palavras de Lyndon por recursao e concatena.
  a[t] = a[t - p] repete o prefixo; o laco seguinte incrementa e corta a periodicidade.

* Problemas e reducoes:
  + Cofre/PIN: menor string que contem todas as senhas de n digitos.
  + Menor string com todas as mascaras de n bits: k = 2.

Cuidados: a saida cresce como k^n; para n = 1 devolve 0..k-1.
Catalogo: Construtivos (de Bruijn)
Digitacao: 12 linhas | media.
*****************************LATEX_DESC_END*/
