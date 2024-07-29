# n^2
def InsertionSort(target_list):
    for i in range(len(target_list)):
        #현재 정렬하고자 하는 원소를 key
        key = target_list[i]
        j = i -1

        # target_list[0..i-1]의 요소들 중 key보다 큰 요소들을 한 칸씩 뒤로 이동
        while j >=0 and key < target_list[j] :
            target_list[j + 1] = target_list[j]
            j -= 1
        
        #맞는 위치에 key 삽입
        target_list[j + 1] = key

# n^2
def SelectionSort(target_list):
    for i in range(len(target_list)):
        minval = target_list[i]
        index = i
        # 현재 index기준 뒤에 있는 원소중 min 값 찾기
        for j in range(i, len(target_list)):
            if minval > target_list[j] :
                minval = target_list[j]
                index = j
        # 그 min 값을 현재 index로 바꾸기
        target_list[index] = target_list[i]
        target_list[i] = minval

# nlogn
def MergeSort(target_list):
    MergeSortHelp(target_list, 0, len(target_list) - 1)

def MergeSortHelp(target_list, first, last):
    if first == last:
        return
    else:
        mid = first + (last - first) // 2
        MergeSortHelp(target_list, first, mid)
        MergeSortHelp(target_list, mid + 1, last)
        Merge(target_list, first, mid, last)

def Merge(target_list, first, mid, last):
    #left sublist랑 right sublist는 정렬이 이미 되어있는 상태임 recursion에 의해
    left_sublist = target_list[first:mid + 1]
    right_sublist = target_list[mid + 1:last + 1]

    left_index = 0
    right_index = 0
    sorted_index = first

    # left sublist와 right sublist 중 작은 원소를 앞에다 쓰면서 target_list를 정렬
    while left_index < len(left_sublist) and right_index < len(right_sublist):
        if left_sublist[left_index] <= right_sublist[right_index]:
            target_list[sorted_index] = left_sublist[left_index]
            left_index += 1
        else:
            target_list[sorted_index] = right_sublist[right_index]
            right_index += 1
        sorted_index += 1
    
    # left 와 right 중 어느 sublist가 먼저 다 target_list안에 들어갔을 때, 남은 sublist의 원소들을 target_list에 붙여넣기
    while left_index < len(left_sublist):
        target_list[sorted_index] = left_sublist[left_index]
        left_index += 1
        sorted_index += 1

    while right_index < len(right_sublist):
        target_list[sorted_index] = right_sublist[right_index]
        right_index += 1
        sorted_index += 1

def heapify(target_list, n, i):
    largest = i
    left = 2 * i + 1
    right = 2 * i + 2
    
    # 더 큰 수가 자식 node에 있는지 확인
    if left < n and target_list[left] > target_list[largest]:
        largest = left

    if right < n and target_list[right] > target_list[largest]:
        largest = right

    # 자식 node 에 더 큰 수가 있을 경우 자식 node와 부모 node의 자리를 바꿈, 그리고 재귀적으로 heap 조정
    if largest != i:
        target_list[i], target_list[largest] = target_list[largest], target_list[i]
        heapify(target_list, n, largest)

def HeapSort(target_list):
    n = len(target_list)

    # heap 만들어주기
    for i in range(n // 2 - 1, -1, -1):
        heapify(target_list, n, i)
    
    # 하나씩 추출해서 target_list정렬
    for i in range(n - 1, 0, -1):
        target_list[i], target_list[0] = target_list[0], target_list[i]
        # heap 다시 만족시켜 주기
        heapify(target_list, i, 0)


target_list = [10, 20, 5, 7, 22, 9, 12, 8, 77]
HeapSort(target_list)
print(target_list)