#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> prefix(string str)
{
    int n = str.size();
    vector<int> pi(n, 0);
    pi[0] = 0;
    for (int i = 1; i < n; i++)
    {
        int len = pi[i - 1];
        while (str[i] != str[len] && len > 0)
        {
            len = pi[len - 1];
        }
        if (str[i] == str[len])
        {
            pi[i] = pi[i - 1] + 1;
        }
    }
    return pi;
}
int kmp(string str, string pattern)
{
    string newStr = pattern + "#" + str;
    vector<int> pis = prefix(newStr);
    int patternLen = pattern.size();
    for (int i = patternLen + 1; i < newStr.size(); i++)
    {
        if (pis[i] == patternLen)
        {
            return i - 2 * patternLen;
        }
    }
    return -1;
}

int main()
{
    string text = "abcabcabc";
    string pattern = "cab";

    int result = kmp(text, pattern);
    if (result != -1)
    {
        cout << "Pattern found at index " << result << endl;
    }
    else
    {
        cout << "Pattern not found" << endl;
    }
    return 0;
}
