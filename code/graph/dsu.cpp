// DSU - union-find

struct DSU {
	vector<int> pai, sz;
	DSU(int n) : pai(n+1), sz(n+1, 1) {
		for(int i=0; i<=n; i++) pai[i] = i;
	}
	
	int find(int u){ return pai[u] == u ? u : pai[u] = find(pai[u]); }

	void join(int u, int v){
		u = find(u), v = find(v);

		if(u == v) return;
		if(sz[v] > sz[u]) swap(u, v);

		pai[v] = u;
		sz[u] += sz[v];
	}
};
/*LATEX_DESC_BEGIN***************************
-> **DSU - union-find**
find(u) com compressao de caminho; join(u,v) une componentes; sz guarda
tamanhos. O construtor aloca n+1 posicoes (indices 0..n).

Complexidade: O(alpha(n)) amortizado por operacao; memoria O(n)
Uso:
  DSU d(n);                  // indices 0..n
  d.join(u, v);
  if (d.find(u) == d.find(v)) ...

* Sobre o codigo:
  pai[] e sz[]; find recursivo comprime; join pendura a menor na maior
  (union by size). alpha(1e6) == 5.

* Problemas e reducoes:
  + Kruskal: ordene as arestas e use join/find.
  + Componentes conexas com apenas unioes.
  + Remocoes ao contrario: processe offline de tras para frente e vire uniao.
  + Arestas online com paridade: DSU com potenciais.
  + Proximo indice livre / cobertura de intervalos: DSU como "jump".

Cuidados: indices 0..n; para 0-indexado puro use DSU(n-1) ou ajuste. Nao
  chame find fora do intervalo. Para rollback use dsu_rollback.
Catalogo: Grafos (DSU, Kruskal, componentes, remocoes ao contrario).
Digitacao: 14 linhas | facil.
*****************************LATEX_DESC_END*/
