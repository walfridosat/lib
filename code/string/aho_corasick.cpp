// Aho-Corasick - automato de varios padroes
struct AhoCorasick {
	static const int K = 26;
	vector<array<int, K>> go;
	vector<int> link, dict, term, order, val; // term[v] = id de um padrao que termina em v (-1 se nenhum)
	vector<char> bad;
	vector<int> pid; // no de cada padrao
	AhoCorasick() { newnode(); }
	int newnode() {
		array<int, K> a; a.fill(-1);
		go.push_back(a); link.push_back(0); dict.push_back(0);
		term.push_back(-1); val.push_back(0); bad.push_back(0);
		return go.size() - 1;
	}
	int add(const string& p) {
		int v = 0;
		for (char ch : p) {
			int c = ch - 'a';
			if (go[v][c] < 0) { int u = newnode(); go[v][c] = u; }
			v = go[v][c];
		}
		pid.push_back(v);
		if (term[v] < 0) term[v] = pid.size() - 1;
		return pid.size() - 1;
	}
	void build() { // BFS
		queue<int> q;
		order.clear();
		for (int c = 0; c < K; c++) {
			int u = go[0][c];
			if (u < 0) go[0][c] = 0;
			else { link[u] = 0; q.push(u); }
		}
		while (!q.empty()) {
			int v = q.front(); q.pop();
			order.push_back(v);
			dict[v] = term[link[v]] >= 0 ? link[v] : dict[link[v]];
			bad[v] = bad[v] || term[v] >= 0 || bad[link[v]];
			val[v] += val[link[v]];
			for (int c = 0; c < K; c++) {
				int u = go[v][c];
				if (u < 0) go[v][c] = go[link[v]][c];
				else { link[u] = go[link[v]][c]; q.push(u); }
			}
		}
	}
	vector<ll> count(const string& t) { // ocorrencias de cada padrao em t
		vector<ll> cnt(go.size(), 0);
		int v = 0;
		for (char ch : t) { v = go[v][ch - 'a']; cnt[v]++; }
		for (int i = (int)order.size() - 1; i >= 0; i--) { // soma pela link tree (ordem BFS invertida)
			int u = order[i];
			cnt[link[u]] += cnt[u];
		}
		vector<ll> r(pid.size());
		for (int i = 0; i < (int)pid.size(); i++) r[i] = cnt[pid[i]];
		return r;
	}
};
/*LATEX_DESC_BEGIN***************************
-> **Aho-Corasick - automato de varios padroes**
Automato de varios padroes. Cada no tem transicao completa go[v][c], link
(maior sufixo proprio que e prefixo de algum padrao), dict link (proximo
terminal na cadeia de links) e contagem de ocorrencias. 0-indexed.

Complexidade: O(Soma|p| * 26 + |T|).
Uso:
  AhoCorasick ac; int id = ac.add(p); ac.build();
  vector<ll> occ = ac.count(t); // occ[i] = ocorrencias do padrao i
  ac.go[v][c], ac.bad[v], ac.val[v];
  listar padroes terminando em v: for (u = term(v) ? v : dict[v]; u > 0; u = dict[u]).
  Padroes iguais compartilham no; cada id recebe o mesmo valor.

* Sobre o codigo:
  add insere na trie e guarda pid[]. build faz BFS: preenche transicoes que
  faltam com go[link[v]][c] e propaga dict, bad e val pelo link. count anda
  no texto e soma as ocorrencias pela link tree em ordem BFS inversa.

* Problemas e reducoes:
  + Muitos padroes em um texto: automato; occ[i] por padrao.
  + DP em automato: go[v][c] como transicao, bad[v] proibe estados que
    contem algum padrao, val[v] soma ganhos dos sufixos.
  + Link tree / contar ocorrencias: soma de cnt na arvore de links.
  + Dict link: pular direto para o proximo padrao que termina no sufixo.
  + Substituicao/filtro de palavras: teste bad[v] ao andar no texto.

Cuidados: alfabeto 'a'..'z' (mude K). build() obrigatorio antes de usar go.
  Padroes vazios nao sao suportados. 0-indexed.
Catalogo: Strings (muitos padroes -> Aho-Corasick, AC: link tree, AC em DP,
  AC com ganhos, dict link).
Digitacao: 58 linhas | media. Atalho: ok.
*****************************LATEX_DESC_END*/
