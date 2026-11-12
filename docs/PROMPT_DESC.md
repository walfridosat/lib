# Tarefa para o DeepSeek: bloco de descrição em cada .cpp (estilo SamuellH12)

Repositório: `C:\Users\WINDOWS\Documents\lib` (branch `main`). Não faça commit nem push: o dono revisa antes.
Referência de estilo: https://github.com/SamuellH12/Competitive-Programming-Algorithms, pasta `Library/`. O código vem primeiro, enxuto, e no fim fica um bloco `/*LATEX_DESC_BEGIN ... LATEX_DESC_END*/`.
**Modelo pronto nesta lib:** `code/flow/dinic.cpp`. Leia antes de começar e siga o mesmo formato.

Use subagentes em paralelo, um por lote (seção 5). Cada lote é independente.

## 1. O que fazer em cada arquivo

Só mexa em COMENTÁRIOS.

1. **Topo:** troque o cabeçalho longo (`// O que faz / Quando usar / Complexidade / Uso / Cuidados`) por UMA linha: `// Nome curto - o que e`.
   - Na combinatória, mantenha logo abaixo a linha `// Requer: code/combinatorics/binom_mod.cpp (cole antes)`.
2. **Corpo:** mantenha os comentários inline curtos (≤ ~50 caracteres) que ajudam a digitar. Explicações longas saem do código e vão para "Sobre o codigo".
3. **Fim do arquivo:** acrescente o bloco abaixo, nesta ordem.

```
/*LATEX_DESC_BEGIN***************************
-> **Nome**
1-2 linhas do que faz (+ indexacao 0/1-based).

Complexidade: ...
Uso:
  exemplo de chamada da API, uma por linha

* Sobre o codigo:
  a ideia do algoritmo em 2-5 linhas; papel das variaveis principais.

* Problemas e reducoes:
  + problema classico -> como modelar com esta tecnica (3-8 itens, concretos e corretos)

Cuidados: overflow, bordas, armadilhas.
Catalogo: secao do catalogo (esta no cabecalho antigo, em "Quando usar").
Digitacao: N linhas | facil/media/dificil. Atalho: (opcional) como digitar menos.
*****************************LATEX_DESC_END*/
```

Regras do bloco:

- **Arquivos triviais** (fastio, debug, int128_io…): bloco de no máximo 10 linhas.
- **Sem acento.** Português sem acentos, porque a lib é impressa.
- **Não perca informação.** API e cuidados do cabeçalho antigo vão para o bloco.
- **Só o que tiver certeza.** Nos itens de "Problemas e reducoes", só reduções corretas; na dúvida, omita.

## 2. Proibido mudar código

Só comentários e espaços podem mudar. Ao terminar cada lote, rode:

```
python docs/tokcheck.py code/<pasta>
```

O resultado precisa ser `codigo alterado: 0` e nenhum arquivo do lote na lista "sem DESC". O script compara com o git HEAD ignorando comentários e espaços. Se acusar mudança, desfaça com `git checkout -- <arquivo>` e refaça só os comentários.

## 3. Relatório de digitabilidade (para ICPC presencial)

Para cada arquivo, escreva em `docs/digitacao.md` uma linha:

`- code/x/y.cpp | N linhas de codigo | facil/media/dificil | sugestao concreta para encurtar (ou "ok")`

Exemplos de sugestão útil:

- função que duplica outra (no dinic, `cut()` vira `lvl[u] >= 0` depois do `flow`);
- helper que o template já tem;
- parte opcional que podia ir para um arquivo à parte;
- estrutura verbosa.

NÃO aplique as sugestões no código.

## 4. Fluxo e matching: atenção especial (`code/flow/*`)

Nos arquivos de fluxo, a seção "Problemas e reducoes" deve ser LONGA: de 8 a 15 itens. Cada item traz o problema e o **modelo do grafo**: quais vértices, quais arestas, que capacidade/custo, e como ler a resposta. Use a lista abaixo como base, ponha cada modelo no arquivo em que ele se resolve (Dinic, MCMF, Hopcroft-Karp, Hungarian, lower bounds, Gomory-Hu, Kuhn, König, cobertura de DAG, project selection…) e complete com o que mais souber de certo.

**Corte e fluxo máximo (dinic, push_relabel, project_selection)**
- **Corte mínimo s–t** = fluxo máximo. Lado S = alcançáveis de s no residual. Arestas do corte = de S para T saturadas.
- **Caminhos disjuntos em arestas** (Menger) com cap 1 em cada aresta. Disjuntos em vértices: v vira v\_in → v\_out com cap 1. O fluxo é o número de caminhos; recupere cada um andando pelas arestas com fluxo.
- **Remover o mínimo de vértices para desconectar s de t:** split v\_in → v\_out com cap 1 (ou custo do vértice), arestas originais com INF.
- **Project selection / closure:** s → projeto (lucro p), máquina → t (custo c), projeto → máquina com INF. Resposta = Σp − corte. Compre as máquinas do lado S.
- **Closure de peso máximo** em grafo dirigido: s → v (w > 0), v → t (−w se w < 0), arestas originais com INF. Resposta = Σ positivos − corte.
- **Segmentação binária** (cada item em A ou B, com custos a\_i, b\_i e penalidade p\_ij por separar i e j): s → i cap a\_i (pago se i ficar em B), i → t cap b\_i, i ↔ j cap p\_ij.
- **Escolha em cadeia** (cada variável escolhe um valor de 1..k, com custo, e |x\_i − x\_j| ≤ d): cadeia de k vértices por variável com arestas INF para trás e arestas INF entre cadeias.
- **Grid: menor número de células bloqueadas para separar dois pontos:** split de células com cap 1, vizinhos com INF.
- **Densest subgraph:** binária em g; s → v com cap m, v → t com cap m + 2g − deg(v), arestas com cap 1 nos dois sentidos.
- **Baseball elimination:** s → jogo (cap jogos restantes), jogo → os 2 times, time → t (cap w\_max − w\_time). Eliminado se não satura.

**Matching e cobertura (kuhn, hopcroft_karp, konig, dag_path_cover, blossom)**
- **Matching bipartido máximo:** s → L cap 1, L → R cap 1, R → t cap 1. Com Hopcroft-Karp é O(E√V).
- **König:** cobertura mínima de vértices = matching máximo. Os vértices são L não alcançados + R alcançados a partir dos L livres no residual. Independente máximo = n − matching.
- **Cobertura mínima de DAG por caminhos disjuntos em vértices:** n − matching no bipartido (u\_out, v\_in). Caminhos não disjuntos: o mesmo com fecho transitivo, e isso é igual à maior anticadeia (Dilworth).
- **Atribuição com capacidades** (cada pessoa faz até c\_p, cada tarefa recebe até d\_t): s → p cap c\_p, p → t' cap 1, t' → t cap d\_t.
- **Tabuleiro: máximo de peças que não se atacam (dominós, torres):** bipartido por cor da casa ou linha × coluna. Torres: aresta linha i – coluna j por casa livre.
- **Matching em grafo geral** (não bipartido) usa blossom; com pesos, blossom ponderado ou DP de máscara para n ≤ 20.
- **Hall:** existe matching que satura L sse |N(S)| ≥ |S| para todo S ⊆ L. Use para provar impossibilidade ou para binária + fluxo.

**Custo mínimo (mcmf, mcmf_spfa, hungarian)**
- **Atribuição de custo mínimo** n × n: Hungarian O(n³), ou MCMF com s → i, i → j (custo), j → t.
- **k caminhos disjuntos de custo total mínimo:** MCMF com fluxo k.
- **Custo convexo por quantidade** (f(x) convexo): arestas paralelas cap 1 com custos f(1) − f(0), f(2) − f(1), …
- **Maximizar lucro:** use custo = −lucro. Pare quando o custo marginal ficar ≥ 0, se o fluxo não precisa ser máximo.
- **Intervalos ponderados com até k sobrepostos em cada ponto:** linha i → i+1 cap k custo 0, e cada intervalo [l, r) vira l → r cap 1 custo −w.
- **Transporte** (oferta e demanda com custo por unidade): s → fornecedor cap oferta, fornecedor → cliente custo c, cliente → t cap demanda.
- **Carteiro chinês dirigido** e "tornar o grafo euleriano com custo mínimo": balanceie os graus com MCMF.

**Limites inferiores e circulação (flow_lower_bounds)**
- **Aresta com l ≤ f ≤ u:** cap u − l. Some l à demanda do destino e à oferta da origem, crie S′ e T′, e adicione T → S com INF. Há fluxo viável sse S′ → T′ satura.
- **Fluxo mínimo com limites inferiores:** primeiro o viável, depois rode o fluxo de t para s no residual, sem a aresta T → S.
- **Arredondamento de matriz** (arredondar cada célula para cima ou para baixo mantendo as somas de linha e coluna): linhas → colunas com cap [⌊a⌋, ⌈a⌉].

**Cortes entre todos os pares (gomory_hu)**
- **Gomory-Hu:** n − 1 fluxos geram uma árvore em que o corte mínimo u–v = menor aresta no caminho. Serve para "min cut de todos os pares" e para "o par com maior corte".

## 5. Lotes (um subagente por lote)

| Lote | Arquivos |
| --- | --- |
| 1 | code/ds, de aliens.cpp até kdtree.cpp (21 arquivos, ordem alfabética) |
| 2 | code/ds, de lichao.cpp até wavelet.cpp (20 arquivos) |
| 3 | code/general (30 .cpp; stress.sh e stress.bat só ganham 2–4 linhas de uso no topo) |
| 4 | code/dp (22) + code/algebra (8) |
| 5 | code/graph (23) + code/tree (7) |
| 6 | code/flow, exceto dinic.cpp que já está feito (15), + code/string (13). Fluxo segue a seção 4. |
| 7 | code/math (16) + code/combinatorics (15) |
| 8 | code/geometry (18) |

Ao terminar: rode `python docs/tokcheck.py`. O resultado deve ser `codigo alterado: 0 | sem bloco DESC: 0`.

Depois disso, avise o dono para pedir a revisão ao Claude. A revisão confere as reduções de fluxo, roda os testes e faz commit e push.
