#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// 정렬 여부 판단
bool is_sorted(const vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i)
        if (arr[i] > arr[i + 1])
            return false;
    return true;
}

// 고정된 prefix 길이 반환
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
    int attempt = 0;

    while (!is_sorted(arr)) {
        ++attempt;
        int fixed_index = find_fixed_prefix(arr);

        // 셔플할 부분만 섞기
        if (fixed_index < arr.size()) {
            vector<int> temp(arr.begin() + fixed_index, arr.end());
            shuffle(temp.begin(), temp.end(), rng);
            copy(temp.begin(), temp.end(), arr.begin() + fixed_index);
        }

        // 매 시행마다 현재 배열 출력
        cout << "Attempt #" << attempt << ": ";
        for (int val : arr) cout << val << " ";
        cout << endl;
    }

    // 최종 결과 출력
    cout << "\nSorted in " << attempt << " attempts \n";
    cout << "Final result: ";
    for (int val : arr) cout << val << " ";
    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " numbers: ";
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    smart_bogo_sort(arr);

    return 0;
}
