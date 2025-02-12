#include <iostream>
#include <array>
#include <sstream>
#include <vector>
#include <deque>
#include <iomanip>

using namespace std;

void printArr(std::array<std::array<float, 3>, 3> a) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            std::cout << std::fixed << std::setprecision(2) << a[i][j];
        }
        std::cout << "\n";
    }
}

void printArr(std::array<std::array<float, 3>, 3> a, float consts[]) {
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
        std::cout <<"x"<<i<<":"<<setw(5) << d[i] << "\n";
    }
}

void rowOp(std::array<std::array<float, 3>, 3>& a, int r, float m, float constants[3]) {
    for (int i = 0; i < a[r].size(); i++) {
        a[r][i] = std::round(std::round((m * a[r][i]) * 1000.f) / 10.f) / 100.f;
    }
    constants[r] = std::round(std::round((m * constants[r]) * 1000.f) / 10.f) / 100.f;
    //std::cout << a[0][0] << "\n\n";
}

void rowOp(std::array<std::array<float, 3>, 3>& a, int r, int r1, float m, float constants[3]) {
    for (int i = 0; i < a[r].size(); i++) {
            a[r][i] = std::round(std::round((a[r][i] - a[r1][i] * m) * 1000.f) / 10.f) / 100.f;
    } 
    constants[r] = std::round(std::round((constants[r] - constants[r1] * m) * 1000.f) / 10.f) / 100.f;
    //std::cout<<"const: " << constants[r] << "\n";
    //printArr(a);
}
    

void gauss(std::array<std::array<float, 3>, 3>& a, float constants[3]) {
    //rowOp(a, 0, 1 / a[0][0], constants);
    std::vector<float> sol;
    for (int i = 1; i < a.size(); i++) {
        for (int j = 0; j <= i-1; j++) {
            //pivoting support
            if (a[j][j] == 0) {
                for (int k = j; k < a.size(); k++) {
                    if (a[k][j] != 0) {
                        a[k].swap(a[j]);
                        float temp = constants[k];
                        constants[k] = constants[j];
                        constants[j] = temp;
                        break;
                    }
                }
            }
            rowOp(a, i, j, a[i][j]/a[j][j], constants);
        }
        //rowOp(a, i, 1 / a[i][i], constants);
    }
}

std::deque<float> solve(std::array<std::array<float, 3>, 3> a, float constants[3]) {

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
    float constants[3] = {1, 1, 1};
    std::array<std::array<float, 3>, 3> a = { {
      {4, 1, 3},  
      {5, 2, 9},  
      {10, 8, 6}
    } };
    gauss(a, constants);
    printArr(a, constants);
    std::deque<float> solutions = solve(a, constants);
    
    std::cout << "Solutions: ";
    printArr(solutions);
    
}




