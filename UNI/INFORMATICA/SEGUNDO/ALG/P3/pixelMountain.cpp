#include <iostream>
#include <vector>

std::vector <int> pixelMountain(int m,int mountain[][m]) {

    std::vector<int> result;
    int n = mountain.size();

    for(int i = 0; i < n; i++){
        int min = mountain[i][0];
        for(int j = 0; j < m; j++){
            if (mountain[i][j] < min){
                min = mountain[i][j];
                result.push_back(i);
            }
        }
    }

    return result;
}



int main() {
    int mountain[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    std::vector<int> result = pixelMountain(mountain[0].size(), mountain);
    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;
    
    return 0;
}