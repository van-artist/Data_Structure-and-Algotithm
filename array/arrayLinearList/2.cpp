#include <iostream>
#include <algorithm>

template <typename T>
void changeLength2D(T **&arr, int targetRow, int oldLen, int newLen)
{
    // 分配新的行
    T *newRow = new T[newLen];

    // 复制旧行中的元素到新行
    std::copy(arr[targetRow], arr[targetRow] + std::min(oldLen, newLen), newRow);

    // 释放旧行的内存
    delete[] arr[targetRow];

    // 将新行赋给目标行
    arr[targetRow] = newRow;
}

int main()
{
    // 示例：创建一个二维数组并改变其中一行的长度
    int rows = 3;
    int cols = 3;
    int **arr = new int *[rows];
    for (int i = 0; i < rows; ++i)
    {
        arr[i] = new int[cols];
        for (int j = 0; j < cols; ++j)
        {
            arr[i][j] = i * cols + j;
        }
    }

    // 输出原始数组
    std::cout << "Original array:" << std::endl;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // 改变第二行的长度
    changeLength2D(arr, 1, cols, 5);

    // 填充新行的元素
    for (int j = cols; j < 5; ++j)
    {
        arr[1][j] = 100 + j;
    }

    // 输出修改后的数组
    std::cout << "Modified array:" << std::endl;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < (i == 1 ? 5 : cols); ++j)
        {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // 释放内存
    for (int i = 0; i < rows; ++i)
    {
        delete[] arr[i];
    }
    delete[] arr;

    return 0;
}
