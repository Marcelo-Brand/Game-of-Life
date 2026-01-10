#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#define RED     "\033[91m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"

using namespace std;

void print_grid(void);
void alive_neighbors(void);
void judge(int pos_x, int pos_y, int n_neighbor);
void add_life(void);

const int SIZE_X = 166;
const int SIZE_Y = 50;

// Real matrices
bool memory_A[SIZE_X][SIZE_Y];
bool memory_B[SIZE_X][SIZE_Y];

// Pointers of game
bool (*grid)[SIZE_Y] = memory_A;
bool (*next_grid)[SIZE_Y] = memory_B;

int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};


int main(void) {
    
    add_life();
    
    while (true){
        
        print_grid();
        
        // Calculate and change matrice
        alive_neighbors();
        
        
        // Double Buffering        
        bool (*temp)[SIZE_Y] = grid;
        grid = next_grid;
        next_grid = temp;

        cin.get();

        system("cls");
    }
}

void add_life(void) {

    for (int i = 0; i < SIZE_X; i++) {
        
        int mid = SIZE_Y / 2;
        grid[i][mid] = true;
        grid[i][mid + 1] = true;

    }

    /*for (int i = 0; i < SIZE_Y; i++) {

        int mid = SIZE_X / 2;
        grid[mid][i] = true;
        grid[mid + 1][i] = true;

    }*/
    
}


void print_grid(void) {

    
    for (int i = 0; i < SIZE_Y; i++) {
        for (int j = 0; j < SIZE_X; j++) {

            if (grid[j][i] == true) {
                cout << "#";
            }
            else {
                cout << " ";
            }
        }

        cout << "\n";
    }


}

void alive_neighbors(void) {


    for (int i = 0; i < SIZE_X; i++) {
        
        for (int j = 0; j < SIZE_Y; j++) {
            
            int neighbor = 0;
            for (int k = 0; k < 8; k++) {

                int pos_x = i + dx[k];
                int pos_y = j + dy[k];
                

                if (pos_x >= SIZE_X || pos_y >= SIZE_Y) {
                    continue;
                }
                else if (pos_x < 0 || pos_y < 0) {
                    continue;
                }

                if (grid[pos_x][pos_y]) {
                    neighbor++;
                }
            }
            judge(i, j, neighbor);

            

        }
    }
}

void judge(int pos_x, int pos_y, int n_neighbor) {

    //  
    if (grid[pos_x][pos_y]) {
        // Still alive
        if (n_neighbor == 2 || n_neighbor == 3) {
            next_grid[pos_x][pos_y] = true;
        }
        // Still dead
        else {
            next_grid[pos_x][pos_y] = false;
        }
    }
    else {
        // Born case
        if (n_neighbor == 3) {
            next_grid[pos_x][pos_y] = true;
        }
        // Reset
        else {
            next_grid[pos_x][pos_y] = false;
        }
    }  
}


//Solidão(Morte) : Qualquer célula viva com menos de
//2 vizinhos vivos morre(como se fosse por isolamento).
//
//Sobrevivência : Qualquer célula viva com 2 ou 3 vizinhos 
//vivos continua viva na próxima geração.
//
//Superpopulação(Morte) : Qualquer célula viva com mais de 3 vizinhos 
//vivos morre(como se fosse por falta de recursos).
//
//Reprodução(Nascimento) : Qualquer célula morta com exatamente 3 vizinhos 
//vivos torna - se uma célula viva.