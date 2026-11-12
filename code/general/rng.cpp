// RNG para testes - vetores aleatorios e permutacoes
#include <bits/stdc++.h>
using namespace std;
mt19937 rng(time(0));
int l = 1;
int r = 1e5;
vector<int> random_a(int n){
    uniform_int_distribution<int>dist(l,r);
    vector<int>a(n);
    for(int& x : a)x=dist(rng);
    return a;
}
vector<int> random_perm(int n){
    vector<int>a(n);
    iota(a.begin(),a.end(),0);
    shuffle(a.begin(),a.end(),rng);
    return a;
}
/*LATEX_DESC_BEGIN***************************
-> **RNG para Testes**
random_a(n) gera n inteiros uniformes em [l, r]; random_perm(n) gera uma permutacao
de 0..n-1. rng e mt19937 semeado com time(0).

Complexidade: O(n) por vetor
Uso:
  ajuste os globais l e r; vector<int> a = random_a(n); auto p = random_perm(n);

* Sobre o codigo:
  random_a usa uniform_int_distribution; random_perm faz iota + shuffle.

* Problemas e reducoes:
  + Gerador de casos para stress test.

Cuidados: standalone (tem #include); para reprodutibilidade semeie com constante;
  nao use na solucao (o juiz pode repetir a seed).
Catalogo: Aleatorizacao (stress test)
Digitacao: 17 linhas | facil.
*****************************LATEX_DESC_END*/
