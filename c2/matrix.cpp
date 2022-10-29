#include <fstream>
#include <iomanip>
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
    if (!std::getline(in, line)) throw("fail!");
    std::istringstream iss(line);
    T val;
    char ch;
    if (iss >> val && !(iss >> ch)) return val;
  }
}

// 读取文件内部的数据
template <typename T>
void readData(std::vector<std::vector<T>> &matrix, std::ifstream &in) {
  if (in.fail()) throw std::domain_error("fail to open file");

  std::string line;
  T num;
  while (std::getline(in, line)) {
    std::vector<T> temp;
    std::istringstream iss(line);
    while (iss >> num) {
      temp.push_back(num);
    }
    if (!temp.empty()) matrix.push_back(temp);
  }
}

// 打印矩阵
template <typename T>
void printMatrix(const std::vector<std::vector<T>> &matrix) {
  for (auto line : matrix) {
    for (auto &b : line) {
      std::cout << std::setw(10) << b << " ";
    }
    std::cout << std::endl;
  }
}

// 矩阵标准化
template <typename T>
void standarden(std::vector<std::vector<T>> &matrix) {
  // 检查
  if (matrix.empty()) throw std::domain_error("empty matrix");
  int n = matrix.size(), m = matrix[0].size();
  if (m <= 1) throw std::domain_error("matrix has no coefficient");
  if (m < n + 1)
    throw std::domain_error("matrix has no solution: equations is less than x");
  // 阶梯化
  for (int i = 0; i < n; ++i) {
    // 第i行的第i项系数化为一
    T t = matrix[i][i];
    for (auto &num : matrix[i]) num /= t;
    // 对下面的每一行消除系数
    for (int j = i + 1; j < n; ++j) {
      for (int k = m - 1; k >= 0; --k)
        matrix[j][k] -= matrix[j][i] * matrix[i][k];
    }
  }
  std::cout << "The ladden matrix is :" << std::endl;
  printMatrix(matrix);
  std::cout << std::endl;

  // 矩阵标准化
  for (int i = n - 1; i >= 0; --i) {
    // 对上面的每一行消除系数
    for (int j = i - 1; j >= 0; --j) {
      for (int k = m - 1; k >= i; k--) {
        matrix[j][k] -= matrix[i][k] * matrix[j][i];
      }
    }
  }

  std::cout << "The standard matrix is :" << std::endl;
  printMatrix(matrix);
}

int main(int argc, char *argv[]) {
  std::string fileName;
  std::vector<std::vector<double>> matrix;  // 点集
  std::cout << "Please enter the fileName: ";
  std::getline(std::cin, fileName);
  std::ifstream ifs(fileName);    // 读取文件
  readData<double>(matrix, ifs);  // 读取数据
  standarden<double>(matrix);

  return 0;
}
