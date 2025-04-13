## Bogo Sort Visualize diagram 

import matplotlib.pyplot as plt
import random
import time


def is_sorted(arr):
    return all(arr[i] <= arr[i + 1] for i in range(len(arr) - 1))


def bogo_sort_visual(arr):
    plt.ion()  # Turn on interactive mode
    fig, ax = plt.subplots()

    attempt = 0
    while not is_sorted(arr):
        attempt += 1
        random.shuffle(arr)

        ax.clear()
        ax.bar(range(len(arr)), arr, color='skyblue')
        ax.set_title(f'BogoSort Attempt #{attempt}')
        ax.set_xlabel('Index')
        ax.set_ylabel('Value')
        ax.set_ylim(0, max(arr) + 1)

        plt.pause(0.001)  # delay for animation

    # Final sorted display
    ax.clear()
    ax.bar(range(len(arr)), arr, color='limegreen')
    ax.set_title(f'Sorted in {attempt} attempts 🎉')
    ax.set_xlabel('Index')
    ax.set_ylabel('Value')
    ax.set_ylim(0, max(arr) + 1)
    plt.ioff()
    plt.show()

 
# Try it out with a small list
array = [1, 2, 4, 8, 16, 32, 64, 128, 3, 9, 27, 81]
bogo_sort_visual(array)

