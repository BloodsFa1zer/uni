#include <iostream>
#include <vector>
#include <ctime>
#include <thread>
#include <cstdlib>

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


struct HatNode {
    vector<int> elements; // Elements in the node
    vector<HatNode*> children; // Child nodes
};

pair<HatNode*, size_t> findNodeAndIndex(HatNode* node, size_t idx) {
    // If the index is within the elements of the current node
    if (idx < node->elements.size()) {
        return {node, idx};
    } else {
        size_t childIndex = 0;
        size_t cumulativeSize = node->elements.size();
        // Finding the child index and recalculating the index relative to the child
        for (const auto& child : node->children) {
            size_t childSize = child->elements.size();
            if (idx < cumulativeSize + childSize) {
                return findNodeAndIndex(child, idx - cumulativeSize);
            } else {
                cumulativeSize += childSize;
                childIndex++;
            }
        }
    }
    throw out_of_range("Failed to find node and index");
}

HatNode* createHat() {
    return new HatNode{{}, {}};
}

// Function to add an element to a node at the beginning
void addElementToNodeAtBeginning(HatNode* node, int value) {
    node->elements.insert(node->elements.begin(), value);
}

void addElementToNodeAtEnd(HatNode* node, int value) {
    node->elements.push_back(value);
}

void addElementToNodeAtPosition(HatNode* node, int value, size_t position) {
    // If position is greater than the size of the elements vector, insert at the end
    if (position >= node->elements.size()) {
        node->elements.push_back(value);
    } else {
        node->elements.insert(node->elements.begin() + position, value);
    }
}

void traverseForward(HatNode* node) {
    if (node == nullptr) return;

    // Visit each element in the current node
    for (const auto& element : node->elements) {
        cout << element << " ";
    }

    // Recursively traverse each child node
    for (const auto& child : node->children) {
        traverseForward(child);
    }
}

void traverseBackward(HatNode* node) {
    if (node == nullptr) return;

    // Recursively traverse each child node
    for (int i = node->children.size() - 1; i >= 0; --i) {
        traverseBackward(node->children[i]);
    }

    // Visit each element in the current node in reverse order
    for (int i = node->elements.size() - 1; i >= 0; --i) {
        cout << node->elements[i] << " ";
    }
}

void deleteElementAtPosition(HatNode* root, size_t index) {
    // Find the node and index within the node
    auto [node, idx] = findNodeAndIndex(root, index);

    // Print the element to be deleted
    cout << "Deleting element at position " << index << ": " << node->elements[idx] << endl;

    // Erase the element at the calculated index
    node->elements.erase(node->elements.begin() + idx);
}

int accessByIndex(HatNode* root, int index) {
    if (index < 0) {
        // Handle the case when the index is negative
        throw out_of_range("Index cannot be negative");
    }

    // Calculate the total number of elements in the tree
    size_t totalElements = 0;
    for (const auto& elem : root->elements) {
        totalElements++;
    }
    for (const auto& child : root->children) {
        for (const auto& elem : child->elements) {
            totalElements++;
        }
    }

    if (index >= totalElements) {
        // Handle the case when the index is out of bounds
        throw out_of_range("Index out of bounds");
    }

    // Find the node and index within the node
    auto [node, idx] = findNodeAndIndex(root, index);

    // Return the element at the calculated index
    return node->elements[idx];
}

bool searchElement(HatNode* node, int value) {
    if (node == nullptr) return false;

    // Search for the value in the current node's elements
    for (const auto& element : node->elements) {
        if (element == value) {
            return true; // Element found
        }
    }

    // Recursively search in the child nodes
    for (const auto& child : node->children) {
        if (searchElement(child, value)) {
            return true; // Element found in a child node
        }
    }

    return false; // Element not found
}

int countElements(HatNode* node) {
    int count = node->elements.size(); // Count elements in the current node
    for (auto child : node->children) {
        count += countElements(child); // Recursively count elements in child nodes
    }
    return count;
}


void totalMemoryUsageMB(int numberOfElements) {
    size_t elementSizeBytes = sizeof(HatNode);
    size_t totalMemoryUsageBytes = elementSizeBytes * numberOfElements;
    double totalMemoryUsageMB = static_cast<double>(totalMemoryUsageBytes) / (1024 * 1024);
    cout << "Memory usage of the hat node: " << totalMemoryUsageMB << " MB" << endl;
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

}

void userManagementMode() {
    HatNode* hat = createHat();
    int value = 0, position = 0;
    int option;
    do {
        option = getIntInput("Select an option:\n"
                             "1. Traverse the list forward\n"
                             "2. Traverse the list backward\n"
                             "3. Insert an element at the beginning\n"
                             "4. Insert an element at the end\n"
                             "5. Insert an element at a specific position\n"
                             "6. Delete an element\n"
                             "7. Access an element by index\n"
                             "8. Search for an element by value\n"
                             "0. Exit\n", 0, 8);
        switch (option) {
            case 0:
                cout << "Thanks for using my algorithm system" << endl;
                return;
            case 1:
                traverseForward(hat);
                cout << endl;
                break;
            case 2:
                traverseBackward(hat);
                cout << endl;
                break;
            case 3:
                cout << "enter the value you want to insert" << endl;
                cin >> value;
                addElementToNodeAtBeginning(hat, value);
                break;
            case 4:
                cout << "enter the value you want to insert" << endl;
                cin >> value;
                addElementToNodeAtEnd(hat, value);
                break;
            case 5:
                cout << "enter the value you want to insert" << endl;
                cin >> value;
                addElementToNodeAtPosition(hat, value, getIntInput("enter the position where you want value to be inserted", 1, countElements(hat)));
                break;
            case 6:
                deleteElementAtPosition(hat, getIntInput("enter the position where you want value to be deleted:\n", 1, countElements(hat)));
                break;
            case 7:
                cout << "Element at index" << position << ": " << accessByIndex(hat, getIntInput("enter the index of element you want to get access to:\n", 1, countElements(hat))) << endl;
                break;
            case 8:
                cout << "enter the value you want to find" << endl;
                cin >> value;
                if (searchElement(hat, value)) {
                    cout << value << " found in the HAT." << endl;
                } else {
                    cout << value << " not found in the HAT." << endl;
                }
                break;
        }
    }while (true);
}

void demonstrationMode() {
    HatNode* hat = createHat();
    int randValue, randPosition;
    cout << "\n**** DEMONSTRATION MODE *****\n";


    cout << "\n\n@@@@@ ADDING 5 RANDOM ELEMENTS AT THE BEGINNING @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    for (int i = 0; i < 5; i++) {
        randValue = rand() % 5000;
        addElementToNodeAtBeginning(hat, randValue);
        cout << "Element: " << randValue << " added at the beginning" << endl;
    }
    cout << "\n**** Data successfully added at the beginning! ****\n";

    cout << "\n\n@@@@@ ADDING 5 RANDOM ELEMENTS AT THE END @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    for (int i = 0; i < 5; i++) {
        randValue = rand() % 5000;
        addElementToNodeAtEnd(hat, randValue);
        cout << "Element: " << randValue << " added at the end" << endl;
    }
    cout << "\n**** Data successfully added at the end! ****\n";

    cout << "\n\n@@@@@ ADDING 5 RANDOM ELEMENTS AT THE RANDOM POSITION @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    for (int i = 0; i < 5; i++) {
        randValue = rand() % 5000;
        randPosition = rand() % 10 + i;
        addElementToNodeAtPosition(hat, randValue, randPosition);
        cout << "Element: " << randValue << "added at the position: " << randPosition << endl;
    }
    cout << "\n**** Data successfully added at the random position! ****\n";


    cout << "\n\n@@@@@ TRAVERSING THE DATA STRUCT FORWARD @@@@@\n\n";
    loadingAnimation();
    traverseForward(hat);
    cout << "\n**** Elements successfully traversed forward! ****\n";


    cout << "\n\n@@@@@ TRAVERSING THE DATA STRUCT BACKWARD @@@@@\n\n";
    loadingAnimation();
    traverseBackward(hat);
    cout << "\n**** Elements successfully traversed backward! ****\n";

    cout << "\n\n@@@@@ DELETING AN ELEMENT AT THE RANDOM POSITION FROM THE DATA STRUCT  @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    randPosition = rand() % 15;
    deleteElementAtPosition(hat, randPosition);
    cout << "\n**** Element was deleted successfully! ****\n";

    cout << "\n\n@@@@@ GETTING ELEMENT BY RANDOM INDEX @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    randPosition = rand() % 14;
    cout << "Element at index - " << randPosition << " is: " << accessByIndex(hat, randPosition) << endl;
    cout << "\n**** Successfully got element by random index! ****\n";


    cout << "\n\n@@@@@ SEARCHING ELEMENT BY RANDOM VALUE @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    randValue = rand() % 5000;
    if (searchElement(hat, randValue)) {
        cout << "There is element with value: " << randValue << " in the data struct" << endl;
    } else {
        cout << "There is no element with value: " << randValue << " in the data struct" << endl;
    }
    cout << "\n**** Successfully searched element by random value! ****\n";

    cout << "\n\n@@@@@ EXIT @@@@@\n\n";
}

void benchmarkMode() {
    cout << "\nYou are now in the benchmark dbMode, time of each operation will be written afterwards\n";
    HatNode* hat = createHat();
    int value = 0;

    auto startTime = high_resolution_clock::now();

    auto startTimeAddingElement = high_resolution_clock::now();
    auto startTimeAddElemAtBeginning = high_resolution_clock::now();
    for (int i = 0; i < 5; i++) {
        int randValue = rand() % 5000;
        addElementToNodeAtBeginning(hat, randValue);
    }
    auto endTimeAddElemAtBeginning = high_resolution_clock::now();

    auto startTimeAddElemAtEnd = high_resolution_clock::now();
    for (int i = 0; i < 5; i++) {
        int randValue = rand() % 5000;
        addElementToNodeAtEnd(hat, randValue);
    }
    auto endTimeAddElemAtEnd = high_resolution_clock::now();

    auto startTimeAddElemAtPosition = high_resolution_clock::now();
    for (int i = 0; i < 5; i++) {
        int randValue = rand() % 5000;
        int randPosition = rand() % 10 + i;
        addElementToNodeAtPosition(hat, randValue, randPosition);
    }
    auto endTimeAddElemAtPosition = high_resolution_clock::now();
    auto endTimeAddingElement = high_resolution_clock::now();

    auto startTimeTraverseForward = high_resolution_clock::now();
    traverseForward(hat);
    auto endTimeTraverseForward = high_resolution_clock::now();

    auto startTimeTraverseBackward = high_resolution_clock::now();
    traverseBackward(hat);
    auto endTimeTraverseBackward = high_resolution_clock::now();

    auto startTimeDeletingElement = high_resolution_clock::now();
    int randPosition = rand() % 15;
    deleteElementAtPosition(hat, randPosition);
    auto endTimeDeletingElement = high_resolution_clock::now();


    auto startTimeAccessingToElemByIndex = high_resolution_clock::now();
    randPosition = rand() % 15;
    accessByIndex(hat, randPosition);
    auto endTimeAccessingToElemByIndex = high_resolution_clock::now();

    auto startTimeSearchingByValue = high_resolution_clock::now();
    value = rand() % 5000;
    searchElement(hat, value);
    auto endTimeSearchingByValue = high_resolution_clock::now();


    auto endTime = high_resolution_clock::now();



    auto durationTotal = duration_cast<duration<double, milli>>(endTime - startTime).count();
    auto durationAddAtBeginning = duration_cast<duration<double, milli>>(endTimeAddElemAtBeginning - startTimeAddElemAtBeginning).count();
    auto durationAddAtEnd = duration_cast<duration<double, milli>>(endTimeAddElemAtEnd - startTimeAddElemAtEnd).count();
    auto durationAddAtPosition = duration_cast<duration<double, milli>>(endTimeAddElemAtPosition - startTimeAddElemAtPosition).count();
    auto durationAddTotal = duration_cast<duration<double, milli>>(endTimeAddingElement - startTimeAddingElement).count();
    auto durationTraverseForward = duration_cast<duration<double, milli>>(endTimeTraverseForward - startTimeTraverseForward).count();
    auto durationTraverseBackward = duration_cast<duration<double, milli>>(endTimeTraverseBackward - startTimeTraverseBackward).count();
    auto durationDeleteElement = duration_cast<duration<double, milli>>(endTimeDeletingElement - startTimeDeletingElement).count();
    auto durationGettingAccessToElement = duration_cast<duration<double, milli>>(endTimeDeletingElement - startTimeDeletingElement).count();
    auto durationSearchingByValue = duration_cast<duration<double, milli>>(endTimeSearchingByValue - startTimeSearchingByValue).count();


    cout << "\n---------------------------\n";
    cout << "\nTime insert 5 elements at beginning: " << durationAddAtBeginning << " milliseconds\n" <<
         "\nTime insert 5 elements at end: " << durationAddAtEnd << " milliseconds\n" <<
         "\nTime insert 5 elements at specific position: " << durationAddAtPosition << " milliseconds\n" <<
         "\nTime insert 15 elements in total: " << durationAddTotal << " milliseconds\n" <<
         "\nTraversing forward time: " << durationTraverseForward << " milliseconds\n" <<
         "\nTraversing backward time: " << durationTraverseBackward << " milliseconds\n" <<
         "\nTraversing backward time: " << durationTraverseBackward << " milliseconds\n" <<
         "\nDeleting element time: " << durationDeleteElement << " milliseconds\n" <<
         "\nGetting access to element time: " << durationGettingAccessToElement << " milliseconds\n" <<
         "\nSearching element by value time: " << durationSearchingByValue << " milliseconds\n" <<
         "\nTotal time: " << durationTotal << " milliseconds\n";

    totalMemoryUsageMB(countElements(hat));
    cout << "\n---------------------------\n";

    cout << "\n\n    BENCHMARK IS ENDED UP WITH THE ABOVE-MENTIONED RESULTS    \n";

}
