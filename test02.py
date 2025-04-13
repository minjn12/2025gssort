## SBS Visualize Diagram

import matplotlib.pyplot as plt
import random
import time

def is_sorted(arr):
    return all(arr[i] <= arr[i+1] for i in range(len(arr)-1))

# 보스의 방식으로 앞쪽 고정 숫자 판단
def find_fixed_prefix(arr):
    fixed = 0
    for i in range(len(arr)):
        if all(arr[i] <= arr[j] for j in range(i+1, len(arr))):
            fixed += 1
        else:
            break
    return fixed

def smart_bogo_sort_visual(arr):
    plt.ion()
    fig, ax = plt.subplots()

    attempt = 0
    while not is_sorted(arr):
        attempt += 1

        fixed_index = find_fixed_prefix(arr)
        if fixed_index < len(arr):
            # 고정된 부분 제외하고 셔플
            part_to_shuffle = arr[fixed_index:]
            random.shuffle(part_to_shuffle)
            arr = arr[:fixed_index] + part_to_shuffle

        # 시각화
        ax.clear()
        colors = ['#523245' if i < fixed_index else '#15985f' for i in range(len(arr))]
        ax.bar(range(len(arr)), arr, color=colors)
        ax.set_title(f'SmartBogoSort Attempt #{attempt}')
        ax.set_xlabel('Index')
        ax.set_ylabel('Value')
        ax.set_ylim(0, max(arr) + 1)
        plt.pause(0.3)

    # 정렬 완료
    ax.clear()
    ax.bar(range(len(arr)), arr, color='limegreen')
    ax.set_title(f'Sorted in {attempt} attempts 🎉')
    ax.set_xlabel('Index')
    ax.set_ylabel('Value')
    ax.set_ylim(0, max(arr) + 1)
    plt.ioff()
    plt.show()

# 테스트 배열
array = [100, 99, 98, 97, 96, 95, 94, 93, 92, 91,
90, 89, 88, 87, 86, 85, 84, 83, 82, 81,
80, 79, 78, 77, 76, 75, 74, 73, 72, 71,
70, 69, 68, 67, 66, 65, 64, 63, 62, 61,
60, 59, 58, 57, 56, 55, 54, 53, 52, 51,
50, 49, 48, 47, 46, 45, 44, 43, 42, 41,
40, 39, 38, 37, 36, 35, 34, 33, 32, 31,
30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
20, 19, 18, 17, 16, 15, 14, 13, 12, 11,
10, 9, 8, 7, 6, 5, 4, 3, 2, 1
]
smart_bogo_sort_visual(array)
