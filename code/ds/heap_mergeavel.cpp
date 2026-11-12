// Heap mergeavel (leftist) de minimo
//
// O que faz: fila de prioridade com uniao de dois heaps em O(log n).
// Quando usar: "Catalogo > Estruturas de dados" (Heap mergeable): juntar
//   heaps de filhos em arvore (slope trick em arvore, "k menores da
//   subarvore") sem small-to-large.
// Complexidade: O(log n) por push/pop/merge.
// Uso: LHeap h; int r = 0; (0 = vazio)
//   r = h.push(r, valor); h.top(r); r = h.pop(r); r = h.merge(r1, r2);
//   Tamanho nao eh mantido; guarde a parte se precisar.
// Cuidados: raiz muda a cada operacao: sempre reatribua. Para maximo, insira
//   negativos. Para pares troque o typedef T.
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
