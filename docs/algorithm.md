# algorithm

map方法

## sort

- bubble sort(冒泡排序)
- selection sort(选择排序)
- insertion sort(插入排序)
- merge sort(归并排序)
### quick sort(快速排序)
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
    return 0;
}
在这个实现中，我们首先选择数组的第一个元素作为基准值。然后通过两个指针 i 和 j 分别从数组的两端向中间扫描，将小于基准值的元素放到左边，大于基准值的元素放到右边。

当 i 和 j 相遇时，将基准值和 arr[j] 进行交换，使得基准值左侧的元素都小于基准值，右侧的元素都大于等于基准值。然后将数组分成两部分，对左右两部分分别进行递归排序。

快速排序的时间复杂度为O(nlogn)，空间复杂度为O(logn)。

- heap sort(堆排序)
- bucket sort(桶排序)
- radix sort(基数排序)
- counting sort(计数排序)

## search

- linear search(线性搜索)
- binary search(二分搜索)
- jump search(跳跃搜索)
- interpolation search(插值搜索)
- exponential search(指数搜索)
- fibonacci search(斐波那契搜索)
- ternary search(三路搜索)
- binary search tree(二叉搜索树)
- red-black tree(红黑树)
- splay tree(splay树)
- avl tree(平衡树)
- b-tree(B树)
- r-tree(R树)
- s-tree(S树)
- t-tree(T树)
- 2-3 tree(2-3树)

## rsa

RSA（Rivest-Shamir-Adleman）是一种非对称加密算法，它可以用于加密和解密数据以及生成数字签名。

RSA算法的关键是基于数论中的两个大素数的乘积难以分解为原始素数的因子。这两个素数被称为公钥和私钥。公钥用于加密数据，私钥用于解密数据。数字签名是通过使用私钥对数据进行加密来生成的，然后可以使用公钥来验证签名的有效性。

RSA算法的工作原理如下：

1. 选择两个大素数p和q，并计算它们的乘积n（n = p * q）。

2. 计算φ(n) = (p - 1) * (q - 1)，其中φ(n)是n的欧拉函数。

3. 选择一个整数e， 1 < e < φ(n)，且e与φ(n)互质。

4. 计算e关于φ(n)的模反元素d，即计算满足 (d * e) % φ(n) = 1 的整数d。

5. 公钥是(n, e)，私钥是(n, d)。

加密算法：
将要加密的数据转换为整数m，满足 0 ≤ m < n。
计算 c = (m^e) % n，c是加密后的数据。

解密算法：
将加密后的数据c计算为明文m，满足 0 ≤ m < n。
计算 m = (c^d) % n，m是解密后的数据。

通过使用RSA算法，可以实现安全的加密通信、数字签名和身份验证等功能。然而，由于RSA算法的加密和解密速度相对较慢，因此通常不会直接用于加密大量数据，而是与对称加密算法结合使用，以提高性能和安全性。

## cmac

## aes

