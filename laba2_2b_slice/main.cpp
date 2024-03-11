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

    vector<int> slice(int start, int end, int step = 1) const {
        vector<int> result;
        int size = data.size();

        if (start < 0) start += size;
        if (end < 0) end += size;

        if (step < 0) {
            for (int i = start; i > end; i += step) {
                result.push_back(data[i]);
            }
        } else {
            for (int i = start; i < end; i += step) {
                result.push_back(data[i]);
            }
        }

        return result;
    }


    void set(int index, int value) {
        if (index >= 0 && index < static_cast<int>(data.size())) {
            data[index] = value;
        } else if (index < 0 && -index <= static_cast<int>(data.size())) {
            data[data.size() + index] = value;
        } else {
            throw out_of_range("Index out of range");
        }
    }


    void insert(int index, int value) {
        if (index >= 0 && index <= static_cast<int>(data.size())) {
            data.insert(data.begin() + index, value);
        } else if (index < 0 && -index <= static_cast<int>(data.size())) {
            data.insert(data.end() + index + 1, value);
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

vector<int> returnSlice(const IndexedList& list, int start, int end, int step = 1) {

    return list.slice(start, end, step);
}

void printSublist(const vector<int>& sublist) {
    cout << "Sublist: [";
    for (size_t i = 0; i < sublist.size(); ++i) {
        cout << sublist[i];
        if (i != sublist.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

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




    return 0;
}

void userManagementMode() {
    IndexedList completedList;
    IndexedList list;
    int value = 0, index = 0;
    int start, end, step;
    int option;
    string YerOrNo;
    while (true) {
        option = getIntInput( "Choose an option:\n"
                              "0. Exit\n"
                              "1. Set\n"
                              "2. Insert\n"
                              "3. Create Slice\n"
                              "4. Print List\n"
                              "5. Get Completed List to Test\n", 0, 5);
        switch (option) {
            case 0:
                cout << "Thanks for using my program!" << endl;
                return;
            case 1:
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
            case 2:
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
            case 3:
                if (list.size() == 0 && completedList.size() == 0) {
                    cerr << "You cannot create slice with empty list" << endl;
                    break;
                }

                cout << "If you want to create slice with step(it equals 1 by default) with negative value,\n"
                        " than you have to start with higher number and end with lower: for example,\n"
                        " start = 8, end = 0, step = -2" << endl;
                cout << "Enter the start of the slice: ";
                cin >> start;
                cout << "Enter the end of the slice: ";
                cin >> end;
                cout << "step = 1 by default, if you want to change it, write yes, instead - no" << endl;
                cin >> YerOrNo;
                if (completedList.size() == 0) {
                    if (YerOrNo == "yes") {
                        cout << "Enter the step of the slice: ";
                        cin >> step;
                        printSublist(list.slice(start, end, step));
                    } else if (YerOrNo == "no") {
                        printSublist(list.slice(start, end, 1));
                    } else {
                        cerr << "You are allowed to write yes or no!!!" << endl;
                    }
                } else {
                    if (YerOrNo == "yes") {
                        cout << "Enter the step of the slice: ";
                        cin >> step;
                        printSublist(completedList.slice(start, end, step));
                    } else if (YerOrNo == "no") {
                        printSublist(completedList.slice(start, end));
                    } else {
                        cerr << "You are allowed to write yes or no!!!" << endl;
                    }
                }
                break;
            case 4:
                list.print();
                break;
            case 5:
                completedList.data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
                completedList.print();
                break;
        }
    }
}

void demonstrationMode() {
    IndexedList list;
    int randValue, randPosition;
    cout << "\n**** DEMONSTRATION MODE *****\n";


    cout << "\n\n@@@@@ INSERTING 5 RANDOM ELEMENTS AT THE BEGINNING @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    for (int i = 0; i < 5; i++) {
        randValue = rand() % 5000;
        list.insert(i, randValue);
        cout << "Element: " << randValue << " inserted at the beginning with index: " << i << endl;
    }
    cout << "\n**** Data successfully inserted at the beginning! ****\n";

    cout << "\n\n@@@@@ INSERTING 5 RANDOM ELEMENTS AT THE END @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    for (int i = -1; i >= -5; i--) {
        randValue = rand() % 5000;
        list.insert(i, randValue);
        cout << "Element: " << randValue << " inserted at the end with index: " << i << endl;
    }
    list.print();
    cout << "\n**** Data successfully inserted at the end! ****\n";


    cout << "\n\n@@@@@ SETTING THE RANDOM VALUE TO THE RANDOM POSITION @@@@@\n\n";
    loadingAnimation();
    randValue = rand() % 5000;
    randPosition = rand() % 11 - 5;
    list.set(randPosition, randValue);
    cout << "Element: " << randValue << " set to the index: " << randPosition << endl;
    cout << "\n**** Element successfully set! ****\n";


    cout << "\n\n@@@@@ CREATING 5 DIFFERENT SLICES @@@@@\n\n";
    loadingAnimation();
    cout << "Create slice with the start = 1 and end = 4" << endl;
    vector<int> result1 = returnSlice(list, 1, 4);
    printSublist(result1);
    cout << endl;

    // Test slice with negative start index
    loadingAnimation();
    cout << "Create slice with the start = -4 and end = 8" << endl;
    vector<int> result2 = returnSlice(list, -4, 8);
    printSublist(result2);
    cout << endl;

    // Test slice with negative end index
    loadingAnimation();
    cout << "Create slice with the start = 2, end = -2 and step = 2" << endl;
    vector<int> result3 = returnSlice(list, 2, -2, 2);
    printSublist(result3);
    cout << endl;

    // Test slice with negative step value
    loadingAnimation();
    cout << "Create slice with the start = 9, end = 0 and step = -2" << endl;
    vector<int> result4 = returnSlice(list, 9, 0, -2);
    printSublist(result4);
    cout << endl;

    // Test slice with negative start and end indices
    loadingAnimation();
    cout << "Create slice with the start = -6 and end = -2" << endl;
    vector<int> result5 = returnSlice(list, -6, -2);
    printSublist(result5);
    cout << endl;


    cout << "\n\n@@@@@ EXIT @@@@@\n\n";
}

void totalMemoryUsageMB(int numberOfElementsList, int numberOfElementsSlice) {
    size_t elementSizeBytes = sizeof(IndexedList);
    size_t totalMemoryUsageBytes = elementSizeBytes * numberOfElementsList + elementSizeBytes * numberOfElementsSlice;
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
        randValue = rand() % 100;
        list.insert(i, randValue);
    }
    auto endTimeInsertingElemAtBeginning = high_resolution_clock::now();

    auto startTimeInsertingElemAtEnd = high_resolution_clock::now();
    for (int i = -1; i >= -5; i--) {
        randValue = rand() % 100;
        list.insert(i, randValue);
    }
//    list.print();
    auto endTimeInsertingElemAtEnd = high_resolution_clock::now();
    auto endTimeInsertingElements = high_resolution_clock::now();

    auto startTimeSettingElement = high_resolution_clock::now();
    randValue = rand() % 5000;
    randPosition = rand() % 11 - 5;
    list.set(randPosition, randValue);
    auto endTimeSettingElement = high_resolution_clock::now();

    auto startTimeCreatingSlice = high_resolution_clock::now();
    int start = rand() % 5; // Generates a random number between 0 and 5
    int end = -1 * (rand() % 5); // // Generates a random number between -5 and 0
//    cout << "start = " << start << ", end = " << end << endl;
    vector<int> res = returnSlice(list, start, end);
    auto endTimeCreatingSlice = high_resolution_clock::now();

    auto startTimePrintingSubList = high_resolution_clock::now();
    printSublist(res);
    auto endTimePrintingSubList = high_resolution_clock::now();

    auto endTime = high_resolution_clock::now();



    auto durationTotal = duration_cast<duration<double, milli>>(endTime - startTime).count();
    auto durationInsertAtBeginning = duration_cast<duration<double, nano>>(endTimeInsertingElemAtBeginning - startTimeInsertingElemAtBeginning).count();
    auto durationInsertAtEnd = duration_cast<duration<double, nano>>(endTimeInsertingElemAtEnd - startTimeInsertingElemAtEnd).count();
    auto durationInsertTotal = duration_cast<duration<double, nano>>(endTimeInsertingElements - startTimeInsertingElements).count();
    auto durationSetValue = duration_cast<duration<double, nano>>(endTimeSettingElement - startTimeSettingElement).count();
    auto durationCreateSlice = duration_cast<duration<double, nano>>(endTimeCreatingSlice - startTimeCreatingSlice).count();
    auto durationPrintData = duration_cast<duration<double, nano>>(endTimePrintingSubList - startTimePrintingSubList).count();


    cout << "\n---------------------------\n";
    cout << "\nTime insert 5 elements at beginning: " << durationInsertAtBeginning << " nanoseconds\n" <<
         "\nTime insert 5 elements at end: " << durationInsertAtEnd << " nanoseconds\n" <<
         "\nTime insert 10 elements in total: " << durationInsertTotal << " nanoseconds\n" <<
         "\nSetting element time: " << durationSetValue << " nanoseconds\n" <<
         "\nCreating slice time: " << durationCreateSlice << " nanoseconds\n" <<
         "\nPrinting slice time: " << durationPrintData << " nanoseconds\n" <<
         "\nTotal time: " << durationTotal << " milliseconds\n";

    totalMemoryUsageMB(list.size(), res.size());
    cout << "\n---------------------------\n";

    cout << "\n\n    BENCHMARK IS ENDED UP WITH THE ABOVE-MENTIONED RESULTS    \n";

}