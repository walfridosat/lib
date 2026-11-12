// Duval (fatoracao de Lyndon) e rotacao minima
vector<pair<int, int>> duval(const string& s) {
	int n = s.size();
	vector<pair<int, int>> r;
	for (int i = 0; i < n;) {
		int j = i + 1, k = i;
		while (j < n && s[k] <= s[j]) { k = s[k] < s[j] ? i : k + 1; j++; }
		while (i <= k) { r.push_back({i, i + (j - k)}); i += j - k; }
	}
	return r;
}
int min_rot(const string& s) {
	int n = s.size(), i = 0, j = 1, k = 0;
	while (i < n && j < n && k < n) {
		char a = s[(i + k) % n], b = s[(j + k) % n];
		if (a == b) { k++; continue; }
		if (a > b) i += k + 1; else j += k + 1;
		if (i == j) j++;
		k = 0;
	}
	return min(i, j);
}
string canon(const string& s) {
	int i = min_rot(s);
	return s.substr(i) + s.substr(0, i);
}
/*LATEX_DESC_BEGIN***************************
-> **Duval (fatoracao de Lyndon) e rotacao minima**
duval(s) fatora s em palavras de Lyndon nao-crescentes; min_rot(s) devolve o
inicio da menor rotacao lexicografica; canon(s) e a string da menor rotacao.
0-indexed.

Complexidade: O(n).
Uso:
  duval(s) -> vector<pair<int,int>> fatores [ini, fim) em ordem;
  min_rot(s) -> indice i da menor rotacao (menor i em empate);
  canon(s) -> string da menor rotacao;
  pulseira: min(canon(s), canon(reverse(s))).

* Sobre o codigo:
  duval compara s[k] com s[j], avancando k enquanto nao-decrescente; ao achar
  queda, emite os fatores e avanca i. min_rot usa dois ponteiros (i, j, k)
  sem dobrar a string; ao comparar rotacoes, descarta a maior.

* Problemas e reducoes:
  + Fatoracao de Lyndon: duval(s).
  + Rotacao minima / menor string ciclica: min_rot ou canon(s).
  + Pulseira (bracelete): min(canon(s), canon(reverso)).
  + Comparar rotacoes sem duplicar a string: min_rot.

Cuidados: min_rot usa o algoritmo dos dois ponteiros (i, j, k), nao precisa
  dobrar a string. 0-indexed.
Catalogo: Strings (Lyndon / Duval, rotacao minima, pulseira, rotacao/ciclico
  -> duplique a string).
Digitacao: 25 linhas | facil. Atalho: ok.
*****************************LATEX_DESC_END*/
