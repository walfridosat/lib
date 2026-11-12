// Prefix function (KMP), automato KMP, bordas, periodos
//
// O que faz: pi[i] = maior borda propria de s[0..i]. Tambem: ocorrencias de p em t,
//   automato aut[i][c], menor periodo, raiz primitiva, todas as bordas,
//   ocorrencias de cada prefixo em s.
// Quando usar: Catalogo > Strings ("Padrao em texto", "Periodo/borda", "Automato KMP",
//   "Prefix function: contar ocorrencias de cada prefixo", "Todas as bordas").
// Complexidade: O(n) (automato O(n*26)).
// Uso: vector<int> p = pi(s); find_all(t, pat) -> posicoes iniciais (0-based) de pat em t;
//   per(s) = menor periodo; prim_root(s) = tamanho da raiz primitiva (s = r^(n/|r|));
//   borders(s) = tamanhos das bordas proprias em ordem decrescente;
//   occ_prefix(s)[k] = nro de ocorrencias do prefixo de tamanho k em s (k=1..n);
//   kmp_aut(s) -> aut[i][c], i em 0..n (estado n transita como pi[n-1]).
// Cuidados: pi so e amortizado O(n) sem rollback (desfazer chars exige o automato
//   ou pilha de estados). Automato assume alfabeto 'a'..'z'. s nao vazia em per/borders.
vector<int> pi(const string& s) {
	int n = s.size();
	vector<int> p(n, 0);
	for (int i = 1; i < n; i++) {
		int k = p[i - 1];
		while (k > 0 && s[i] != s[k]) k = p[k - 1];
		if (s[i] == s[k]) k++;
		p[i] = k;
	}
	return p;
}
vector<int> find_all(const string& t, const string& pat) { // ocorrencias de pat em t
	string u = pat + '\x01' + t; // separador que nao aparece
	vector<int> p = pi(u), r;
	int m = pat.size();
	for (int i = m + 1; i < (int)u.size(); i++)
		if (p[i] == m) r.push_back(i - 2 * m);
	return r;
}
int per(const string& s) { // menor periodo
	return s.size() - pi(s).back();
}
int prim_root(const string& s) { // tamanho da raiz primitiva
	int n = s.size(), p = per(s);
	return n % p == 0 ? p : n;
}
vector<int> borders(const string& s) { // todas as bordas proprias, decrescente
	vector<int> p = pi(s), r;
	for (int k = p.back(); k > 0; k = p[k - 1]) r.push_back(k);
	return r;
}
vector<ll> occ_prefix(const string& s) { // r[k] = ocorrencias do prefixo de tam k
	int n = s.size();
	vector<int> p = pi(s);
	vector<ll> c(n + 1, 0);
	for (int i = 0; i < n; i++) c[p[i]]++;
	for (int i = n - 1; i > 0; i--) c[p[i - 1]] += c[i]; // propaga pela cadeia de bordas
	for (int i = 1; i <= n; i++) c[i]++; // a ocorrencia que termina no fim de cada prefixo
	return c;
}
vector<array<int, 26>> kmp_aut(const string& s) { // aut[i][c], i em [0,n]
	int n = s.size();
	vector<int> p = pi(s);
	vector<array<int, 26>> a(n + 1);
	for (int i = 0; i <= n; i++)
		for (int c = 0; c < 26; c++) {
			if (i < n && s[i] - 'a' == c) a[i][c] = i + 1;
			else a[i][c] = i == 0 ? 0 : a[p[i - 1]][c];
		}
	return a;
}
