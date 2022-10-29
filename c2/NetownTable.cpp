#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

template <typename T>
T getValue(std::string promt, std::istream &in = std::cin) {
  while (true) {
    std::cout << promt;
    std::string line;
    if (!std::getline(in, line))
      throw("fail!");
    std::istringstream iss(line);
    T val;
    char ch;
    if (iss >> val && !(iss >> ch))
      return val;
  }
}

// 读取文件内部的数据
template <typename T> void readData(std::vector<T> &nums, std::ifstream &in) {
  if (in.fail())
    throw std::domain_error("Fail to open file");
  T n;
  while (true) {
    in >> n;
    if (in.fail())
      break;
    nums.push_back(n);
  }
}

// 打印差分表
template <typename T>
void printY(std::vector<T> &nums, int depth, std::vector<std::vector<T>> &tri) {
  std::cout << "Y" << depth << " | ";
  for (auto item : nums) {
    std::cout << std::setw(10) << item << " ";
  }
  std::cout << std::endl;

  tri.push_back(nums);
  if (nums.size() == 1)
    return;

  std::vector<T> newNums;
  for (size_t i = 1; i < nums.size(); ++i) {
    newNums.push_back(nums[i] - nums[i - 1]);
  }
  printY(newNums, depth + 1, tri);
}

// 计算牛顿差值
template <typename T>
void netown(const std::vector<std::vector<T>> &tri, const T x, const T t) {
  long double res = tri[0][0];
  std::cout << "N" << 1 << " | " << res << std::endl;
  for (size_t n = 1; n < tri.size(); ++n) {
    long double son = tri[n][0] * t / (t - 1);
    long double mom = 1;
    for (int i = 1; i <= n; ++i) {
      son *= (t - i);
      mom *= i;
    }
    res += son / mom;

    std::cout << "N" << n + 1 << " | " << res << std::endl;
  }
}

int main(int argc, char *argv[]) {
  std::string fileName;
  std::cout << "Please enter the fileName: ";
  std::getline(std::cin, fileName);
  std::ifstream ifs(fileName); // 读取文件

  std::vector<long double> nums;
  std::vector<std::vector<long double>> tri;
  readData(nums, ifs);

  printY(nums, 0, tri);

  long double x = getValue<long double>("Please input the value of x: ");
  long double h = getValue<long double>("Please input the value of h: ");
  std::cout << "The Netown result of " << x << " is:" << std::endl;
  netown(tri, x, (x - nums[0]) / h);

  return 0;
}
