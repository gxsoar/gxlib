#pragma once

#include <vector>

void quick_sort(std::vector<int> &arrs, int l, int r) {
  if (l >= r) return;
  int i = l - 1, j = r + 1, x = arrs[(l + r) >> 1];
  while(i < j) {
    do i++; while(arrs[i] < x);
    do j--; while(arrs[j] > x);
    if (i < j) {
      std::swap(arrs[i], arrs[j]);
    }
  }
  quick_sort(arrs, l, j);
  quick_sort(arrs, j + 1, r);
}