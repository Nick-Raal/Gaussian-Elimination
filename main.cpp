#include <iostream>
#include <vector>
#include <sstream>
#include <deque>
#include <iomanip>

using namespace std;

void printArr(std::vector<std::vector<float>> a) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            std::cout << std::fixed << std::setprecision(2) << a[i][j];
        }
        std::cout << "\n";
    }
}

void printArr(std::vector<std::vector<float>> a, float consts[]) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            std::cout << std::fixed << std::setprecision(2) << setw(7)<<a[i][j] << " ";
        }
        std::cout << " | " << setw(5) << consts[i] << "\n";
    }
}

void printArr(std::deque<float> d) {
    std::cout /* << std::fixed << std::setprecision(2)*/ << "\n";
    for (int i = 0; i < d.size(); i++) {
        std::cout <<"x"<<i+1<<":"<<setw(5) << d[i] << "\n";
    }
}

void rowOp(std::vector<std::vector<float>>& a, int r, float m, float constants[]) {
    for (int i = 0; i < a[r].size(); i++) {
        a[r][i] = std::round(std::round((m * a[r][i]) * 1000.f) / 10.f) / 100.f;
    }
    constants[r] = std::round(std::round((m * constants[r]) * 1000.f) / 10.f) / 100.f;
    //std::cout << a[0][0] << "\n\n";
}

void rowOp(std::vector<std::vector<float>>& a, int r, int r1, float m, float constants[]) {
    for (int i = 0; i < a[r].size(); i++) {
            a[r][i] = std::round(std::round((a[r][i] - a[r1][i] * m) * 1000.f) / 10.f) / 100.f;
    } 
    constants[r] = std::round(std::round((constants[r] - constants[r1] * m) * 1000.f) / 10.f) / 100.f;
    //std::cout<<"const: " << constants[r] << "\n";
    //printArr(a);
}
    

void gauss(std::vector<std::vector<float>>& a, float constants[]) {
    //rowOp(a, 0, 1 / a[0][0], constants);
    std::vector<float> sol;
    for (int i = 1; i < a.size(); i++) {
        for (int j = 0; j <= i-1; j++) {
            //std::cout << (a[i][j] / a[j][j]) << "\n";
            rowOp(a, i, j, a[i][j]/a[j][j], constants);
        }
        //rowOp(a, i, 1 / a[i][i], constants);
    }
}

std::deque<float> solve(std::vector<std::vector<float>> a, float constants[]) {

    std::cout << "\n";
    std::deque<float> solutions;
    solutions.push_front(constants[a.size() - 1]/a[a.size() - 1][a.size() - 1]);
    for (int i = a.size() - 2; i >=0; i--) {
        float sum = 0;
        for (int j = i + 1, n = 0; j < a[i].size(); j++) {
            sum += a[i][j] * solutions[n];
            n++;
        }

        solutions.push_front((constants[i]-sum)/(a[i][i]));
    }
    return solutions;
}

int main() {
#pragma region Title

    std::cout << "01000111 01100001 01110101 01110011 01110011 01101001 01100001 01101110 01001101 01100001 01110100 01110010 01101001 01111000 01010011 01101111 01101100 01110110 01100101 01110010\n";
 /*std::cout << "             _____                    _____                    _____\n"
<<"         /\\   \\                 /\\   \\                 /\\   \\        \n"
<< "        /::\\   \\               /::\\   \\               /::\\____\\       \n"
<< "       /::::\\   \\             /::::\\   \\             /:::/    /        \n"
<< "      /::::::\\   \\           /::::::\\   \\           /:::/    /         \n"
<< "     /:::/\\:::\\   \\         /:::/\\:::\\   \\         /:::/    /          \n"
<< "    /:::/  \\:::\\   \\       /:::/__\\:::\\   \\       /:::/    /           \n"
<< "   /:::/    \\:::\\   \\     /::::\\  \\:::\\   \\     /:::/    /            \n"
<< "  /:::/    / \\:::\\   \\   /::::::\\  \\:::\\   \\   /:::/    /      _____  \n"
<< " /:::/    /   \\:::\\\___\\ /:::/\\:::\\  \\:::\\   \\ /:::/____/      /\\   \\\n"
<< "/:::/____/  ___\\:::|    |/:::/  \\:::\\  \\:::\\____\|:::|    /      /::\\____\\\n"
<<"\\:::\\   \\/\\ /:::|____|\\::/    \\:::\\ /:::/    /|:::|____\\    /:::/    / \n"
<<" \\:::\\   /::\\\\::/    /  \\/____/ \\:::\\/:::/    /  \\:::\\   \\  /:::/    / \n"
<< "  \\:::\\  \\:::\\\\/____/            \\::::::/    /    \\:::\\   \\/:::/    /  \n"
<< "   \\:::\\  \\:::\\____\\              \\::::/    /      \\:::\\   /:::/    /   \n"
<< "    \\:::\\ /:::/    /               /:::/    /        \\:::\\__/:::/    /    \n"
<< "     \\:::\\/:::/    /               /:::/    /          \\::::::::/    /     \n"
<< "      \\::::::/    /               /:::/    /            \\::::::/    /      \n"
<< "       \\::::/    /               /:::/    /              \\::::/    /       \n"
<< "        \\::/____/                \\::/    /                \\::/____/        \n"
<< "                                  \\/____/                  ~~              \n"
<< "                                                                           \n"
<< "          _____                    _____                    _____          \n"
<< "         /\\   \\                 /\\   \\                 /\\   \\        \n"
<< "        /::\\   \\               /::\\   \\               /::\\   \\       \n"
<< "       /::::\\   \\             /::::\\   \\              \\:::\\   \\      \n"
<< "      /::::::\\   \\           /::::::\\   \\              \\:::\\   \\     \n"
<< "     /:::/\\:::\\   \\         /:::/\\:::\\   \\              \\:::\\   \\    \n"
<< "    /:::/__\\:::\\   \\       /:::/__\\:::\\   \\              \\:::\\   \\   \n"
<< "    \\:::\\  \\:::\\   \\      \\:::\\  \\:::\\   \\             /::::\\   \\  \n"
<< "  ___\\:::\\  \\:::\\   \\   ___\\:::\\  \\:::\\   \\   ____    /::::::\\   \\ \n"
<< " /\\  \\:::\\  \\:::\\   \\ /\\  \\:::\\  \\:::\\   \\ /\\  \\ /:::/\\:::\\   \\\n"
<< "/::\\  \\:::\\  \\:::\\____\\/::\\  \\:::\\  \\:::\\____\\/::\\  \\/:::/  \\:::\\____\ \n"
<<"\\:::\\  \\:::\\  \\::/    /\\:::\\  \\:::\\  \\::/    /\\:::\\ /:::/    \\::/    /\n"
<<" \\:::\\  \\:::\\  \\/____/  \\:::\\  \\:::\\  \\/____/  \\:::\\/:::/    / \\/____/ \n"
<< "  \\:::\\  \\:::\\   \\      \\:::\\  \\:::\\   \\      \\::::::/    /          \n"
<< "   \\:::\\  \\:::\\____\\      \\:::\\  \\:::\\____\\      \\::::/____/           \n"
<< "    \\:::\\ /:::/    /        \\:::\\ /:::/    /        \\:::\\   \\          \n"
<< "     \\:::\\/:::/    /          \\:::\\/:::/    /          \\:::\\   \\         \n"
<< "      \\::::::/    /            \\::::::/    /            \\:::\\   \\        \n"
<< "       \\::::/    /              \\::::/    /              \\:::\\____\\       \n"
<< "        \\::/    /                \\::/    /                \\::/    /        \n"
<< "         \\/____/                  \\/____/                  \\/____/         \n"
<< "                                                                           \n"
<< "          _____                    _____                                   \n"
<< "         /\\   \\                 /\\   \\                                 \n"
<< "        /::\\   \\               /::\\____\\                                \n"
<< "       /::::\\   \\             /::::|   |                                 \n"
<< "      /::::::\\   \\           /:::::|   |                                 \n"
<< "     /:::/\\:::\\   \\         /::::::|   |                                 \n"
<< "    /:::/__\\:::\\   \\       /:::/|::|   |                                 \n"
<< "   /::::\\  \\:::\\   \\     /:::/ |::|   |                                 \n"
<< "  /::::::\\  \\:::\\   \\   /:::/  |::|   | _____                           \n"
<< " /:::/\\:::\\  \\:::\\   \\ /:::/   |::|   |/\\   \\                         \n"
<< "/:::/  \\:::\\  \\:::\\____\\/:: /    |::|   /::\\____\\                        \n"
<< "\\::/    \\:::\\ /:::/    /\\::/    /|::|  /:::/    /                         \n"
<< " \\/____/ \\:::\\/:::/    /  \\/____/ |::| /:::/    /                          \n"
<< "          \\::::::/    /           |::|/:::/    /                           \n"
<< "           \\::::/    /            |::::::/    /                            \n"
<< "           /:::/    /             |:::::/    /                             \n"
<< "          /:::/    /              |::::/    /                              \n"
<< "         /:::/    /               /:::/    /                               \n"
<< "        /:::/    /               /:::/    /                                \n"
<< "        \\::/    /                \\::/    /                                 \n"
<< "         \\/____/                  \\/____/                                  \n"
<< "                                                                           \n"
<< "          _____                    _____                _____              \n"
<< "         /\\   \\                 /\\   \\             /\\   \\            \n"
<< "        /::\\____\\               /::\\   \\           /::\\   \\           \n"
<< "       /::::|   |               /::::\\   \\          \\:::\\   \\          \n"
<< "      /:::::|   |              /::::::\\   \\          \\:::\\   \\         \n"
<< "     /::::::|   |             /:::/\\:::\\   \\          \\:::\\   \\        \n"
<< "    /:::/|::|   |            /:::/__\\:::\\   \\          \\:::\\   \\       \n"
<< "   /:::/ |::|   |           /::::\\  \\:::\\   \\         /::::\\   \\      \n"
<< "  /:::/  |::|___|______    /::::::\\  \\:::\\   \\       /::::::\\   \\     \n"
<< " /:::/   |::::::::\\   \\ /:::/\\:::\\  \\:::\\   \\     /:::/\\:::\\   \\    \n"
<< "/:::/    |:::::::::\\____\\/:::/  \\:::\\  \\:::\\____\\   /:::/  \\:::\\____\\   \n"
<< "\\::/    / ~~~~~/:::/    /\\::/    \\:::\\ /:::/    /   /:::/    \\::/    /    \n"
<< " \\/____/      /:::/    /  \\/____/ \\:::\\/:::/    /   /:::/    / \\/____/     \n"
<< "             /:::/    /            \\::::::/    /   /:::/    /              \n"
<< "            /:::/    /              \\::::/    /   /:::/    /               \n"
<< "           /:::/    /               /:::/    /    \\::/    /                \n"
<< "          /:::/    /               /:::/    /      \\/____/                 \n"
<< "         /:::/    /               /:::/    /                               \n"
<< "        /:::/    /               /:::/    /                                \n"
<< "        \\::/    /                \\::/    /                                 \n"
<< "         \\/____/                  \\/____/                                  \n"
<< "                                                                           \n"
<< "          _____                    _____                                   \n"
<< "         /\\   \\                 /\\   \\                ______           \n"
<< "        /::\\   \\               /::\\   \\              |::|   |          \n"
<< "       /::::\\   \\              \\:::\\   \\             |::|   |          \n"
<< "      /::::::\\   \\              \\:::\\   \\            |::|   |          \n"
<< "     /:::/\\:::\\   \\              \\:::\\   \\           |::|   |          \n"
<< "    /:::/__\\:::\\   \\              \\:::\\   \\          |::|   |          \n"
<< "   /::::\\  \\:::\\   \\             /::::\\   \\         |::|   |          \n"
<< "  /::::::\\  \\:::\\   \\   ____    /::::::\\   \\        |::|   |          \n"
<< " /:::/\\:::\\  \\:::\\____\\ /\\  \\ /:::/\\:::\\   \\ ______|::|___|___ ____  \n"
<< "/:::/  \\:::\\  \\:::|    |/::\\  \\/:::/  \\:::\\____\|:::::::::::::::::|    | \n"
<< "\\::/   |::::\\ /:::|____|\\:::\\ /:::/    \\::/    /|:::::::::::::::::|____| \n"
<< " \\/____|:::::\\/:::/    /  \\:::\\/:::/    / \\/____/  ~~~~~~|::|~~~|~~~       \n"
<< "       |:::::::::/    /    \\::::::/    /                 |::|   |          \n"
<< "       |::|\\::::/    /      \\::::/____/                  |::|   |          \n"
<< "       |::| \\::/____/        \\:::\\   \\                 |::|   |          \n"
<< "       |::|  ~|               \\:::\\   \\                |::|   |          \n"
<< "       |::|   |                \\:::\\   \\               |::|   |          \n"
<< "       \\::|   |                 \\:::\\____\\              |::|   |          \n"
<< "        \\:|   |                  \\::/    /               |::|___|          \n"
<< "         \|___|                   \\/____/                 ~~               \n"
<< "                                                                           \n"
<< "          _____                   _______                   _____          \n"
<< "         /\\   \\                /::\\   \\                /\\   \\        \n"
<< "        /::\\   \\              /::::\\   \\              /::\\____\\       \n"
<< "       /::::\\   \\            /::::::\\   \\            /:::/    /        \n"
<< "      /::::::\\   \\          /::::::::\\   \\          /:::/    /         \n"
<< "     /:::/\\:::\\   \\        /:::/~~\\:::\\   \\        /:::/    /          \n"
<< "    /:::/__\\:::\\   \\      /:::/    \\:::\\   \\      /:::/    /           \n"
<< "    \\:::\\  \\:::\\   \\    /:::/    / \\:::\\   \\    /:::/    /            \n"
<< "  ___\\:::\\  \\:::\\   \\  /:::/____/   \\:::\\____\\  /:::/    /             \n"
<< " /\\  \\:::\\  \\:::\\   \\|:::|    |     |:::|    | /:::/    /              \n"
<< "/::\\  \\:::\\  \\:::\\\____\\|:::|____|     |:::|    |/:::/____/               \n"
<< "\\:::\\  \\:::\\  \\::/    / \\:::\\   \\  /:::/    / \\:::\\   \\              \n"
<< " \\:::\\  \\:::\\  \\/____/   \\:::\\   \\/:::/    /   \\:::\\   \\             \n"
<< "  \\:::\\  \\:::\\   \\       \\:::\\   /:::/    /     \\:::\\   \\            \n"
<< "   \\:::\\  \\:::\\____\\       \\:::\\__/:::/    /       \\:::\\   \\           \n"
<< "    \\:::\\ /:::/    /         \\::::::::/    /         \\:::\\   \\          \n"
<< "     \\:::\\/:::/    /           \\::::::/    /           \\:::\\   \\         \n"
<< "      \\::::::/    /             \\::::/    /             \\:::\\   \\        \n"
<< "       \\::::/    /               \\::/____/               \\:::\\____\\       \n"
<< "        \\::/    /                 ~~                      \\::/    /        \n"
<< "         \\/____/                                           \\/____/         \n"
<< "                                                                           \n"
<< "          _____                    _____                    _____          \n"
<< "         /\\   \\                 /\\   \\                 /\\   \\        \n"
<< "        /::\\____\\               /::\\   \\               /::\\   \\       \n"
<< "       /:::/    /               /::::\\   \\             /::::\\   \\      \n"
<< "      /:::/    /               /::::::\\   \\           /::::::\\   \\     \n"
<< "     /:::/    /               /:::/\\:::\\   \\         /:::/\\:::\\   \\    \n"
<< "    /:::/____/               /:::/__\\:::\\   \\       /:::/__\\:::\\   \\   \n"
<< "    |::|    |               /::::\\  \\:::\\   \\     /::::\\  \\:::\\   \\  \n"
<< "    |::|    |     _____    /::::::\\  \\:::\\   \\   /::::::\\  \\:::\\   \\ \n"
<< "    |::|    |    /\\   \\ /:::/\\:::\\  \\:::\\   \\ /:::/\\:::\\  \\:::\\____\\\n"
<< "    |::|    |   /::\\____\\\\/:::/__\\:::\\  \\:::\\____\\/:::/  \\:::\\  \\:::|    |\n"
<< "    |::|    |  /:::/    /\\:::\\  \\:::\\  \\::/    /\\::/   |::::\\ /:::|____|\n"
<< "    |::|    | /:::/    /  \\:::\\  \\:::\\  \\/____/  \\/____|:::::\\/:::/    / \n"
<< "    |::|____|/:::/    /    \\:::\\  \\:::\\   \\           |:::::::::/    /  \n"
<< "    |:::::::::::/    /      \\:::\\  \\:::\\____\\          |::|\\::::/    /   \n"
<< "    \\::::::::::/____/        \\:::\\  \\::/    /           |::| \\::/____/    \n"
<< "     ~~~~~~~~~~               \\:::\\  \\/____/            |::|  ~|          \n"
<< "                               \\:::\\   \\               |::|   |          \n"
<< "                                \\:::\\____\\              \\::|   |          \n"
<< "                                 \\::/    /                \\:|   |          \n"
<< "                                  \\/____/                  \|___|          \n";*/
#pragma endregion
    
    float constants[3] = { -3, -2, -1};
    std::vector<std::vector<float>> a = { {
    {1, -5, 4},
    {2, -7, 3},
    {-2, 1, 7},
    } };
    /*srand((unsigned)time(0));
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            a[i].push_back((rand()));
        } 
        srand((unsigned)time(0));
        constants[i] = rand();
     }*/
    gauss(a, constants);
    printArr(a, constants);
    std::deque<float> solutions = solve(a, constants);
    
    std::cout << "Solutions: ";
    printArr(solutions);
}




