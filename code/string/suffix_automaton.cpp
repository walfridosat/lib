// Suffix automaton (SAM), incluindo generalizado
//
// O que faz: automato minimo dos sufixos. Estado v = classe de substrings com mesmo
//   endpos; len[v] = maior, len[link[v]]+1 = menor. Fornece: substrings distintas,
//   ocorrencias de cada substring, k-esima substring (distinta ou com multiplicidade),
//   maior substring comum com outra string, menor string que nao e substring.
// Quando usar: Catalogo > Strings ("Substrings distintas, k-esima, ocorrencias", "SAM: ...",
//   "SAM generalizado", "Menor string que NAO e substring", "Suffix tree = SAM do reverso").
// Complexidade: O(n*26) memoria e tempo de construcao.
// Uso: SAM sm; for c in s: sm.extend(c - 'a'); (para varias strings: sm.last = 0 antes de cada)
//   sm.calc_cnt() (so p/ UMA string): cnt[v] = nro de ocorrencias das substrings do estado v.
//   sm.distinct() = nro de substrings distintas (soma len[v]-len[link[v]]).
//   sm.kth(k, repete): k-esima (1-based) substring lexicografica; repete=true conta
//   multiplicidade (precisa calc_cnt). Devolve "" se k > total.
//   sm.lcs(t): maior substring comum entre a string do SAM e t.
//   sm.min_not_sub(): menor (e lex menor) string que nao e substring.
// Cuidados: no generalizado nao use cnt do calc_cnt sem adaptar (prefixos de varias
//   strings); extend ja trata transicao existente (sem clone duplicado). Alfabeto K=26.
//   O estado inicial e 0; len[0]=0, link[0]=-1.
struct SAM {
	static const int K = 26;
	vector<array<int, K>> nx;
	vector<int> len, link, cnt;
	vector<char> clone;
	int last = 0;
	SAM() { nx.push_back(array<int, K>()); nx[0].fill(-1); len.push_back(0); link.push_back(-1); clone.push_back(0); }
	int mk(int l, int lk, bool cl) {
		array<int, K> a; a.fill(-1);
		nx.push_back(a); len.push_back(l); link.push_back(lk); clone.push_back(cl);
		return nx.size() - 1;
	}
	void extend(int c) {
		if (nx[last][c] >= 0) { // generalizado: transicao ja existe
			int p = last, q = nx[p][c];
			if (len[q] == len[p] + 1) { last = q; return; }
			int cl = mk(len[p] + 1, link[q], true);
			nx[cl] = nx[q];
			for (; p != -1 && nx[p][c] == q; p = link[p]) nx[p][c] = cl;
			link[q] = cl; last = cl;
			return;
		}
		int cur = mk(len[last] + 1, 0, false);
		int p = last;
		for (; p != -1 && nx[p][c] < 0; p = link[p]) nx[p][c] = cur;
		if (p == -1) link[cur] = 0;
		else {
			int q = nx[p][c];
			if (len[p] + 1 == len[q]) link[cur] = q;
			else {
				int cl = mk(len[p] + 1, link[q], true);
				nx[cl] = nx[q];
				for (; p != -1 && nx[p][c] == q; p = link[p]) nx[p][c] = cl;
				link[q] = link[cur] = cl;
			}
		}
		last = cur;
	}
	void calc_cnt() { // ocorrencias (string unica): 1 nos nao-clones, soma pela link tree
		int n = nx.size();
		cnt.assign(n, 0);
		vector<int> ord(n);
		iota(ord.begin(), ord.end(), 0);
		sort(ord.begin(), ord.end(), [&](int a, int b) { return len[a] > len[b]; });
		for (int v = 1; v < n; v++) cnt[v] = clone[v] ? 0 : 1;
		for (int v : ord) if (v > 0) cnt[link[v]] += cnt[v];
	}
	ll distinct() {
		ll r = 0;
		for (int v = 1; v < (int)nx.size(); v++) r += len[v] - len[link[v]];
		return r;
	}
	string kth(ll k, bool repete = false) {
		int n = nx.size();
		vector<ll> d(n, 0); // d[v] = nro de strings (com/sem multiplicidade) comecando em v (inclui vazia)
		vector<int> ord(n);
		iota(ord.begin(), ord.end(), 0);
		sort(ord.begin(), ord.end(), [&](int a, int b) { return len[a] > len[b]; });
		for (int v : ord) { // len maior primeiro: transicoes vao pra len maior -> ja prontos
			d[v] = (v == 0) ? 0 : (repete ? cnt[v] : 1);
			for (int c = 0; c < K; c++) if (nx[v][c] >= 0) d[v] += d[nx[v][c]];
		}
		if (k > d[0]) return "";
		string r; int v = 0;
		while (k > 0) {
			for (int c = 0; c < K; c++) {
				int u = nx[v][c];
				if (u < 0) continue;
				if (k <= d[u]) { r += char('a' + c); v = u; k -= (repete ? cnt[u] : 1); break; }
				k -= d[u];
			}
		}
		return r;
	}
	int lcs(const string& t) { // maior substring comum com t
		int v = 0, l = 0, best = 0;
		for (char ch : t) {
			int c = ch - 'a';
			while (v && nx[v][c] < 0) v = link[v], l = len[v];
			if (nx[v][c] >= 0) v = nx[v][c], l++;
			best = max(best, l);
		}
		return best;
	}
	string min_not_sub() { // menor string (por tamanho, depois lex) que nao e substring
		int n = nx.size();
		vector<int> d(n, 0), nxt(n, -1);
		vector<int> ord(n);
		iota(ord.begin(), ord.end(), 0);
		sort(ord.begin(), ord.end(), [&](int a, int b) { return len[a] > len[b]; });
		for (int v : ord) {
			int best = INT_MAX, bc = -1;
			for (int c = 0; c < K; c++) {
				int x = nx[v][c] < 0 ? 0 : d[nx[v][c]];
				if (x < best) best = x, bc = c;
			}
			d[v] = best + 1; nxt[v] = bc; // c com d de destino minimo (menor c em empate)
		}
		string r; int v = 0;
		while (v >= 0) {
			int c = nxt[v];
			r += char('a' + c);
			v = nx[v][c];
		}
		return r;
	}
};
