// Ordered set / multiset (pb_ds): rank e k-esimo
//
// O que faz: set ordenado com order_of_key(x) (quantos < x) e
//   find_by_order(k) (k-esimo, 0-based) em O(log n).
// Quando usar: "Catalogo > Estruturas de dados" (Ordered set trick): rank,
//   k-esimo dinamico, mediana dinamica, inversoes online.
// Complexidade: O(log n) por operacao.
// Uso: oset<int> s; s.insert(x); s.order_of_key(x); *s.find_by_order(k);
//   Multiset: oset<pair<int,int>> e insira {valor, id unico}.
//   Contar valores <= x em multiset: s.order_of_key({x, INT_MAX}).
// Cuidados: erase por valor funciona; por iterador tambem. Nao use
//   s.lower_bound com pares sem id. find_by_order(k>=size) devolve end().
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T, class C = less<T>>
using oset = tree<T, null_type, C, rb_tree_tag, tree_order_statistics_node_update>;
