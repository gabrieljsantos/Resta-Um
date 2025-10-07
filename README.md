# Resta Um — Projeto de Programação 2 (C++)

## Descrição

Implementação do jogo de tabuleiro **Resta Um** (peg solitaire) em C++ como projeto da disciplina de Programação 2. O objetivo é reproduzir as regras clássicas, fornecer uma interface em terminal para jogar e demonstrar organização de código, uso de estruturas de dados e testes básicos.

## Regras do jogo

* Tabuleiro inicial com peças ocupando quase todas as posições, exceto um buraco central (configuração clássica).
* Uma peça pode pular sobre uma peça adjacente (horizontal ou vertical) para uma casa vazia imediatamente após a peça pulada; a peça pulada é removida.
* Objetivo: restar apenas 1 peça no tabuleiro (idealmente no centro).
* Jogo termina quando não há movimentos válidos ou quando resta 1 peça.

## Funcionalidades implementadas

* Representação do tabuleiro (matriz).
* Movimentação válida (checar salto e remoção).
* Interface em terminal para entrada de jogadas (coordenadas).
* Validação de movimentos e detecção de fim de jogo.
* Contador de peças restantes.
* Salvamento/carregamento simples do estado do jogo (arquivo de texto).
* Modo solução automática (heurística simples / backtracking) — opcional/implementado conforme especificação do grupo.

## Requisitos

* Compilador C++ compatível com C++17 (g++, clang).
* Make (opcional) para automação de build.
* Sistema operacional: multiplataforma (Linux, macOS, Windows via MinGW).

## Como compilar (exemplo)

Usando g++:

```
g++ -std=c++17 src/*.cpp -Iinclude -O2 -o bin/resta_um
```

Com Makefile (se disponível):

```
make
```

## Como executar

```
./bin/resta_um
```

ou em Windows:

```
bin\resta_um.exe
```

Ao iniciar, siga as instruções no terminal para:

* Selecionar configuração inicial do tabuleiro (clássica ou customizada).
* Inserir jogadas no formato: `linha origem, coluna origem -> linha destino, coluna destino` (ex.: `3 1 3 3`) — adaptar conforme a interface implementada.
* Salvar/Carregar partida quando solicitado.

## Estrutura sugerida do repositório

```
/ (raiz)
├─ src/
│  ├─ main.cpp
│  ├─ board.cpp
│  ├─ board.h
│  ├─ game.cpp
│  ├─ game.h
│  └─ io.cpp
├─ include/
│  └─ (headers públicos, se necessário)
├─ tests/
│  └─ test_board.cpp
├─ data/
│  └─ saved_game.txt
├─ bin/
│  └─ resta_um (executável)
├─ Makefile
└─ README.md
```

## Padrões e boas práticas adotadas

* Código modular (separação entre lógica do jogo e I/O).
* Comentários sucintos e function-level documentation.
* Tratamento de erros e validações de entrada.
* Testes unitários básicos para funções críticas (validação de movimentos, contagem de peças).

## Possíveis melhorias (próximos passos)

* Interface gráfica simples (SDL2/raylib) para melhor visualização.
* Algoritmo de solução eficiente (A*, DFS com poda).
* Modo de níveis e variantes de tabuleiro.
* Estatísticas de partidas e replay.
* Testes automatizados completos (unitários e integração).

## Como contribuir

1. Fazer fork do repositório.
2. Criar branch para sua feature: `feature/nome-da-feature`.
3. Implementar e testar localmente.
4. Enviar Pull Request descrevendo mudanças e testes realizados.

## Licença

Projeto sob a licença MIT — consulte o arquivo `LICENSE` para detalhes.

## Autoria / Participantes

* Cauã Cruz dos Santos
* Gabriel Carvalho Tenório
* Eduardo de jesus santos
* Gabriel de Jesus Santos
* Anderson Santos Santana
* Alysson Santos

## Referências

* Descrição clássica do jogo Resta Um / Peg Solitaire.
* Materiais de apoio da disciplina de Programação 2.
