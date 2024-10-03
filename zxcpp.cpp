#include <iostream> 
#include <algorithm> 
#include <ctime> 
#include <cstdlib> 
using namespace std;

int pole[100][100];
int field[100][100];
const int N = 9, M = 9, K = 10;

void print_field() {
    system("cls"); // clear screen
    cout << ' ';
    for (int i = 0; i < M; i++) {
        if (i + 1 < 10) cout << ' ';
        cout << ' ' << i + 1;
    }
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << i + 1 << ' ';
        if (i + 1 < 10) cout << ' ';
        for (int j = 0; j < M; j++) {
            if (field[i][j] == -2) cout << "_  ";
            else if (field[i][j] == -1) cout << "f  ";
            else if (field[i][j] == -3) cout << "m  ";
            else cout << field[i][j] << "  ";
        }
        cout << endl;
    }
}

void dfs(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= M || field[x][y] > -2) return;
    field[x][y] = pole[x][y];
    if (field[x][y] > 0) return;
    for (int i2 = x - 1; i2 <= x + 1; i2++) {
        for (int j2 = y - 1; j2 <= y + 1; j2++) {
            if (i2 != x || j2 != y) dfs(i2, j2);
        }
    }
}

bool open_cell(int x, int y) {
    if (pole[x][y] == -1) return false;
    if (pole[x][y] > 0) {
        field[x][y] = pole[x][y];
        return true;
    }
    dfs(x, y);
    return true;
}

bool is_win() {
    int opened = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (field[i][j] >= 0) opened++;
        }
    }
    return (N * M - K == opened);
}

void generate_field() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            pole[i][j] = 0;
            field[i][j] = -2;
        }
    }
    int mines_placed = 0;
    while (mines_placed < K) {
        int x = rand() % N;
        int y = rand() % M;
        if (pole[x][y] != -1) {
            pole[x][y] = -1;
            mines_placed++;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (pole[i][j] != -1) {
                for (int i2 = i - 1; i2 <= i + 1; i2++) {
                    for (int j2 = j - 1; j2 <= j + 1; j2++) {
                        if (i2 >= 0 && i2 < N && j2 >= 0 && j2 < M && pole[i2][j2] == -1) {
                            ++pole[i][j];
                        }
                    }
                }
            }
        }
    }
    print_field();
}

int main() {
    srand(time(0)); // для генерации рандомных чисел
    generate_field();

    while (true) {
        cout << "vvedite kommandu (o - open kletka):" << endl;
        string command;
        cin >> command;
        if (command == "o") {
            int x, y;
            cin >> x >> y;
            --x; --y; 
            if (x < 0 || x >= N || y < 0 || y >= M) continue;
            if (!open_cell(x, y)) {
                
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < M; j++) {
                        if (pole[i][j] == -1) field[i][j] = -3;  
                    }
                }
                print_field(); // Вывести поле 
                cout << "lose" << endl;
                string s;
                cin >> s; 
                break; 
            }
            if (is_win()) {
                print_field();
                cout << "w1n" << endl;
                break;
            }
        }
        else if (command == "f") {
            int x, y;
            cin >> x >> y;
            --x; --y; 
            if (x < 0 || x >= N || y < 0 || y >= M || pole[x][y] >= 0) continue;
            if (field[x][y] == -1) field[x][y] = -2;
            else field[x][y] = -1;
        }
        else if (command == "n") {
            break;
        }
        else if (command == "q") {
            return 0;
        }
        print_field();
    }
    return 0;
}