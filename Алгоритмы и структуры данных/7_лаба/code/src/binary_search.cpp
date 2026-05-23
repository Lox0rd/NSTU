#include "binary_search.h"
#include <algorithm>

int binarySearch(int arr[], int size, int target) {
    std::sort(arr, arr + size);
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
