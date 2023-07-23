#pragma once

#include <vector>

void merge_sort(std::vector<int> &nums, int l, int r) {
  if (l >= r) return;
  
  int mid = (l + r) >> 1;
  merge_sort(nums, l, mid);
  merge_sort(nums, mid + 1, r);
  std::vector<int> tmp;
  
  int k = 0, i = l, j = mid + 1;
  while(i <= mid && j <= r) {
    if (nums[i] <= nums[j]) tmp.push_back(nums[i++]);
    else tmp.push_back(nums[j++]);
  }

  while(i <= mid) tmp.push_back(nums[i++]);
  while(j <= r) tmp.push_back(nums[j++]);

  for (i = l, j = 0; i <= r; i++, j++) nums[i] = tmp[j];
}