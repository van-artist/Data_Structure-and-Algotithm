#include <stdio.h>
#include <stdlib.h>

struct tree_node
{
    int data;
    int height;
    struct tree_node *left;
    struct tree_node *right;
};

typedef struct tree_node Node;
typedef struct tree_node *NodePtr;

NodePtr createNode(int data, int height)
{
    NodePtr newNode = (NodePtr)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->height = height;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void addNode(NodePtr *root, int data)
{
    NodePtr current_node = *root;
    NodePtr pre_node = NULL;
    int height = 1;

    while (current_node != NULL)
    {
        pre_node = current_node;
        if (data >= current_node->data)
        {
            current_node = current_node->right;
        }
        else
        {
            current_node = current_node->left;
        }
        height++;
    }

    NodePtr new_node = createNode(data, height);
    if (pre_node == NULL)
    {
        *root = new_node;
    }
    else if (data >= pre_node->data)
    {
        pre_node->right = new_node;
    }
    else
    {
        pre_node->left = new_node;
    }
}

void get_leaves(NodePtr root)
{
    if (root == NULL)
    {
        return;
    }
    if (root->left == NULL && root->right == NULL)
    {
        printf("%d %d\n", root->data, root->height);
    }
    else
    {
        get_leaves(root->left);
        get_leaves(root->right);
    }
}

int main()
{
    int TIMES = 0;
    NodePtr root = NULL;

    scanf("%d", &TIMES);
    for (int i = 0; i < TIMES; i++)
    {
        int tempdata;
        scanf("%d", &tempdata);
        addNode(&root, tempdata);
    }

    get_leaves(root);

    return 0;
}
