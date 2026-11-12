// Heap com remocao preguicosa
//
// O que faz: priority_queue que aceita erase(x) de um valor presente,
//   mantendo um segundo heap de removidos.
// Quando usar: "Catalogo > Estruturas de dados" (Heap com remocao
//   preguicosa, mediana dinamica com dois heaps, janela com remocao).
// Complexidade: O(log n) amortizado.
// Uso: LazyHeap<ll> h; h.push(x); h.erase(x); h.top(); h.pop(); h.size();
//   Maximo por padrao; para minimo: LazyHeap<ll, greater<ll>>.
// Cuidados: erase so de valor realmente presente (senao corrompe o size).
//   Multiplicidades funcionam. Se o item muda de valor, use (valor,versao).
template<class T, class C = less<T>>
struct LazyHeap {
	priority_queue<T, vector<T>, C> a, b; int n = 0;
	void clean() { // tira dos dois heaps enquanto os topos forem iguais
		while (!b.empty() && !a.empty() && !C()(b.top(), a.top()) && !C()(a.top(), b.top())) a.pop(), b.pop();
	}
	void push(T x) { a.push(x); n++; }
	void erase(T x) { b.push(x); n--; clean(); }
	T top() { clean(); return a.top(); }
	void pop() { clean(); a.pop(); n--; clean(); }
	int size() { return n; }
	bool empty() { return n == 0; }
};
