//Реалізувати алгоритми сортування для заданої структури даних
// (список 1) - Дата і час, за зростанням
// Реалізувати наступні алгоритми:
//простий алгоритм (список 2); - Insertion sort
//більш ефективний алгоритм quicksort (список 3); - Lomuto partition scheme, middle index pivot.
//більш ефективний алгоритм merge sort (список 4); - bottom-up
//комбінований алгоритм, який використовує більш ефективний алгоритм (один з quicksort чи merge sort)
// для великих масивів і простий алгоритм для маленький масивів;
//сортування з використанням бібліотечних функцій.
//
//Всі алгоритми мають працювати на однакових масивах.
// Варто розглянути як випадкові масиви, так і майже відсортовані в правильному та неправильному порядку
// (тобто якщо треба відсортувати за зростанням, то розглянути масиви,
// майже відсортовані за зростанням – правильний порядок,
// та за спаданням – неправильний порядок).
//Для комбінованого алгоритму, розглянути різні значення порогу,
// коли переходити від простого до більш ефективного алгоритму – і виміряти час виконання для різних значень порогу,
// а також підібрати оптимальне значення порогу. Алгоритм працює рекурсивно,
// і для маленьких підмасивів переключається на більш простий алгоритм
// (наприклад, якщо поріг=10 елементів, на вхід подається масив з 10000 елементів,
// то спершу використовується більш ефективний алгоритм,
// але на подальших кроках може бути використаний більш простий алгоритм для сортування підмасивів не більше 10 елементів).
//Всі алгоритми мають бути реалізовані у вигляді однієї програми (з однією функцією main).
// Варто не копіювати код, а виносити спільні фрагменти коду в функції та викликати їх.


#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <thread>
#include <array>
#include <vector>
#include <ctime>
#include <cmath>
#include <random>

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

// Struct representing date and time
struct Date {
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;

    // Constructor
    Date(int year = int(), int month = int(), int day = int(), int hour = int(), int minute = int(), int second = int()) {
        this->day = day;
        this->month = month;
        this->year = year;
        this->hour = hour;
        this->minute = minute;
        this->second = second;
    }

    int howManyDaysInMonth(int thisMonth) {
        switch (thisMonth){
            case 1: case 3: case 5: case 7: case 8: case 10: case 12: // for month that has 31 days
                return 31;
            case 4: case 6: case 9: case 11: // for month that has 30 days
                return 30;
            case 2: // check if the year is a leap, it will put 29 or 28 days for the February
                if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
                    return 29;
                } else {
                    return 28;
                }
            default:  // if such month does not exist
                return 0;
        }
    }

    void printDateTime() {
        cout << "Date: " << setfill('0') << setw(2) << day << "-"
                  << setfill('0') << setw(2) << month << "-" << year << " ";
        cout << "Time: " << setw(2) << hour << ":" << setw(2) << minute
                  << ":" << setw(2) << second << endl;
    }


    bool operator<=(const Date& another) const {
        if (year != another.year) return year <= another.year;
        if (month != another.month) return month <= another.month;
        if (day != another.day) return day <= another.day;
        if (hour != another.hour) return hour <= another.hour;
        if (minute != another.minute) return minute <= another.minute;
        return second <= another.second;
    }

    bool operator>(const Date& another) const {
        if (year != another.year) return year > another.year;
        if (month != another.month) return month > another.month;
        if (day != another.day) return day > another.day;
        if (hour != another.hour) return hour > another.hour;
        if (minute != another.minute) return minute > another.minute;
        return second > another.second;
    }

    bool operator<(const Date& another) const {
        if (year != another.year) return year < another.year;
        if (month != another.month) return month < another.month;
        if (day != another.day) return day < another.day;
        if (hour != another.hour) return hour < another.hour;
        if (minute != another.minute) return minute < another.minute;
        return second < another.second;
    }
};

bool isSorted(const vector<Date>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}


// Insertion sort function
void insertionSort(vector<Date>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        Date key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}


void swap(Date& a, Date& b) {
    Date temp = a;
    a = b;
    b = temp;
}

// Lomuto partition scheme with middle index pivot
int partition(vector<Date>& arr, int low, int high) {
    Date pivot = arr[(low + high) / 2]; // Choose middle element as pivot
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j) {
            return j;
        }

        swap(arr[i], arr[j]);
    }
}

// Quicksort algorithm using Lomuto partition scheme with middle index pivot
void quicksort(vector<Date>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi);
        quicksort(arr, pi + 1, high);
    }
}


void merge(vector<Date>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<Date> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

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

void mergeSort(vector<Date>& arr) {
    int n = arr.size();
    for (int currSize = 1; currSize <= n - 1; currSize *= 2) {
        for (int leftStart = 0; leftStart < n - 1; leftStart += 2 * currSize) {
            int mid = min(leftStart + currSize - 1, n - 1);
            int rightEnd = min(leftStart + 2 * currSize - 1, n - 1);
            merge(arr, leftStart, mid, rightEnd);
        }
    }
}




void demonstrationMode();
void benchmarkMode();

int main() {
    srand(time(nullptr));
    int mode;
    mode = getIntInput("Select mode:\n"
                       "1. Demonstration mode \n"
                       "2. Benchmark mode:\n", 1, 2);

    switch (mode) {
        case 1:
            demonstrationMode();
            break;
        case 2:
            benchmarkMode();
            break;
    }
}


int getRandomInt(int min, int max) {
    static default_random_engine generator(time(0));
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

Date generateRandomTime() {
    Date randomTime;
    randomTime.year = getRandomInt(2000, 2024);  // Adjust range as needed
    randomTime.month = getRandomInt(1, 12);
    randomTime.day = getRandomInt(1, randomTime.howManyDaysInMonth(randomTime.month));// Adjust based on the month and year
    randomTime.hour = getRandomInt(0, 23);
    randomTime.minute = getRandomInt(0, 59);
    randomTime.second = getRandomInt(0, 59);
    return randomTime;
}

Date generateNextDate(const Date& currentDate, bool isIncreasing) {
    Date nextDate = currentDate;

    if (isIncreasing) {
        nextDate.day++;
        if (nextDate.day > nextDate.howManyDaysInMonth(nextDate.month)) {
            nextDate.day = 1;
            nextDate.month++;
            if (nextDate.month > 12) {
                nextDate.month = 1;
                nextDate.year++;
            }
        }
    } else {
        nextDate.day--;
        if (nextDate.day == 0) {
            nextDate.month--;
            if (nextDate.month == 0) {
                nextDate.month = 12;
                nextDate.year--;
            }
            nextDate.day = nextDate.howManyDaysInMonth(nextDate.month);
        }
    }

    return nextDate;
}



void demonstrationMode() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int size = 5;
    cout << "\n**** DEMONSTRATION MODE *****\n";


    cout << "\n\n@@@@@ CREATING 3 ARRAYS: RANDOM, INCREASING AND DECREASING @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    vector<Date> randDates, increasingDates, decreasingDates;
    Date startDateIncr = {2024, 01, 01, 00, 00, 00};
    Date startDateDecr = startDateIncr;

    for (int i = 0; i < size; i++) {
        randDates.push_back(generateRandomTime());
        startDateIncr = generateNextDate(startDateIncr, true);
        startDateDecr = generateNextDate(startDateDecr, false);
        increasingDates.push_back(startDateIncr);
        decreasingDates.push_back(startDateDecr);
    }
    cout << "\n**** Arrays successfully created! ****\n";

    vector<Date> tempRandArray, tempIncreasingArray, tempDecreasingArray;
    cout << "Random array:" << endl;
    for (auto& item : randDates) {
        item.printDateTime();
        tempRandArray.push_back(item);
    }

    cout << "Increasing array:" << endl;
    for (auto& item : increasingDates) {
        item.printDateTime();
        tempIncreasingArray.push_back(item);
    }

    cout << "Decreasing array:" << endl;
    for (auto& item : decreasingDates) {
        item.printDateTime();
        tempDecreasingArray.push_back(item);
    }


    cout << "\n\n@@@@@ SORTING USING INSERTION SORT @@@@@\n\n";
    loadingAnimation();
    insertionSort(tempRandArray);
    if (isSorted(tempRandArray)) {
        cout << "\n Rand Array is sorted correctly." << endl;
    } else {
        cout << "\n Rand Array is not sorted correctly." << endl;
    }

    insertionSort(tempIncreasingArray);
    if (isSorted(tempIncreasingArray)) {
        cout << "\nIncreasing Array is sorted correctly." << endl;
    } else {
        cout << "\nIncreasing Array is not sorted correctly." << endl;
    }

    insertionSort(tempDecreasingArray);
    if (isSorted(tempDecreasingArray)) {
        cout << "\nDecreasing Array is sorted correctly." << endl;
    } else {
        cout << "\nDecreasing Array is not sorted correctly." << endl;
    }


    tempRandArray = randDates;
    tempIncreasingArray = increasingDates;
    tempDecreasingArray = decreasingDates;
    cout << "\n\n@@@@@ SORTING USING QUICKSORT(Lomuto partition scheme with middle index pivot) @@@@@\n\n";
    loadingAnimation();
    quicksort(tempRandArray, 0, tempRandArray.size() - 1);
    if (isSorted(tempRandArray)) {
        cout << "\n Rand Array is sorted correctly." << endl;
    } else {
        cout << "\n Rand Array is not sorted correctly." << endl;
    }

    quicksort(tempIncreasingArray, 0, tempIncreasingArray.size() - 1);
    if (isSorted(tempIncreasingArray)) {
        cout << "\nIncreasing Array is sorted correctly." << endl;
    } else {
        cout << "\nIncreasing Array is not sorted correctly." << endl;
    }

    quicksort(tempDecreasingArray, 0, tempDecreasingArray.size() - 1);
    if (isSorted(tempDecreasingArray)) {
        cout << "\nDecreasing Array is sorted correctly." << endl;
    } else {
        cout << "\nDecreasing Array is not sorted correctly." << endl;
    }


    tempRandArray = randDates;
    tempIncreasingArray = increasingDates;
    tempDecreasingArray = decreasingDates;
    cout << "\n\n@@@@@ SORTING USING MERGE SORT(bottom-up) @@@@@\n\n";
    loadingAnimation();
    mergeSort(tempRandArray);
    if (isSorted(tempRandArray)) {
        cout << "\n Rand Array is sorted correctly." << endl;
    } else {
        cout << "\n Rand Array is not sorted correctly." << endl;
    }

    mergeSort(tempIncreasingArray);
    if (isSorted(tempIncreasingArray)) {
        cout << "\nIncreasing Array is sorted correctly." << endl;
    } else {
        cout << "\nIncreasing Array is not sorted correctly." << endl;
    }

    mergeSort(tempDecreasingArray);
    if (isSorted(tempDecreasingArray)) {
        cout << "\nDecreasing Array is sorted correctly." << endl;
    } else {
        cout << "\nDecreasing Array is not sorted correctly." << endl;
    }


    cout << "Random array sorted:" << endl;
    for (auto& item : tempRandArray) {
        item.printDateTime();
    }

    cout << "Increasing array sorted:" << endl;
    for (auto& item : tempIncreasingArray) {
        item.printDateTime();

    }

    cout << "Decreasing array sorted:" << endl;
    for (auto& item : tempDecreasingArray) {
        item.printDateTime();

    }


    cout << "\n\n@@@@@ EXIT @@@@@\n\n";
}

void benchmarkMode() {
    cout << "\nYou are now in the benchmark mode, time of each operation will be written afterwards\n";

    int num = getIntInput("Enter a number of elements for array (from 1 to 1000): ", 1, 1000);

    vector<Date> randDates, increasingDates, decreasingDates;
    Date startDateIncr = {2024, 01, 01, 00, 00, 00};
    Date startDateDecr = startDateIncr;

    for (int i = 0; i < num; i++) {
        randDates.push_back(generateRandomTime());
        startDateIncr = generateNextDate(startDateIncr, true);
        startDateDecr = generateNextDate(startDateDecr, false);
        increasingDates.push_back(startDateIncr);
        decreasingDates.push_back(startDateDecr);
    }

    vector<Date> tempRandArray, tempIncreasingArray, tempDecreasingArray;

    cout << "Random array:" << endl;
    for (auto &item: randDates) {
        item.printDateTime();
    }

    cout << "Increasing array:" << endl;
    for (auto &item: increasingDates) {
        item.printDateTime();
    }

    cout << "Decreasing array:" << endl;
    for (auto &item: decreasingDates) {
        item.printDateTime();
    }

    for (int algthMode = 0; algthMode <= 2; algthMode++) {
        tempRandArray = randDates;
        tempIncreasingArray = increasingDates;
        tempDecreasingArray = decreasingDates;
        if (algthMode == 0) {
            cout << "\n\n@@@@@    START BENCHMARK WITH INSERTION SORT     @@@@@\n";

            auto startTimeInsertionSort = high_resolution_clock::now();

            auto startTimeInsertionSortRand = high_resolution_clock::now();
            insertionSort(tempRandArray);
            auto endTimeInsertionSortRand = high_resolution_clock::now();

            auto startTimeInsertionSortIncr = high_resolution_clock::now();
            insertionSort(tempIncreasingArray);
            auto endTimeInsertionSortIncr = high_resolution_clock::now();
            auto startTimeInsertionSortDecr = high_resolution_clock::now();
            insertionSort(tempDecreasingArray);
            auto endTimeInsertionSortDecr = high_resolution_clock::now();
            auto endTimeInsertionSort = high_resolution_clock::now();

            if (isSorted(tempRandArray)) {
                cout << "\nRand Array is sorted correctly." << endl;
            } else {
                cout << "\nRand Array is not sorted correctly." << endl;
            }

            if (isSorted(tempIncreasingArray)) {
                cout << "\nIncreasing Array is sorted correctly." << endl;
            } else {
                cout << "\nIncreasing Array is not sorted correctly." << endl;
            }

            if (isSorted(tempDecreasingArray)) {
                cout << "\nDecreasing Array is sorted correctly." << endl;
            } else {
                cout << "\nDecreasing Array is not sorted correctly." << endl;
            }

            auto durationTotalInsertionSort = duration_cast<duration<double, milli>>(endTimeInsertionSort - startTimeInsertionSort).count();
            auto durationInsertionSortRand = duration_cast<duration<double, milli>>(endTimeInsertionSortRand - startTimeInsertionSortRand).count();
            auto durationInsertionIncr = duration_cast<duration<double, milli>>(endTimeInsertionSortIncr - startTimeInsertionSortIncr).count();
            auto durationInsertionSortDecr = duration_cast<duration<double, milli>>(endTimeInsertionSortDecr - startTimeInsertionSortDecr).count();

            cout << "\nTime insertion sort: " << durationTotalInsertionSort << " milliseconds\n" <<
                 "\nTime insertion sort for rand numbers: " << durationInsertionSortRand << " milliseconds\n" <<
                 "\nTime insertion sort for increase numbers: " << durationInsertionIncr << " milliseconds\n" <<
                 "\nTime insertion sort for decrease numbers: " << durationInsertionSortDecr << " milliseconds\n\n\n";

        }
        else if (algthMode == 1) {
            cout << "\n\n@@@@@    START BENCHMARK WITH QUICKSORT    @@@@@\n";
            auto startTimeQuickSort = high_resolution_clock::now();

            auto startTimeQuickSortRand = high_resolution_clock::now();
            quicksort(tempRandArray, 0, tempRandArray.size() - 1);
            auto endTimeQuickSortRand = high_resolution_clock::now();

            auto startTimeQuickSortIncr = high_resolution_clock::now();
            quicksort(tempIncreasingArray, 0, tempIncreasingArray.size() - 1);
            auto endTimeQuickSortIncr = high_resolution_clock::now();

            auto startTimeQuickSortDecr = high_resolution_clock::now();
            quicksort(tempDecreasingArray, 0, tempDecreasingArray.size() - 1);
            auto endTimeQuickSortDecr = high_resolution_clock::now();

            auto endTimeQuickSort = high_resolution_clock::now();

            if (isSorted(tempRandArray)) {
                cout << "\nRand Array is sorted correctly." << endl;
            } else {
                cout << "\nRand Array is not sorted correctly." << endl;
            }

            if (isSorted(tempIncreasingArray)) {
                cout << "\nIncreasing Array is sorted correctly." << endl;
            } else {
                cout << "\nIncreasing Array is not sorted correctly." << endl;
            }

            if (isSorted(tempDecreasingArray)) {
                cout << "\nDecreasing Array is sorted correctly." << endl;
            } else {
                cout << "\nDecreasing Array is not sorted correctly." << endl;
            }

            auto durationTotalQuickSort = duration_cast<duration<double, milli>>(endTimeQuickSort - startTimeQuickSort).count();
            auto durationQuickSortRand = duration_cast<duration<double, milli>>(endTimeQuickSortRand - startTimeQuickSortRand).count();
            auto durationQuickIncr = duration_cast<duration<double, milli>>(endTimeQuickSortIncr - startTimeQuickSortIncr).count();
            auto durationQuickSortDecr = duration_cast<duration<double, milli>>(endTimeQuickSortDecr - startTimeQuickSortDecr).count();

            cout << "\nTime quick sort: " << durationTotalQuickSort << " milliseconds\n" <<
                 "\nTime quick sort for rand numbers: " << durationQuickSortRand << " milliseconds\n" <<
                 "\nTime quick sort for increase numbers: " << durationQuickIncr << " milliseconds\n" <<
                 "\nTime quick sort for decrease numbers: " << durationQuickSortDecr << " milliseconds\n\n\n";

        }
        else {
            cout << "\n\n@@@@@    START BENCHMARK WITH MERGE SORT    @@@@@\n";

            auto startTimeMergeSort = high_resolution_clock::now();

            auto startTimeMergeSortRand = high_resolution_clock::now();
            mergeSort(tempRandArray);
            auto endTimeMergeSortRand = high_resolution_clock::now();

            auto startTimeMergeSortIncr = high_resolution_clock::now();
            mergeSort(tempIncreasingArray);
            auto endTimeMergeSortIncr = high_resolution_clock::now();
            auto startTimeMergeSortDecr = high_resolution_clock::now();
            mergeSort(tempDecreasingArray);
            auto endTimeMergeSortDecr = high_resolution_clock::now();
            auto endTimeMergeSort = high_resolution_clock::now();

            if (isSorted(tempRandArray)) {
                cout << "\nRand Array is sorted correctly." << endl;
            } else {
                cout << "\nRand Array is not sorted correctly." << endl;
            }

            if (isSorted(tempIncreasingArray)) {
                cout << "\nIncreasing Array is sorted correctly." << endl;
            } else {
                cout << "\nIncreasing Array is not sorted correctly." << endl;
            }

            if (isSorted(tempDecreasingArray)) {
                cout << "\nDecreasing Array is sorted correctly." << endl;
            } else {
                cout << "\nDecreasing Array is not sorted correctly." << endl;
            }



            auto durationTotalMergeSort = duration_cast<duration<double, milli>>(endTimeMergeSort - startTimeMergeSort).count();
            auto durationMergeSortRand = duration_cast<duration<double, milli>>(endTimeMergeSortRand - startTimeMergeSortRand).count();
            auto durationMergeSortIncr = duration_cast<duration<double, milli>>(endTimeMergeSortIncr - startTimeMergeSortIncr).count();
            auto durationMergeSortDecr = duration_cast<duration<double, milli>>(endTimeMergeSortDecr - startTimeMergeSortDecr).count();



            cout << "\nTime merge sort: " << durationTotalMergeSort << " milliseconds\n" <<
                                  "\nTime merge sort for rand numbers: " << durationMergeSortRand << " milliseconds\n" <<
                                  "\nTime merge sort for increase numbers: " << durationMergeSortIncr << " milliseconds\n" <<
                                  "\nTime merge sort for decrease numbers: " << durationMergeSortDecr << " milliseconds\n\n\n";

        }
    }
    cout << "\n\n    BENCHMARK IS ENDED UP WITH THE ABOVE-MENTIONED RESULTS    \n";

}