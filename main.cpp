#include <iostream>
#include <array>
#include <sstream>
#include <vector>
#include <deque>

void rowOp(std::array<std::array<float, 3>, 3>& a, int r, float m) {
    for (int i = 0; i < a[r].size(); i++) {
        a[r][i] *= m;
    }
    std::cout << a[0][0] << "\n\n";
}

void rowOp(std::array<std::array<float, 3>, 3>& a, int r, int r1, float m) {
        for (int i = 0; i < a[r].size(); i++) {
            a[r][i] -= a[r1][i] * m;
    } 
}
    

void gauss(std::array<std::array<float, 3>, 3>& a) {
    rowOp(a, 0, 1 / a[0][0]);
    std::vector<float> sol;
    for (int i = 1; i < a.size(); i++) {
        for (int j = 0; j <= i-1; j++) {
            rowOp(a, i, j, a[i][j]/a[j][j]);
        }
        rowOp(a, i, 1 / a[i][i]);
    }
}

void printArr(std::array<std::array<float, 3>, 3> a) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a[i].size(); j++) {
            std::cout << a[i][j]<<" ";
        }
        std::cout <<"\n";
    }
}
void printArr(std::deque<float> d) {
    std::cout << "\n";
    for (int i = 0; i < d.size(); i++) {
        std::cout << d[i] << " ";
    }
}

std::deque<float> solve(std::array<std::array<float, 3>, 3> a, float constants[3]) {
    std::deque<float> solutions;
    solutions.push_front(constants[a.size() - 1]);
    for (int i = a.size() - 2; i >=0; i--) {
        float sum = 0;
        for (int j = i + 1, n = 0; j < a[i].size(); j++) {
            sum += a[i][j] * solutions[n];
            n++;
        }
        solutions.push_front(constants[i]/sum);
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
    gauss(a);
    printArr(a);
    std::deque<float> solutions = solve(a, constants);
    
    std::cout << "Solutions: ";
    printArr(solutions);
    
}




