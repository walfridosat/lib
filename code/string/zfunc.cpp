// Z-function
vector<int> zf(const string& s) {
	int n = s.size();
	vector<int> z(n, 0);
	if (n) z[0] = n;
	for (int i = 1, l = 0, r = 0; i < n; i++) { // [l,r) = janela mais a direita que casa com prefixo
		if (i < r) z[i] = min(r - i, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
		if (i + z[i] > r) l = i, r = i + z[i];
	}
	return z;
}
vector<int> zfind(const string& t, const string& p) {
	string u = p + '\x01' + t;
	vector<int> z = zf(u), r;
	int m = p.size();
	for (int i = m + 1; i < (int)u.size(); i++)
		if (z[i] >= m) r.push_back(i - m - 1);
	return r;
}
vector<ll> cnt_prefix(const string& s) { // c[L] = #{i: z[i]>=L} (i=0 incluso)
	int n = s.size();
	vector<int> z = zf(s);
	vector<ll> c(n + 2, 0);
	for (int i = 0; i < n; i++) c[z[i]]++;
	for (int L = n - 1; L >= 1; L--) c[L] += c[L + 1]; // soma de sufixo
	return c;
}
/*LATEX_DESC_BEGIN***************************
-> **Z-function**
z[i] = LCP de s e s[i..]. Busca de padrao e contagem de prefixos. 0-indexed.

Complexidade: O(n).
Uso:
  vector<int> z = zf(s); // z[0] = n por convencao
  zfind(t, p) -> posicoes iniciais de p em t;
  cnt_prefix(s)[L] -> ocorrencias (como substring) do prefixo de tamanho L,
  L = 1..n.

* Sobre o codigo:
  Mantem [l, r) como a janela mais a direita que casa com o prefixo; dentro
  dela z[i] = min(r - i, z[i - l]) e depois estende. zfind concatena
  p + separador + t e filtra z[i] >= |p|.

* Problemas e reducoes:
  + Padrao em texto: zfind(t, p).
  + Contar ocorrencias de cada prefixo: cnt_prefix.
  + Prefixo que tambem e sufixo: compare z[i] com n - i.
  + Compressao/periodo: primeiro i > 0 com i + z[i] == n.
  + Comparar duas strings concatenando com separador.

Cuidados: separador do concatenado deve ser char que nao aparece. 0-indexed.
Catalogo: Strings (padrao em texto, concatenar com separador, Z-function para
  contar prefixos).
Digitacao: 27 linhas | facil. Atalho: ok.
*****************************LATEX_DESC_END*/
