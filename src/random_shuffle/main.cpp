#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <random>
#include <iostream>

int main() {
  std::vector<int> deck(52);
  // 初始化卡组
  for (int i = 0; i < 52; ++ i) deck[i] = i;
  // 开始进行洗牌
  std::srand(unsigned(std::time(0)));
  std::random_shuffle(deck.begin(), deck.end());

  for (int i = 0; i < 52; ++ i) {
    std::cout << deck[i] << " ";
  }
  return 0;
}