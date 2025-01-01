#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

class Sort
{
protected:
    std::vector<int> data;

public:
    Sort(int arr[], int n) : data(arr, arr + n) {}

    // 默认升序排序
    virtual void sort(bool reverse = false)
    {
        introsort(data.begin(), data.end(), 2 * log2(data.size()), reverse);
    }

    int get(int index) const
    {
        if (index >= 0 && index < data.size()) {
            return data[index];
        }
        throw std::out_of_range("Index out of range");
    }

    virtual ~Sort() = default;

protected:
    template <typename RandomIt>
    void introsort(RandomIt first, RandomIt last, int depth_limit, bool reverse)
    {
        while (last - first > 16) {
            if (depth_limit == 0) {
                heapsort(first, last, reverse);  // 超过递归深度限制时使用堆排序
                return;
            }
            --depth_limit;
            RandomIt pivot = median_of_three(first, first + (last - first) / 2, last - 1, reverse);
            pivot = partition(first, last, *pivot, reverse);
            if (pivot - first < last - pivot) {  // 优先排序较小的区间
                introsort(first, pivot, depth_limit, reverse);
                first = pivot + 1;
            } else {
                introsort(pivot + 1, last, depth_limit, reverse);
                last = pivot;
            }
        }
        insertion_sort(first, last, reverse);  // 小区间使用插入排序
    }

    // 插入排序
    template <typename RandomIt>
    void insertion_sort(RandomIt first, RandomIt last, bool reverse)
    {
        for (RandomIt i = first + 1; i < last; ++i) {
            auto key = *i;
            RandomIt pos = i;
            while (pos > first && (reverse ? *(pos - 1) < key : *(pos - 1) > key)) {
                *pos = *(pos - 1);
                --pos;
            }
            *pos = key;
        }
    }

    // 堆排序实现
    template <typename RandomIt>
    void heapify(RandomIt first, RandomIt last, RandomIt root, bool reverse)
    {
        auto cmp =
            reverse ? [](int a, int b) { return a < b; } : [](int a, int b) { return a > b; };
        while (true) {
            RandomIt largest = root;
            RandomIt left = first + 2 * (root - first) + 1;
            RandomIt right = first + 2 * (root - first) + 2;

            if (left < last && cmp(*largest, *left)) {
                largest = left;
            }
            if (right < last && cmp(*largest, *right)) {
                largest = right;
            }
            if (largest != root) {
                std::swap(*root, *largest);
                root = largest;
            } else {
                break;
            }
        }
    }

    template <typename RandomIt>
    void heapsort(RandomIt first, RandomIt last, bool reverse)
    {
        for (RandomIt i = first + (last - first) / 2 - 1; i >= first; --i) {
            heapify(first, last, i, reverse);
        }
        for (RandomIt i = last - 1; i > first; --i) {
            std::swap(*first, *i);
            heapify(first, i, first, reverse);
        }
    }

    // 快速排序分区操作
    template <typename RandomIt, typename T>
    RandomIt partition(RandomIt first, RandomIt last, T pivot, bool reverse)
    {
        RandomIt left = first;
        RandomIt right = last - 1;
        while (true) {
            if (reverse) {
                while (*left > pivot) ++left;
                while (*right < pivot) --right;
            } else {
                while (*left < pivot) ++left;
                while (*right > pivot) --right;
            }
            if (left >= right) return right;
            std::swap(*left, *right);
            ++left;
            --right;
        }
    }

    // 三点中值法选择枢轴
    template <typename RandomIt>
    RandomIt median_of_three(RandomIt a, RandomIt b, RandomIt c, bool reverse)
    {
        if (reverse) {
            if (*a > *b) {
                if (*b > *c)
                    return b;
                else if (*a > *c)
                    return c;
                else
                    return a;
            } else {
                if (*a > *c)
                    return a;
                else if (*b > *c)
                    return c;
                else
                    return b;
            }
        } else {
            if (*a < *b) {
                if (*b < *c)
                    return b;
                else if (*a < *c)
                    return c;
                else
                    return a;
            } else {
                if (*a < *c)
                    return a;
                else if (*b < *c)
                    return c;
                else
                    return b;
            }
        }
    }
};

class ExSort : public Sort
{
public:
    ExSort(int arr[], int n) : Sort(arr, n) {}

    virtual ~ExSort() = default;

    void exsort(int order)
    {
        if (order == 0) {  // 升序排序
            sort(false);
        } else {         // 降序排序
            sort(true);  // 使用父类提供的内省排序算法，控制排序方向
        }
    }
};

// DO NOT modify any parts below this line

void disp(Sort *s, int partial, int n)
{
    if (partial == 0) {
        for (int i = 0; i < n; i++) {
            std::cout << s->get(i) << " ";
        }
        std::cout << std::endl;
    } else {
        int nprint = n;
        if (nprint > 20) nprint = 20;
        for (int i = 0; i < nprint; i++) {
            std::cout << s->get(rand() % (n)) << " ";
        }
        std::cout << std::endl;
    }
}

// 以下程序会自动产生随机数组list，自动将list输入Sort对象和ExSort对象，
// 并调用排序函数进行排序，以及进行打印，不需要进行更改
int main(int argc, char **argv)
{
    int *list;
    int n = std::stoi(argv[1]);
    int partial_disp = std::stoi(argv[2]);
    int seed = std::stoi(argv[3]);
    srand(seed);

    list = new int[n];
    for (int i = 0; i < n; i++) {
        list[i] = rand() % (n * 20);
    }

    // 开始
    Sort s0(list, n);  // 初始化
    disp(&s0, partial_disp, n);
    s0.sort();  // 排序（升序）
    disp(&s0, partial_disp, n);

    ExSort s1(list, n);  // 初始化
    disp(&s1, partial_disp, n);
    s1.exsort(1);  // 降序排序
    disp(&s1, partial_disp, n);

    delete[] list;

    return 0;
}
