#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHAR_NUM 256
#define MAX_CODE_LEN 64 // 增加编码长度以支持更复杂的编码

typedef struct node
{
    int weight;
    char value;
    struct node *parent;
    struct node *left;
    struct node *right;
} Node, *HuffmanTree, *NodePtr;

typedef struct min_heap
{
    NodePtr *elems;
    int curSize;
} MinHeap;

NodePtr create_node(int weight, char value)
{
    NodePtr node = (NodePtr)malloc(sizeof(Node));
    if (node == NULL)
    {
        perror("Failed to allocate memory");
        return NULL;
    }
    node->weight = weight;
    node->value = value;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void heapify(MinHeap *heap, int i)
{
    int smallest_index = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->curSize && heap->elems[left]->weight < heap->elems[smallest_index]->weight)
    {
        smallest_index = left;
    }

    if (right < heap->curSize && heap->elems[right]->weight < heap->elems[smallest_index]->weight)
    {
        smallest_index = right;
    }

    if (smallest_index != i)
    {
        NodePtr temp = heap->elems[i];
        heap->elems[i] = heap->elems[smallest_index];
        heap->elems[smallest_index] = temp;

        heapify(heap, smallest_index);
    }
}

int array_to_min_heap(MinHeap *heap)
{
    for (int i = heap->curSize / 2 - 1; i >= 0; i--)
    {
        heapify(heap, i);
    }
    return 0;
}

int pop_min_heap(MinHeap *heap, NodePtr *output)
{
    if (heap->curSize == 0)
        return -1;

    *output = heap->elems[0];
    heap->elems[0] = heap->elems[heap->curSize - 1];
    (heap->curSize)--;
    heapify(heap, 0);
    return 0;
}

int insert_min_heap(MinHeap *heap, NodePtr elem)
{
    heap->elems[heap->curSize] = elem;
    int i = heap->curSize;
    heap->curSize++;

    while (i > 0 && heap->elems[(i - 1) / 2]->weight > heap->elems[i]->weight)
    {
        NodePtr temp = heap->elems[i];
        heap->elems[i] = heap->elems[(i - 1) / 2];
        heap->elems[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
    return 0;
}

void free_huffman_tree(NodePtr root)
{
    if (root == NULL)
    {
        return;
    }
    free_huffman_tree(root->left);
    free_huffman_tree(root->right);
    free(root);
}

void generate_codes(HuffmanTree root, char **codes, char *code, int depth)
{
    if (root == NULL)
    {
        return;
    }

    if (root->left == NULL && root->right == NULL)
    {
        code[depth] = '\0';
        codes[(unsigned char)root->value] = strdup(code);
        return;
    }

    code[depth] = '0';
    generate_codes(root->left, codes, code, depth + 1);

    code[depth] = '1';
    generate_codes(root->right, codes, code, depth + 1);
}

void write_bit(FILE *file, unsigned char *bit_buffer, int *bit_count, int bit)
{
    // Set the bit in the correct position in the buffer
    if (bit)
        *bit_buffer |= (1 << (7 - *bit_count));
    (*bit_count)++;

    // If we have 8 bits, write it as a byte
    if (*bit_count == 8)
    {
        fwrite(bit_buffer, sizeof(unsigned char), 1, file);
        *bit_count = 0;
        *bit_buffer = 0;
    }
}

void write_code(FILE *file, const char *code, unsigned char *bit_buffer, int *bit_count)
{
    for (int i = 0; code[i] != '\0'; i++)
    {
        int bit = code[i] - '0';
        write_bit(file, bit_buffer, bit_count, bit);
    }
}

int encode(const char *input_file_path, const char *output_file_path)
{
    int *char_count = (int *)malloc(sizeof(int) * MAX_CHAR_NUM);
    int char_type_count = 0;
    MinHeap char_min_heap;
    char **huffman_codes;
    huffman_codes = (char **)malloc(sizeof(char *) * MAX_CHAR_NUM);

    if (char_count == NULL)
    {
        perror("Failed to allocate memory");
        return -1;
    }

    memset(char_count, 0, sizeof(int) * MAX_CHAR_NUM);
    FILE *file = fopen(input_file_path, "r");
    if (file == NULL)
    {
        perror("Failed to open file");
        return -1;
    }

    int tmp_ch;
    while ((tmp_ch = fgetc(file)) != EOF)
    {
        char_count[tmp_ch]++;
    }
    fclose(file);

    for (int i = 0; i < MAX_CHAR_NUM; i++)
    {
        if (char_count[i] > 0)
        {
            char_type_count++;
        }
    }

    char_min_heap.elems = (NodePtr *)malloc(sizeof(NodePtr) * char_type_count);
    char_min_heap.curSize = 0;
    for (int i = 0; i < MAX_CHAR_NUM; i++)
    {
        if (char_count[i] > 0)
        {
            NodePtr node = create_node(char_count[i], i);
            char_min_heap.elems[char_min_heap.curSize++] = node;
        }
    }

    array_to_min_heap(&char_min_heap);
    HuffmanTree huffman_tree = NULL;

    while (char_min_heap.curSize > 1)
    {
        NodePtr tmp_node1, tmp_node2;
        if (pop_min_heap(&char_min_heap, &tmp_node1) != 0 || pop_min_heap(&char_min_heap, &tmp_node2) != 0)
        {
            printf("Failed to pop from heap\n");
            break;
        }

        NodePtr new_node = create_node(tmp_node1->weight + tmp_node2->weight, 0);
        new_node->left = tmp_node1;
        new_node->right = tmp_node2;
        tmp_node1->parent = new_node;
        tmp_node2->parent = new_node;

        insert_min_heap(&char_min_heap, new_node);
        huffman_tree = new_node;
    }

    for (int i = 0; i < MAX_CHAR_NUM; i++)
    {
        huffman_codes[i] = NULL;
    }

    char code[MAX_CODE_LEN];
    generate_codes(huffman_tree, huffman_codes, code, 0);

    FILE *input_file = fopen(input_file_path, "r");
    FILE *output_file = fopen(output_file_path, "wb");
    if (input_file == NULL || output_file == NULL)
    {
        perror("Failed to open file");
        return -1;
    }

    unsigned char bit_buffer = 0;
    int bit_count = 0;

    while ((tmp_ch = fgetc(input_file)) != EOF)
    {
        write_code(output_file, huffman_codes[tmp_ch], &bit_buffer, &bit_count);
    }

    // Flush remaining bits in the buffer
    if (bit_count > 0)
    {
        fwrite(&bit_buffer, sizeof(unsigned char), 1, output_file);
    }

    fclose(input_file);
    fclose(output_file);

    free_huffman_tree(huffman_tree);
    for (int i = 0; i < MAX_CHAR_NUM; i++)
    {
        if (huffman_codes[i] != NULL)
        {
            free(huffman_codes[i]);
        }
    }
    free(huffman_codes);
    free(char_count);
    free(char_min_heap.elems);
    return 0;
}

int main()
{
    encode("input.txt", "./out/output.bin");
    return 0;
}
