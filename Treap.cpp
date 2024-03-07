#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

// Definir una estructura para el nodo del treap
typedef struct TreapNode
{
    int priority, size, value;
    struct TreapNode *left, *right;

} TreapNode;
typedef TreapNode *pTreapNode;

// Función para crear un nuevo nodo
pTreapNode newNode(int value)
{
    pTreapNode node = new TreapNode;
    node->priority = rand();
    node->size = 1;
    node->value = value;
    return node;
}

// Función para obtener el tamaño del treap
int getSize(pTreapNode tree)
{
    return tree ? tree->size : 0;
}

// Función para actualizar el tamaño del treap
void refreshSize(pTreapNode tree)
{
    if (tree)
        tree->size = getSize(tree->left) + 1 + getSize(tree->right);
}

// Función para dividir el treap en dos partes
void split(pTreapNode tree, pTreapNode &left, pTreapNode &right, int pos, int add = 0)
{
    if (!tree)
        return void(left = right = NULL);

    int curr_pos = add + getSize(tree->left);
    if (curr_pos <= pos)
    {
        split(tree->right, tree->right, right, pos, curr_pos + 1);
        left = tree;
    }
    else
    {
        split(tree->left, left, tree->left, pos, add);
        right = tree;
    }
        
    refreshSize(tree);
}

// Función para unir dos treaps
void merge(pTreapNode &tree, pTreapNode left, pTreapNode right)
{
    if (!left || !right)
        tree = left ? left : right;
    else if (left->priority > right->priority)
        merge(left->right, left->right, right), tree = left;
    else
        merge(right->left, left, right->left), tree = right;
    refreshSize(tree);
}

// Función para agregar un nodo al treap
void insertNode(pTreapNode &tree, pTreapNode node)
{
    if (!tree)
        tree = node;
    else if (node->priority > tree->priority)
    {
        split(tree, node->left, node->right, node->value);
        tree = node;
    }
    else
        insertNode(tree->value <= node->value ? tree->right : tree->left, node);
    
    refreshSize(tree);
}

// Función para realizar múltiples intercambios en el treap
void multipleSwap(pTreapNode &root, int start, int end, int total)
{
    start--;
    end--; 

    if (start == -1 && 2 * end >= total)
    {
        pTreapNode root0, root1, root2;
        pTreapNode temp1, temp2;
        split(root, root0, temp1, total - end - 2);
        split(temp1, root1, root2, 2 * (end + 1) - total - 1);

        merge(temp2, root2, root1);
        merge(root, temp2, root0);
        return;
    }

    pTreapNode root0, root1, root2, root3;
    pTreapNode temp1, temp2, temp3, temp4, temp5;
    bool out_range = 2 * end - start >= total;
    int split2 = (out_range ? total - end - 2 : end - start - 1);
    int split3 = (out_range ? 2 * end - total - 2 : end - start - 1);

    split(root, root0, temp1, start);
    split(temp1, root1, temp2, split2);
    split(temp2, root2, root3, split3);

    if (!out_range)
    {
        merge(temp4, root0, root2);
        merge(temp5, temp4, root1);
        merge(root, temp5, root3);
        return;
    }

    merge(temp4, root0, root3);
    merge(temp5, temp4, root2);
    merge(root, temp5, root1);
}


// Función para imprimir el treap en recorrido en orden
void inorderPrint(pTreapNode tree)
{
    if (!tree)
        return;

    inorderPrint(tree->left);
    cout << tree->value << " ";
    inorderPrint(tree->right);
}

// Función para realizar los intercambios
void performSwaps(int n, vector<pair<int,int>> swaps)
{
    pTreapNode root = newNode(1);
    for (int i = 2; i <= n; ++i)
        insertNode(root, newNode(i));

    for (pair<int, int> op : swaps)
        multipleSwap(root, op.first - 1, op.second - 1, n);

    inorderPrint(root);
    cout << endl;
}

// Ejemplo
int main()
{
    performSwaps(5, {{1,3}, {2,4}});
}


