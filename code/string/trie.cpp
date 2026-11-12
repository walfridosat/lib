// Trie (arvore de prefixos) para minusculas
const int MAXS = 1000005; // nos totais: soma dos |p|
const int sigma = 26;

int trie[MAXS][sigma], terminal[MAXS], z = 1;
bool trie_ready = false;

void init(){
	memset(trie[0], -1, sizeof trie[0]);
	z = 1;
	trie_ready = true;
}

void insert(string &p){
	if(!trie_ready) init();
	int cur = 0;

	for(int i=0; i<(int)p.size(); i++){
		int id = p[i] - 'a';

		if(trie[cur][id] == -1 ){
			memset(trie[z], -1, sizeof trie[z]);
			trie[cur][id] = z++;
		}

		cur = trie[cur][id];
	}

	terminal[cur]++;
}

int count(string &p){
	if(!trie_ready) init();
	int cur = 0;

	for(int i=0; i<(int)p.size(); i++){
		int id = (p[i] - 'a');

		if(trie[cur][id] == -1) return 0;

		cur = trie[cur][id];
	}
	return terminal[cur];
}
/*LATEX_DESC_BEGIN***************************
-> **Trie (arvore de prefixos) para minusculas**
insert(p) insere p; count(p) devolve quantas vezes p foi inserida (0 se nao
existe); terminal guarda o numero de ocorrencias.

Complexidade: O(|p|) por insercao/consulta; O(MAXS * sigma) memoria.
Uso:
  init(); insert(p); int k = count(p);
  (init e chamado automaticamente na 1a vez)
  MAXS = soma dos |p| + 1; sigma = 26 e 'a'..'z'.

* Sobre o codigo:
  trie[cur][id] e o filho; terminal[cur] conta palavras que terminam no no.
  init zera o no 0; insert cria nos com memset(-1) e count para no primeiro
  filho ausente. Para varias execucoes/subcasos chame init().

* Problemas e reducoes:
  + Prefixos e contagem de palavras: insert/count.
  + Max xor: trie de bits, sigma = 2 e os bits do valor.
  + Base para Aho-Corasick: mesma trie com links.
  + Dicionario/autocomplete: armazene mais dados por no.

Cuidados: MAXS = soma dos |p| + 1 (ajuste ao problema); sigma = 26 e
  'a'..'z'; para varias execucoes/subcasos chame init(); a trie de bits usa
  sigma = 2 e os bits do valor, nao caracteres.
Catalogo: Strings (trie).
Digitacao: 32 linhas | facil. Atalho: ok.
*****************************LATEX_DESC_END*/
