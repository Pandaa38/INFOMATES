#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int INF = 1000000000;
const int N   = 21;
const int START = 0;  // Granada

// Índices:
//  0 Granada
//  1 Almería
//  2 Jaén
//  3 Sevilla
//  4 Huelva
//  5 Cádiz
//  6 Badajoz
//  7 Cáceres
//  8 Valladolid
//  9 Vigo
// 10 Coruña
// 11 Oviedo
// 12 Bilbao
// 13 Lérida
// 14 Gerona
// 15 Barcelona
// 16 Zaragoza
// 17 Madrid
// 18 Albacete
// 19 Valencia
// 20 Murcia

const char* cityName[N] = {
    "Granada","Almería","Jaén","Sevilla","Huelva","Cádiz",
    "Badajoz","Cáceres","Valladolid","Vigo","Coruña","Oviedo",
    "Bilbao","Lérida","Gerona","Barcelona","Zaragoza","Madrid",
    "Albacete","Valencia","Murcia"
};

const int distMat[N][N] = {
  //  0      1      2      3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18    19    20
    {   0,   224,   278,   256,  291, INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  173 }, // 0 Granada
    { 224,     0,   INF,   INF,  INF, INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  224 }, // 1 Almería
    { 278,   INF,     0,   242,  INF, INF,  363,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  335,  INF,  INF }, // 2 Jaén
    { 256,   INF,   242,     0,   92, 256,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF }, // 3 Sevilla
    { 291,   INF,   INF,    92,    0, 101,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF }, // 4 Huelva
    { INF,   INF,   INF,   256,  101,   0,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF }, // 5 Cádiz
    { INF,   INF,   363,   INF,  INF, INF,    0,   90,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF }, // 6 Badajoz
    { INF,   INF,   INF,   INF,  INF, INF,   90,    0,  297,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  403,  INF,  INF,  INF }, // 7 Cáceres
    { INF,   INF,   INF,   INF,  INF, INF,  INF,   297,   0,  356,  455,  259,  INF,  INF,  INF,  INF,  INF,  193,  INF,  INF,  INF }, // 8 Valladolid
    { INF,   INF,   INF,   INF,  INF, INF,  INF,  INF,  356,    0,  171,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF }, // 9 Vigo
    { INF,   INF,   INF,   INF,  INF, INF,  INF,  INF,  455,  171,    0,  386,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF }, // 10 Coruña
    { INF,   INF,   INF,   INF,  INF, INF,  INF,  INF,  259,  INF,  386,    0,  304,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF }, // 11 Oviedo
    { INF,   INF,   INF,   INF,  INF, INF,  INF,  INF,  INF,  INF,  INF,  304,    0,  449,  INF,  INF,  324,  395,  INF,  INF,  INF }, // 12 Bilbao
    { INF,   INF,   INF,   INF,  INF, INF,  INF,  INF,  INF,  INF,  INF,  INF,  449,    0,  157,  INF,  222,  INF,  INF,  INF,  INF }, // 13 Lérida
    { INF,   INF,   INF,   INF,  INF, INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  157,    0,  100,  INF,  INF,  INF,  INF,  INF }, // 14 Gerona
    { INF,   INF,   INF,   INF,  INF, INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  100,    0,  296,  INF,  INF,  349,  INF }, // 15 Barcelona
    { INF,   INF,   INF,   INF,  INF, INF,  INF,  INF,  INF,  INF,  INF,  INF,  324,  222,  INF,  296,    0,  325,  INF,  308,  INF }, // 16 Zaragoza
    { INF,   INF,   INF,   INF,  INF, INF,  INF,  403,  193,  INF,  INF,  INF,  395,  INF,  INF,  INF,  325,    0,  251,  353,  INF }, // 17 Madrid
    { INF,   INF,   335,   INF,  INF, INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  251,    0,  191,  150 }, // 18 Albacete
    { INF,   INF,   INF,   INF,  INF, INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  349,  308,  353,  191,    0,  241 }, // 19 Valencia
    { 173,   224,   INF,   INF,  INF, INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  INF,  150,  241,    0 }  // 20 Murcia
};

// ----------------------------
// Backtracking
int bestCostBT = INF;
vector<int> bestPathBT;
bool usedBT[N];

void dfsBT(int u, int depth, int cost, vector<int>& path) {
    if (depth == N) {
        if (distMat[u][START] < INF) {
            int total = cost + distMat[u][START];
            if (total < bestCostBT) {
                bestCostBT = total;
                bestPathBT = path;
                bestPathBT.push_back(START);
            }
        }
        return;
    }
    for (int v = 0; v < N; ++v) {
        if (!usedBT[v] && distMat[u][v] < INF) {
            usedBT[v] = true;
            path.push_back(v);
            dfsBT(v, depth + 1, cost + distMat[u][v], path);
            path.pop_back();
            usedBT[v] = false;
        }
    }
}

// ----------------------------
// Branch & Bound
int minEdgeGlobal = INF;
int bestCostBB = INF;
vector<int> bestPathBB;
bool usedBB[N];

void dfsBB(int u, int depth, int cost, vector<int>& path) {
    // poda
    int cota = cost + (N - depth + 1) * minEdgeGlobal;
    if (cota >= bestCostBB) return;

    if (depth == N) {
        if (distMat[u][START] < INF) {
            int total = cost + distMat[u][START];
            if (total < bestCostBB) {
                bestCostBB = total;
                bestPathBB = path;
                bestPathBB.push_back(START);
            }
        }
        return;
    }
    for (int v = 0; v < N; ++v) {
        if (!usedBB[v] && distMat[u][v] < INF) {
            usedBB[v] = true;
            path.push_back(v);
            dfsBB(v, depth + 1, cost + distMat[u][v], path);
            path.pop_back();
            usedBB[v] = false;
        }
    }
}

// imprime ruta en nombres
void printRoute(const vector<int>& path) {
    for (int i = 0; i < (int)path.size() - 1; i++) {
        cout << i << ". " << cityName[path.at(i)] << " -> ";
    }
    cout << N << ". " << cityName[START] << "\n";
}

int main() {
    // Precomputar arista mínima global
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        if (i!=j && distMat[i][j] < minEdgeGlobal)
          minEdgeGlobal = distMat[i][j];

    // Backtracking
    vector<int> path; path.push_back(START);
    usedBT[START] = true;
    dfsBT(START, 1, 0, path);

    cout << "=== Backtracking ===\n"
         << "Coste mínimo: " << bestCostBT << "\nRuta: ";
    printRoute(bestPathBT);
    cout << "\n";

    // Branch & Bound
    fill(begin(usedBB), end(usedBB), false);
    bestCostBB = INF;
    path.clear(); path.push_back(START);
    usedBB[START] = true;
    dfsBB(START, 1, 0, path);

    cout << "=== Branch & Bound ===\n"
         << "Coste mínimo: " << bestCostBB << "\nRuta: ";
    printRoute(bestPathBB);

    return 0;
}
