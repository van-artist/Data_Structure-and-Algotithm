#include <cmath>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include "Stack.h"

std::unordered_map<char, int> priority_map = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
    {'^', 3},
    {'(', 0},
    {')', 0},
};

static int charToNum(const char &ch)
{
    if (ch >= '0' && ch <= '9')
    {
        return ch - '0';
    }
    else
    {
        throw std::invalid_argument("无法转换");
    }
    return -1;
}

class Calculator
{
private:
    Stack<char> operate_stack;   // 运算符栈
    Stack<long long> nums_stack; // 操作数栈

public:
    Calculator() : operate_stack(Stack<char>()), nums_stack(Stack<long long>()) {}

    long long single_caculate(long long a, long long b, char operate);
    long long caculate(std::string input);
};

long long Calculator::single_caculate(long long a, long long b, char operate)
{
    switch (operate)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
        {
            throw std::invalid_argument("除数不能为0");
        }
        return a / b;
    case '^':
        return std::pow(a, b);
    default:
        break;
    }
    return 0;
}

long long Calculator::caculate(std::string input)
{
    operate_stack.push('(');

    int top_num = 0;
    for (int i = 0; i < input.size(); i++)
    {
        char ch = input[i];
        if (ch >= '0' && ch <= '9')
        {
            int cur_digit = charToNum(ch);
            top_num = top_num * 10 + cur_digit;
            if (i + 1 >= input.size() || input[i + 1] < '0' || input[i + 1] > '9')
            {
                nums_stack.push(top_num);
                top_num = 0;
            }
        }
        else if (ch == '(')
        {
            operate_stack.push(ch);
        }
        else if (ch == ')')
        {
            char top = operate_stack.pop();
            while (top != '(')
            {
                if (nums_stack.size() < 2)
                {
                    throw std::runtime_error("表达式错误: 数字栈中元素不足");
                }
                long long b = nums_stack.pop();
                long long a = nums_stack.pop();
                long long result = single_caculate(a, b, top);
                nums_stack.push(result);
                if (operate_stack.isEmpty())
                {
                    throw std::runtime_error("括号不匹配: 缺少 '('");
                }
                top = operate_stack.pop();
            }
        }
        else if (priority_map.find(ch) != priority_map.end())
        {
            char top = operate_stack.peek();
            if (priority_map[ch] > priority_map[top] || top == '(')
            {
                operate_stack.push(ch);
            }
            else
            {
                while (!operate_stack.isEmpty() && operate_stack.peek() != '(')
                {
                    char top = operate_stack.pop();
                    if (nums_stack.size() < 2)
                    {
                        throw std::runtime_error("表达式错误: 数字栈中元素不足");
                    }
                    long long b = nums_stack.pop();
                    long long a = nums_stack.pop();
                    long long result = single_caculate(a, b, top);
                    nums_stack.push(result);
                }
                operate_stack.push(ch);
            }
        }
        else if (ch == '#' || ch == '=')
        {
            char top = operate_stack.pop();
            while (top != '(' && top != '#' && !operate_stack.isEmpty())
            {
                if (nums_stack.size() < 2)
                {
                    throw std::runtime_error("表达式错误: 数字栈中元素不足");
                }
                long long b = nums_stack.pop();
                long long a = nums_stack.pop();
                long long result = single_caculate(a, b, top);
                nums_stack.push(result);
                if (operate_stack.isEmpty())
                {
                    throw std::runtime_error("括号不匹配: 缺少 '('");
                }
                top = operate_stack.pop();
            }
            return nums_stack.peek();
        }
    }
    throw std::runtime_error("表达式未正确结束");
}

int main()
{
    Calculator calculator;

    try
    {
        long long result = calculator.caculate("123*1324-2*(3-5^6)=");
        std::cout << "Result: " << result << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
