//10. (**) Реалізувати алгоритм сортування heap sort
//20. (***) Реалізувати алгоритм сортування block merge sort

#include <iostream>
#include <vector>
#include <thread>
#include <stdexcept>
#include <ctime>

using namespace std;
using namespace chrono;

void loadingAnimation() {
    for (int i = 0; i < 3; ++i) {
        cout << "Loading.";
        cout.flush();
        this_thread::sleep_for(milliseconds(250));
        cout << "\r";

        cout << "Loading..";
        cout.flush();
        this_thread::sleep_for(milliseconds(250));
        cout << "\r";

        cout << "Loading...";
        cout.flush();
        this_thread::sleep_for(milliseconds(250));
        cout << "\r";
    }
}

int getIntInput(const string& prompt, int minValue, int maxValue) {
    int value;
    bool inputIsValid;
    do {
        cout << prompt;
        if (cin >> value && value >= minValue && value <= maxValue) {
            inputIsValid = true;
        } else {
            cerr << "\n### Invalid input. Please enter a valid integer between "
                 << minValue << " and " << maxValue << ". ###\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            inputIsValid = false;
        }
    } while (!inputIsValid);
    return value;
}

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[i], arr[largest]);

        heapify(arr, n, largest);
    }
}


void heapSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);

        heapify(arr, i, 0);

    }
}



void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }


    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void blockMergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        blockMergeSort(arr, l, m);
        blockMergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}


vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    srand(time(nullptr));

    for (int i = 0; i < size; ++i)
        arr[i] = rand() % 100;

    return arr;
}

void printArray(vector<int>& arr) {
    for (int i = 0; i < arr.size(); ++i)
        cout << arr[i] << " ";
    cout << endl;
}

void DemonstrationMode();
void BenchmarkMode();

int main() {

    srand(time(nullptr));
    int mode;
    mode = getIntInput("Select mode:\n"
                       "1. Demonstration mode \n"
                       "2. Benchmark mode:\n", 1, 2);
    switch (mode) {
        case 1:
            DemonstrationMode();
            break;
        case 2:
            BenchmarkMode();
            break;
    }
    return 0;
}

void DemonstrationMode() {

    cout << "\n**** DEMONSTRATION MODE *****\n";
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;


    cout << "\n\n@@@@@ INSERTING "<< size << " RANDOM ELEMENTS FROM 1 TO 100 @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    vector<int> arr = generateRandomArray(size), arrTemp;
    arrTemp = arr;
    cout << "Created array: ";
    printArray(arrTemp);


    cout << "\n\n@@@@@ HEAP SORTING ALGORITHM @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    heapSort(arrTemp);
    cout << "Sorted array: ";
    printArray(arrTemp);
    arrTemp = arr;


    cout << "\n\n@@@@@ BLOCK MERGE SORTING ALGORITHM @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    blockMergeSort(arrTemp, 0, arrTemp.size() - 1);
    cout << "Sorted array: ";
    printArray(arrTemp);


    cout << "\n\n@@@@@ EXIT @@@@@\n\n";
}


void BenchmarkMode() {
    cout << "\nYou are now in the benchmark mode, time of each operation will be written afterwards\n";

    vector<int> arr = generateRandomArray(10), arrTemp;
    arrTemp = arr;
    cout << "Created array: ";
    printArray(arrTemp);

    auto startTimeHeapSort = high_resolution_clock::now();
    heapSort(arrTemp);
    auto endTimeHeapSort = high_resolution_clock::now();
    arrTemp = arr;



    auto startTimeBlockMergeSort = high_resolution_clock::now();
    blockMergeSort(arrTemp, 0, arrTemp.size() - 1);
    auto endTimeBlockMergeSort = high_resolution_clock::now();
    arrTemp = arr;



    auto startTimeSort = high_resolution_clock::now();
    sort(arrTemp.begin(), arrTemp.end());
    auto endTimeSort = high_resolution_clock::now();
    arrTemp = arr;



    auto startTimeInPlaceSort = high_resolution_clock::now();
    inplace_merge(arrTemp.begin(), arrTemp.begin() + 5, arrTemp.end());
    auto endTimeInPlaceSort = high_resolution_clock::now();
    arrTemp = arr;



    auto startTimeStableSort = high_resolution_clock::now();
    stable_sort(arrTemp.begin(), arrTemp.end());
    auto endTimeStableSort = high_resolution_clock::now();
    arrTemp = arr;



    auto durationHeapSort = duration_cast<duration<double, nano>>(endTimeHeapSort - startTimeHeapSort).count();
    auto durationBlockMergeSort = duration_cast<duration<double, nano>>(endTimeBlockMergeSort - startTimeBlockMergeSort).count();
    auto durationSort = duration_cast<duration<double, nano>>(endTimeSort - startTimeSort).count();
    auto durationInPlaceSort = duration_cast<duration<double, nano>>(endTimeInPlaceSort - startTimeInPlaceSort).count();
    auto durationStableSort = duration_cast<duration<double, nano>>(endTimeStableSort - startTimeStableSort).count();

    cout << "---------------------------------------------------" << endl;
    cout << "\nTime heap sort: " << durationHeapSort << " nanoseconds\n" <<
         "\nTime block merge sort: " << durationBlockMergeSort << " nanoseconds\n" <<
         "\nTime std::sort(): " << durationSort << " nanoseconds\n" <<
         "\nTime std::inplace_merge(): " << durationInPlaceSort << " nanoseconds\n" <<
         "\nTime std::stable_sort(): " << durationStableSort << " nanoseconds\n\n\n";

    cout << "\n\n    BENCHMARK IS ENDED UP WITH THE ABOVE-MENTIONED RESULTS    \n";
}