// Prefix function (KMP), automato, bordas e periodos
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
/*LATEX_DESC_BEGIN***************************
-> **Prefix function (KMP), automato, bordas e periodos**
pi[i] = maior borda propria de s[0..i]. Tambem: ocorrencias de p em t,
automato aut[i][c], menor periodo, raiz primitiva, todas as bordas e
ocorrencias de cada prefixo. 0-indexed.

Complexidade: O(n) (automato O(n*26)).
Uso:
  vector<int> p = pi(s);
  find_all(t, pat) -> posicoes iniciais de pat em t;
  per(s) -> menor periodo; prim_root(s) -> tamanho da raiz primitiva;
  borders(s) -> bordas proprias em ordem decrescente;
  occ_prefix(s)[k] -> ocorrencias do prefixo de tamanho k (k = 1..n);
  kmp_aut(s) -> aut[i][c], i em 0..n (estado n transita como pi[n-1]).

* Sobre o codigo:
  pi segue a borda anterior e cai por pi[k-1] enquanto nao casa; amortizado
  O(n). find_all concatena pat + separador + t e procura pi == |pat|.
  occ_prefix conta pela cadeia de bordas e soma 1 por prefixo. kmp_aut monta
  as transicoes completas a partir de pi.

* Problemas e reducoes:
  + Padrao em texto: find_all ou pi concatenado.
  + Menor periodo: n - pi[n-1]; raiz primitiva se n % periodo == 0.
  + Todas as bordas: cadeia p.back(), p[p.back()-1], ...
  + Ocorrencias de cada prefixo: occ_prefix.
  + Automato KMP para DP/transicoes em texto: kmp_aut.
  + Verificar se s e periodica e qual o bloco: per/prim_root.

Cuidados: pi so e amortizado O(n) sem rollback (desfazer chars exige o
  automato ou pilha de estados). Automato assume alfabeto 'a'..'z'. s nao
  vazia em per/borders. 0-indexed.
Catalogo: Strings (padrao em texto, periodo/borda, automato KMP, prefix
  function: contar ocorrencias de cada prefixo, todas as bordas).
Digitacao: 51 linhas | facil. Atalho: ok.
*****************************LATEX_DESC_END*/
