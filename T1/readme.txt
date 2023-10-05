- O código foi separado em três arquivos, sendo o app.c a main e os arquivos board.c e board.h onde 
as funções e os tipos de dados foram implementados e definidos. 

- A matriz principal do jogo foi alocada dinamicamente com base no tamanho e na quantidade de minas 
especificadas pelo usuário. 

- O tempo de jogo, tanto do usuário quanto do computador, são exibidos no final da partida, junto com 
as posições de todas as minas e da pontuação que foi calculada com base no número de posições vazias 
encontradas. 

- A lógica de resolução do computador foi feita com base na definição de possíveis minas. Antes de cada 
escolha randômica nas posições vazias do tabuleiro, possíveis minas são definidas com base na quantidade 
de números presentes em um espaço 2x2, onde se existe 3 posições de números conhecidas e uma posição vazia 
no espaço de análise a posição vazia é definida como uma possível mina. Posições de possíveis minas não 
são selecionadas como jogadas válidas do computador. 

- O jogo termina quanto alguma mina é encontrada ou 
quando o número de espaços vazio é igual ao número de minas, o que significa uma vitória. 

- A matriz é desalocada após o término do jogo. 