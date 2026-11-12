// Trie (arvore de prefixos) para minusculas
//
// O que faz: insert(p) insere a palavra p; count(p) devolve quantas vezes p foi
//            inserida (0 se nao existe); terminal guarda o numero de ocorrencias.
// Quando usar: Catalogo > Strings (trie). Gatilhos: prefixos, contagem de palavras,
//            max xor (trie de bits), Aho-Corasick, autômato de dicionario.
// Complexidade: O(|p|) por insercao/consulta; O(MAXS * sigma) memoria.
// Uso: init(); insert(p); int k = count(p); (init e chamado automaticamente na 1a vez)
// Cuidados: MAXS = soma dos |p| + 1 (ajuste ao problema); sigma = 26 e 'a'..'z';
//            para varias execucoes/subcasos chame init() para zerar; a trie de bits
//            usa sigma = 2 e os bits do valor, nao caracteres.
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
