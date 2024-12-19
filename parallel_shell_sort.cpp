#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>
#include <random>

void shell_sort_parallel(std::vector<int>& arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
#pragma omp parallel for schedule(dynamic, 1)
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

int main() {

    int n = 30000000;
    std::vector<int> arr(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }

    omp_set_num_threads(8); 
    omp_set_nested(1);  
    omp_set_dynamic(0);

    auto start = std::chrono::high_resolution_clock::now();
    shell_sort_parallel(arr);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Time: " << duration.count() << " seconds\n";

    return 0;
}
