// Eertree (arvore de palindromos) + particao em palindromos
const ll MODP = 1e9 + 7;
struct Eertree {
	static const int K = 26;
	vector<array<int, K>> to;
	vector<int> len, link, diff, slink, cnt;
	string s; int last;
	Eertree() {
		newnode(-1, 0); newnode(0, 0); // 0: raiz impar, 1: raiz par
		last = 1;
	}
	int sz() { return len.size(); }
	int newnode(int l, int lk) {
		array<int, K> a; a.fill(0);
		to.push_back(a); len.push_back(l); link.push_back(lk);
		diff.push_back(0); slink.push_back(0); cnt.push_back(0);
		return len.size() - 1;
	}
	int getlink(int v, int i) { // maior sufixo palindromo de v que estende com s[i]
		while (i - len[v] - 1 < 0 || s[i - len[v] - 1] != s[i]) v = link[v];
		return v;
	}
	void add(char ch) {
		int i = s.size(), c = ch - 'a';
		s.push_back(ch);
		int cur = getlink(last, i);
		if (!to[cur][c]) {
			int w = newnode(len[cur] + 2, 0);
			// link: tem que ser calculado antes de ligar to[cur][c]
			link[w] = len[w] == 1 ? 1 : to[getlink(link[cur], i)][c];
			diff[w] = len[w] - len[link[w]];
			slink[w] = diff[w] == diff[link[w]] ? slink[link[w]] : link[w];
			to[cur][c] = w;
		}
		last = to[cur][c];
		cnt[last]++;
	}
	void calc_cnt() { // propaga: palindromo tambem ocorre dentro dos que o tem como sufixo
		for (int v = sz() - 1; v >= 2; v--) cnt[link[v]] += cnt[v];
	}
};
vector<pair<int, ll>> part(const string& s) { // {min pecas, nro de particoes} por prefixo
	int n = s.size();
	Eertree T;
	vector<int> dp(n + 1, INT_MAX);
	vector<ll> ways(n + 1, 0);
	vector<int> sdp; vector<ll> sways;
	dp[0] = 0; ways[0] = 1;
	// por no: melhor valor da serie (para reaproveitar via link)
	vector<int> smin; vector<ll> ssum;
	smin.assign(2, INT_MAX); ssum.assign(2, 0);
	for (int i = 1; i <= n; i++) {
		T.add(s[i - 1]);
		smin.resize(T.sz(), INT_MAX); ssum.resize(T.sz(), 0);
		for (int v = T.last; T.len[v] > 0; v = T.slink[v]) {
			int p = i - T.len[T.slink[v]] - T.diff[v]; // inicio da menor peca da serie
			smin[v] = dp[p]; ssum[v] = ways[p];
			if (T.diff[v] == T.diff[T.link[v]]) {
				smin[v] = min(smin[v], smin[T.link[v]]);
				ssum[v] = (ssum[v] + ssum[T.link[v]]) % MODP;
			}
			if (smin[v] != INT_MAX) dp[i] = min(dp[i], smin[v] + 1);
			ways[i] = (ways[i] + ssum[v]) % MODP;
		}
	}
	vector<pair<int, ll>> r(n + 1);
	for (int i = 0; i <= n; i++) r[i] = {dp[i], ways[i]};
	return r;
}
/*LATEX_DESC_BEGIN***************************
-> **Eertree (arvore de palindromos)**
No por palindromo distinto (<= n nos): len, link (maior sufixo palindromo
proprio), cnt (ocorrencias). Com diff/slink (series link) faz DP de particao
em palindromos em O(n log n): minimo de pecas e numero de particoes.
Alfabeto 'a'..'z'.

Complexidade: add amortizado O(1); particao O(n log n).
Uso:
  Eertree T; for (char c : s) T.add(c);
  T.last = no do maior sufixo palindromo do prefixo atual;
  T.sz() - 2 = numero de palindromos distintos;
  T.calc_cnt(); // cnt[v] = ocorrencias de v na string inteira
  auto r = part(s); // r[i] = {min pecas, numero de particoes mod MODP}
  Nos 0 (len -1, raiz impar) e 1 (len 0, raiz par); palindromos reais: v >= 2.

* Sobre o codigo:
  getlink sobe pelos links ate achar um palindromo que se estende com s[i].
  add cria no novo se preciso e calcula link, diff e slink (series link).
  calc_cnt propaga cnt[v] para link[v] em ordem inversa de criacao. part usa
  a serie para agrupar transicoes com a mesma diff no DP.

* Problemas e reducoes:
  + Palindromos distintos: T.sz() - 2.
  + Ocorrencias de cada palindromo: calc_cnt().
  + Minimo de pecas para particionar s em palindromos: part(s).
  + Numero de particoes em palindromos (mod MODP): part(s).
  + Fatoracao em palindromos de tamanho par: intercale s1 sn s2 sn-1... e
    some so as posicoes pares do dp (CF 932G).
  + Maior sufixo palindromo a cada prefixo: T.last.

Cuidados: particao em palindromos de tamanho PAR: intercale s1 sn s2 sn-1...
  e some so posicoes pares do dp (CF 932G). Contagem de particoes aqui e mod
  MODP. Nos 0-indexados; a string em si nao e indexada na API.
Catalogo: Strings (palindromos distintos/contar -> eertree, eertree:
  ocorrencias, fatoracao em palindromos (serie link)).
Digitacao: 68 linhas | dificil. Atalho: part duplica o laco de series; poderia
  virar um metodo da struct com o DP como parametro.
*****************************LATEX_DESC_END*/
