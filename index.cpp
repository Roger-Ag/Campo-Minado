#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define TAM 5  // Define o tamanho do tabuleiro (5x5)
#define MINAS 5 // Define a quantidade de minas no tabuleiro

int main() {
    char mapa[TAM][TAM];  // Cria o tabuleiro
    int minas[TAM][TAM];  // Cria a matriz de minas
    int jogadas = 0;       // Contador de jogadas válidas
    int jogoTerminado = 0; // Indicador de término do jogo

    // Inicializa o mapa e a matriz de minas
    for (int i = 0; i < TAM; ++i) {
        for (int j = 0; j < TAM; ++j) {
            mapa[i][j] = '-'; // Inicializa cada célula do mapa como oculta (-)
            minas[i][j] = 0;  // Inicializa cada célula da matriz de minas com 0 (sem mina)
        }
    }

    // Coloca as minas aleatoriamente
    srand(time(0)); // Inicializa o gerador de números aleatórios
    int colocadas = 0; // Contador de minas colocadas
    while (colocadas < MINAS) {
        int linha = rand() % TAM;  // Gera uma linha aleatória
        int coluna = rand() % TAM; // Gera uma coluna aleatória
        if (minas[linha][coluna] == 0) { // Verifica se a célula está livre
            minas[linha][coluna] = -1; // Marca a célula como mina
            colocadas++;              // Incrementa o contador de minas colocadas
            // Atualiza a contagem de minas nas posições adjacentes
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int nl = linha + i, nc = coluna + j;
                    if (nl >= 0 && nl < TAM && nc >= 0 && nc < TAM && minas[nl][nc] != -1) {
                        minas[nl][nc]++; // Incrementa o contador de minas adjacentes
                    }
                }
            }
        }
    }

    // Loop principal do jogo
    while (!jogoTerminado) {
        // Imprime o mapa atual
        cout << "  ";
        for (int i = 0; i < TAM; ++i) {
            cout << i << " ";
        }
        cout << endl;
        for (int i = 0; i < TAM; ++i) {
            cout << i << " ";
            for (int j = 0; j < TAM; ++j) {
                cout << mapa[i][j] << " ";
            }
            cout << endl;
        }

        // Lê a entrada do usuário (linha e coluna)
        cout << "Digite a linha e a coluna (ex: 1 2): ";
        int linha, coluna;
        cin >> linha >> coluna;

        // Verifica se a posição é válida
        if (linha < 0 || linha >= TAM || coluna < 0 || coluna >= TAM) {
            cout << "Posição inválida!" << endl;
            continue; // Volta para o início do loop
        }

        // Verifica se a posição já foi revelada
        if (mapa[linha][coluna] != '-') {
            cout << "Posição já revelada!" << endl;
            continue; // Volta para o início do loop
        }

        jogadas++; // Incrementa o contador de jogadas válidas

        // Verifica se a posição escolhida é uma mina
        if (minas[linha][coluna] == -1) {
            mapa[linha][coluna] = '*'; // Marca a mina no mapa
            // Imprime o mapa com a mina revelada
            cout << "  ";
            for (int i = 0; i < TAM; ++i) {
                cout << i << " ";
            }
            cout << endl;
            for (int i = 0; i < TAM; ++i) {
                cout << i << " ";
                for (int j = 0; j < TAM; ++j) {
                    cout << mapa[i][j] << " ";
                }
                cout << endl;
            }
            cout << "Você perdeu! Acertou uma mina." << endl;
            jogoTerminado = 1; // Termina o jogo
        } else {
            // Revela a contagem de minas adjacentes
            mapa[linha][coluna] = '0' + minas[linha][coluna];
            int livres = 0; // Contador de posições livres
            // Conta as posições não reveladas no mapa
            for (int i = 0; i < TAM; ++i) {
                for (int j = 0; j < TAM; ++j) {
                    if (mapa[i][j] == '-') {
                        livres++; // Incrementa o contador de células livres
                    }
                }
            }
            // Verifica se todas as posições livres foram reveladas
            if (livres == MINAS) {
                // Imprime o mapa com todas as células reveladas
                cout << "  ";
                for (int i = 0; i < TAM; ++i) {
                    cout << i << " ";
                }
                cout << endl;
                for (int i = 0; i < TAM; ++i) {
                    cout << i << " ";
                    for (int j = 0; j < TAM; ++j) {
                        cout << mapa[i][j] << " ";
                    }
                    cout << endl;
                }
                cout << "Parabéns! Você venceu!" << endl;
                jogoTerminado = 1; // Termina o jogo
            }
        }
    }
    cout << "Número de jogadas válidas: " << jogadas << endl; // Imprime o número de jogadas

    return 0;
}