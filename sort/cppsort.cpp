#include <iostream>
#include <vector>

// n^2
void InsertionSort(std::vector<int>& target_list) {
    for (size_t i = 0; i < target_list.size(); ++i) {
        // 현재 정렬하고자 하는 원소를 key
        int key = target_list[i];
        int j = i - 1;

        // target_list[0..i-1]의 요소들 중 key보다 큰 요소들을 한 칸씩 뒤로 이동
        while (j >= 0 && key < target_list[j]) {
            target_list[j + 1] = target_list[j];
            --j;
        }

        // 맞는 위치에 key 삽입
        target_list[j + 1] = key;
    }
}

// n^2
void SelectionSort(std::vector<int>& target_list) {
    for (size_t i = 0; i < target_list.size(); ++i) {
        int minval = target_list[i];
        size_t index = i;
        // 현재 index기준 뒤에 있는 원소중 min 값 찾기
        for (size_t j = i; j < target_list.size(); ++j) {
            if (minval > target_list[j]) {
                minval = target_list[j];
                index = j;
            }
        }
        // 그 min 값을 현재 index로 바꾸기
        target_list[index] = target_list[i];
        target_list[i] = minval;
    }
}

void Merge(std::vector<int>& target_list, int first, int mid, int last) {
    // left sublist랑 right sublist는 정렬이 이미 되어있는 상태임 recursion에 의해
    std::vector<int> left_sublist(target_list.begin() + first, target_list.begin() + mid + 1);
    std::vector<int> right_sublist(target_list.begin() + mid + 1, target_list.begin() + last + 1);

    size_t left_index = 0;
    size_t right_index = 0;
    int sorted_index = first;

    // left sublist와 right sublist 중 작은 원소를 앞에다 쓰면서 target_list를 정렬
    while (left_index < left_sublist.size() && right_index < right_sublist.size()) {
        if (left_sublist[left_index] <= right_sublist[right_index]) {
            target_list[sorted_index] = left_sublist[left_index];
            ++left_index;
        } else {
            target_list[sorted_index] = right_sublist[right_index];
            ++right_index;
        }
        ++sorted_index;
    }

    // left 와 right 중 어느 sublist가 먼저 다 target_list안에 들어갔을 때, 남은 sublist의 원소들을 target_list에 붙여넣기
    while (left_index < left_sublist.size()) {
        target_list[sorted_index] = left_sublist[left_index];
        ++left_index;
        ++sorted_index;
    }

    while (right_index < right_sublist.size()) {
        target_list[sorted_index] = right_sublist[right_index];
        ++right_index;
        ++sorted_index;
    }
}

void MergeSortHelp(std::vector<int>& target_list, int first, int last) {
    if (first == last) {
        return;
    } else {
        int mid = first + (last - first) / 2;
        MergeSortHelp(target_list, first, mid);
        MergeSortHelp(target_list, mid + 1, last);
        Merge(target_list, first, mid, last);
    }
}

// nlogn
void MergeSort(std::vector<int>& target_list) {
    MergeSortHelp(target_list, 0, target_list.size() - 1);
}

void heapify(std::vector<int>& target_list, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // 더 큰 수가 자식 node에 있는지 확인
    if (left < n && target_list[left] > target_list[largest]) {
        largest = left;
    }

    if (right < n && target_list[right] > target_list[largest]) {
        largest = right;
    }

    // 자식 node 에 더 큰 수가 있을 경우 자식 node와 부모 node의 자리를 바꿈, 그리고 재귀적으로 heap 조정
    if (largest != i) {
        std::swap(target_list[i], target_list[largest]);
        heapify(target_list, n, largest);
    }
}

void HeapSort(std::vector<int>& target_list) {
    int n = target_list.size();

    // heap 만들어주기
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(target_list, n, i);
    }

    // 하나씩 추출해서 target_list정렬
    for (int i = n - 1; i > 0; --i) {
        std::swap(target_list[i], target_list[0]);
        // heap 다시 만족시켜 주기
        heapify(target_list, i, 0);
    }
}

int main() {
    std::vector<int> target_list = {10, 20, 5, 7, 22, 9, 12, 8};
    MergeSort(target_list);

    for (int num : target_list) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}