// // Дано число N и N строк. Каждая строка содержит команду добавления или удаления натуральных чисел,
// а также запрос на получение k-ой порядковой статистики.
// Команда добавления числа A задается положительным числом A,
//  команда удаления числа A задается отрицательным числом “-A”.
//  Запрос на получение k-ой порядковой статистики задается числом k.
// Требования: скорость выполнения запроса - O(log n)

// Тест 1
// Ввод
// 5
// 40 0
// 10 1
// 4 1
// -10 0
// 50 2

// Вывод
// 40
// 40
// 10
// 4
// 50

// Тест 2
// Ввод
// 3
// 1 0
// 2 0
// -1 0

// Вывод
// 1 1 2

// Реализация AVL дерева. Необходимо его доработать:

//     добавить компаратор
//     логику findMin и removeMin нужно объединить в один метод findAndRemoveMin
//     элемент на место удаляемого берется из более глубокого поддерева (либо максимальный из левого, либо минимальный из правого)

#include <iostream>
#include <vector>
#include <cmath>

template <typename T>
struct DefaultComparator
{
    int operator()(const T &l, const T &r) const
    {
        if (l < r)
            return -1;
        if (l > r)
            return 1;
        return 0;
    }
};

template <typename Key, typename Value, typename Comparator = DefaultComparator<Key>>
class AVLTree
{
    struct Node
    {
        Node *left;
        Node *right;

        Key key;
        Value value;

        uint8_t height;

        Node() : left(nullptr), right(nullptr){};

        Node(const Key &key, const Value &value) : left(nullptr), right(nullptr),
                                                   key(key), value(value), height(1)
        {
        }
        ~Node() {}
    };

public:
    AVLTree(Comparator comp = Comparator()) : root(nullptr),
                                              items_count(0),
                                              comp(comp)
    {
    }

    ~AVLTree()
    {
        destroyTree(root);
    }

    size_t size() const { return items_count; }

    Value *find(const Key &key)
    {
        return find_aux(key, root);
    }

    void insert(const Key &key, const Value &value)
    {
        root = insert_aux(key, value, root);
    }

    void erase(const Key &key)
    {
        root = erase_aux(key, root);
    }

    Value kth_statistic(int index)
    {
        std::vector<Value> arr(0, 0);

        biuld_array(root, arr);

        Value ans = arr[index];

        return ans;
    }

private:
    // Обходим дерево в порядке in-order
    void biuld_array(Node *node, std::vector<Value> &result)
    {
        if (node->left)
        {
            biuld_array(node->left, result);
        }
        result.push_back(node->value);
        if (node->right)
        {
            biuld_array(node->right, result);
        }
    }

    void destroyTree(Node *node)
    {
        if (node)
        {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    Value *find_aux(const Key &key, Node *node)
    {
        if (!node)
        {
            return nullptr;
        }
        int cmp_res = comp(key, node->key);
        if (cmp_res == -1)
        { // key < node->key
            return find_aux(key, node->left);
        }
        else if (cmp_res == 1)
        { // key > node->key
            return find_aux(key, node->right);
        }
        // key == node->key
        return &node->value;
    }

    Node *insert_aux(const Key &key, const Value &value, Node *node)
    {
        if (!node)
        {
            items_count++;
            return new Node(key, value);
        }
        int cmp_res = comp(key, node->key);
        if (cmp_res == -1)
        { // key < node->key
            node->left = insert_aux(key, value, node->left);
        }
        else if (cmp_res == 1)
        { // key > node->key
            node->right = insert_aux(key, value, node->right);
        }
        // key == node->key
        return balance(node);
    }

    Node *erase_aux(const Key &key, Node *node)
    {
        if (!node)
        {
            return nullptr;
        }

        int cmp_res = comp(key, node->key);
        if (cmp_res == -1)
        { // key < node->key
            node->left = erase_aux(key, node->left);
        }
        else if (cmp_res == 1)
        { // key > node->key
            node->right = erase_aux(key, node->right);
        }
        else
        { // key == node->key
            Node *left = node->left;
            Node *right = node->right;

            // delete node;
            items_count--;

            if (!right)
            {
                return left;
            }

            // В ДЗ ДЕЛАТЬ ОДНОЙ ФУНКЦИЕЙ find_and_remove_min_node
            Node *new_node = find_and_remove_min_or_max(node);
            delete node;

            if (left && new_node->value != left->value)
            {
                new_node->left = left;
            }
            if (right && new_node->value != right->value)
            {
                new_node->right = right;
            }

            return balance(new_node);
        }
        return balance(node);
    }

    // Node *remove_min_node(Node *node)
    // {
    //     if (!node->left)
    //     {
    //         return node->right;
    //     }

    //     node->left = remove_min_node(node->left);
    //     return balance(node);
    // }

    Node *find_and_remove_min_or_max(Node *node)
    {
        Node *need_node = nullptr;
        // Найдем минимум в более глубоком дереве
        int bf = bfactor(node);
        Node *parent = nullptr;

        // Если правое дерево глубже или имеют такую же глубину
        if (bf >= 0)
        {
            node = node->right;
            parent = node;

            while (node->left) // Ищем родителя минимального элемента
            {
                parent = node;
                node = node->left;
            }
            need_node = node;                // need_node - минимальный
            parent->left = need_node->right; // правое поддерево минимального элемента переносим к родителю минимального элемента
        }
        // Если левое дерево глубже
        else
        {
            node = node->left;
            parent = node;

            while (node->right->right) // Ищем родителя максимального элемента
            {
                parent = node;
                node = node->right;
            }

            need_node = node->right;         // need_node - максимальный
            parent->right = need_node->left; // левое поддерево максимального элемента переносим к родителю максимального элемента
        }
        return need_node;
    }

    uint8_t height(Node *node)
    {
        if (!node)
        {
            return 0;
        }
        return node->height;
    }

    void fix_height(Node *node)
    {
        node->height = std::max(height(node->left), height(node->right)) + 1;
        //
    }

    int bfactor(Node *node)
    {
        return height(node->right) - height(node->left);
    }

    Node *balance(Node *node)
    {
        fix_height(node);

        int bf = bfactor(node);
        if (bf == 2)
        {
            if (bfactor(node->right) < 0)
            {
                node->right = rotate_right(node->right);
            }
            return rotate_left(node);
        }

        if (bf == -2)
        {
            if (bfactor(node->left) > 0)
            {
                node->left = rotate_left(node->left);
            }
            return rotate_right(node);
        }

        return node;
    }

    Node *rotate_left(Node *node)
    {
        Node *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        fix_height(node);
        fix_height(tmp);
        return tmp;
    };
    Node *rotate_right(Node *node)
    {
        Node *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        fix_height(node);
        fix_height(tmp);
        return tmp;
    };

    Node *root;
    size_t items_count;
    Comparator comp;
};

int main(int argc, const char *argv[])
{
    AVLTree<int, int> *tree = new AVLTree<int, int>();
    int n = 0, value = 0, index = 0;

    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> value >> index;
        if (value > 0)
        {
            tree->insert(value, value);
        }
        else if (value < 0)
        {
            value = std::abs(value);
            tree->erase(value);
        }
        std::cout << tree->kth_statistic(index) << std::endl;
    }

    delete tree;

    return 0;
}