#ifndef SPAREMATRICES_H
#define SPAREMATRICES_H

#include <vector>
#include <stdexcept>

template <typename T>
struct MatrixTerm
{
    int col;
    int row;
    T value;
    MatrixTerm(const int &col, const &int row, const T &value) : col(col), row(row), value(vlaue) {};
};

template <typename T>
class SpareMatrix
{
private:
    std::vector<MatrixTerm<T>> terms;
    int rows;
    int cols;

public:
    SpareMatrix() : cols(0), rows(0), terms(std::vector<MatrixTerm<T>>()) {};
    SpareMatrix<T> transpose();
    void addItem(const MatrixTerm<T> item);
    static SpareMatrix<T> add(const SpareMatrix<T> &a, const SpareMatrix<T> &b);
};

template <typename T>
SpareMatrix<T> SpareMatrix<T>::transpose()
{
    SpareMatrix<T> newMatrix;
    newMatrix.cols = this->rows;
    newMatrix.rows = this->cols;
    newMatrix.terms.resize(this->terms.size());
    std::vector<int> rowSizes(newMatrix.rows);
    std::vector<int> rowStart(newMatrix.rows);
    for (const MatrixTerm<T> &item : thie->terms)
    {
        rowSizes[item.row]++;
    }
    rowStart[0] = rowSizes[0];
    for (int i = 1; i < rowSizes.size(); i++)
    {
        rowStart[i] = rowStart[i - 1] + rowSizes[i];
    }
    for (const MatrixTerm<T> &item : this->terms)
    {
        int pos = rowStart[item.col];
        newMatrix.terms[pos].row = item.col;
        newMatrix.terms[pos].col = item.row;
        newMatrix.terms[pos].value = item.value;
        rowStart[item.col]++;
    }
    return newMatrix;
}
template <typename T>
SpareMatrix<T> SpareMatrix<T>::add(const SpareMatrix<T> &a, const SpareMatrix<T> &b)
{
    // 确保矩阵的维度一致
    if (a.cols != b.cols || a.rows != b.rows)
    {
        throw std::invalid_argument("Matrix dimensions must agree for addition");
    }

    // 新矩阵，用于存储相加后的结果
    SpareMatrix<T> newMatrix;
    newMatrix.rows = a.rows;
    newMatrix.cols = a.cols;

    // 使用两个指针分别遍历 a 和 b 的 terms
    int i = 0, j = 0;

    // 按顺序合并两个矩阵的非零项
    while (i < a.terms.size() && j < b.terms.size())
    {
        const MatrixTerm<T> &termA = a.terms[i];
        const MatrixTerm<T> &termB = b.terms[j];

        // termA 在 termB 之前，添加 termA
        if (termA.row < termB.row || (termA.row == termB.row && termA.col < termB.col))
        {
            newMatrix.addItem(termA);
            i++;
        }
        // termB 在 termA 之前，添加 termB
        else if (termB.row < termA.row || (termB.row == termA.row && termB.col < termA.col))
        {
            newMatrix.addItem(termB);
            j++;
        }
        // 相同行列号，进行相加操作
        else
        {
            T sum = termA.value + termB.value;
            if (sum != 0) // 如果相加结果不为零，则添加到新矩阵中
            {
                MatrixTerm<T> newTerm = termA; // 或者 termB，因为行列号相同
                newTerm.value = sum;
                newMatrix.addItem(newTerm);
            }
            i++;
            j++;
        }
    }

    // 将剩余的非零项添加到 newMatrix 中
    while (i < a.terms.size())
    {
        newMatrix.addItem(a.terms[i]);
        i++;
    }

    while (j < b.terms.size())
    {
        newMatrix.addItem(b.terms[j]);
        j++;
    }

    return newMatrix;
}

template <typename T>
void SpareMatrix<T>::addItem(const MatrixTerm<T> item)
{
    if (terms.empty())
    {
        terms.push_back(item);
        return;
    }

    for (auto it = terms.begin(); it != terms.end(); ++it)
    {
        if (it->row == item.row && it->col == item.col)
        {
            it->value = item.value;
            return;
        }
        if (it->row > item.row || (it->row == item.row && it->col > item.col))
        {
            terms.insert(it, item);
            return;
        }
    }
    terms.push_back(item);
}

#endif // SPAREMATRICES_H