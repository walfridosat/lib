// Z-function
//
// O que faz: z[i] = LCP de s e s[i..]. Busca de padrao, contagem de prefixos.
// Quando usar: Catalogo > Strings ("Padrao em texto", "Concatenar com separador",
//   "Z-function para contar prefixos").
// Complexidade: O(n).
// Uso: vector<int> z = zf(s); z[0] = n por convencao.
//   zfind(t, p) = posicoes de p em t (0-based).
//   cnt_prefix(s)[L] = nro de ocorrencias (como substring) do prefixo de tamanho L, L=1..n.
// Cuidados: separador do concatenado deve ser char que nao aparece.
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
