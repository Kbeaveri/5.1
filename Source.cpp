#include <iostream>
#include <fstream>



using namespace std;


class tree_elem
{
public:
    int m_data;
    tree_elem* m_left;
    tree_elem* m_right;
    tree_elem(int val)
    {
        m_left = NULL;
        m_right = NULL;
        m_data = val;
    }
};


class binary_tree
{
private:
    tree_elem* m_root;
    int m_size;
    void print_tree(tree_elem*);
    void delete_tree(tree_elem*);

public:
    binary_tree(int);
    ~binary_tree();
    void print();
    int findy();
    int find_tree(tree_elem*, int&);
    bool find(int);
    void insert(int);
    void erase(int);
};



binary_tree::binary_tree(int key)
{
    m_root = new tree_elem(key);
    m_size = 1;
}


binary_tree::~binary_tree()
{
    delete_tree(m_root);
}

void binary_tree::delete_tree(tree_elem* curr)
{
    if (curr)
    {
        delete_tree(curr->m_left);
        delete_tree(curr->m_right);
        delete curr;
    }
}


void binary_tree::print()
{
    print_tree(m_root);
    cout << endl;
}

int binary_tree::findy()
{
    int sum = 0;
    return find_tree(m_root, sum);
    cout << endl;
}

void binary_tree::print_tree(tree_elem* curr)
{
    if (curr) // Проверка на ненулевой указатель
    {
        print_tree(curr->m_left);
        cout << curr->m_data << " ";
        print_tree(curr->m_right);
    }
}

int binary_tree::find_tree(tree_elem* curr, int& sum)
{
    if (curr) // Проверка на ненулевой указатель
    {
        find_tree(curr->m_left, sum);
        if (curr->m_left == NULL && curr->m_right == NULL) {
            sum++;
        }
        find_tree(curr->m_right, sum);
    }
    return sum;
}



bool binary_tree::find(int key)
{
    tree_elem* curr = m_root;
    while (curr && curr->m_data != key)
    {
        if (curr->m_data > key)
            curr = curr->m_left;
        else
            curr = curr->m_right;
    }
    return curr != NULL;
}



void binary_tree::insert(int key)
{
    tree_elem* curr = m_root;
    while (curr && curr->m_data != key)
    {
        if (curr->m_data > key && curr->m_left == NULL)
        {
            curr->m_left = new tree_elem(key);
            ++m_size;
            return;
        }
        if (curr->m_data < key && curr->m_right == NULL)
        {
            curr->m_right = new tree_elem(key);
            ++m_size;
            return;
        }
        if (curr->m_data > key)
            curr = curr->m_left;
        else
            curr = curr->m_right;
    }
}


void binary_tree::erase(int key)
{
    tree_elem* curr = m_root;
    tree_elem* parent = NULL;
    while (curr && curr->m_data != key)
    {
        parent = curr;
        if (curr->m_data > key)
        {
            curr = curr->m_left;
        }
        else
        {
            curr = curr->m_right;
        }
    }
    if (!curr)
        return;
    if (curr->m_left == NULL)
    {
        if (parent && parent->m_left == curr)
            parent->m_left = curr->m_right;
        if (parent && parent->m_right == curr)
            parent->m_right = curr->m_right;
        --m_size;
        delete curr;
        return;
    }
    if (curr->m_right == NULL)
    {
        // Вместо curr подвешивается его левое поддерево
        if (parent && parent->m_left == curr)
            parent->m_left = curr->m_left;
        if (parent && parent->m_right == curr)
            parent->m_right = curr->m_left;
        --m_size;
        delete curr;
        return;
    }
    // У элемента есть два потомка, тогда на место элемента поставим
    // наименьший элемент из его правого поддерева
    tree_elem* replace = curr->m_right;
    while (replace->m_left)
        replace = replace->m_left;
    int replace_value = replace->m_data;
    erase(replace_value);
    curr->m_data = replace_value;

}


int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    ifstream fin("input.txt");
    int n, x;
    fin >> n >> x;
    binary_tree tree(x);
    for (int i = 0; i < n; i++) {
        int x;
        fin >> x;
        tree.insert(x);
    }
    int k = -1;
    while (k < 7) {
        cout << "1.Добавить элемент" << endl;
        cout << "2.Удалить элемент" << endl;
        cout << "3.Просмотр дерева" << endl;
        cout << "4.Очистка дерева" << endl;
        cout << "5.Поиск элемента" << endl;
        cout << "6.Подсчет листьев в дереве" << endl;
        cout << "7.Выход" << endl;
        cin >> k;
        switch (k)
        {
        case 1:
            int x;
            cout << "Введите элемент" << endl;
            cin >> x;
            tree.insert(x);
            break;
        case 2:
            int x2;
            cout << "Введите элемент" << endl;
            cin >> x2;
            tree.erase(x2);
            break;
        case 3:
            tree.print();
            break;
        case 4:
            tree.~binary_tree();
            break;
        case 5:
            int x5;
            cout << "Введите элемент" << endl;
            cin >> x5;
            if (tree.find(x5)) {
                cout << "YES" << endl;
            }
            else {
                cout << "NO" << endl;
            }
            break;
        case 6:
            cout << tree.findy() << endl;
            break;
        case 7:
            cout << "Спасибо за использование";
            break;
        default:
            break;
        }
    }
}