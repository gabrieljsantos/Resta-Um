


## Pasta `sandbox`

A pasta `sandbox` serve como um ambiente de testes isolado do projeto principal.
Você pode criar, editar e compilar pequenos exemplos nela sem interferir no código oficial.

Dentro dessa pasta, crie um diretório com o nome do seu teste e faça o que quiser — ela funciona como um espaço de rascunho.
Por enquanto contém alguns arquivos e configurações específicas que só funcionam no **VS Code**, mas se não quiser testar nada, ignore a pasta.

Por exemplo, se quiser testar uma função nova, configurar uma tela da **Raylib** ou validar algum comportamento gráfico, faça isso dentro da `sandbox`.
Dessa forma, o projeto principal permanece limpo e estável enquanto você experimenta e desenvolve livremente.

E detalhe: a ideia de manter esses testes na pasta `sandbox` é **exclusivamente didática**, voltada para **compartilhar curiosidades e aprendizados**, sem impacto no código oficial do projeto.


---

## Pasta `empty_project_template`

É o **template base** usado como estrutura do nosso projeto.
Nele já estão todas as **dependências necessárias para a Raylib funcionar**, inclusive os **créditos do desenvolvedor original** do template.

---

## Raylib

Segundo o ChatGPT, A **Raylib** é uma biblioteca em **C/C++** voltada para **criação de jogos e aplicações gráficas**.
Ela oferece uma interface simples para trabalhar com **gráficos 2D/3D, sons, entrada de teclado, mouse e janelas**, sendo ideal para projetos acadêmicos e protótipos rápidos.
Foi desenvolvida para ser **leve, multiplataforma e de fácil aprendizado**.

---



# Resta Um — Projeto de Programação 2 (C++) 

## 
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


## Exemplo de futura Estrutura do repositório

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

## Autoria / Participantes

* Cauã Cruz dos Santos
* Gabriel Carvalho Tenório
* Eduardo de jesus santos
* Gabriel de Jesus Santos
* Anderson Santos Santana
* Alysson Santos
* Gabriel da Silva Bispo

## Referências

* Descrição clássica do jogo Resta Um / Peg Solitaire.
* Materiais de apoio da disciplina de Programação 2.
