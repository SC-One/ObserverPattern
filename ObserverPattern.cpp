#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <string>

class TeaFan {
 public:
  TeaFan() = default;
  void checkMarketNow(std::string str) {
    std::cout << str << " tea is available now ^_^" << std::endl;
  }
};

class TeaMarket {
 public:
  TeaMarket() = delete;
  TeaMarket(const TeaMarket &) = delete;
  TeaMarket(const std::initializer_list<std::string> stdList)
      : teaNums{stdList.size()},
        teaString{new std::string[teaNums]}

  {
    size_t counter{0u};
    for (const std::string &str : stdList) {
      teaString[counter] = str;
      counter++;
    }
  }

  void pushBack(TeaFan *teaFan) {
    waiters.push(teaFan);
    notifyWaiters();
  }
  void popFront() { waiters.pop(); }

  TeaMarket(const size_t teaNums)
      : teaNums{teaNums},
        teaString{new std::string[teaNums]}

  {}
  void notifyWaiters() {
    while (waiters.size() > 0) {
      for (size_t i{0}; i < teaNums; i++) {
        waiters.front()->checkMarketNow(teaString[i]);
      }

      popFront();
    }
  }
  std::string &operator[](const size_t ind) { return teaString.get()[ind]; }
  size_t getTeaNums() const { return teaNums; }

 private:
  size_t teaNums;
  std::unique_ptr<std::string[]> teaString;  // infinit Teas
  std::queue<TeaFan *> waiters;
};

int main() {
  TeaMarket teaMarket({"Capitan", "Green", "Chines"});
  TeaFan teaFan[2];
  teaMarket.pushBack(&teaFan[0]);
  teaMarket.pushBack(&teaFan[1]);

  return 0;
}
