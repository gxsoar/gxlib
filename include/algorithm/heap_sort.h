#pragma once

#include <vector>

void adjuct(std::vector<int> &arr, int i) {
  int largest = i;
  int l = 2 * i + 1, r = 2 * i + 2;
  int n = arr.size();
  if (l < n && arr[l] > arr[largest]) largest = l;
  if (r < n && arr[r] > arr[largest]) largest = r;
  if (largest != i) {
    std::swap(arr[i], arr[largest]);
    adjuct(arr, largest);
  }
}

void heap_sort(std::vector<int> &arr) {
  int n = arr.size();
  // 初建堆
  for (int i = n / 2 - 1; i >= 0; -- i) {
    adjuct(arr, i);
  }
  for (int i = n - 1; i >= 0; -- i) {
    std::swap(arr[0], arr[i]);
    adjuct(arr, i);
  }
}