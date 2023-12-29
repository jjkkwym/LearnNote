#include <iostream>
#include <stdexcept>

template<typename T>
class Stack {
private:
    int _capacity;  // 栈容量
    int _size;      // 栈大小
    T* _data;       // 栈元素数组

public:
    Stack(int capacity = 100) : _capacity(capacity), _size(0) {
        _data = new T[_capacity];
    }

    ~Stack() {
        delete[] _data;
    }

    bool isEmpty() const {
        return _size == 0;
    }

    bool isFull() const {
        return _size == _capacity;
    }

    void push(const T& elem) {
        if (isFull()) {
            throw std::overflow_error("Stack is full.");
        }
        _data[_size++] = elem;
    }

    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty.");
        }
        return _data[--_size];
    }

    T& top() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty.");
        }
        return _data[_size - 1];
    }

    int size() const {
        return _size;
    }
};

#include <iostream>

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
private:
    TreeNode* root;

public:
    BinaryTree() {
        root = nullptr;
    }

    void insert(int value) {
        if (root == nullptr) {
            root = new TreeNode(value);
        } else {
            insertNode(root, value);
        }
    }

    void insertNode(TreeNode* node, int value) {
        if (value < node->data) {
            if (node->left != nullptr) {
                insertNode(node->left, value);
            } else {
                node->left = new TreeNode(value);
            }
        } else {
            if (node->right != nullptr) {
                insertNode(node->right, value);
            } else {
                node->right = new TreeNode(value);
            }
        }
    }

    void printInorder() {
        printInorderTraversal(root);
    }

    void printInorderTraversal(TreeNode* node) {
        if (node != nullptr) {
            printInorderTraversal(node->left);
            std::cout << node->data << " ";
            printInorderTraversal(node->right);
        }
    }
};

template<typename type>
class list_stack{
private:
    int _capacity;
    int _size;
    type* _data;
public:
    list_stack(int capacity = 100) : _capacity(capacity), _size(0), _data(new type[_capacity]) 
    {

    }
    
    ~list_stack(){
        delete[] _data;
    }
    
    bool isEmpty() const{
        return (_size == 0);
    }

    bool isFull() const{
        return (_size == _capacity);
    }

    void push(const type& elem){
        if(isFull())
        {
            throw std::out_of_range("Stack is full");
        }
    }
};



/* 类模板特化之数组.cpp */
#include <cstring>
#include <iostream>
using namespace std;
#define MAXSIZE 5
template <class T> class Array {
public:
  Array() {
    for (int i = 0; i < MAXSIZE; i++) {
      array[i] = 0;
    }
  }

  T &operator[](int i);
  void Sort();

private:
  T array[MAXSIZE];
};

template <class T> T &Array<T>::operator[](int i) {
  if (i < 0 || i > MAXSIZE - 1) {
    cout << "数组下标越界！" << endl;
    exit(0);
  }
  return array[i];
}

template <class T> void Array<T>::Sort() {
  int p, j;
  for (int i = 0; i < MAXSIZE - 1; i++) {
    p = i;
    for (j = i + 1; j < MAXSIZE; j++) {
      if (array[p] < array[j])
        p = j;
    }
    T t;
    t = array[i];
    array[i] = array[p];
    array[p] = t;
  }
}
template <> void Array<char *>::Sort() {
  int p, j;
  for (int i = 0; i < MAXSIZE - 1; i++) {
    p = i;
    for (j = i + 1; j < MAXSIZE; j++) {
      if (strcmp(array[p], array[j]) < 0)
        p = j;
    }
    char *t = array[i];
    array[i] = array[p];
    array[p] = t;
  }
}

class A{
public:
    int a;
    A(int a = 5):a(a){
        std::cout << "A(int a = 5):a = " << a << std::endl;
    }
};

class B:A{
public:
    int b;
    B(int b = 5):b(b){
        std::cout << "B(int b = 5):b = " << b << std::endl; 
    }
};


#include <iostream>
using namespace std;

// 快速排序
void quick_sort(int arr[], int left, int right) {
    if (left >= right) return;
    
    int pivot = arr[left];  // 基准值
    int i = left + 1, j = right;
    
        while (i <= j) {
        while (i <= j && arr[i] < pivot) i++;
        while (i <= j && arr[j] > pivot) j--;
        
        if (i < j) swap(arr[i++], arr[j--]);
    }
    swap(arr[left], arr[j]);
    
    quick_sort(arr, left, j - 1);
    quick_sort(arr, j + 1, right);
}

int main() {
    int arr[] = {4, 5, 1, 3, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    quick_sort(arr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    std::cout << (15*127 + 8)/16 << endl;
    std::cout << (16*127 + 8)/16 << endl;
    
    /* quick sort */
    Array<int> a1;
    Array<char *> b1;
    a1[0] = 1;
    a1[1] = 23;
    a1[2] = 6;
    a1[3] = 3;
    a1[4] = 9;
    a1.Sort();
    for (int i = 0; i < 5; i++)
    
    cout << a1[i] << "\t";
    cout << endl;
    b1[0] = "x1";
    b1[1] = "ya";
    b1[2] = "ad";
    b1[3] = "be";
    b1[4] = "bc";
    b1.Sort();
    for (int i = 0; i < 5; i++)
    cout << b1[i] << "\t";
    cout << endl;
}

/* int main()
{
    B bb(4);
    bb.b = 10;
    std::cout << bb.b << std::endl;
} */

/* int main(int argc, char const *argv[]) {
  Array<int> a1;
  Array<char *> b1;
  a1[0] = 1;
  a1[1] = 23;
  a1[2] = 6;
  a1[3] = 3;
  a1[4] = 9;
  a1.Sort();
  for (int i = 0; i < 5; i++)
    cout << a1[i] << "\t";
  cout << endl;
  b1[0] = "x1";
  b1[1] = "ya";
  b1[2] = "ad";
  b1[3] = "be";
  b1[4] = "bc";
  b1.Sort();
  for (int i = 0; i < 5; i++)
    cout << b1[i] << "\t";
  cout << endl;
  
  return 0;
} */

/* int main() {
    BinaryTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(8);
    tree.insert(2);
    tree.insert(4);

    std::cout << "Inorder traversal of binary tree: ";
    tree.printInorder();
    std::cout << std::endl;

    return 0;
} */

/* int main() {
    Stack<int> s(10);
    s.push(1);
    s.push(2);
    s.push(3);
    std::cout << "Stack size: " << s.size() << std::endl;
    std::cout << "Stack top element: " << s.top() << std::endl;
    s.pop();
    std::cout << "Stack top element after pop: " << s.top() << std::endl;
    return 0;
} */