// Ordered set - rank e k-esimo (pb_ds)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T, class C = less<T>>
using oset = tree<T, null_type, C, rb_tree_tag, tree_order_statistics_node_update>;
/*LATEX_DESC_BEGIN***************************
-> **Ordered Set (pb_ds)** - rank e k-esimo em O(log n); order_of_key(x) = #elementos < x, find_by_order(k) 0-based.
Complexidade: O(log n) por operacao.
Uso: oset<int> s; s.insert(x); int r = s.order_of_key(x); auto it = s.find_by_order(k);
* Sobre o codigo: alias do tree com tree_order_statistics_node_update (tamanhos de subarvore).
* Problemas e reducoes: + rank/k-esimo online; + mediana dinamica; + inversoes online; + multiset com pares {valor, id}.
Cuidados: erase por valor ou iterador; nao use lower_bound com pares sem id; find_by_order(k >= size) = end(); contar <= x no multiset: order_of_key({x, INT_MAX}).
Catalogo: Estruturas de dados (Ordered set trick).
Digitacao: 5 linhas | facil. Atalho: ok.
*****************************LATEX_DESC_END*/
