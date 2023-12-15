// Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
// Требуется построить бинарное дерево, заданное наивным порядком вставки.
// Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
// Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.

// pre-order обход (в глубину)
// visit(node)
// DFS(left)
// DFS(right)

// 10 2 5 6 4 7 8 9 3 1 10
// 2 1 5 4 3 6 7 8 9 10

// 10 5 9 4 3 7 2 6 10 1 8
// 5 4 3 2 1 9 7 6 8 10

#include <iostream>
#include <vector>
#include <stack>

template <class T>
struct Node
{
    Node() : left(nullptr), right(nullptr){};
    Node(T &data) : left(nullptr), right(nullptr), value(data){};
    ~Node(){};

    T value;
    Node *left;
    Node *right;
};

template <class T>
struct DefaultComparator
{
    bool operator()(const T &l, const T &r) const
    {
        return l > r;
    }
};

class NodeComparator
{
public:
    NodeComparator()
    {
    }

    bool operator()(const Node<int> *l, const Node<int> *r)
    {
        return l->value >= r->value;
    }
};

// B-Tree
template <typename T, typename Comparator = DefaultComparator<int>>
class BTree
{
public:
    BTree() : root(nullptr){};
    BTree(int size) : root(nullptr), size(size){};
    ~BTree();

    // Insert
    void Insert(T &data);

    // Print
    std::vector<int> PrintPreOrder();

private:
    size_t size;
    Node<int> *root;
    Comparator cmp;
};

template <typename T, typename Comparator>
void BTree<T, Comparator>::Insert(T &data)
{
    Node<int> *tmp = new Node(data);
    bool find = false;
    // если еще нет элементов
    if (!root)
    {
        root = tmp;
    }
    else
    {
        Node<int> *p = root;
        while (!find)
        {
            if (cmp(p, tmp))
            {
                if (!p->left)
                {
                    find = true;
                    p->left = tmp;
                }
                p = p->left;
            }
            else
            {
                if (!p->right)
                {
                    find = true;
                    p->right = tmp;
                }
                p = p->right;
            }
        }
    }
}

template <typename T, typename Comparator>
std::vector<int> BTree<T, Comparator>::PrintPreOrder()
{
    std::vector<int> ans(size, 0);
    std::stack<Node<T> *> st;
    int i = 0;

    Node<T> *current = root;

    while (current || !st.empty())
    {
        while (current)
        {
            ans[i++] = current->value;

            if (current->right)
                st.push(current->right);

            current = current->left;
        }

        if (!st.empty())
        {
            current = st.top();
            st.pop();
        }
    }

    return ans;
}

template <typename T, typename Comparator>
BTree<T, Comparator>::~BTree()
{
    std::stack<Node<T> *> st;
    Node<T> *current = root;

    while (current || !st.empty())
    {
        while (current)
        {
            st.push(current);
            current = current->left;
        }

        current = st.top();
        st.pop();

        Node<T> *tmp = current->right;
        delete current;
        current = tmp;
    }
}

int main()
{
    int n = 0;
    std::cin >> n;
    BTree<int, NodeComparator> tree(n);
    int data = 0;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> data;
        tree.Insert(data);
    }
    std::vector<int> ans = tree.PrintPreOrder();
    int size = ans.size();
    for (int i = 0; i < size; ++i)
    {
        std::cout << ans[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}