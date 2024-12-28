#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>

class Sort {
protected:
    std::vector<int> data;

public:
    Sort(int arr[], int n) : data(arr, arr + n) {}

    virtual void sort() {
        introsort(data.begin(), data.end(), 2 * log2(data.size()));
    }

    int get(int index) const {
        if(index >=0 && index < data.size()) {
            return data.at(index);
        }
        throw std::out_of_range("Index out of range");
    }

    virtual ~Sort() = default;

private:
    template <typename RandomIt>
    void introsort(RandomIt first, RandomIt last, int depth_limit) {
        if (last - first <= 16) {
            insertion_sort(first, last); // 小区间使用插入排序
            return;
        }
        if (depth_limit == 0) {
            heapsort(first, last); // 超过递归深度限制时使用堆排序
            return;
        }
        RandomIt pivot = partition(first, last); // 快速排序的分区操作
        introsort(first, pivot, depth_limit - 1); // 递归排序左半部分
        introsort(pivot + 1, last, depth_limit - 1); // 递归排序右半部分
    }

    // 插入排序实现
    template <typename RandomIt>
    void insertion_sort(RandomIt first, RandomIt last) {
        for (RandomIt i = first + 1; i < last; ++i) {
            auto key = *i;
            RandomIt j = i - 1;
            while (j >= first && *j > key) {
                *(j + 1) = *j;
                --j;
            }
            *(j + 1) = key;
        }
    }

    // 堆排序实现
    template <typename RandomIt>
    void heapsort(RandomIt first, RandomIt last) {
        std::make_heap(first, last);
        std::sort_heap(first, last);
    }

    // 快速排序分区操作
    template <typename RandomIt>
    RandomIt partition(RandomIt first, RandomIt last) {
        auto pivot = *(first + (last - first) / 2); // 选取中间元素为枢轴
        RandomIt i = first - 1;
        RandomIt j = last;
        while (true) {
            do { ++i; } while (*i < pivot);
            do { --j; } while (*j > pivot);
            if (i >= j) return j;
            std::iter_swap(i, j);
        }
    }

};

class ExSort : public Sort {
public:
    ExSort(int arr[], int n) : Sort(arr, n) {}

    void exsort(int order) {
        if (order == 1) {
            std::sort(data.begin(), data.end(), std::greater<int>()); // 降序排序
        } else {
            std::sort(data.begin(), data.end()); // 升序排序
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
