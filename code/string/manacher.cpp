// Manacher (palindromos)
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
/*LATEX_DESC_BEGIN***************************
-> **Manacher (palindromos)**
d1[i] = numero de palindromos de tamanho impar centrados em i (raio incl.
centro); d2[i] = numero de palindromos de tamanho par centrados entre i-1
e i. Tambem conta palindromos que comecam/terminam em cada posicao, acha o
maior palindromo e testa substring palindroma em O(1). 0-indexed.

Complexidade: O(n).
Uso:
  Manacher M(s);
  M.is_pal(l, r) -> s[l..r) e palindromo;
  M.st[i] -> palindromos que comecam em i; M.en[i] -> que terminam em i;
  M.best_l, M.best_len -> maior palindromo; M.total();
  Pares adjacentes: sum_i en[i] * st[i + 1].

* Sobre o codigo:
  Os dois lacos classicos mantem [l, r] como o palindromo mais a direita e
  reaproveitam o raio do espelho. Arrays de diferenca st/en acumulam 1 em
  cada intervalo de inicio/fim; a soma final da as contagens.

* Problemas e reducoes:
  + Contar palindromos total/por posicao: d1/d2 e st/en.
  + Maior palindromo: best_l/best_len.
  + Testar substring palindroma: is_pal(l, r).
  + Pares de palindromos adjacentes: sum en[i] * st[i+1].
  + Substrings palindromas com restricao de centro: use d1/d2.

Cuidados: nao serve com updates de char (use hash). d1[i] >= 1 sempre.
  0-indexed, intervalo [l, r).
Catalogo: Strings (palindromos, Manacher + diferencas, pares de palindromos
  adjacentes).
Digitacao: 39 linhas | media. Atalho: ok.
*****************************LATEX_DESC_END*/
