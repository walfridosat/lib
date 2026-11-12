// Heap mergeavel (leftist) - merge O(log n)
struct LHeap {
	typedef ll T;
	vector<T> v; vector<int> l, r, d; // d = distancia ate nulo (rank)
	LHeap() { v.push_back(0); l.push_back(0); r.push_back(0); d.push_back(0); }
	int merge(int a, int b) {
		if (!a || !b) return a ^ b;
		if (v[b] < v[a]) swap(a, b);
		r[a] = merge(r[a], b); // recursao na perna direita: profundidade O(log n)
		if (d[l[a]] < d[r[a]]) swap(l[a], r[a]);
		d[a] = d[r[a]] + 1;
		return a;
	}
	int push(int root, T x) {
		v.push_back(x); l.push_back(0); r.push_back(0); d.push_back(1);
		return merge(root, v.size() - 1);
	}
	T top(int root) { return v[root]; }
	int pop(int root) { return merge(l[root], r[root]); }
};
/*LATEX_DESC_BEGIN***************************
-> **Heap mergeavel (leftist)**
Fila de prioridade de minimo com uniao de dois heaps em O(log n).
A raiz 0 representa heap vazio.

Complexidade: O(log n) por push/pop/merge.
Uso:
  LHeap h; int r = 0;        // 0 = vazio
  r = h.push(r, x); h.top(r); r = h.pop(r); r = h.merge(r1, r2);
  Tamanho nao e mantido; guarde a parte se precisar.

* Sobre o codigo:
  Leftist heap em arrays v,l,r,d (d = rank). merge desce pela perna
  direita, troca filhos por rank e devolve a nova raiz.

* Problemas e reducoes:
  + Juntar heaps de filhos em arvore (slope trick, k menores da subarvore)
    sem small-to-large.
  + Merge de priority queues.
  + Estrutura meldable em algoritmos de arvore.

Cuidados: a raiz muda a cada operacao: sempre reatribua. Para maximo
  insira negativos. Para pares troque o typedef T.
Catalogo: Estruturas de dados.
Digitacao: 19 linhas | media. Atalho: trocar typedef ll T por
  template<class T> evita reescrever para pares.
*****************************LATEX_DESC_END*/
