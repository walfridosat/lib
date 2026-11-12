// Manacher (palindromos)
//
// O que faz: d1[i] = nro de palindromos de tamanho impar centrados em i (raio incl. centro);
//   d2[i] = nro de palindromos de tamanho par centrados entre i-1 e i.
//   Tambem: nro de palindromos que comecam / terminam em cada posicao, maior palindromo,
//   teste de substring palindromo em O(1).
// Quando usar: Catalogo > Strings ("Palindromos", "Manacher + diferencas",
//   "Pares de palindromos adjacentes").
// Complexidade: O(n).
// Uso: Manacher M(s); M.is_pal(l,r) para s[l..r) (r exclusivo);
//   M.st[i] = nro de palindromos que comecam em i; M.en[i] = que terminam em i;
//   M.best_l, M.best_len = (inicio, tamanho) do maior palindromo; M.total().
//   Pares adjacentes: sum_i en[i]*st[i+1].
// Cuidados: nao serve com updates de char (use hash). d1[i]>=1 sempre.
struct Manacher {
	int n; vector<int> d1, d2, st, en;
	int best_l = 0, best_len = 0;
	Manacher(const string& s) : n(s.size()), d1(n), d2(n), st(n + 2, 0), en(n + 2, 0) {
		for (int i = 0, l = 0, r = -1; i < n; i++) { // impares
			int k = i > r ? 1 : min(d1[l + r - i], r - i + 1);
			while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
			d1[i] = k;
			if (i + k - 1 > r) l = i - k + 1, r = i + k - 1;
		}
		for (int i = 0, l = 0, r = -1; i < n; i++) { // pares
			int k = i > r ? 0 : min(d2[l + r - i + 1], r - i + 1);
			while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
			d2[i] = k;
			if (i + k - 1 > r) l = i - k, r = i + k - 1;
		}
		// cada centro soma 1 em um intervalo de inicios e em um de fins (array de diferencas)
		for (int i = 0; i < n; i++) {
			int k = d1[i];
			st[i - k + 1]++; st[i + 1]--; // inicios em [i-k+1, i]
			en[i]++; en[i + k]--;         // fins em [i, i+k-1]
			if (2 * k - 1 > best_len) best_len = 2 * k - 1, best_l = i - k + 1;
			k = d2[i];
			if (k) {
				st[i - k]++; st[i]--;       // inicios em [i-k, i-1]
				en[i]++; en[i + k]--;       // fins em [i, i+k-1]
				if (2 * k > best_len) best_len = 2 * k, best_l = i - k;
			}
		}
		for (int i = 1; i < n; i++) st[i] += st[i - 1], en[i] += en[i - 1];
	}
	bool is_pal(int l, int r) { // s[l..r)
		int len = r - l;
		if (len <= 0) return true;
		if (len & 1) return d1[l + len / 2] >= len / 2 + 1;
		return d2[l + len / 2] >= len / 2;
	}
	ll total() { ll t = 0; for (int i = 0; i < n; i++) t += d1[i] + d2[i]; return t; }
};
