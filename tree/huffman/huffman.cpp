#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <memory>
#include <string>
#include <iomanip>
#include <cstring>

using namespace std;

struct Node
{
    int weight;
    char value;
    shared_ptr<Node> left, right;

    Node(int w, char v = '\0', shared_ptr<Node> l = nullptr, shared_ptr<Node> r = nullptr)
        : weight(w), value(v), left(l), right(r) {}
};

struct CompareNode
{
    bool operator()(const shared_ptr<Node> &a, const shared_ptr<Node> &b)
    {
        if (a->weight == b->weight)
        {
            return a->value > b->value;
        }
        return a->weight > b->weight;
    }
};

using HuffmanTree = shared_ptr<Node>;
using MinHeap = priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, CompareNode>;

void generate_codes(const HuffmanTree &root, unordered_map<char, string> &codes, string code = "")
{
    if (!root)
        return;

    if (!root->left && !root->right)
    {
        codes[root->value] = code;
        return;
    }

    generate_codes(root->left, codes, code + "0");
    generate_codes(root->right, codes, code + "1");
}

void save_huffman_codes_in_hex(ofstream &output_file, ifstream &input_file, const unordered_map<char, string> &huffman_codes)
{
    char tmp_ch;
    int bit_count = 0;
    unsigned char current_byte = 0;

    while (input_file.get(tmp_ch))
    {
        if (tmp_ch == '\n')
            continue;

        const string &code = huffman_codes.at(tmp_ch);
        for (char bit : code)
        {
            current_byte = (current_byte << 1) | (bit - '0');
            bit_count++;

            if (bit_count == 8)
            {
                output_file << hex << setw(2) << setfill('0') << (int)current_byte;
                current_byte = 0;
                bit_count = 0;
            }
        }
    }

    const string &eof_code = huffman_codes.at('\0');
    for (char bit : eof_code)
    {
        current_byte = (current_byte << 1) | (bit - '0');
        bit_count++;

        if (bit_count == 8)
        {
            output_file << hex << setw(2) << setfill('0') << (int)current_byte;
            current_byte = 0;
            bit_count = 0;
        }
    }

    if (bit_count > 0)
    {
        current_byte <<= (8 - bit_count);
        output_file << hex << setw(2) << setfill('0') << (int)current_byte;
    }
}

int encode(const string &input_file_path, const string &output_file_path)
{
    unordered_map<char, int> char_count;
    unordered_map<char, string> huffman_codes;

    ifstream input_file(input_file_path);
    if (!input_file)
    {
        cerr << "Failed to open input file" << endl;
        return -1;
    }

    char tmp_ch;
    while (input_file.get(tmp_ch))
    {
        if (tmp_ch != '\n')
        {
            char_count[tmp_ch]++;
        }
    }
    char_count['\0'] = 1;
    input_file.clear();
    input_file.seekg(0, ios::beg);

    MinHeap min_heap;
    for (const auto &[ch, count] : char_count)
    {
        min_heap.push(make_shared<Node>(count, ch));
    }

    while (min_heap.size() > 1)
    {
        auto left = min_heap.top();
        min_heap.pop();
        auto right = min_heap.top();
        min_heap.pop();

        auto new_node = make_shared<Node>(left->weight + right->weight, '\0', left, right);
        min_heap.push(new_node);
    }

    HuffmanTree huffman_tree = min_heap.top();
    generate_codes(huffman_tree, huffman_codes);

    ofstream freq_output("frequency.txt");
    for (const auto &[ch, count] : char_count)
    {
        freq_output << ch << ": " << count << endl;
    }

    ofstream code_output("codes.txt");
    for (const auto &[ch, code] : huffman_codes)
    {
        code_output << ch << ": " << code << endl;
    }

    ofstream output_file(output_file_path);
    if (!output_file)
    {
        cerr << "Failed to open output file" << endl;
        return -1;
    }

    save_huffman_codes_in_hex(output_file, input_file, huffman_codes);

    return 0;
}

int main()
{
    if (encode("input.txt", "output.txt") != 0)
    {
        cerr << "Encoding failed." << endl;
        return 1;
    }
    cout << "Encoding completed successfully." << endl;
    return 0;
}
