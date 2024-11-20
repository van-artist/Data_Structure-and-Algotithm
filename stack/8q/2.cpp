// 八皇后问题:栈
#include <iostream>
#include <vector>
#include "Stack.h"

#define STATE_EMPTY -1
#define N 8

using namespace std;
struct State
{
    vector<int> board;
    int row;
    State() : board(N, STATE_EMPTY), row(0) {}
    State(const vector<int> &board, int row) : board(board), row(row) {}
};

static bool is_safe(const vector<int> &board, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        if (board[i] == col || board[i] - i == col - row || board[i] + i == col + row)
        {
            return false;
        }
    }
    return true;
}

int solve(vector<int> board)
{
    int count = 0;
    int n = board.size();
    Stack<State> stack;
    State start_state(board, 0);
    stack.push(start_state);
    while (!stack.isEmpty())
    {
        State cur_state = stack.pop();
        if (cur_state.row == n)
        {
            count++;
            continue;
        }
        for (int i = 0; i < n; i++)
        {
            if (is_safe(cur_state.board, cur_state.row, i))
            {
                State new_state = cur_state;
                new_state.board[cur_state.row] = i;
                new_state.row++;
                stack.push(new_state);
            }
        }
    }
    return count;
}

int main()
{
    vector<int> board(N, STATE_EMPTY);
    int result = solve(board);
    cout << result << endl;
    return 0;
}