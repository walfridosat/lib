# Índice da biblioteca

Gerado em 2026-11-11 a partir dos cabeçalhos de cada arquivo. Total: **206 trechos**.
Status `compila` = `g++ -std=c++17 -Wall -fsyntax-only` com o prelude do template; `testado` = conferido contra brute force/casos conhecidos; `com binom_mod` = precisa colar `code/combinatorics/binom_mod.cpp` antes.

Pastas ainda vazias: `code/bits/`, `code/games/`, `code/primitives/` (Lote 1 e 2 de `docs/PLANO_LIB.md`).

| Arquivo | Nome | Descrição | Seção do catálogo | Status |
|---|---|---|---|---|
| **algebra/** | | | | |
| `code/algebra/berlekamp_massey.cpp` | Berlekamp-Massey + n-esimo termo de recorrencia linear (Kitamasa O(k^2 log n)) | dado s[0..m) de uma recorrencia linear de ordem L (mod primo), acha os | Álgebra, polinômios e FFT | compila |
| `code/algebra/bostan_mori.cpp` | Bostan-Mori: [x^n] P(x)/Q(x) mod 998244353 | n-esimo coeficiente de uma serie racional P/Q (Q[0] != 0) | Álgebra, polinômios e FFT | compila |
| `code/algebra/conv_mod.cpp` | Convolucao com modulo arbitrario por 3 NTT + CRT (Garner) | c = a*b mod M para M qualquer (ex.: 1e9+7), exato (sem erro de ponto flutuante) | Álgebra, polinômios e FFT | compila |
| `code/algebra/fft.cpp` | FFT complexa (double) e convolucao com modulo arbitrario por split | conv(a,b) convolui vetores de double | Álgebra, polinômios e FFT | compila |
| `code/algebra/lagrange.cpp` | Interpolacao de Lagrange em pontos consecutivos (0..d) | dado y[i] = P(i) para i = 0..d (P de grau <= d), calcula P(n) para n qualquer | Álgebra, polinômios e FFT | compila |
| `code/algebra/ntt.cpp` | NTT (transformada teorica dos numeros) e convolucao mod 998244353 | multiplica dois polinomios com coeficientes mod 998244353 (g = 3) | Álgebra, polinômios e FFT | testado (brute, 2026-11-11) |
| `code/algebra/poly.cpp` | Polinomios e series formais mod 998244353 (inv, ln, exp, sqrt, pow, divmod, multipoint, interpolacao) | operacoes de series formais por Newton, divisao de polinomios, avaliacao em | Álgebra, polinômios e FFT | compila |
| `code/algebra/power_sum.cpp` | Soma de potencias sum_{k=1}^n k^d mod p (Faulhaber via Lagrange) | calcula S(n,d) = 1^d + 2^d + | Álgebra, polinômios e FFT | compila |
| **combinatorics/** | | | | |
| `code/combinatorics/binom_general.cpp` | Binomial modulo composto qualquer (e potencia de primo) | C(n,k) mod m para m arbitrario, n,k ate 1e18 | Combinatória, contagem e probabilidade | compila |
| `code/combinatorics/binom_mod.cpp` | Fatoriais e binomiais modulo primo | pre-calcula fact, ifact e inv_[1..N] | Combinatória, contagem e probabilidade | compila |
| `code/combinatorics/burnside.cpp` | Burnside, colares, pulseiras, strings primitivas | (1) Burnside generico: dado um grupo de permutacoes (lista de | Combinatória, contagem e probabilidade | compila |
| `code/combinatorics/catalan_family.cpp` | Familia de Catalan e contagens de caminhos/selecoes classicas | Catalan, ballot (estrito e com empate), Narayana, Fuss-Catalan, | Combinatória, contagem e probabilidade | compila (com binom_mod) |
| `code/combinatorics/counting_misc.cpp` | Contagens diversas: hook length, floresta, graficidade, torneios, torres, Ryser | # SYT por hook length | Combinatória, contagem e probabilidade | compila (com binom_mod) |
| `code/combinatorics/grid_paths.cpp` | Caminhos em grid: obstaculos, faixa 0<=y<=h (reflexao alternada) | (1) # caminhos (direita/cima) de (0,0) a (X,Y) evitando k pontos | Combinatória, contagem e probabilidade | compila (com binom_mod) |
| `code/combinatorics/inclusion_exclusion.cpp` | Inclusao-exclusao: utilitarios | (1) contar inteiros em [1,N] nao divisiveis por nenhum de uma lista | Combinatória, contagem e probabilidade | compila (com binom_mod) |
| `code/combinatorics/lgv.cpp` | Lindstrom-Gessel-Viennot (caminhos disjuntos em vertices) | dado e[i][j] = # caminhos de a_i ate b_j em um DAG, devolve | Combinatória, contagem e probabilidade | compila (com binom_mod) |
| `code/combinatorics/lucas.cpp` | Lucas e Kummer | C(n,k) mod p para p primo PEQUENO (p ate ~1e6) e n,k ate 1e18 | Combinatória, contagem e probabilidade | compila |
| `code/combinatorics/matrix_tree.cpp` | Matrix-Tree (Kirchhoff), determinante mod p e mod composto | det de matriz mod primo (Gauss) e mod qualquer m (eliminacao tipo | Combinatória, contagem e probabilidade | compila |
| `code/combinatorics/partitions.cpp` | Particoes de inteiros (numeros pentagonais de Euler e DPs em sqrt) | p(0..N) por pentagonais | Combinatória, contagem e probabilidade | compila |
| `code/combinatorics/perm_counts.cpp` | Contagens de permutacoes especiais | desarranjos D_n, perms com exatamente k pontos fixos, involucoes, | Combinatória, contagem e probabilidade | compila (com binom_mod) |
| `code/combinatorics/prob_expect.cpp` | Probabilidade e esperanca modulo p: utilitarios | cadeia de Markov absorvente (E[tempos] = (I-Q)^-1 1 por Gauss mod p), | Combinatória, contagem e probabilidade | compila (com binom_mod) |
| `code/combinatorics/stirling_bell.cpp` | Stirling 1a e 2a especie, Bell, Eulerianos (tabelas O(n^2) e valor unico) | tabelas S2[n][k], S1[n][k] (sem sinal), Eulerianos A[n][k], | Combinatória, contagem e probabilidade | compila (com binom_mod) |
| `code/combinatorics/tree_counting.cpp` | Contagens de arvores rotuladas e estruturas classicas (Cayley, Prufer, componentes) | Cayley n^{n-2} | Combinatória, contagem e probabilidade | compila (com binom_mod) |
| **dp/** | | | | |
| `code/dp/bitset_subset_sum.cpp` | Subset sum com bitset e multiplicidades | dado multiconjunto de pesos, diz quais somas 0..W sao alcancaveis | DP | compila |
| `code/dp/broken_profile.cpp` | Broken profile DP (plug DP simples): ladrilhar grade com dominos | conta (mod) o numero de ladrilhamentos de uma grade n x m com dominos 1x2, com celulas bloqueadas '#' | DP | compila |
| `code/dp/coins.cpp` | Mochila de moedas: minimo de moedas para um valor | dp[i] = minimo de moedas (uso ilimitado) para somar i | DP | compila + testado |
| `code/dp/comb.cpp` | Fatoriais e binomiais modulo M (versao antiga e simples) | pre-calcula fact/invFact e responde C(n,k) modulo M | Combinatória, contagem e probabilidade | compila |
| `code/dp/dc_opt.cpp` | Divide and conquer optimization (D&C DP) | calcula dp[k][i] = min_{j<i} dp[k-1][j] + C(j,i) para k=1..K quando opt(i) e monotono | DP | compila |
| `code/dp/digitdp.cpp` | Digit DP (soma dos digitos de 0..k) | conta/otimiza sobre os digitos de 0..k com estado (posicao, soma, tight) | DP | compila + testado |
| `code/dp/edit_distance.cpp` | Edit distance (Levenshtein) com reconstrucao e versao em faixa | edit_dist: distancia minima (inserir/remover/trocar) entre a e b e uma sequencia de operacoes | DP | compila |
| `code/dp/frog.cpp` | Frog: custo minimo pulando de 1 a k posicoes | dp[i] = min_{1<=j<=k} dp[i-j] + \|a[i]-a[i-j]\| | DP | compila + testado |
| `code/dp/frog3_cht.cpp` | Frog 3 com CHT (exemplo completo, standalone) | resolve o DP dp[i] = c + h[i]^2 + min_j (dp[j] + h[j]^2 - 2*h[i]*h[j]) | DP | compila (programa completo) |
| `code/dp/interval_dp.cpp` | DP em intervalo: exemplos classicos (baloes, impressora estranha, jogo em intervalo, circular) | moldes de dp[l][r] O(n^3) | DP | compila |
| `code/dp/knapsack.cpp` | Mochila 0/1 | valor maximo com peso total <= w, cada item no maximo uma vez | DP | compila + testado |
| `code/dp/knapsack_bounded.cpp` | Mochila limitada (bounded knapsack): fila monotona e binary splitting | maximiza valor com itens (peso w_i, valor v_i, quantidade c_i), capacidade W | DP | compila |
| `code/dp/knuth.cpp` | Knuth optimization (DP em intervalo) | dp[l][r] = min_{l<=k<r} dp[l][k] + dp[k+1][r] + w(l,r) em O(n^2) usando opt[l][r-1] <= opt[l][r] <= opt[l+1][r] | DP | compila |
| `code/dp/lcs.cpp` | LCS classica O(n*m) (subsequencia comum maxima) | dp[i][j] = LCS dos prefixos a[0..i) e b[0..j) | DP | compila |
| `code/dp/lcs_bitset.cpp` | LCS com bitset (Hyyro / Allison-Dix) | comprimento da LCS de a e b em O(n*m/64), usando vetor de palavras de 64 bits com soma e carry | DP | compila |
| `code/dp/lis.cpp` | LIS em O(n log n) | tamanho da maior subsequencia estritamente crescente | DP | compila + testado |
| `code/dp/slope_trick.cpp` | Slope trick | mantem uma funcao convexa linear por partes f(x) com dois heaps (pontos de quebra a esquerda L e a direita R) | DP | compila |
| `code/dp/sosdp.cpp` | SOS DP recursivo (soma sobre submascaras) | gen_submask(b, mask) = soma de F[s] para todas as submascaras s de mask | Bits e XOR | compila |
| `code/dp/subsetsum.cpp` | Maior soma de subconjunto <= t (subset sum otimizado) | dado w (pesos inteiros >= 0) e limite t, devolve o maior valor <= t | DP | compila + testado |
| `code/dp/tree_knapsack.cpp` | Knapsack em arvore: merge O(n^2) e DP sobre ordem DFS O(nK) | escolher exatamente k vertices formando subarvore conexa que contem a raiz (se pega v, pega o pai), | Árvores | compila |
| `code/dp/tsp_bitmask.cpp` | DP em bitmask: TSP, atribuicao e particao em subconjuntos | (1) tsp: menor ciclo hamiltoniano, dp[mask][ultimo] | DP | compila |
| **ds/** | | | | |
| `code/ds/aliens.cpp` | Aliens trick / WQS binary search (lambda optimization) generico | se f(k) = melhor custo usando EXATAMENTE k itens eh CONVEXA | Busca binária e otimização | compila |
| `code/ds/bit.cpp` | BIT (Fenwick) 1D + busca binaria na BIT + BIT de maximo | soma de prefixo/intervalo com update pontual | Estruturas de dados e queries | compila |
| `code/ds/bit2d.cpp` | BIT 2D | update pontual (soma) e soma em retangulo numa grade n x m | Estruturas de dados e queries | compila |
| `code/ds/bit_rr.cpp` | BIT range-update range-query | soma em intervalo de v (add em [l,r]) e soma de intervalo, | Estruturas de dados e queries | compila |
| `code/ds/busca_binaria.cpp` | Busca binaria: templates (inteira, real, exponencial, k-esimo, mediana) | colecao de templates de binaria na resposta | Busca binária e otimização | compila |
| `code/ds/busca_binaria_paralela.cpp` | Busca binaria paralela (por niveis) | para Q queries "primeiro tempo t em que pred(query) vale", com | Busca binária e otimização | compila |
| `code/ds/busca_ternaria.cpp` | Busca ternaria (real, inteira) e Dinkelbach | acha o minimo de f unimodal/convexa | Busca binária e otimização | compila |
| `code/ds/cdq.cpp` | CDQ (divide e conquista offline) - template com BIT: dominancia 3D / DP 2D | exemplo completo de CDQ: res[i] = val[i] + max(res[j]) para | Estruturas de dados e queries | compila |
| `code/ds/cht_dinamico.cpp` | Line container (CHT dinamico, estilo KACTL) | insere retas y=k*x+m em qualquer ordem e consulta o MAXIMO em x | Estruturas de dados e queries | compila |
| `code/ds/cht_monotono.cpp` | Convex Hull Trick monotono (deque) | mantem envoltoria inferior de retas y=m*x+b inseridas com | Estruturas de dados e queries | compila |
| `code/ds/conectividade_dinamica.cpp` | Conectividade dinamica offline (segtree no tempo + DSU com rollback) | cada aresta existe em um intervalo de tempo [l, r) | Estruturas de dados e queries | compila |
| `code/ds/disjoint_sparse.cpp` | Disjoint sparse table | query de qualquer operacao ASSOCIATIVA (soma, produto mod, xor, | Estruturas de dados e queries | compila |
| `code/ds/distinct_range.cpp` | Distintos em intervalo (offline, sweep por r + BIT) | para cada query [l,r] devolve (a) quantidade de valores | Estruturas de dados e queries | compila |
| `code/ds/dsu_paridade.cpp` | DSU com paridade (bipartido online / equacoes xor) | mantem, para cada no, a paridade (xor) da distancia ate a raiz | Estruturas de dados e queries | compila |
| `code/ds/dsu_potencial.cpp` | DSU com pesos / potencial (soma) | mantem w[x] = pot[x] - pot[raiz] | Estruturas de dados e queries | compila |
| `code/ds/dsu_proximo_livre.cpp` | DSU "proximo livre" | nxt(i) = menor j >= i ainda nao removido | Estruturas de dados e queries | compila |
| `code/ds/dsu_rollback.cpp` | DSU com rollback | uniao-busca sem compressao de caminho, com desfazer (undo) das | Estruturas de dados e queries | compila |
| `code/ds/fila_monotonica.cpp` | Fila/janela monotonica + fila com agregado (duas pilhas) | (1) deque monotono: min de janela deslizante em O(n) | Estruturas de dados e queries | compila |
| `code/ds/heap_lazy.cpp` | Heap com remocao preguicosa | priority_queue que aceita erase(x) de um valor presente, | Estruturas de dados e queries | compila |
| `code/ds/heap_mergeavel.cpp` | Heap mergeavel (leftist) de minimo | fila de prioridade com uniao de dois heaps em O(log n) | Estruturas de dados e queries | compila |
| `code/ds/kdtree.cpp` | K-d tree 2D (estatica): vizinho mais proximo e contagem em retangulo | constroi arvore balanceada alternando eixos (mediana por | Estruturas de dados e queries | compila |
| `code/ds/lichao.cpp` | Li Chao tree (minimo de retas / segmentos em x) | insere retas y=a*x+b (ou segmentos) e consulta o minimo em x | Estruturas de dados e queries | testado (brute, 2026-11-11) |
| `code/ds/merge_sort_tree.cpp` | Merge sort tree | cada no guarda seu intervalo ordenado | Estruturas de dados e queries | compila |
| `code/ds/odt.cpp` | ODT / Chtholly (set de intervalos com valor constante) | mantem a particao de [0,n) em intervalos de valor constante | Estruturas de dados e queries | compila |
| `code/ds/ordered_set.cpp` | Ordered set / multiset (pb_ds): rank e k-esimo | set ordenado com order_of_key(x) (quantos < x) e | Estruturas de dados e queries | compila |
| `code/ds/ps2d.cpp` | Soma de prefixo 2D (prefix sum em matriz) | prefix[i][j] = soma do retangulo [0..i] x [0..j] | Estruturas de dados e queries | compila + testado |
| `code/ds/seg2d.cpp` | Segtree de segtrees (2D online): update de ponto, soma em retangulo | camada externa iterativa em x, cada no externo tem uma segtree | Estruturas de dados e queries | compila |
| `code/ds/seg_beats.cpp` | Segtree beats (chmin em intervalo + add em intervalo; soma e max) | a[i] = min(a[i], x) em [l,r), a[i] += v em [l,r), query soma e | Estruturas de dados e queries | compila |
| `code/ds/seg_descent.cpp` | Segtree com descida: primeiro i>=l com a[i]>=x, ultimo i<=r, k-esimo 1 | segtree de max (point update) com first_ge/last_ge em O(log n), | Estruturas de dados e queries | compila |
| `code/ds/seg_dyn.cpp` | Segtree dinamica (esparsa) com soma, k-esimo e merge de segtrees | segtree sobre dominio [0, U) enorme (ate 1e18), nos criados sob | Estruturas de dados e queries | compila |
| `code/ds/seg_iter.cpp` | Segtree iterativa (bottom-up) com monoide generico (nao comutativo ok) | update pontual e query de intervalo com qualquer operacao | Estruturas de dados e queries | compila |
| `code/ds/seg_lazy.cpp` | Segtree com lazy generica (estilo ACL) + descida max_right | update em intervalo (aplica tag F) e query de intervalo (monoide S), | Estruturas de dados e queries | testado (brute, 2026-11-11) |
| `code/ds/seg_nodes.cpp` | Nos prontos para segtree (max subarray, parenteses, funcao afim) | structs de no + merge para usar com Seg (code/ds/seg_iter.cpp) | Estruturas de dados e queries | compila |
| `code/ds/seg_persist.cpp` | Segtree persistente (contagem) - k-esimo em [l,r] e contagem <= x | versao i = prefixo a[0..i] inserido numa segtree sobre os valores | Estruturas de dados e queries | testado (brute, 2026-11-11) |
| `code/ds/seg_t.cpp` | Segtree iterativa (ponto + consulta de intervalo) | arvore de soma com update pontual O(log n) e query de intervalo O(log n) | Estruturas de dados e queries | compila + testado |
| `code/ds/segtree.cpp` | Segtree lazy (soma em intervalo + soma em range) | arvore recursiva com lazy para somar val em [l, r] e consultar a soma | Estruturas de dados e queries | compila |
| `code/ds/sparse_min.cpp` | Sparse table para minimo em intervalo estatico | pre-processa um array e responde min(a[l..r]) em O(1) | Estruturas de dados e queries | compila + testado |
| `code/ds/sparse_table.cpp` | Sparse table (RMQ O(1) para operacoes idempotentes) com indice | min/max estatico em O(1) | Estruturas de dados e queries | compila |
| `code/ds/sqrt_decomp.cpp` | Sqrt decomposition (exemplo: add em intervalo + contar >= x em intervalo) | blocos de tamanho B | Estruturas de dados e queries | compila |
| `code/ds/treap_implicito.cpp` | Treap implicito (sequencia) com split/merge, reverse e soma/add lazy | sequencia dinamica | Estruturas de dados e queries | testado (brute, 2026-11-11) |
| `code/ds/wavelet.cpp` | Wavelet matrix | sobre array estatico de inteiros >= 0: k-esimo menor, contar < x, | Estruturas de dados e queries | testado (brute, 2026-11-11) |
| **flow/** | | | | |
| `code/flow/blossom.cpp` | Blossom (Edmonds) - emparelhamento maximo em grafo geral | matching maximo em grafo nao bipartido, encolhendo ciclos impares (blossoms) | Grafos | compila |
| `code/flow/dag_path_cover.cpp` | Cobertura minima de caminhos em DAG (disjuntos em vertices, ou com repeticao) | minimo de caminhos que cobrem todos os vertices de um DAG | Grafos | compila |
| `code/flow/dinic.cpp` | Dinic (fluxo maximo) + recuperacao do corte minimo | fluxo maximo s->t | Grafos | testado (brute, 2026-11-11) |
| `code/flow/flow_lower_bounds.cpp` | Fluxo com limites inferiores: circulacao viavel e fluxo maximo s->t | arestas com low <= f <= high | Grafos | compila |
| `code/flow/gale_shapley.cpp` | Gale-Shapley - casamento estavel | n homens e n mulheres com listas de preferencia completas | Grafos | compila |
| `code/flow/gomory_hu.cpp` | Arvore de Gomory-Hu (Gusfield) - corte minimo entre todos os pares | dado grafo NAO direcionado com capacidades, constroi arvore com n-1 arestas | Grafos | compila |
| `code/flow/hopcroft_karp.cpp` | Hopcroft-Karp - emparelhamento bipartido maximo | matching maximo em bipartido L x R em fases (BFS de niveis + DFS) | Grafos | testado (brute, 2026-11-11) |
| `code/flow/hungarian.cpp` | Hungarian - problema de atribuicao de custo minimo | dada matriz de custos n x m (n <= m), atribui cada linha a uma coluna | Grafos | testado (brute, 2026-11-11) |
| `code/flow/konig.cpp` | Konig - cobertura minima de vertices e conjunto independente maximo em bipartido | a partir do matching maximo (Hopcroft-Karp embutido) constroi cobertura | Grafos | compila |
| `code/flow/kuhn.cpp` | Kuhn - emparelhamento bipartido maximo (com heuristicas) | matching maximo em bipartido L x R por caminhos aumentantes | Grafos | compila |
| `code/flow/matroid_intersection.cpp` | Interseccao de matroides (cardinalidade maxima e peso maximo) | maior conjunto S do universo {0..n-1} independente em DUAS matroides, via | Grafos | compila |
| `code/flow/mcmf.cpp` | Min-cost max-flow (Dijkstra com potenciais; custos negativos ok se sem ciclo negativo) | fluxo de custo minimo de s a t, com limite opcional de fluxo | Grafos | testado (brute, 2026-11-11) |
| `code/flow/mcmf_spfa.cpp` | Min-cost max-flow simples com SPFA (aceita custos negativos sem ciclo negativo) | igual a mcmf.cpp, porem mais curto (bom para colar rapido, grafos pequenos) | Grafos | compila |
| `code/flow/project_selection.cpp` | Fecho maximo / selecao de projetos (closure) via corte minimo | escolhe conjunto S de itens maximizando soma dos lucros p[i] (podem ser | Grafos | compila |
| `code/flow/push_relabel.cpp` | Push-relabel (highest label + gap) - fluxo maximo | fluxo maximo | Grafos | compila |
| `code/flow/simplex.cpp` | Simplex (programacao linear) - estilo KACTL | maximiza c.x sujeito a A x <= b, x >= 0 | Grafos | compila |
| **general/** | | | | |
| `code/general/annealing.cpp` | Simulated annealing e hill climbing | template de recozimento simulado (maximizar score) com T geometrico e limite de tempo | Aleatorização | compila |
| `code/general/buscaternaria.cpp` | Busca ternaria (minimo de funcao convexa/unimodal) | tern_double(l, r) acha o x que minimiza func em [l, r] (250 iteracoes) | Busca binária e otimização | compila |
| `code/general/compressao.cpp` | Compressao de coordenadas | mapeia valores arbitrarios para 0..k-1 preservando a ordem | Arrays e guloso | compila |
| `code/general/debruijn.cpp` | Sequencia de de Bruijn | string ciclica de tamanho k^n contendo toda string de tamanho n sobre alfabeto {0..k-1} exatamente uma vez | Construtivos e interativos | compila |
| `code/general/debug.cpp` | Macro de debug e timer | dbg(x, y, ...) imprime nome e valor em cerr (so com -DLOCAL) | Aleatorização | compila |
| `code/general/diff2d.cpp` | Prefixos 2D, diferencas 2D e maior submatriz de soma maxima | soma de retangulo em O(1) | Estruturas de dados e queries | compila |
| `code/general/fastio.cpp` | Fast IO (leitura/escrita manual com buffer) | leitura de inteiros/strings via fread e escrita via buffer | Como usar quando travar | compila |
| `code/general/gale_ryser.cpp` | Matriz 0/1 com somas de linhas e colunas dadas (Gale-Ryser) e canto noroeste | constroi matriz 0/1 com somas r[i] (linhas) e c[j] (colunas), ou diz que nao existe | Grafos | compila |
| `code/general/gen_exemplo.cpp` | Gerador de testes (exemplo para stress.sh / stress.bat) | gera um caso aleatorio pequeno determinado pela seed (argv[1]) | Amostras de problemas e padrões de ICPC | compila (programa completo) |
| `code/general/grau_seq.cpp` | Sequencias de graus: Erdos-Gallai, Havel-Hakimi, arvore com graus dados | testa se uma sequencia e grafica | Construtivos e interativos | compila |
| `code/general/gray_code.cpp` | Codigo de Gray | g(i) = i ^ (i>>1) percorre todas as mascaras mudando 1 bit por passo | Construtivos e interativos | compila |
| `code/general/guloso_heap.cpp` | Gulosos com heap e arrependimento | (1) jobs com prazo e lucro (1 unidade cada) | Arrays e guloso | compila + testado |
| `code/general/hash_anti.cpp` | Hash customizado anti-hack (unordered_map / gp_hash_table) | splitmix64 com semente aleatoria para unordered_map/unordered_set e pb_ds gp_hash_table | Aleatorização | compila |
| `code/general/int128_io.cpp` | IO de __int128 | le e imprime __int128 (cin/cout nao suportam) | Como usar quando travar | compila |
| `code/general/interativo.cpp` | Template interativo + buscas binarias interativas + interator local | funcao de query com flush, busca binaria por query (valor ate 1e18 em ~60 queries), | Construtivos e interativos | compila (standalone) |
| `code/general/intervalos.cpp` | Intervalos: sweep de eventos, salas, furar, cobrir, k maquinas | maxima sobreposicao (com tratamento de empates), atribuicao de salas, minimo de pontos para furar todos, | Arrays e guloso | compila |
| `code/general/inversoes.cpp` | Contagem de inversoes (merge sort e BIT) e pares com condicao | numero de pares i<j com a[i] > a[j] | Arrays e guloso | compila |
| `code/general/maioria.cpp` | Elemento majoritario: Boyer-Moore, > n/k, e versao aleatorizada | acha candidatos a elemento com frequencia > n/k em O(1)·k de memoria | Arrays e guloso | compila |
| `code/general/mediana_janela.cpp` | Mediana dinamica em janela deslizante (dois multisets) | mantem mediana e soma \|a_i - mediana\| de um multiconjunto com inserir/remover | Arrays e guloso | compila |
| `code/general/meet_middle.cpp` | Meet in the middle (subconjuntos, n <= 40) | gera somas das duas metades e combina com ordenacao + two pointers | Arrays e guloso | compila |
| `code/general/perm_ciclos.cpp` | Ciclos de permutacao, potencia, paridade, trocas minimas | decompoe permutacao em ciclos | Arrays e guloso | compila |
| `code/general/permutacoes.cpp` | Geracao de permutacoes (backtracking) | generatePermutations(nums) devolve todas as permutacoes dos n elementos, | Construtivos e interativos | compila |
| `code/general/pilha_monotonica.cpp` | Pilha monotonica (proximo maior/menor, contribuicao, histograma, lexicografico) | prox/ant maior e menor | Arrays e guloso | compila |
| `code/general/rng.cpp` | RNG para gerar testes e stress | random_a(n) gera n inteiros uniformes em [l, r] | Aleatorização | compila |
| `code/general/subsets.cpp` | Geracao de todos os subconjuntos (por mascara) | subsets(nums) devolve os 2^n subconjuntos de nums (cada um como vetor) | Construtivos e interativos | compila |
| `code/general/template.cpp` | Template base para colar no inicio do arquivo | includes, macros (FORI, FORJ, endl, pb, all, pii), solve() vazio e main | Como usar quando travar | compila (programa completo) |
| `code/general/torneio_landau.cpp` | Torneio com pontuacoes dadas (Landau) | decide se uma sequencia de pontuacoes e de um torneio e constroi o torneio | Construtivos e interativos | compila |
| `code/general/two_pointers.cpp` | Two pointers / janela deslizante (templates) | (1) conta subarrays "bons" quando a propriedade e monotonica (encolher nunca piora) | Arrays e guloso | compila |
| **geometry/** | | | | |
| `code/geometry/angle_sort.cpp` | Sweep angular: contar pontos em semiplano e triangulos que contem a origem | ordena pontos por angulo em torno da origem (exato, com cross) e usa dois | Geometria | compila |
| `code/geometry/calipers.cpp` | Rotating calipers: diametro, largura minima, retangulo envolvente de menor area | sobre um fecho convexo CCW (de hull_andrew.cpp) acha o par mais distante, | Geometria | compila |
| `code/geometry/circles.cpp` | Circulos: interseções, tangentes, area de interseção com poligono, area da uniao | circulo-reta, circulo-circulo, tangentes de ponto e comuns, area de interseção | Geometria | compila |
| `code/geometry/closest_pair.cpp` | Par de pontos mais proximo (sweep + set) | menor distancia^2 entre dois pontos (e os indices) | Geometria | compila |
| `code/geometry/convex_extreme.cpp` | Vertice extremo de poligono convexo numa direcao (busca binaria O(log n)) | dado poligono convexo CCW e direcao dir, devolve o indice do vertice que maximiza | Geometria | compila |
| `code/geometry/convex_layers.cpp` | Camadas convexas (convex layers / onion peeling) e frente de Pareto 2D | layer[i] = indice da camada do ponto i (0 = fecho externo) | Geometria | compila |
| `code/geometry/convexhull.cpp` | Fecho convexo (monotone chain) | convexHull(pontos) devolve o hull em ordem anti-horaria, sem pontos | Geometria | compila |
| `code/geometry/geometry3d.cpp` | Geometria 3D basica + fecho convexo 3D (incremental O(n^2)) | struct P3 (cross, dot), volume de tetraedro (produto misto), distancia ponto-plano, | Geometria | compila |
| `code/geometry/half_plane.cpp` | Interseção de semiplanos (HPI) O(n log n) | acha o poligono convexo (vertices CCW) = interseção de semiplanos "a esquerda de p->p+d" | Geometria | compila |
| `code/geometry/hull_andrew.cpp` | Fecho convexo (Andrew monotone chain) - versao correta | devolve os vertices do fecho convexo em ordem anti-horaria, comecando pelo | Geometria | compila |
| `code/geometry/min_circle.cpp` | Circulo minimo envolvente (Welzl iterativo) e circuncentro | menor circulo contendo todos os pontos | Geometria | compila |
| `code/geometry/minkowski.cpp` | Soma de Minkowski de poligonos convexos | A + B = {a+b} | Geometria | compila |
| `code/geometry/point_dbl.cpp` | Ponto/vetor em ponto flutuante (long double) + primitivas | struct Pd com operadores, rotacao, projecao, reflexao, interseção de retas, | Geometria | compila |
| `code/geometry/point_int.cpp` | Ponto/vetor inteiro + primitivas exatas | struct P (ll) com cross, dot, orientacao, ordenacao angular exata, | Geometria | compila |
| `code/geometry/polygon.cpp` | Poligonos: area, centroide, Pick, ponto em poligono (geral e convexo O(log n)), pontos de rede | area*2 sinalizada (shoelace), centroide, contagem de pontos de rede (Pick), | Geometria | compila |
| `code/geometry/polygon_cut.cpp` | Corte de poligono por semiplano (Sutherland-Hodgman) | devolve a parte do poligono que fica a esquerda (ou sobre) da reta orientada a->b | Geometria | compila |
| `code/geometry/rect_union.cpp` | Area e perimetro da uniao de retangulos (sweep + segtree) | area da uniao de retangulos alinhados aos eixos | Geometria | compila |
| `code/geometry/seg_any_inter.cpp` | Existe interseção entre n segmentos? (Shamos-Hoey, sweep + set) | acha um par de segmentos que se intersectam (inclui toque), ou {-1,-1} | Geometria | compila |
| **graph/** | | | | |
| `code/graph/bcc_block_cut.cpp` | BCC (componentes biconexas por vertices) e Block-Cut Tree | separa o grafo em blocos (BCCs) | Grafos | compila |
| `code/graph/bellman_ford.cpp` | Bellman-Ford (ciclo negativo, -infinito, ciclo explicito) | distancias com pesos negativos | Grafos | compila |
| `code/graph/bfs.cpp` | BFS (busca em largura) | percorre o grafo nao ponderado a partir de start, marcando visitados e | Grafos | compila |
| `code/graph/bfs01.cpp` | 0-1 BFS e BFS com pesos pequenos (Dial) | menor distancia com pesos em {0,1} usando deque (bfs01), ou com pesos | Grafos | compila |
| `code/graph/bipartite.cpp` | Teste de bipartido / 2-coloracao com ciclo impar | colore o grafo com 2 cores por BFS | Grafos | compila |
| `code/graph/bridges_2ecc.cpp` | Pontes, articulacoes e componentes 2-aresta-conexas (bridge tree) | acha pontes e vertices de articulacao | Grafos | compila |
| `code/graph/ciclos.cpp` | Deteccao de ciclos: orientado, nao orientado, girth (menor ciclo nao ponderado) | find_cycle_dir devolve um ciclo orientado | Grafos | compila |
| `code/graph/dijkstra.cpp` | Dijkstra (menores caminhos de fonte unica, pesos nao negativos) | devolve dist[] com a menor distancia de start a todos os vertices | Grafos | compila |
| `code/graph/dijkstra_estados.cpp` | Dijkstra em grafo implicito / de estados (grid, k cupons, camadas) | Dijkstra generico onde os vizinhos sao gerados por uma lambda | Grafos | compila |
| `code/graph/dijkstra_variantes.cpp` | Dijkstra: variantes (denso O(n^2), gargalo/minimax, contagem de caminhos, arestas em | dij_dense (sem heap) | Grafos | compila |
| `code/graph/dsu.cpp` | DSU (union-find com path compression + union by size) | find(u) com compressao | Grafos | compila |
| `code/graph/euler.cpp` | Caminho/circuito euleriano (Hierholzer) - nao direcionado e direcionado | devolve a sequencia de vertices de um circuito/trilha que usa cada aresta | Grafos | compila |
| `code/graph/floyd.cpp` | Floyd-Warshall (distancias, ciclo negativo, caminho, ciclo minimo) | todos-os-pares em O(n^3) | Grafos | compila |
| `code/graph/grafo_funcional.cpp` | Grafo funcional (cada vertice tem exatamente uma aresta de saida) | acha os ciclos, e para cada vertice: se esta no ciclo, id do ciclo, posicao, | Grafos | compila |
| `code/graph/johnson.cpp` | Johnson (todos-os-pares com pesos negativos, esparso) | Bellman-Ford de super-fonte para achar potenciais h, reponderar | Grafos | compila |
| `code/graph/kruskal.cpp` | Kruskal: arvore geradora minima | calcula a MST de um grafo nao direcionado e diz se ele e conexo | Grafos | compila |
| `code/graph/kth_walks.cpp` | K menores caminhos (walks) de s a t | devolve os k menores comprimentos de walks (vertices/arestas podem repetir) | Grafos | compila |
| `code/graph/range_graph.cpp` | Grafo com arestas para intervalos (segtree de arestas) + Dijkstra | permite arestas u -> [l,r] e [l,r] -> v com custo w usando duas arvores | Grafos | compila |
| `code/graph/scc_kosaraju.cpp` | SCC (Kosaraju iterativo) | componentes fortemente conexas | Grafos | compila |
| `code/graph/scc_tarjan.cpp` | SCC (Tarjan iterativo) + condensacao | componentes fortemente conexas | Grafos | testado (brute, 2026-11-11) |
| `code/graph/spfa.cpp` | SPFA (Bellman-Ford com fila) | menor caminho com pesos negativos | Grafos | compila |
| `code/graph/toposort.cpp` | Ordenacao topologica (Kahn) | devolve uma ordem topologica de um DAG | Grafos | compila |
| `code/graph/two_sat.cpp` | 2-SAT | decide satisfatibilidade de clausulas de 2 literais e devolve uma atribuicao | Grafos | testado (brute, 2026-11-11) |
| **math/** | | | | |
| `code/math/bsgs.cpp` | Logaritmo discreto (BSGS) para modulo qualquer | menor x >= 0 com a^x = b (mod m), ou -1 se nao existe | Teoria dos números e divisores | compila |
| `code/math/crt.cpp` | CRT geral (modulos nao coprimos) e Garner | crt_merge combina x=a1 (m1) e x=a2 (m2) em x=r (lcm) | Teoria dos números e divisores | compila |
| `code/math/divisores.cpp` | Divisores: listar, formulas, altamente compostos, serie geometrica | divisores de n por sqrt | Teoria dos números e divisores | compila |
| `code/math/exgcd.cpp` | Euclides estendido, diofantina linear, contagem de solucoes em caixa | exgcd | Teoria dos números e divisores | compila |
| `code/math/floor_sum.cpp` | Floor sum (algoritmo tipo Euclides) | floor_sum = sum_{i=0}^{n-1} floor((a*i+b)/m) exato (cabe em ll se | Teoria dos números e divisores | compila |
| `code/math/inv_lote.cpp` | Inversos modulares em lote | inv[1..n] mod p linear | Teoria dos números e divisores | compila |
| `code/math/miller_rabin.cpp` | Miller-Rabin deterministico (64 bits) | testa primalidade de n < 2^64 de forma exata | Teoria dos números e divisores | compila |
| `code/math/mint.cpp` | mint: struct de inteiro modular | aritmetica mod MOD (primo) com operadores, pow e inverso | Teoria dos números e divisores | compila |
| `code/math/mod.cpp` | Aritmetica modular e utilidades de inteiros | gcd, lcm, soma/subtracao/multiplicacao mod MOD, exponenciacao e inverso | Teoria dos números e divisores | compila |
| `code/math/ntt.cpp` | NTT (Number Theoretic Transform) modulo 998244353 | convolucao/multiplicacao de polinomios com raiz primitiva 3 | Álgebra, polinômios e FFT | compila |
| `code/math/pollard_rho.cpp` | Pollard rho (Brent) + fatoracao completa | fatora n < 2^63 (~9e18 | Teoria dos números e divisores | testado (brute, 2026-11-11) |
| `code/math/primitive_root.cpp` | phi, lambda de Carmichael, ordem multiplicativa, raiz primitiva | phi(n) e lambda(n) por trial division | Teoria dos números e divisores | compila |
| `code/math/sieve.cpp` | Crivo de Eratostenes | marca is_prime[0..MAXN] e guarda todos os primos em primes | Teoria dos números e divisores | compila |
| `code/math/sieve_linear.cpp` | Crivo linear (menor fator primo, phi, mu, tau, sigma) | em O(N) calcula lp[i] (menor fator primo), lista de primos, phi, mu, | Teoria dos números e divisores | compila |
| `code/math/sieve_seg.cpp` | Crivo segmentado (primos e phi em [L, R]) | primos em [L,R] e phi de cada numero do intervalo, usando so os | Teoria dos números e divisores | compila |
| `code/math/tonelli.cpp` | Raiz quadrada modular (Tonelli-Shanks) e simbolo de Jacobi | x com x^2 = a (mod p), p primo | Teoria dos números e divisores | compila |
| **string/** | | | | |
| `code/string/aho_corasick.cpp` | Aho-Corasick | automato de varios padroes | Strings | compila |
| `code/string/bitset_match.cpp` | Matching e LCS com bitset | (1) ocorrencias de p em t por bitset (util quando ha variacoes tipo | Strings | compila + testado |
| `code/string/eertree.cpp` | Eertree (arvore de palindromos) + particao em palindromos (serie link) | no por palindromo distinto (<= n nos) | Strings | compila |
| `code/string/hash.cpp` | Hash polinomial de string (prefix hash) | StringHash(s) monta o hash dos prefixos | Strings | compila |
| `code/string/hash2d.cpp` | Hash 2D de submatrizes (mod 2^61-1) | hash de qualquer submatriz em O(1) | Strings | compila |
| `code/string/hash61.cpp` | Hash polinomial mod 2^61-1 (substrings, LCP, palindromo, concatenacao) | hash de substring em O(1) com base aleatoria | Strings | compila |
| `code/string/kmp.cpp` | Prefix function (KMP), automato KMP, bordas, periodos | pi[i] = maior borda propria de s[0..i] | Strings | testado (brute, 2026-11-11) |
| `code/string/lyndon.cpp` | Duval (fatoracao de Lyndon) e rotacao minima | duval(s) fatora s em palavras de Lyndon nao-crescentes | Strings | compila |
| `code/string/manacher.cpp` | Manacher (palindromos) | d1[i] = nro de palindromos de tamanho impar centrados em i (raio incl | Strings | testado (brute, 2026-11-11) |
| `code/string/suffix_array.cpp` | Suffix array + LCP + RMQ de LCP | sa (sufixos ordenados), rnk, lcp[i] = LCP(sa[i-1], sa[i]) (lcp[0]=0), | Strings | testado (brute, 2026-11-11) |
| `code/string/suffix_automaton.cpp` | Suffix automaton (SAM), incluindo generalizado | automato minimo dos sufixos | Strings | testado (brute, 2026-11-11) |
| `code/string/trie.cpp` | Trie (arvore de prefixos) para minusculas | insert(p) insere a palavra p | Strings | compila + testado |
| `code/string/zfunc.cpp` | Z-function | z[i] = LCP de s e s[i..] | Strings | testado (brute, 2026-11-11) |
| **tree/** | | | | |
| `code/tree/centroid.cpp` | Centroid decomposition (arvore de centroides + distancias por nivel) | constroi a arvore de centroides (altura <= log n) | Árvores | compila |
| `code/tree/centroid_paths.cpp` | Contar pares (u<v) com dist(u,v) <= K via centroide (arestas ponderadas >= 0) | para cada centroide junta as distancias da componente, conta pares com | Árvores | compila |
| `code/tree/hld.cpp` | Heavy-Light Decomposition + segtree sobre monoide (caminho e subarvore) | decompoe a arvore em cadeias pesadas | Árvores | testado (brute, 2026-11-11) |
| `code/tree/hld_bit.cpp` | HLD com BIT range-add / range-sum (soma e add em caminho e subarvore) | add x em todos os vertices de um caminho / subarvore e soma sobre | Árvores | compila |
| `code/tree/lca_lifting.cpp` | LCA com binary lifting (+ k-esimo ancestral, distancia, k-esimo no caminho) | pre-processa pai 2^k de cada vertice | Árvores | testado (brute, 2026-11-11) |
| `code/tree/lca_sparse.cpp` | LCA O(1) com sparse table sobre a ordem de DFS (n posicoes) | LCA em O(1) por query | Árvores | compila |
| `code/tree/lca_tarjan.cpp` | LCA offline de Tarjan (DFS + DSU) | responde um lote de queries (u,v) de LCA sem tabela de saltos | Árvores | compila |
