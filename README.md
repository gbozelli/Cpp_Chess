# CppChess - Jogo de Xadrez em C++ (Terminal)

![GitHub last commit](https://img.shields.io/github/last-commit/SEU_USUARIO_GITHUB/SEU_REPOSITORIO.svg?style=for-the-badge)
![GitHub top language](https://img.shields.io/github/top-language/SEU_USUARIO_GITHUB/SEU_REPOSITORIO.svg?style=for-the-badge)
![GitHub license](https://img.shields.io/github/license/SEU_USUARIO_GITHUB/SEU_REPOSITORIO.svg?style=for-the-badge)

## 🚀 Sobre o Projeto

`CppChess` é um projeto de um jogo de xadrez para terminal desenvolvido em C++. O objetivo é criar uma implementação funcional das regras básicas do xadrez, permitindo que dois jogadores humanos interajam com o tabuleiro e as peças através de comandos no terminal.

Este projeto está em desenvolvimento e serve como um exercício prático em Programação Orientada a Objetos (POO) com C++, utilizando conceitos como herança, polimorfismo e gerenciamento de memória.

## ✨ Funcionalidades Atuais

* **Representação do Tabuleiro:** Exibição simples do tabuleiro no terminal.
* **Inicialização das Peças:** Posicionamento inicial de todas as peças de xadrez (peões, torres, cavalos, bispos, rainhas, reis) para ambos os jogadores.
* **Movimento Básico de Peças:** Capacidade de selecionar uma peça pela sua posição atual e mover para uma nova posição.
* **Estrutura de Peças:** Classes individuais para cada tipo de peça (Rook, Knight, Bishop, Queen, King, Pawn) herdando de uma classe base `Piece`.
* **Validação de Movimento (Básica):** Implementação inicial de funções como `movIsValid` e `atkIsValid` para algumas peças.
* **Gerenciamento de Memória:** Utiliza `new` e `delete` para peças, com destrutor virtual na classe `Piece` para evitar vazamentos de memória em polimorfismo.

## ⚠️ Limitações e Próximos Passos (To-Do)

O projeto ainda está em fase inicial de desenvolvimento e possui as seguintes limitações:

* **Regras Completas do Xadrez:** A validação de movimentos (`movIsValid`, `atkIsValid`) para a maioria das peças é básica e **não implementa todas as regras complexas** do xadrez (ex: movimento em L do cavalo, diagonais do bispo, bloqueios, movimentos de abertura do peão, captura *en passant*, roque, promoção de peão, etc.).
* **Lógica de Xeque e Xeque-Mate:** As verificações de xeque, xeque-mate e condições de empate (afogamento, repetição, material insuficiente) ainda não estão totalmente implementadas ou são rudimentares.
* **Controle de Turnos:** A lógica de alternância de turnos está presente, mas a validação de que o jogador está movendo sua própria peça e que não está se colocando em xeque precisa ser aprimorada.
* **Design de `isSquareAttacked`:** A função `isSquareAttacked` precisa de uma refatoração para iterar pelas peças existentes no tabuleiro, em vez de tentar criar "peças dummy".
* **Tratamento de `NULL`:** As verificações de `NULL` em `movIsValid` e `atkIsValid` nas classes das peças precisam ser ajustadas para comparar com o caractere de "espaço vazio" (`' '`) ou identificar se o quadrado contém uma peça do oponente. `NULL` é para ponteiros, não para caracteres.
* **Iteração de `std::list`:** Em algumas funções de validação de movimento (`movIsValid`, `atkIsValid`) das peças, o iterador `it` de `std::list` é incrementado múltiplas vezes dentro da mesma iteração de um loop `for` ou `if` (ex: `y==*(it++)`), o que pode causar saltos de elementos e lógica incorreta. Isso precisa ser revisado.
* **Sem IA:** Não há inteligência artificial para jogar contra. É um jogo para dois jogadores humanos.
* **Sem Histórico de Movimentos:** O jogo não mantém um registro completo dos movimentos.
* **Estrutura do Tabuleiro:** Atualmente, o `gameBoard` é uma variável global, o que pode ser refatorado para ser um membro da classe `Board` para um design mais encapsulado.

Contribuições para resolver estas limitações são muito bem-vindas!

## ⚙️ Como Compilar

Este projeto pode ser compilado usando um compilador C++ como `g++`.

1.  **Clone o repositório:**
    ```bash
    git clone https://github.com/SEU_USUARIO_GITHUB/SEU_REPOSITORIO.git
    cd SEU_REPOSITORIO
    ```
2.  **Compile o projeto:**
    ```bash
    g++ -std=c++11 -I./include src/*.cpp -o chess_game
    ```
    * `-std=c++11`: Garante a compatibilidade com o padrão C++11.
    * `-I./include`: Informa ao compilador para procurar arquivos de cabeçalho na pasta `include`.
    * `src/*.cpp`: Compila todos os arquivos `.cpp` dentro da pasta `src`.
    * `-o chess_game`: Define o nome do executável de saída como `chess_game`.

## ▶️ Como Jogar

Após a compilação bem-sucedida, execute o jogo a partir do terminal:

```bash
./chess_game
