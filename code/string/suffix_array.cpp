// Suffix array + LCP + RMQ de LCP
//
// O que faz: sa (sufixos ordenados), rnk, lcp[i] = LCP(sa[i-1], sa[i]) (lcp[0]=0),
//   LCP de dois sufixos quaisquer em O(1) (sparse table), substrings distintas,
//   k-esima substring distinta, comparacao de substrings.
// Quando usar: Catalogo > Strings ("Substrings distintas, k-esima substring",
//   "LCP de dois sufixos quaisquer", "SA: ...", "Maior substring comum de k strings").
// Complexidade: O(n log n) construcao; consulta de LCP O(1).
// Uso: SuffixArray S(s); S.sa, S.rnk, S.lcp (0-based);
//   S.query(i, j) = LCP dos sufixos que comecam em i e j (i != j; i==j devolve n-i);
//   S.distinct() = nro de substrings distintas;
//   S.kth(k) = k-esima (1-based) substring distinta em ordem lexicografica (string);
//   S.cmp(a,b,c,d) compara s[a..b) com s[c..d) (-1,0,1).
//   Varias strings: concatene com separadores distintos (chars < ' ' ou >= 'a' livres)
//   e limite o LCP, ou use janela deslizante sobre lcp (min da janela com todas as cores).
// Cuidados: chars da string devem ser >= 1 (0 e o sentinela interno).
//   Menor substring que ocorre >=k vezes etc: ver catalogo (janela de k-1 lcps).
struct SuffixArray {
	int n; string s;
	vector<int> sa, rnk, lcp;
	vector<vector<int>> sp; // sparse table sobre lcp (min)
	SuffixArray(const string& s_) : n(s_.size()), s(s_) {
		vector<int> t(n + 1, 0);
		for (int i = 0; i < n; i++) t[i] = (unsigned char)s[i];
		int lim = 256, N = n + 1;
		vector<int> x(t), y(N), ws(max(N, lim)), sa2(N), lc(N), rk(N);
		iota(sa2.begin(), sa2.end(), 0);
		// doubling com counting sort (estilo KACTL); sa2[0] = sentinela
		for (int j = 0, p = 0; p < N; j = max(1, j * 2), lim = p) {
			p = j; iota(y.begin(), y.end(), N - j);
			for (int i = 0; i < N; i++) if (sa2[i] >= j) y[p++] = sa2[i] - j;
			fill(ws.begin(), ws.end(), 0);
			for (int i = 0; i < N; i++) ws[x[i]]++;
			for (int i = 1; i < lim; i++) ws[i] += ws[i - 1];
			for (int i = N; i--;) sa2[--ws[x[y[i]]]] = y[i];
			swap(x, y); p = 1; x[sa2[0]] = 0;
			for (int i = 1; i < N; i++) {
				int a = sa2[i - 1], b = sa2[i];
				x[b] = (y[a] == y[b] && (a + j < N ? y[a + j] : -1) == (b + j < N ? y[b + j] : -1)) ? p - 1 : p++;
			}
		}
		for (int i = 1; i < N; i++) rk[sa2[i]] = i;
		for (int i = 0, k = 0, j; i < n; lc[rk[i++]] = k)
			for (k && k--, j = sa2[rk[i] - 1]; t[i + k] == t[j + k]; k++);
		sa.assign(sa2.begin() + 1, sa2.end());
		lcp.assign(n, 0);
		for (int i = 1; i < n; i++) lcp[i] = lc[i + 1];
		rnk.assign(n, 0);
		for (int i = 0; i < n; i++) rnk[sa[i]] = i;
		int L = 1; while ((1 << L) <= n) L++;
		sp.assign(L, vector<int>(n));
		sp[0] = lcp;
		for (int k = 1; k < L; k++)
			for (int i = 0; i + (1 << k) <= n; i++)
				sp[k][i] = min(sp[k - 1][i], sp[k - 1][i + (1 << (k - 1))]);
	}
	int query(int i, int j) { // LCP dos sufixos i e j
		if (i == j) return n - i;
		int a = rnk[i], b = rnk[j];
		if (a > b) swap(a, b);
		a++; // min de lcp[a..b]
		int k = 31 - __builtin_clz(b - a + 1);
		return min(sp[k][a], sp[k][b - (1 << k) + 1]);
	}
	ll distinct() {
		ll r = (ll)n * (n + 1) / 2;
		for (int i = 1; i < n; i++) r -= lcp[i];
		return r;
	}
	string kth(ll k) { // k-esima substring distinta (1-based), "" se nao existe
		for (int i = 0; i < n; i++) {
			ll c = n - sa[i] - lcp[i]; // novas substrings: tamanhos lcp[i]+1 .. n-sa[i]
			if (k <= c) return s.substr(sa[i], lcp[i] + k);
			k -= c;
		}
		return "";
	}
	int cmp(int a, int b, int c, int d) { // s[a..b) vs s[c..d)
		int l = query(a, c), la = b - a, lb = d - c;
		if (l >= min(la, lb)) return la == lb ? 0 : (la < lb ? -1 : 1);
		return s[a + l] < s[c + l] ? -1 : 1;
	}
};
