#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

#define MAX_CHAR_NUM 256
#define MAX_CODE_LEN 16

int index_count = 0;
typedef struct node
{
    int weight;
    char value;
    struct node *parent;
    struct node *left;
    struct node *right;
    int index;
} Node, *HuffmanTree, *NodePtr;

typedef struct min_heap
{
    NodePtr *elems;
    int curSize;
} MinHeap;

void print_heap(NodePtr *heap, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("(%c)%d[%d] \t", heap[i]->value, heap[i]->weight, heap[i]->index);
    }
    printf("\n");
}

NodePtr create_node(int weight, char value, int index)
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
    node->index = index;
    index_count++;
    return node;
}

int should_swap(NodePtr a, NodePtr b)
{
    return (a->weight < b->weight) ||
           (a->weight == b->weight && a->index < b->index);
}

void heapify(MinHeap *heap, int i)
{
    int smallest_index = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->curSize && should_swap(heap->elems[left], heap->elems[smallest_index]))
    {
        smallest_index = left;
    }

    if (right < heap->curSize && should_swap(heap->elems[right], heap->elems[smallest_index]))
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

    while (i > 0)
    {
        int parentIndex = (i - 1) / 2;

        if (heap->elems[parentIndex]->weight > heap->elems[i]->weight ||
            (heap->elems[parentIndex]->weight == heap->elems[i]->weight &&
             heap->elems[parentIndex]->index > heap->elems[i]->index))
        {
            NodePtr temp = heap->elems[i];
            heap->elems[i] = heap->elems[parentIndex];
            heap->elems[parentIndex] = temp;
            i = parentIndex;
        }
        else
        {
            break;
        }
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
        codes[(unsigned char)root->value] = (char *)malloc(strlen(code) + 1);
        if (codes[(unsigned char)root->value] != NULL)
        {
            strcpy(codes[(unsigned char)root->value], code);
        }
        // printf("Character '%c'\t: %s \n", root->value, code);
        return;
    }

    code[depth] = '0';
    generate_codes(root->left, codes, code, depth + 1);

    code[depth] = '1';
    generate_codes(root->right, codes, code, depth + 1);
}

void save_huffman_codes_in_hex(FILE *output_file, FILE *input_file, char **huffman_codes)
{
    char tmp_ch;
    int bit_count = 0;
    unsigned char current_half_byte = 0;
    while ((tmp_ch = fgetc(input_file)) != EOF)
    {
        if (tmp_ch == '\n')
            continue;

        const char *code = huffman_codes[(unsigned char)tmp_ch];
        for (const unsigned char *p = (const unsigned char *)code; *p != '\0'; ++p)
        {
            current_half_byte = (current_half_byte << 1) | (*p - '0');
            bit_count++;

            if (bit_count == 8)
            {
                fprintf(output_file, "%02x", current_half_byte);
                printf("%02x", current_half_byte);
                current_half_byte = 0;
                bit_count = 0;
            }
        }
    }

    const char *code = huffman_codes['\0'];
    for (const char *p = code; *p != '\0'; ++p)
    {
        current_half_byte = (current_half_byte << 1) | (*p - '0');
        bit_count++;

        if (bit_count == 8)
        {
            fprintf(output_file, "%02x", current_half_byte);
            printf("%02x", current_half_byte);
            current_half_byte = 0;
            bit_count = 0;
        }
    }

    if (bit_count > 0)
    {
        current_half_byte <<= (8 - bit_count);
        fprintf(output_file, "%02x", current_half_byte);
        printf("%02x", current_half_byte);
    }
}

NodePtr merge_nodes(NodePtr left, NodePtr right)
{
    NodePtr new_node = (NodePtr)malloc(sizeof(Node));
    if (!new_node)
    {
        return NULL;
    }

    new_node->weight = left->weight + right->weight;
    new_node->value = 0;
    new_node->left = left;
    new_node->right = right;
    new_node->parent = NULL;
    new_node->index = index_count;
    index_count++;

    left->parent = new_node;
    right->parent = new_node;

    return new_node;
}

int encode(const char *input_file_path, const char *output_file_path)
{
    int *char_count = (int *)calloc(MAX_CHAR_NUM, sizeof(int));
    char **huffman_codes = (char **)malloc(sizeof(char *) * MAX_CHAR_NUM);

    for (int i = 0; i < MAX_CHAR_NUM; i++)
    {
        huffman_codes[i] = (char *)malloc(MAX_CODE_LEN);
    }

    FILE *file = fopen(input_file_path, "r");
    if (file == NULL)
    {
        perror("Failed to open file");
        return -1;
    }

    int tmp_ch;
    while ((tmp_ch = fgetc(file)) != EOF)
    {
        if (tmp_ch != '\n')
        {
            char_count[tmp_ch]++;
        }
    }
    char_count['\0'] = 1;
    fclose(file);
    FILE *frequncy_output = fopen("frequency.txt", "w");
    for (int i = 0; i < MAX_CHAR_NUM; i++)
    {
        if (char_count[i] > 0)
        {
            fprintf(frequncy_output, "%c: %d\n", i, char_count[i]);
        }
    }
    MinHeap char_min_heap;
    char_min_heap.elems = (NodePtr *)malloc(MAX_CHAR_NUM * sizeof(NodePtr));
    char_min_heap.curSize = 0;
    for (int i = 0; i < MAX_CHAR_NUM; i++)
    {
        if (char_count[i] > 0)
        {
            char_min_heap.elems[char_min_heap.curSize] = create_node(char_count[i], i, char_min_heap.curSize);
            char_min_heap.curSize++;
        }
    }
    // print_heap(char_min_heap.elems, char_min_heap.curSize);
    for (int i = char_min_heap.curSize / 2 - 1; i >= 0; i--)
    {
        heapify(&char_min_heap, i);
    }
    print_heap(char_min_heap.elems, char_min_heap.curSize);
    HuffmanTree huffman_tree = NULL;

    while (char_min_heap.curSize > 1)
    {
        NodePtr tmp_node1, tmp_node2;

        // 弹出堆顶的两个最小节点
        if (pop_min_heap(&char_min_heap, &tmp_node1) != 0 || pop_min_heap(&char_min_heap, &tmp_node2) != 0)
        {
            printf("Failed to pop from heap\n");
            break;
        }

        NodePtr new_node = merge_nodes(tmp_node1, tmp_node2);
        if (!new_node)
        {
            printf("Failed to merge nodes\n");
            break;
        }

        insert_min_heap(&char_min_heap, new_node);
        // print_heap(char_min_heap.elems, char_min_heap.curSize);

        huffman_tree = new_node;
    }

    char code[MAX_CODE_LEN];
    generate_codes(huffman_tree, huffman_codes, code, 0);
    FILE *code_output = fopen("codes.txt", "w");
    for (int i = 0; i < MAX_CHAR_NUM; i++)
    {
        if (huffman_codes[i][0] == '\0')
        {
            continue;
        }

        fprintf(code_output, "%c: ", i);
        fprintf(code_output, "%s", huffman_codes[i]);
        fprintf(code_output, "\n");
    }
    fclose(code_output);
    FILE *input_file = fopen(input_file_path, "r");
    FILE *output_file = fopen(output_file_path, "w");
    if (input_file == NULL || output_file == NULL)
    {
        perror("Failed to open file");
        return -1;
    }

    save_huffman_codes_in_hex(output_file, input_file, huffman_codes);

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
    encode("input.txt", "output.txt");
    return 0;
}
