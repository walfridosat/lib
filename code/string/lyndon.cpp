// Duval (fatoracao de Lyndon) e rotacao minima
//
// O que faz: duval(s) fatora s em palavras de Lyndon nao-crescentes; min_rot(s) devolve
//   o inicio da menor rotacao lexicografica; canon(s) a string da menor rotacao.
// Quando usar: Catalogo > Strings ("Lyndon / Duval", "Rotacao minima", "Pulseira",
//   "Rotacao/ciclico -> duplique a string").
// Complexidade: O(n).
// Uso: duval(s) -> vector<pair<int,int>> fatores [ini, fim) em ordem;
//   min_rot(s) -> indice i tal que s[i..]+s[..i) e minima (menor i em empate);
//   canon(s) = rotacao minima; pulseira: min(canon(s), canon(reverse(s))).
// Cuidados: min_rot usa o algoritmo dos dois ponteiros (i, j, k), nao precisa dobrar a string.
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
