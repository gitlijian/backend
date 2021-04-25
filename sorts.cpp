#include <iostream>
#include <vector>
#include <map>
using namespace std;
// 1.bubble sort
void bubbleSort(vector<int> &v)
{

    for (int i = 0; i < v.size() - 1; i++)
    {
        for (int j = 0; j < v.size() - i - 1; j++)
        {
            if (v[j] > v[j + 1])
            {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// 2.selection sort
void selectionSort(vector<int> &v)
{
    int minIndex = 0;
    for (int i = 0; i < v.size() - 1; i++)
    {
        minIndex = i;
        for (int j = i + 1; j < v.size(); j++)
        {
            if (v[minIndex] > v[j])
                minIndex = j;
        }
        int temp = v[i];
        v[i] = v[minIndex];
        v[minIndex] = temp;
    }
}

// 3.insertion sort
void insertionSort(vector<int> &v)
{
    int current = v[1], preIndex = 0;
    for (int i = 1; i < v.size(); i++)
    {
        current = v[i]; // 該位置的值被保存在一個中間變量中 不需要再用一個哨兵位
        preIndex = i - 1;
        while (preIndex >= 0 && v[preIndex] > current)
        {
            v[preIndex + 1] = v[preIndex];
            preIndex--;
        }
        v[preIndex + 1] = current;
    }
}

// 4.shell sort
void shellSort(vector<int> &v)
{
    int len = v.size();
    for (int gap = len / 2; gap > 0; gap = gap / 2)
    {
        for (int i = gap; i < len; i++)
        {
            int j = i;
            int current = v[i];
            while (j - gap >= 0 && current < v[j - gap])
            {
                v[j] = v[j - gap];
                j = j - gap;
            }
            v[j] = current;
        }
    }
}

// 5.merge sort
vector<int> tempArr(10);
void merge(vector<int> &v, int low, int mid, int high)
{
    for (int k = low; k <= high; k++)
    {
        tempArr[k] = v[k];
    }
    int i = 0, j = 0, k = 0;
    for (i = low, j = mid + 1, k = low; i <= mid && j <= high; k++)
    {
        if (tempArr[i] < tempArr[j])
        {
            v[k] = tempArr[i++];
        }
        else
        {
            v[k] = tempArr[j++];
        }
    }
    while (i <= mid)
        v[k++] = tempArr[i++];
    while (j <= high)
        v[k++] = tempArr[j++];
}

void mergeSort(vector<int> &v, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(v, low, mid);
        mergeSort(v, mid + 1, high);
        merge(v, low, mid, high);
    }
}

// 6.quick sort
int partition(vector<int> &v, int low, int high)
{
    int pivot = v[low];
    while (low < high)
    {
        while (low < high && pivot <= v[high])
            high--;
        v[low] = v[high];
        while (low < high && pivot >= v[low])
            low++;
        v[high] = v[low];
    }
    v[low] = pivot;
    return low;
}

void quicksort(vector<int> &v, int low, int high)
{
    if (low < high)
    {
        int pivotpos = partition(v, low, high);
        quicksort(v, low, pivotpos - 1);
        quicksort(v, pivotpos + 1, high);
    }
}

// 7.heap sort
namespace hs
{
    int len;
    void heapify(vector<int> &v, int i);
    void swap1(vector<int> &v, int i, int j);
    void buildMaxHeap(vector<int> &v)
    {
        len = v.size();
        for (int i = (len / 2); i >= 0; i--)
        {
            heapify(v, i);
        }
    }

    void heapify(vector<int> &v, int i)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < len && v[left] > v[largest])
        {
            largest = left;
        }
        if (right < len && v[right] > v[largest])
        {
            largest = right;
        }

        if (i != largest)
        {
            swap1(v, i, largest);
            heapify(v, largest);
        }
    }

    void swap1(vector<int> &v, int i, int j)
    {
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }

    void heapsort(vector<int> &v)
    {
        buildMaxHeap(v);

        for (int i = v.size() - 1; i > 0; i--)
        {
            swap1(v, 0, i);
            len--;
            heapify(v, 0);
        }
    }
};

// 8.counting sort
void countingSort(vector<int> &v)
{
    map<int, int> m;
    for (int num : v)
    {
        m[num]++;
    }
    int i = 0;
    for (map<int, int>::iterator iter = m.begin(); iter != m.end(); iter++)
    {
        while (iter->second--)
        {
            v[i++] = iter->first;
        }
    }
}

// 9.radix sort
int maxbit(vector<int> &data, int n) // 辅助函数，求数据的最大位数
{
    int maxData = data[0];
    // 先求出最大数，再求其位数
    for (int i = 1; i < n; ++i)
    {
        if (maxData < data[i])
            maxData = data[i];
    }
    int d = 1;
    while (maxData)
    {
        maxData /= 10;
        ++d;
    }
    return d;
}

void radixsort(vector<int> &data, int n)
{
    int d = maxbit(data, n);
    int *tmp = new int[n];
    int *count = new int[10]; // 计数器
    int i, j, k;
    int radix = 1;
    for (i = 1; i <= d; i++) // 进行d次排序
    {
        for (j = 0; j < 10; j++)
            count[j] = 0; // 每次分配前清空计数器
        for (j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; // 统计每个桶中的记录数
            count[k]++;
        }
        for (j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; // 将tmp中的位置一次分配给每个桶
        for (j = n - 1; j >= 0; j--)            // 将所有桶中记录一次收集到tmp中
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for (j = 0; j < n; j++) // 将临时数组的内容复制到data中
            data[j] = tmp[j];
        radix = radix * 10;
    }
    delete[] tmp;
    delete[] count;
}

// 10.bucket sort
const int BUCKET_NUM = 10;

struct ListNode
{
    explicit ListNode(int i = 0) : mData(i), mNext(NULL) {}
    ListNode *mNext;
    int mData;
};

ListNode *insert(ListNode *head, int val)
{
    ListNode dummyNode;
    ListNode *newNode = new ListNode(val);
    ListNode *pre, *curr;
    dummyNode.mNext = head;
    pre = &dummyNode;
    curr = head;
    while (NULL != curr && curr->mData <= val)
    {
        pre = curr;
        curr = curr->mNext;
    }
    newNode->mNext = curr;
    pre->mNext = newNode;
    return dummyNode.mNext;
}

ListNode *Merge(ListNode *head1, ListNode *head2)
{
    ListNode dummyNode;
    ListNode *dummy = &dummyNode;
    while (NULL != head1 && NULL != head2)
    {
        if (head1->mData <= head2->mData)
        {
            dummy->mNext = head1;
            head1 = head1->mNext;
        }
        else
        {
            dummy->mNext = head2;
            head2 = head2->mNext;
        }
        dummy = dummy->mNext;
    }
    if (NULL != head1)
        dummy->mNext = head1;
    if (NULL != head2)
        dummy->mNext = head2;

    return dummyNode.mNext;
}

void BucketSort(int n, vector<int>& arr)
{
    vector<ListNode *> buckets(BUCKET_NUM, (ListNode *)(0));
    for (int i = 0; i < n; ++i)
    {
        int index = arr[i] / BUCKET_NUM;
        ListNode *head = buckets.at(index);
        buckets.at(index) = insert(head, arr[i]);
    }
    ListNode *head = buckets.at(0);
    for (int i = 1; i < BUCKET_NUM; ++i)
    {
        head = Merge(head, buckets.at(i));
    }
    for (int i = 0; i < n; ++i)
    {
        arr[i] = head->mData;
        head = head->mNext;
    }
}

void print(vector<int> v)
{
    for (auto t : v)
    {
        cout << t << "\t";
    }
    cout << endl;
}

int main()
{
    vector<int> v{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    print(v);
    // bubbleSort(v);
    // selectionSort(v);
    // insertionSort(v);
    // shellSort(v);
    // mergeSort(v,0, v.size()-1);
    // countingSort(v);
    // quicksort(v, 0, v.size() - 1);
    // hs::heapsort(v);
    // radixsort(v, v.size());
    BucketSort(v.size(), v);
    print(v);
    return 0;
}