// 八皇后问题:递归
#include <iostream>
#include <vector>

#define STATE_EMPTY -1
#define STATE_FULL 1
#define N 8

using namespace std;

static bool is_safe(const vector<int> &board, int cur_row, int cur_col)
{
    for (int i = 0; i < cur_row; i++)
    {
        if (board[i] == cur_col || board[i] - i == cur_col - cur_row || board[i] + i == cur_col + cur_row)
        {
            return false;
        }
    }
    return true;
}

static int solve(vector<int> &board, int cur_row)
{
    if (cur_row == N)
    {
        return 1;
    }
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        if (is_safe(board, cur_row, i))
        {
            board[cur_row] = i;
            count += solve(board, cur_row + 1);
            board[cur_row] = STATE_EMPTY;
        }
    }
    return count;
}
int main()
{
    vector<int> board(N, STATE_EMPTY);
    int result = solve(board, 0);
    cout << result << endl;
    return 0;
}