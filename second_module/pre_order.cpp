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

// B-Tree
template <typename T>
class BTree
{
public:
    struct Node
    {
        Node() : left(nullptr), right(nullptr), visited(false){};
        Node(T &data) : left(nullptr), right(nullptr), visited(false), value(data){};
        ~Node()
        {
            delete left;
            delete right;
        };

        bool is_visited()
        {
            return visited;
        }

        void visit()
        {
            visited = true;
        }

        T value;
        bool visited;
        Node *left;
        Node *right;
    };
    BTree() : root(nullptr){};
    BTree(int size) : root(nullptr), size(size){};
    ~BTree(){};

    // Insert
    void Insert(T data)
    {
        Node *tmp = new Node(data);
        bool find = false;
        // если еще нет элементов
        if (!root)
        {
            root = tmp;
        }
        else
        {
            Node *p = root;
            while (!find)
            {
                if (p->value > data)
                {
                    if (!p->left)
                    {
                        find = true;
                        p->left = tmp;
                    }
                    p = p->left;
                }
                else if (p->value < data)
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

    // Print
    std::vector<int> PrintPreOrder()
    {
        std::stack<Node *> st;
        Node *p = root;
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

private:
    size_t size;
    Node *root;
};

int main()
{
    int n = 0;
    int data = 0;
    std::cin >> n;
    BTree<int> tree(n);
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