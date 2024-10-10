#include <ostream>
#include <exception>
#include <stdexcept>
#include <iostream>

template <typename T>
class Matrix
{
private:
    T *element;
    int rowsNum;
    int columnsNum;

public:
    // 构造函数
    Matrix(int rows = 0, int cols = 0);

    // 拷贝构造函数
    Matrix(const Matrix<T> &m);

    // 析构函数
    ~Matrix();

    // 行数和列数的访问函数
    int rows() const { return rowsNum; }
    int columns() const { return columnsNum; }
    void readFromStream(std::istream &s);
    // 元素访问运算符
    T &operator()(int i, int j) const;

    // 赋值运算符
    Matrix<T> &operator=(const Matrix<T> &m);

    // 一元运算符 + 和 - （通常返回对象本身或副本）
    Matrix<T> operator+() const;
    Matrix<T> operator-() const;

    // 二元运算符 + 和 -，矩阵加法和减法
    Matrix<T> operator+(const Matrix<T> &M) const;
    Matrix<T> operator-(const Matrix<T> &M) const;

    // 矩阵乘法
    Matrix<T> operator*(const Matrix<T> &M) const;

    // 自加运算符 +=
    void operator+=(const Matrix<T> &M);
    void operator-=(const T elem);
    void operator*=(const T elem);
    void operator/=(const T elem);
    // 重载 >> 运算符
    friend std::istream &operator>>(std::istream &s, Matrix<T> &m);

    // 重载 << 运算符用于输出矩阵
    friend std::ostream &operator<<(std::ostream &s, const Matrix<T> &m);
};

// 构造函数实现
template <typename T>
Matrix<T>::Matrix(int rows, int cols)
{
    if (rows < 0 || cols < 0)
    {
        throw std::out_of_range("Rows and columns must be >= 0");
    }
    rowsNum = rows;
    columnsNum = cols;
    element = new T[rows * cols];
}

// 析构函数实现
template <typename T>
Matrix<T>::~Matrix()
{
    delete[] element;
}

// 拷贝构造函数实现
template <typename T>
Matrix<T>::Matrix(const Matrix<T> &m)
{
    rowsNum = m.rowsNum;
    columnsNum = m.columnsNum;
    element = new T[rowsNum * columnsNum];
    for (int i = 0; i < rowsNum * columnsNum; ++i)
    {
        element[i] = m.element[i];
    }
}

// 元素访问运算符实现（索引从 0 开始）
template <typename T>
T &Matrix<T>::operator()(int i, int j) const
{
    if (i < 0 || i >= rowsNum || j < 0 || j >= columnsNum)
    {
        throw std::out_of_range("Index out of range");
    }
    return element[i * columnsNum + j];
}

// 赋值运算符实现
template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &m)
{
    if (this != &m)
    {
        // 释放旧的内存
        delete[] element;

        // 复制行列数
        rowsNum = m.rowsNum;
        columnsNum = m.columnsNum;

        // 分配新内存并复制元素
        element = new T[rowsNum * columnsNum];
        for (int i = 0; i < rowsNum * columnsNum; ++i)
        {
            element[i] = m.element[i];
        }
    }
    return *this;
}

// 一元 + 运算符实现
template <typename T>
Matrix<T> Matrix<T>::operator+() const
{
    return *this; // 返回对象本身
}

// 一元 - 运算符实现
template <typename T>
Matrix<T> Matrix<T>::operator-() const
{
    Matrix<T> result(rowsNum, columnsNum);
    for (int i = 0; i < rowsNum * columnsNum; ++i)
    {
        result.element[i] = -element[i];
    }
    return result;
}

// 二元 + 运算符实现
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &M) const
{
    if (rowsNum != M.rowsNum || columnsNum != M.columnsNum)
    {
        throw std::invalid_argument("Matrix dimensions must agree for addition");
    }
    Matrix<T> result(rowsNum, columnsNum);
    for (int i = 0; i < rowsNum * columnsNum; ++i)
    {
        result.element[i] = element[i] + M.element[i];
    }
    return result;
}

// 二元 - 运算符实现
template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &M) const
{
    if (rowsNum != M.rowsNum || columnsNum != M.columnsNum)
    {
        throw std::invalid_argument("Matrix dimensions must agree for subtraction");
    }
    Matrix<T> result(rowsNum, columnsNum);
    for (int i = 0; i < rowsNum * columnsNum; ++i)
    {
        result.element[i] = element[i] - M.element[i];
    }
    return result;
}

// 矩阵乘法运算符实现
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &M) const
{
    if (columnsNum != M.rowsNum)
    {
        throw std::invalid_argument("Matrix dimensions must agree for multiplication");
    }
    Matrix<T> result(rowsNum, M.columnsNum);
    for (int i = 0; i < rowsNum; ++i)
    {
        for (int j = 0; j < M.columnsNum; ++j)
        {
            result.element[i * M.columnsNum + j] = 0;
            for (int k = 0; k < columnsNum; ++k)
            {
                result.element[i * M.columnsNum + j] += element[i * columnsNum + k] * M.element[k * M.columnsNum + j];
            }
        }
    }
    return result;
}

// 自加运算符实现
template <typename T>
void Matrix<T>::operator+=(const Matrix<T> &M)
{
    if (rowsNum != M.rowsNum || columnsNum != M.columnsNum)
    {
        throw std::invalid_argument("Matrix dimensions must agree for addition");
    }
    for (int i = 0; i < rowsNum * columnsNum; ++i)
    {
        element[i] += M.element[i];
    }
}
template <typename T>
void Matrix<T>::operator-=(const T elem)
{
    for (int i = 0; i < rowsNum * columnsNum; ++i)
    {
        element[i] -= elem;
    }
}
template <typename T>
void Matrix<T>::operator*=(const T elem)
{
    for (int i = 0; i < rowsNum * columnsNum; ++i)
    {
        element[i] *= elem;
    }
}
template <typename T>
void Matrix<T>::operator/=(const T elem)
{
    for (int i = 0; i < rowsNum * columnsNum; ++i)
    {
        element[i] /= elem;
    }
}

template <typename T>
void Matrix<T>::readFromStream(std::istream &s)
{
    for (int i = 0; i < rowsNum; ++i)
    {
        for (int j = 0; j < columnsNum; ++j)
        {
            if (!(s >> element[i * columnsNum + j]))
            {
                throw std::runtime_error("Failed to read matrix data");
            }
        }
    }
}
// 重载 >> 运算符用于输入矩阵数据
template <typename T>
std::istream &operator>>(std::istream &s, Matrix<T> &m)
{
    for (int i = 0; i < m.rowsNum; ++i)
    {
        for (int j = 0; j < m.columnsNum; ++j)
        {
            if (!(s >> m.element[i * m.columnsNum + j]))
            {
                throw std::runtime_error("Failed to read matrix data");
            }
        }
    }
    return s;
}

// 重载 << 运算符用于输出矩阵数据
template <typename T>
std::ostream &operator<<(std::ostream &s, const Matrix<T> &m)
{
    for (int i = 0; i < m.rowsNum; ++i)
    {
        for (int j = 0; j < m.columnsNum; ++j)
        {
            s << m.element[i * m.columnsNum + j] << " ";
        }
        s << std::endl;
    }
    return s;
}
int main()
{
    Matrix<int> m1(2, 2);
    Matrix<int> m2(2, 2);

    // 示例操作
    m1(0, 0) = 1;
    m1(0, 1) = 2;
    m1(1, 0) = 3;
    m1(1, 1) = 4;

    m2(0, 0) = 5;
    m2(0, 1) = 6;
    m2(1, 0) = 7;
    m2(1, 1) = 8;

    Matrix<int> m3 = m1 + m2; // 矩阵加法

    for (int i = 0; i < m3.rows(); ++i)
    {
        for (int j = 0; j < m3.columns(); ++j)
        {
            std::cout << m3(i, j) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
