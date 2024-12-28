#include <cstdlib>
#include <iostream>
#include <algorithm>

class Sort
{
public:
    Sort(int* a, int n) : data(a), size(n), front(0), back(n - 1) {}

    ~Sort() = default;

    void sort()
    {
        quickSort(front, back);
    }

    int get(int i) const
    {
        if (data) {
            return data[i];
        } else {
            return -1;
        }
    }

private:
    int partition(int front, int back)
    {
        int pivot = data[back], index = front - 1;

        for (size_t i = front; i <= back - 1; i++) {
            if (data[i] < pivot) {
                index++;
                std::swap(data[index], data[i]);
            }
        }
        std::swap(data[index + 1], data[back]);

        return (index + 1);
    }

    void quickSort(int front, int back)
    {
        if (front < back) {
            int pi = partition(front, back);

            quickSort(front, pi - 1);
            quickSort(pi + 1, back);
        }
    }

protected:
    int *data;
    int size, front, back;
};

class ExSort : public Sort
{
public:
    ExSort(int a[], int n) : Sort(a, n) {}

    ~ExSort() = default;

    void exsort(int order)
    {
        if (order == 1) {
            quickSortReverse(front, back);
        } else {
            this->sort();
        }
    }

private:
    int partitionReverse(int front, int back)
    {
        int pivot = data[back], index = front - 1;

        for (size_t i = front; i <= back - 1; i++) {
            if (data[i] > pivot) {
                index++;
                std::swap(data[index], data[i]);
            }
        }
        std::swap(data[index + 1], data[back]);

        return (index + 1);
    }

    void quickSortReverse(int front, int back)
    {
        if (front < back) {
            int pi = partitionReverse(front, back);

            quickSortReverse(front, pi - 1);
            quickSortReverse(pi + 1, back);
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
