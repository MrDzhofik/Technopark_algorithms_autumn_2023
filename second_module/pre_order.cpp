// Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
// Требуется построить бинарное дерево, заданное наивным порядком вставки.
// Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
// Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.

// pre-order обход (в глубину)
// visit(node)
// DFS(left)
// DFS(right)

#include <iostream>
#include <vector>
#include <stack>

template <class T>
struct Node
{
    Node() : left(nullptr), right(nullptr), visited(false){};
    Node(T &data) : left(nullptr), right(nullptr), visited(false), deleted(false), value(data){};
    ~Node(){
        // delete left;
        // delete right;
    };

    bool is_visited()
    {
        return visited;
    }

    void visit()
    {
        visited = true;
    }

    void delet()
    {
        deleted = true;
    }

    T value;
    bool deleted;
    bool visited;
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
    std::stack<Node<int> *> st;
    Node<int> *p = root;
    int i = 0;
    std::vector<int> result(size, 0);
    result[i++] = p->value;
    st.push(p);
    while (i != size)
    {
        if (p->left && !p->left->is_visited())
        {
            p = p->left;
            p->visit();
            result[i] = p->value;
            st.push(p);
            ++i;
        }
        else if (p->right && !p->right->is_visited())
        {
            p = p->right;
            p->visit();
            result[i] = p->value;
            st.push(p);
            ++i;
        }
        else
        {
            p = st.top();
            st.pop();
        }
    }
    return result;
};

template <typename T, typename Comparator>
BTree<T, Comparator>::~BTree()
{
    // std::stack<Node<int> *> st;
    // Node<int> *p = root;
    // st.push(p);
    // while (!st.empty())
    // {
    //     if (p->left || p->right)
    //     {
    //         if (p->left->left || p->left->right)
    //         {
    //             st.push(p);
    //             p = p->left;
    //         }
    //         else if (p->right->left || p->right->right)
    //         {
    //             st.push(p);
    //             p = p->right;
    //         }
    //         else
    //         {
    //             delete p;
    //             p = st.top();
    //             st.pop();
    //         }
    //     }
    // }

    std::stack<Node<int> *> st;
    Node<int> *p = root;
    int i = 0;
    if (p->left && p->right)
    {
        st.push(p);
        st.push(p);
    }
    else if (p->left || p->right)
    {
        st.push(p);
    }
    while (!st.empty())
    {
        if (p->left && !p->left->deleted)
        {
            p = p->left;
            if (p->left && p->right)
            {
                st.push(p);
                st.push(p);
            }
            else if (p->left || p->right)
            {
                st.push(p);
            }
            else
            {
                delete p;
                p = st.top();
                st.pop();
                p->left->deleted = true;
            }
            ++i;
        }
        else if (p->right && !p->right->deleted)
        {
            p = p->right;
            if (p->left && p->right)
            {
                st.push(p);
                st.push(p);
            }
            else if (p->left || p->right)
            {
                st.push(p);
            }
            else
            {
                delete p;
                p = st.top();
                st.pop();
                p->right->deleted = true;
            }
        }
        else
        {
            delete p;
            p->deleted = true;
            p = st.top();
            st.pop();
        }
    }
    delete root;
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