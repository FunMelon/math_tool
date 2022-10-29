#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
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

// 点的数据结构
template <typename T> struct point {
  T x;
  T y;
};

// 读取文件内部的数据
template <typename T>
void readData(std::vector<point<T>> &points, std::ifstream &in) {
  if (in.fail())
    throw std::domain_error("Fail to open file");
  while (true) {
    T x, y;
    in >> x >> y;
    if (in.fail())
      break;
    point<T> point{x, y};
    points.push_back(point);
  }
}

// 打印所有点的函数
template <typename T, typename P>
void printAllPoints(const std::vector<point<T>> &points, P fun) {
  for (auto item : points)
    fun(item);
}

// 计算拉格朗日差值
template <typename T> T lagrange(const std::vector<point<T>> &points, T x) {
  T res = 0;
  for (auto item : points) {
    T den = 1;      // 分母
    T num = item.y; // 分子
    for (auto item2 : points) {
      if (item2.x != item.x) {
        num *= x - item2.x;
        den *= item.x - item2.x;
      }
    }
    res += num / den;
  }
  return res;
}

int main(int argc, char *argv[]) {
  auto printPoint = [](auto item) {
    std::cout << "(" << item.x << ", " << item.y << ")" << std::endl;
  };

  std::string fileName;
  std::vector<point<double>> points; // 点集
  std::cout << "Please enter the fileName: ";
  std::getline(std::cin, fileName);
  std::ifstream ifs(fileName);   // 读取文件
  readData<double>(points, ifs); // 读取数据

  std::cout << "Successfully load the file " << fileName << std::endl;
  printAllPoints(points, printPoint);

  double x = getValue<double>("Please Enter x: ");

  std::cout << "The result of x = " << x << " 's y is " << lagrange(points, x)
            << std::endl;

  return 0;
}
