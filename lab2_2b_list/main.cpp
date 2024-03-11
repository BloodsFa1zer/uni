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


struct IndexedList {
    vector<int> data;

    // Додавання елементу в кінець списку
    void append(int value) {
        data.push_back(value);
    }

    // Отримання значення за індексом
    int get(int index) {
        if (index >= 0 && index < static_cast<int>(data.size())) {
            return data[index];
        } else if (index < 0 && -index <= static_cast<int>(data.size())) {
            return data[data.size() + index];
        } else {
            throw out_of_range("Index out of range");
        }
    }

    // Встановлення значення за індексом
    void set(int index, int value) {
        if (index >= 0 && index < static_cast<int>(data.size())) {
            data[index] = value;
        } else if (index < 0 && -index <= static_cast<int>(data.size())) {
            data[data.size() + index] = value;
        } else {
            throw out_of_range("Index out of range");
        }
    }

    // Вставка елементу за індексом
    void insert(int index, int value) {
        if (index >= 0 && index <= static_cast<int>(data.size())) {
            data.insert(data.begin() + index, value);
        } else if (index < 0 && -index <= static_cast<int>(data.size())) {
            data.insert(data.end() + index + 1, value);
        } else {
            throw out_of_range("Index out of range");
        }
    }

    // Вилучення елементу за індексом
    void remove(int index) {
        if (index >= 0 && index < static_cast<int>(data.size())) {
            data.erase(data.begin() + index);
        } else if (index < 0 && -index <= static_cast<int>(data.size())) {
            data.erase(data.end() + index);
        } else {
            throw out_of_range("Index out of range");
        }
    }

    size_t size() const {
        return data.size();
    }

    void print() {
        cout << "List: [";
        for (int i = 0; i < data.size(); ++i) {
            cout << data[i];
            if (i !=  data.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
};

void userManagementMode();
void benchmarkMode();
void demonstrationMode();


int main() {
    srand(time(nullptr));
    int mode;
    mode = getIntInput("Select mode:\n"
                       "1. User management mode\n"
                       "2. Demonstration mode \n"
                       "3. Benchmark mode:\n", 1, 3);

    switch (mode) {
        case 1:
            userManagementMode();
            break;
        case 2:
            demonstrationMode();
            break;
        case 3:
            benchmarkMode();
            break;
    }

}


void userManagementMode() {
    IndexedList list;
    int value = 0, index = 0;
    int option;
    while (true) {
        option = getIntInput( "Choose an option:\n"
                              "0. Exit\n"
                              "1. Get\n"
                              "2. Set\n"
                              "3. Insert\n"
                              "4. Remove\n"
                              "5. Print\n", 0, 5);
        switch (option) {
            case 0:
                cout << "Thanks for using my program!" << endl;
                return;
            case 1:
                cout << "Enter index: ";
                cin >> index;
                try {
                    cout << "Value at index " << index << ": " << list.get(index) << endl;
                } catch (const out_of_range& e) {
                    cerr << e.what() << endl;
                }
                break;
            case 2:
                cout << "Enter index where you want value to be set: ";
                cin >> index;
                cout << "Enter value you want to be set: ";
                cin >> value;
                try {
                    list.set(index, value);
                    cout << "Value set successfully" << endl;
                } catch (const out_of_range& e) {
                    cerr << e.what() << endl;
                }
                break;
            case 3:
                cout << "Enter index where you want value to be set: ";
                cin >> index;
                cout << "Enter value you want to be set: ";
                cin >> value;
                try {
                    list.insert(index, value);
                    cout << "Value inserted successfully" << endl;
                } catch (const out_of_range& e) {
                    cerr << e.what() << endl;
                }
                break;
            case 4:
                cout << "Enter index: ";
                cin >> index;
                try {
                    list.remove(index);
                    cout << "Value removed successfully" << endl;
                } catch (const out_of_range& e) {
                    cerr << e.what() << endl;
                }
                break;
            case 5:
                list.print();
                break;
        }
    }
}

void demonstrationMode() {
    IndexedList list;
    int randValue, randPosition;
    cout << "\n**** DEMONSTRATION MODE *****\n";


    cout << "\n\n@@@@@ ADDING 5 RANDOM ELEMENTS AT THE BEGINNING @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    for (int i = 0; i < 5; i++) {
        randValue = rand() % 5000;
        list.insert(i, randValue);
        cout << "Element: " << randValue << " added at the beginning with index: " << i << endl;
    }
    cout << "\n**** Data successfully added at the beginning! ****\n";

    cout << "\n\n@@@@@ ADDING 5 RANDOM ELEMENTS AT THE END @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    for (int i = -1; i >= -5; i--) {
        randValue = rand() % 5000;
        list.insert(i, randValue);
        cout << "Element: " << randValue << " added at the beginning with index: " << i << endl;
    }
    list.print();
    cout << "\n**** Data successfully added at the end! ****\n";


    cout << "\n\n@@@@@ SETTING THE RANDOM VALUE TO THE RANDOM POSITION @@@@@\n\n";
    loadingAnimation();
    randValue = rand() % 5000;
    randPosition = rand() % 11 - 5;
    list.set(randPosition, randValue);
    cout << "Element: " << randValue << " set to the index: " << randPosition << endl;
    cout << "\n**** Element successfully set! ****\n";


    cout << "\n\n@@@@@ GETTING THE RANDOM ELEMENT @@@@@\n\n";
    loadingAnimation();
    randPosition = rand() % 11 - 5;
    cout << "Value at index " << randPosition << ": " << list.get(randPosition) << endl;
    cout << "\n**** Elements successfully got! ****\n";

    cout << "\n\n@@@@@ REMOVING AN ELEMENT WITH THE RANDOM INDEX  @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    randPosition = rand() % 11 - 5;
    list.remove(randPosition);
    cout << "\n**** Element was removed successfully! ****\n";

    cout << "\n\n@@@@@ PRINTING THE LIST  @@@@@\n\n";
    loadingAnimation();
    list.print();
    cout << "\n**** List was printed successfully! ****\n";


    cout << "\n\n@@@@@ EXIT @@@@@\n\n";
}


void totalMemoryUsageMB(int numberOfElements) {
    size_t elementSizeBytes = sizeof(IndexedList);
    size_t totalMemoryUsageBytes = elementSizeBytes * numberOfElements;
    double totalMemoryUsageMB = static_cast<double>(totalMemoryUsageBytes);
    cout << "Memory usage of the list: " << totalMemoryUsageMB << " B" << endl;
}

void benchmarkMode() {
    cout << "\nYou are now in the benchmark dbMode, time of each operation will be written afterwards\n";
    IndexedList list;
    int randValue, randPosition;

    auto startTime = high_resolution_clock::now();

    auto startTimeInsertingElements = high_resolution_clock::now();
    auto startTimeInsertingElemAtBeginning = high_resolution_clock::now();
    for (int i = 0; i < 5; i++) {
        randValue = rand() % 5000;
        list.insert(i, randValue);
    }
    auto endTimeInsertingElemAtBeginning = high_resolution_clock::now();

    auto startTimeInsertingElemAtEnd = high_resolution_clock::now();
    for (int i = -1; i >= 5; i--) {
        randValue = rand() % 5000;
        list.insert(i, randValue);
    }
    auto endTimeInsertingElemAtEnd = high_resolution_clock::now();
    auto endTimeInsertingElements = high_resolution_clock::now();

    auto startTimeSettingElement = high_resolution_clock::now();
    randValue = rand() % 5000;
    randPosition = rand() % 11 - 5;
    list.set(randPosition, randValue);
    auto endTimeSettingElement = high_resolution_clock::now();

    auto startTimeGettingElement = high_resolution_clock::now();
    randPosition = rand() % 11 - 5;
    list.get(randPosition);
    auto endTimeGettingElement = high_resolution_clock::now();

    auto startTimeRemovingElement = high_resolution_clock::now();
    randPosition = rand() % 11 - 5;
    list.remove(randPosition);
    auto endTimeRemovingElement = high_resolution_clock::now();

    auto startTimePrintingList = high_resolution_clock::now();
    list.print();
    auto endTimePrintingList = high_resolution_clock::now();



    auto endTime = high_resolution_clock::now();



    auto durationTotal = duration_cast<duration<double, milli>>(endTime - startTime).count();
    auto durationInsertAtBeginning = duration_cast<duration<double, nano>>(endTimeInsertingElemAtBeginning - startTimeInsertingElemAtBeginning).count();
    auto durationInsertAtEnd = duration_cast<duration<double, nano>>(endTimeInsertingElemAtEnd - startTimeInsertingElemAtEnd).count();
    auto durationInsertTotal = duration_cast<duration<double, nano>>(endTimeInsertingElements - startTimeInsertingElements).count();
    auto durationSetValue = duration_cast<duration<double, nano>>(endTimeSettingElement - startTimeSettingElement).count();
    auto durationGetValue = duration_cast<duration<double, nano>>(endTimeGettingElement - startTimeGettingElement).count();
    auto durationRemoveElement = duration_cast<duration<double, nano>>(endTimeRemovingElement - startTimeRemovingElement).count();
    auto durationPrintData = duration_cast<duration<double, nano>>(endTimePrintingList - startTimePrintingList).count();


    cout << "\n---------------------------\n";
    cout << "\nTime insert 5 elements at beginning: " << durationInsertAtBeginning << " nanoseconds\n" <<
         "\nTime insert 5 elements at end: " << durationInsertAtEnd << " nanoseconds\n" <<
         "\nTime insert 10 elements in total: " << durationInsertTotal << " nanoseconds\n" <<
         "\nSetting element time: " << durationSetValue << " nanoseconds\n" <<
         "\nGetting element time: " << durationGetValue << " nanoseconds\n" <<
         "\nRemoving element time: " << durationRemoveElement << " nanoseconds\n" <<
         "\nPrinting fata time: " << durationPrintData << " nanoseconds\n" <<
         "\nTotal time: " << durationTotal << " milliseconds\n";

    totalMemoryUsageMB(list.size());
    cout << "\n---------------------------\n";

    cout << "\n\n    BENCHMARK IS ENDED UP WITH THE ABOVE-MENTIONED RESULTS    \n";

}