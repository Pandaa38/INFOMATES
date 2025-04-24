#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> pixelMountain(const std::vector<std::vector<int>>& mountain) {
    std::vector<int> path;
    int n = mountain.size();
    if (n == 0) return path;
    int m = mountain[0].size();

    double center = (m - 1) / 2.0;

    int current_col = 0;
    int min_cost = mountain[n - 1][0];
    for (int j = 1; j < m; j++) {
        if (mountain[n - 1][j] < min_cost ||
            (mountain[n - 1][j] == min_cost && std::abs(j - center) < std::abs(current_col - center))) {
            min_cost = mountain[n - 1][j];
            current_col = j;
        }
    }
    path.push_back(current_col);

    for (int i = n - 2; i >= 0; i--) {
        int best_col  = current_col;
        int best_cost = mountain[i][current_col];

        for (int dj = -1; dj <= 1; dj++) {
            int next_col = current_col + dj;
            if (next_col >= 0 && next_col < m) {
                int cost = mountain[i][next_col];
                if (cost < best_cost ||
                    (cost == best_cost && std::abs(next_col - center) < std::abs(best_col - center))) {
                    best_cost = cost;
                    best_col  = next_col;
                }
            }
        }
        current_col = best_col;
        path.push_back(current_col);
    }

    return path;
}

int main() {

    std::vector<std::vector<int>> mountain = {
        {2, 8, 9, 5, 8},  // fila 0 (cima)
        {4, 4, 6, 2, 3},
        {5, 7, 5, 6, 1},
        {3, 2, 5, 4, 8}   // fila 3 (base)
    };

    std::cout << "Matriz a escalar:" << std::endl;
    std::cout << "(cima)" << std::endl;
    for (const auto& row : mountain) {
        for (int v : row) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }

    std::vector<int> path = pixelMountain(mountain);

    std::cout << "Segimos el siguiente camino en orden de subida:" << std::endl;
    std::string camino = "";
    for (int i = 0; i < path.size(); i++) {
        camino += "[" + std::to_string(i) + "," + std::to_string(path[i]) + "]" + " - ";
    }
    camino.erase(camino.size() - 3);
    std::cout << camino << std::endl;

    int totalCost = 0;
    for (int i = mountain.size() - 1; i >= 0; i--) {
        totalCost += mountain[i][path[mountain.size() - i - 1]];
    }

    std::cout << "\nCoste total del camino: " << totalCost << std::endl;

    return 0;
}
