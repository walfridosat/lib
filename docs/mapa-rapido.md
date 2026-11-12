# Mapa rápido

Uma linha por salto: gatilho → técnica. O porquê está em `catalogo-completo.md`; a versão longa antiga deste mapa está em `mapa-rapido-longo.md`.

## Reduções

**Universais**
- Σ_i Σ_j difícil → troque a ordem dos fors; contribuição de cada elemento
- Σ a_i → Σ_t #{a_i ≥ t} (fatiar por camadas); E[X] = Σ P(X ≥ k)
- "Pelo menos um" → complemento; vários defeitos → inclusão-exclusão
- Remoções → adições ao contrário (DSU)
- Min do max / max do min → binária na resposta
- "Exatamente k" com custo convexo → Aliens (λ)
- Operação reversível → forma canônica dos dois lados
- "Sempre existe" → pombal / extremo / invariante viram a construção
- Min difícil → dual (corte = fluxo, König, Dilworth)

**Arrays e guloso**
- Soma = 0 → prefixos iguais; média ≥ k → subtraia k; mediana ≥ x → ±1
- Op. em intervalo → 2 pontos no array de diferenças
- Ordem ótima de tarefas → exchange argument (t/w, prazo)
- Estritamente crescente → a_i − i não decrescente
- Minimizar Σ|a_i − b_i| com b monótono → slope trick (heap)
- Escolher k não adjacentes → heap + lista ligada (arrependimento)
- Trocas em permutação → ciclos (n − #ciclos) / inversões (adjacentes)
- Pares i < j com condição → ordene + BIT; 3 dimensões → CDQ
- Cíclico → duplique; n ≤ 40 → meet in the middle
- Cobertura mínima por crescentes → maior não crescente (Dilworth)

**Busca**
- k-ésimo de conjunto implícito → binária + contar ≤ x
- Razão máxima Σa/Σb → binária em r ou Dinkelbach
- Primeiro índice com prefixo ≥ x → descida em BIT/segtree
- Primeiro instante em que conecta → Kruskal reconstruction ou binária paralela
- Binária sobre racionais / fração mais simples → Stern–Brocot

**DP**
- Valor grande, resposta pequena → troque estado e valor (dp[resposta] = melhor parâmetro)
- dp[i] = min_j (dp[j] + (S_i − S_j)²) → CHT / Li Chao
- opt monótono (Monge) → D&C DP; intervalo → Knuth
- Transição linear com n enorme → matriz / Kitamasa; recorrência desconhecida → Berlekamp–Massey
- dp(n) polinomial em n → Lagrange com d+1 pontos
- Árvore + escolher k → knapsack O(n²) por tamanho ou ordem DFS pegar/pular
- Estado = profundidade em árvore → long-path decomposition
- Permutação com restrição de adjacência → connected components DP / insertion DP
- Esperança com ciclos → sistema linear ou E[i] = a_i·E[0] + b_i
- Grid estreito → broken profile; n ≤ 20 → máscara / SOS / IE + SOS
- Custos ≥ 0 com ciclos nos estados → Dijkstra em vez de DP
- Mochila com remoção ou itens com validade → dp inversa (modular) ou segtree no tempo

**Números**
- Pares com gcd = g, Σ gcd(i, j) → Möbius/φ + blocos de ⌊n/d⌋
- Soma de multiplicativa até 10¹¹ → Dirichlet sieve / Lucy / Min_25
- Σ ⌊(ai+b)/m⌋, pontos sob reta → floor sum
- Congruências → CRT (não coprimo: g | diferença); a^x ≡ b → BSGS; x² ≡ a → Tonelli–Shanks
- a^b^c… mod m → cadeia φ(φ(·)); v_p(xⁿ ± yⁿ) → LTE
- Muitas moedas, menor pequena → Dijkstra nos restos

**Contagem**
- "Exatamente k defeitos" → inversão binomial de "pelo menos k"
- Rotações/reflexões → Burnside
- Conexos rotulados → total − componente do vértice 1 (ln de EGF)
- Árvores rotuladas → Prüfer/Cayley; geradoras → Matrix-Tree; circuitos eulerianos → BEST
- Caminhos disjuntos em DAG/grid → LGV (determinante)
- Extensões lineares de floresta → n!/∏ sz
- Caminhos que não cruzam uma linha → reflexão / Catalan
- Tempo esperado até padrão → Σ q^k sobre as bordas
- Subconjuntos com soma ≡ r (mod m) → (1+x)ⁿ mod (xᵐ − 1)

**Bits**
- Soma/contagem com AND/OR/XOR → bit a bit
- Max xor → trie; com intervalo/versões → trie persistente ou base com índice mais recente
- Max xor de passeio em grafo → px + base linear dos ciclos
- Operação a_i ^= a_j, lights out, paridades → Gauss em GF(2)
- Pares com a_i & a_j = 0 → SOS; convolução xor/and/or → Walsh / zeta

**Strings**
- Substring de s em t → s + '#' + t; rotação/potência → s + s
- Ocorrências de vários padrões → Aho-Corasick + soma na link tree
- Substrings de um padrão → intervalo no suffix array; LCP de sufixos → RMQ no lcp
- Suffix tree de s → SAM de rev(s)
- Partição em palíndromos → eertree + série link; palíndromos por posição → Manacher
- LCS de permutações → LIS; subsequência palindrômica → LCS(s, rev s)
- Casamento com erros/curinga → FFT por letra ou kangaroo (LCE)
- Período d → DSU em classes i mod d
- Árvore ↔ parênteses → subárvore = intervalo, LCA = RMQ do balanço

**Grafos**
- Grafo direcionado → DAG (SCC); 2 opções por item + conflitos → 2-SAT
- Restrições x_j − x_i ≤ c → caminho mínimo (ciclo negativo = inviável)
- Atribuir/emparelhar → matching/fluxo; lucro com dependências → corte mínimo (closure)
- Rótulo 0/1 com custo por par submodular → corte mínimo
- Bipartido: independente máximo = n − matching; cobertura de caminhos em DAG = n − matching
- Antichain máxima = cadeias mínimas (Dilworth) → matching no fecho transitivo
- Caminhos disjuntos → fluxo com v_in/v_out; custo convexo → arestas unitárias marginais
- Minimax de caminho → MST + LCA / árvore de Kruskal
- Árvore + poucas arestas extras → Dijkstra dos extremos + LCA
- Orientar/decompor arestas, de Bruijn → circuito euleriano (vértice fantasma para ímpares)
- Vizinhos = intervalo de vértices → segtree de arestas; "todos os não visitados" → set/DSU
- Corte mínimo planar → caminho mínimo no dual
- Grafo funcional → ciclos + árvores; k passos → binary lifting

**Árvores**
- Subárvore → intervalo (Euler tour); caminho → HLD ou prefixos da raiz + LCA
- Todos os caminhos com condição → centroide; resposta para toda raiz → rerooting
- Update em caminho, leitura no fim → diferenças com lca e pai(lca)
- Soma sobre pares de vértices → aresta contribui sz·(n − sz)
- Query com k vértices → virtual tree; cores na subárvore → small-to-large
- Isomorfismo → hash AHU a partir dos centros

**Estruturas**
- Queries sem updates → offline + sweep, Mo
- Arestas/itens com tempo de vida → segtree no tempo + rollback
- Janela com operação sem inverso → duas pilhas
- k-ésimo em intervalo → wavelet / persistente; mex → last[v] em segtree + descida
- Reta mais alta em x → Li Chao; no caminho da raiz → Li Chao com rollback
- Só insere + estrutura estática → Bentley–Saxe
- Estado de autômato com updates → segtree de funções

**Geometria**
- Manhattan → (x + y, x − y)
- Ponto acima/abaixo de retas → dualidade + CHT/hull
- Ordenar por ângulo → semiplano + cross; "contém a origem" → complemento por semiplano
- União de retângulos → sweep + segtree; retângulo → 4 prefixos + BIT
- Interseção de convexos → origem ∈ Minkowski(A, −B); LP 2D → semiplanos
- Espelhos/bilhar → refletir o mundo; bolas idênticas colidindo → atravessam

**Jogos**
- Configuração simétrica → espelho / pareamento
- Duração fixa → paridade de lances
- Jogos independentes somados → xor dos Grundy
- Lance que o outro desfaz → ignore
- Ciclos com empate → BFS retrógrada
- Pontuação → dp de diferença (minimax)

**Álgebra**
- Pares com soma/diferença em valores pequenos → produto de polinômios (FFT/NTT)
- Total = exp(conexas) → ln/exp de série
- Σ kᵈ e contagens polinomiais → Lagrange
- Igualdade de polinômios/matrizes → ponto aleatório (Schwartz–Zippel, Freivalds)
- Matching perfeito existe? → posto da matriz de Tutte aleatória

## Limites escondidos

**Raiz e log**
- Σ tamanhos ≤ S → ≤ √(2S) tamanhos distintos; itens > √S são ≤ √S
- m arestas → ≤ 2√m vértices de grau ≥ √m; grau de saída ≤ √(2m) orientando por grau
- Σ ⌊n/i⌋ → 2√n valores; 1 + 2 + … + k ≤ n → k ≤ √(2n)
- gcd/OR/AND de subarray → ≤ log mudanças; x mod y → cai pela metade
- Caminho raiz–folha → ≤ log arestas leves; cadeia de divisibilidade ≤ log₂ N + 1
- φ(φ(…m)) chega a 1 em ≤ 2 log₂ m passos
- Bordas de string → O(log n) PAs; ocorrências de p em janela 2|p| → uma PA
- "Pelo menos metade" → aleatorizar (30–60 tentativas)

**Números para decorar**
- Divisores máx.: 10⁶ → 240; 10⁹ → 1344; 10¹² → 6720; 10¹⁸ → 103680
- Primos distintos: 10⁶ → 7; 10⁹ → 9; 10¹⁸ → 15
- π(10⁶) = 78498; π(10⁷) = 664579; π(10⁹) ≈ 5,08·10⁷
- Maior gap de primos: < 10⁹ → 282; < 10¹⁸ → < 1500
- 20! < 2⁶³ < 21!; lcm(1..43) estoura 2⁶³; ~86 Fibonacci ≤ 10¹⁸
- double guarda inteiros até 2⁵³; FFT double ok se n·coef² ≲ 10¹⁴–10¹⁵
- NTT em 998244353 → tamanho ≤ 2²³; módulo arbitrário → 3 NTTs + CRT
- Miller–Rabin 64 bits → 12 primeiras bases primas
- Pares com n = 2·10⁵ → 4·10¹⁰ (long long); a·d vs b·c com 10⁹ → __int128

**Complexidades-chave**
- Subconjuntos 3^n: n ≤ 16–18; 2^n·n: n ≤ 20–22; meet in the middle: n ≤ 40
- Knapsack em árvore → O(n²), ou O(nK) com limite K
- Mo → n√q; com updates → n^(5/3)
- Triângulos e C4 → m√m; bitset → ÷64
- Hopcroft–Karp → E√V; Hungarian → n³; Gauss → n³ (GF(2): n³/64)
- Berlekamp–Massey precisa de 2k termos; Σ kᵈ → d + 2 pontos
- Interativo: ⌈log_b(#respostas)⌉ queries; 10¹⁸ → 60 perguntas binárias

**Estrutura garantida**
- Planar → m ≤ 3n − 6, degenerescência ≤ 5
- Sem triângulo → m ≤ n²/4; sem C4 → m = O(n√n)
- Torneio → sempre tem caminho hamiltoniano
- Grau mínimo ≥ k → caminho de comprimento ≥ k; ≥ n/2 → ciclo hamiltoniano
- n + 1 prefixos mod n → bloco com soma ≡ 0; LIS · LDS ≥ n
- n > nº de bits → subconjunto de xor 0; base linear tem ≤ (nº de bits) vetores
- Centroide → componentes ≤ n/2; virtual tree → ≤ 2k − 1 vértices
- SAM → ≤ 2n − 1 estados; palíndromos distintos ≤ n; runs < n
- Dim. do espaço de ciclos → m − n + c; Euler: V − E + F = 1 + c

## Por tópico

**Arrays/guloso:** ordenar · trás pra frente · two pointers · pilha monotônica · deque · heap com arrependimento · diferenças · mediana · contribuição · exchange argument · slope trick

**Busca binária:** na resposta · k-ésimo · razão · paralela · descida na segtree · ternária · Aliens · Dinkelbach

**DP:** prefixo · intervalo · subárvore · máscara · dígitos · trocar estado e valor · última operação · CHT · D&C · Knuth · matriz · SOS · bitset · rerooting · small-to-large · broken profile · long-path · connected components · Lagrange · BM

**Números:** √ divisores · múltiplos (harmônico) · fatorar e separar primos · Möbius · gcd(a, b − a) · CRT · Euclides estendido · crivo linear · blocos de ⌊n/d⌋ · floor sum · BSGS · Miller–Rabin/Pollard · LTE

**Contagem:** complemento · IE · bijeção · reflexão · contribuição · linearidade da esperança · Burnside · OEIS · inversão binomial · Prüfer · Matrix-Tree · LGV · EGF · tail sum

**Bits:** bit a bit · trie · base linear · prefix xor · submáscaras · SOS · Walsh · Gauss GF(2) · Gray · pigeonhole n > bits

**Strings:** hash · Z/KMP · Aho-Corasick · SA + LCP · SAM · trie · Manacher · eertree · frequências 26 · máscara de paridade · run-length · s + s · Fine–Wilf · Duval · next[i][c]

**Grafos:** grafo de estados · 0-1 BFS · super-fonte · SCC · 2-SAT · pontes · DSU · MST · bipartido · funcional + lifting · Euler · fluxo/corte · König/Hall/Dilworth · árvore de Kruskal · base de ciclos · degenerescência

**Árvores:** enraizar bem · rerooting · centroide · diâmetro · LCA · HLD · Euler tour · small-to-large · virtual tree · pesado/leve · long-path · diferenças em caminho · AHU

**Estruturas:** offline + sweep · Mo · segtree (o que o nó guarda?) · lazy · persistente · beats · sparse · ODT · √ decomposition · CDQ · DSU com info · segtree no tempo · duas pilhas · Li Chao · wavelet · treap implícito

**Jogos:** brute force pequeno · espelho · primeira escolha decide · roubo de estratégia · pares · paridade de lances · invariante · Grundy · Nim · BFS retrógrada · minimax em intervalo

**Construtivos:** impossível primeiro · n pequeno à mão · indução n → n + 2 · forma canônica · paridade/xadrez · pares · sentinela · Gray · de Bruijn · Havel–Hakimi · interativo: binária/centroide

**Aleatório:** sortear e verificar · hash de conjunto · xor hashing · shuffle · color coding · Schwartz–Zippel · Freivalds · annealing

**Geometria:** cross/dot · ordem por ângulo · hull · calipers · Minkowski · semiplanos · sweep · Pick · dualidade · closest pair · Welzl

**Álgebra/otimização:** FFT/NTT · série formal · Lagrange · BM/Kitamasa · Gauss · Kirchhoff · dualidade LP · matroide (guloso) · fluxo convexo · Hungarian

**Travado:** brute force n ≤ 15 · imprimir a escolha ótima · releia o enunciado · o que o autor quer cortar? · trocar a ordem dos fors · casos de borda · stress test
