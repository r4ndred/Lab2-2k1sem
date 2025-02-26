#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

// Структура узла бинарного дерева
struct TreeNode {
    int val;          // Значение узла
    TreeNode* left;   // Указатель на левое поддерево
    TreeNode* right;  // Указатель на правое поддерево

    // Конструктор узла
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Функция для построения сбалансированного бинарного дерева из отсортированного массива
TreeNode* insertLevelOrder(vector<int>& arr, int start, int end) {
    if (start > end) return nullptr;

    int mid = (start + end) / 2;
    TreeNode* root = new TreeNode(arr[mid]);

    root->left = insertLevelOrder(arr, start, mid - 1);
    root->right = insertLevelOrder(arr, mid + 1, end);

    return root;
}

// Функция для вывода дерева уровнями
void printTree(TreeNode* root) {
    if (!root) return;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();

        while (size--) {
            TreeNode* temp = q.front();
            q.pop();
            cout << temp->val << " ";

            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
        cout << endl;
    }
}

// Функция для поиска узла с заданным значением
TreeNode* search(TreeNode* root, int key) {
    if (root == nullptr || root->val == key)
        return root;

    if (key < root->val)
        return search(root->left, key);

    return search(root->right, key);
}

// Функция для удаления узла из дерева
TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) return root;

    // Находим узел, который нужно удалить
    if (key < root->val)
        root->left = deleteNode(root->left, key);
    else if (key > root->val)
        root->right = deleteNode(root->right, key);
    else {
        // Узел, который нужно удалить, найден

        // Если у узла нет детей (листьевой узел)
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        // Если у узла есть только один дочерний элемент
        else if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        // Если у узла есть два дочерних элемента, находим минимальный узел в правом поддереве
        TreeNode* temp = root->right;
        while (temp && temp->left) {
            temp = temp->left;
        }

        // Переносим значение минимального узла в текущий узел
        root->val = temp->val;

        // Удаляем минимальный узел
        root->right = deleteNode(root->right, temp->val);
    }

    return root;
}

int main() {
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Введите элементы множества: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());

    TreeNode* root = insertLevelOrder(arr, 0, n - 1);

    cout << "Дерево в виде уровней:" << endl;
    printTree(root);

    int valueToDelete;
    cout << "Введите значение для удаления: ";
    cin >> valueToDelete;

    // Ищем и удаляем узел с заданным значением
    root = deleteNode(root, valueToDelete);

    cout << "Дерево после удаления:" << endl;
    printTree(root);

    return 0;
}
