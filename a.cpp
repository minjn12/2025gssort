#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace chrono;

// 현재 시간을 [HH:MM:SS.mmm] 형식으로 반환
string current_time() {
    auto now = system_clock::now();
    time_t now_time = system_clock::to_time_t(now);
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    tm local_tm = *localtime(&now_time);
    stringstream ss;
    ss << put_time(&local_tm, "%H:%M:%S")
       << '.' << setfill('0') << setw(3) << ms.count();
    return ss.str();
}

// 정렬 여부 확인
bool is_sorted(const vector<int>& arr) {
    for (size_t i = 0; i + 1 < arr.size(); ++i)
        if (arr[i] > arr[i + 1])
            return false;
    return true;
}

// SmartBogo용 prefix 계산
int find_fixed_prefix(const vector<int>& arr) {
    int fixed = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        bool ok = true;
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[i] > arr[j]) {
                ok = false;
                break;
            }
        }
        if (ok) ++fixed;
        else break;
    }
    return fixed;
}

// SmartBogoSort
void smart_bogo_sort(vector<int>& arr) {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    while (!is_sorted(arr)) {
        int fixed_index = find_fixed_prefix(arr);
        if (fixed_index < arr.size()) {
            vector<int> temp(arr.begin() + fixed_index, arr.end());
            shuffle(temp.begin(), temp.end(), rng);
            copy(temp.begin(), temp.end(), arr.begin() + fixed_index);
        }
    }
}

// Bubble Sort
void bubble_sort(vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// Heap Sort
void heap_sort(vector<int>& arr) {
    make_heap(arr.begin(), arr.end());
    sort_heap(arr.begin(), arr.end());
}

// 정렬 실행 시간 측정 (ms)
template <typename Func>
long long measure_time(Func sort_func, const vector<int>& arr) {
    vector<int> temp = arr;
    auto start = high_resolution_clock::now();
    sort_func(temp);
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}

// 평균 실행 시간 측정
template <typename Func>
double average_time(Func sort_func, const vector<int>& base_arr, int repeats = 5) {
    long long total = 0;
    for (int i = 0; i < repeats; ++i) {
        total += measure_time(sort_func, base_arr);
    }
    return static_cast<double>(total) / repeats;
}

int main() {
    ofstream file("timing_results.csv");
    file << "N,BubbleSort(ms),HeapSort(ms),SmartBogoSort(ms)\n";

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    double n = 2;
    while (n <= 20000) {
        int ni = static_cast<int>(n);
        vector<int> base_arr(ni);
        for (int& x : base_arr) x = rng() % 1000000;

        // ⏰ 시간 포함 출력
        cout << "[" << current_time() << "] Measuring N = " << ni << "..." << endl;

        double bubble_avg = average_time(bubble_sort, base_arr);
        double heap_avg = average_time(heap_sort, base_arr);
        double smart_avg = average_time(smart_bogo_sort, base_arr);

        file << ni << "," << bubble_avg << "," << heap_avg << "," << smart_avg << "\n" << flush;
        n *= 1.2;
    }

    file.close();
    cout << "[" << current_time() << "] ✅ Done. Results saved to timing_results.csv\n";
    return 0;
}
