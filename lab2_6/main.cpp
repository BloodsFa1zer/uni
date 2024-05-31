#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include "benchmark_MacOS.h"
#include "benchmark_Windows.h"

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

struct DateTime {
    int year, month, day, hour, minute, second;

    DateTime() : year(1970), month(1), day(1), hour(0), minute(0), second(0) {}

    DateTime(int y, int mo, int d, int h, int mi, int s)
            : year(y), month(mo), day(d), hour(h), minute(mi), second(s) {}

    bool operator<(const DateTime& other) const {
        return tie(year, month, day, hour, minute, second) <
               tie(other.year, other.month, other.day, other.hour, other.minute, other.second);
    }

    bool operator>(const DateTime& other) const {
        return tie(year, month, day, hour, minute, second) >
               tie(other.year, other.month, other.day, other.hour, other.minute, other.second);
    }

    bool operator==(const DateTime& other) const {
        return tie(year, month, day, hour, minute, second) ==
               tie(other.year, other.month, other.day, other.hour, other.minute, other.second);
    }

    bool operator!=(const DateTime& other) const {
        return tie(year, month, day, hour, minute, second) !=
               tie(other.year, other.month, other.day, other.hour, other.minute, other.second);
    }

    bool operator>=(const DateTime& other) const {
        return tie(year, month, day, hour, minute, second) >=
               tie(other.year, other.month, other.day, other.hour, other.minute, other.second);
    }

    bool operator<=(const DateTime& other) const {
        return tie(year, month, day, hour, minute, second) <=
               tie(other.year, other.month, other.day, other.hour, other.minute, other.second);
    }

    friend ostream& operator<<(ostream& os, const DateTime& dt) {
        os << dt.year << "-" << dt.month << "-" << dt.day << " "
           << dt.hour << ":" << dt.minute << ":" << dt.second;
        return os;
    }

    DateTime addDaysToDate(int days)
    {
        DateTime resultDate = *this;
        while (days > 0)
        {
            int daysInCurrentMonth = resultDate.dayInMonth(resultDate.month);
            if (days <= daysInCurrentMonth - resultDate.day)
            {
                resultDate.day += days;
                days = 0;
            }
            else
            {
                days -= (daysInCurrentMonth - resultDate.day + 1);
                resultDate.day = 1;
                resultDate.month += 1;
                if (resultDate.month > 12)
                {
                    resultDate.month = 1;
                    resultDate.year += 1;
                }
            }
        }
        return resultDate;
    }
    int dayInMonth(int month)
    {
        switch (month)
        {
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                return 31;
            case 4: case 6: case 9: case 11:
                return 30;
            case 2:
                return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
            default:
                return -1;
        }
    }
};

DateTime enterDateTime() {
    int year, month, day, hour, minute, second;

    std::cout << "Enter year: ";
    std::cin >> year;
    std::cout << "Enter month: ";
    std::cin >> month;
    std::cout << "Enter day: ";
    std::cin >> day;
    std::cout << "Enter hour: ";
    std::cin >> hour;
    std::cout << "Enter minute: ";
    std::cin >> minute;
    std::cout << "Enter second: ";
    std::cin >> second;

    return DateTime(year, month, day, hour, minute, second);
}

DateTime generateRandomDateTime() {
    int year = rand() % 5 + 2020;
    int month = rand() % 12 + 1;
    int day = rand() % 28 + 1;
    int hour = rand() % 24;
    int minute = rand() % 60;
    int second = rand() % 60;
    return DateTime(year, month, day, hour, minute, second);
}

void printDateTime(DateTime& dt) {
    cout << dt << endl;
}

// LinkedList structure
struct LinkedListNode {
    DateTime data;
    LinkedListNode* next;

    LinkedListNode(DateTime val) : data(val), next(nullptr) {}
};

struct LinkedList {
    LinkedListNode* head;

    LinkedList() : head(nullptr) {}

    void insert(DateTime value) {
        LinkedListNode* newNode = new LinkedListNode(value);
        newNode->next = head;
        head = newNode;
    }

    void remove(DateTime value) {
        LinkedListNode* current = head;
        LinkedListNode* prev = nullptr;
        while (current && !(current->data == value)) {
            prev = current;
            current = current->next;
        }
        if (current) {
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
        }
    }

    LinkedListNode* search(DateTime value) {
        LinkedListNode* current = head;
        while (current && !(current->data == value)) {
            current = current->next;
        }
        return current;
    }

    vector<DateTime> searchRange(DateTime start, DateTime end) {
        vector<DateTime> result;
        LinkedListNode* current = head;
        while (current) {
            if (current->data >= start && current->data <= end) {
                result.push_back(current->data);
            }
            current = current->next;
        }
        return result;
    }

    void printInOrder() {
        LinkedListNode* current = head;
        while (current) {
            cout << current->data << endl;
            current = current->next;
        }
    }

    void applyToAll(void(*func)(DateTime&)) {
        LinkedListNode* current = head;
        while (current) {
            func(current->data);
            current = current->next;
        }
    }

    void fillWithRandom(int n) {
        for (int i = 0; i < n; ++i) {
            insert(generateRandomDateTime());
        }
    }
};


// ArrayList structure
struct ArrayList {
    vector<DateTime> data;

    void insert(DateTime value) {
        data.push_back(value);
    }

    void remove(DateTime value) {
        data.erase(std::remove(data.begin(), data.end(), value), data.end());
    }

    DateTime* search(DateTime value) {
        auto it = find(data.begin(), data.end(), value);
        return it != data.end() ? &(*it) : nullptr;
    }

    vector<DateTime> searchRange(DateTime start, DateTime end) {
        vector<DateTime> result;
        for (const auto& dt : data) {
            if (dt >= start && dt <= end) {
                result.push_back(dt);
            }
        }
        return result;
    }

    void printInOrder() {
        for (const auto& dt : data) {
            cout << dt << endl;
        }
    }

    void applyToAll(void(*func)(DateTime&)) {
        for (auto& dt : data) {
            func(dt);
        }
    }

    void fillWithRandom(int n) {
        for (int i = 0; i < n; ++i) {
            insert(generateRandomDateTime());
        }
    }
};


// BST structure
struct BSTNode {
    DateTime data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(DateTime val) : data(val), left(nullptr), right(nullptr) {}
};

struct BST {
    BSTNode* root;

    BST() : root(nullptr) {}

    void insert(DateTime value) {
        root = insertRec(root, value);
    }

    BSTNode* insertRec(BSTNode* node, DateTime value) {
        if (!node) return new BSTNode(value);
        if (value < node->data) {
            node->left = insertRec(node->left, value);
        } else {
            node->right = insertRec(node->right, value);
        }
        return node;
    }

    void remove(DateTime value) {
        root = removeRec(root, value);
    }

    BSTNode* removeRec(BSTNode* node, DateTime value) {
        if (!node) return node;
        if (value < node->data) {
            node->left = removeRec(node->left, value);
        } else if (value > node->data) {
            node->right = removeRec(node->right, value);
        } else {
            if (!node->left) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            BSTNode* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = removeRec(node->right, temp->data);
        }
        return node;
    }

    BSTNode* minValueNode(BSTNode* node) {
        BSTNode* current = node;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }

    BSTNode* search(DateTime value) {
        return searchRec(root, value);
    }

    BSTNode* searchRec(BSTNode* node, DateTime value) {
        if (!node || node->data == value) return node;
        if (value < node->data) return searchRec(node->left, value);
        return searchRec(node->right, value);
    }

    vector<DateTime> searchRange(DateTime start, DateTime end) {
        vector<DateTime> result;
        searchRangeRec(root, start, end, result);
        return result;
    }

    void searchRangeRec(BSTNode* node, DateTime start, DateTime end, vector<DateTime>& result) {
        if (!node) return;
        if (node->data >= start && node->data <= end) {
            result.push_back(node->data);
        }
        if (node->data > start) searchRangeRec(node->left, start, end, result);
        if (node->data < end) searchRangeRec(node->right, start, end, result);
    }

    void printInOrder() {
        printInOrderRec(root);
    }

    void printInOrderRec(BSTNode* node) {
        if (node) {
            printInOrderRec(node->left);
            cout << node->data << endl;
            printInOrderRec(node->right);
        }
    }

    void applyToAll(void(*func)(DateTime&)) {
        applyToAllRec(root, func);
    }

    void applyToAllRec(BSTNode* node, void(*func)(DateTime&)) {
        if (node) {
            func(node->data);
            applyToAllRec(node->left, func);
            applyToAllRec(node->right, func);
        }
    }

    void fillWithRandom(int n) {
        for (int i = 0; i < n; ++i) {
            insert(generateRandomDateTime());
        }
    }
};


// AVL Tree structure
struct AVLNode {
    DateTime data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(DateTime val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

struct AVL {
    AVLNode* root;

    AVL() : root(nullptr) {}

    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    void insert(DateTime value) {
        root = insertRec(root, value);
    }

    AVLNode* insertRec(AVLNode* node, DateTime value) {
        if (!node) return new AVLNode(value);
        if (value < node->data) {
            node->left = insertRec(node->left, value);
        } else {
            node->right = insertRec(node->right, value);
        }

        node->height = max(height(node->left), height(node->right)) + 1;

        int balance = getBalance(node);

        if (balance > 1 && value < node->left->data) {
            return rightRotate(node);
        }

        if (balance < -1 && value > node->right->data) {
            return leftRotate(node);
        }

        if (balance > 1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void remove(DateTime value) {
        root = removeRec(root, value);
    }

    AVLNode* removeRec(AVLNode* node, DateTime value) {
        if (!node) return node;

        if (value < node->data) {
            node->left = removeRec(node->left, value);
        } else if (value > node->data) {
            node->right = removeRec(node->right, value);
        } else {
            if (!node->left) {
                AVLNode* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                AVLNode* temp = node->left;
                delete node;
                return temp;
            }

            AVLNode* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = removeRec(node->right, temp->data);
        }

        if (!node) return node;

        node->height = max(height(node->left), height(node->right)) + 1;

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) {
            return rightRotate(node);
        }

        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0) {
            return leftRotate(node);
        }

        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->left) {
            current = current->left;
        }
        return current;
    }

    AVLNode* search(DateTime value) {
        return searchRec(root, value);
    }

    AVLNode* searchRec(AVLNode* node, DateTime value) {
        if (!node || node->data == value) return node;
        if (value < node->data) return searchRec(node->left, value);
        return searchRec(node->right, value);
    }

    vector<DateTime> searchRange(DateTime start, DateTime end) {
        vector<DateTime> result;
        searchRangeRec(root, start, end, result);
        return result;
    }

    void searchRangeRec(AVLNode* node, DateTime start, DateTime end, vector<DateTime>& result) {
        if (!node) return;
        if (node->data >= start && node->data <= end) {
            result.push_back(node->data);
        }
        if (node->data > start) searchRangeRec(node->left, start, end, result);
        if (node->data < end) searchRangeRec(node->right, start, end, result);
    }

    void printInOrder() {
        printInOrderRec(root);
    }

    void printInOrderRec(AVLNode* node) {
        if (node) {
            printInOrderRec(node->left);
            cout << node->data << endl;
            printInOrderRec(node->right);
        }
    }

    void applyToAll(void(*func)(DateTime&)) {
        applyToAllRec(root, func);
    }

    void applyToAllRec(AVLNode* node, void(*func)(DateTime&)) {
        if (node) {
            func(node->data);
            applyToAllRec(node->left, func);
            applyToAllRec(node->right, func);
        }
    }

    void fillWithRandom(int n) {
        for (int i = 0; i < n; ++i) {
            insert(generateRandomDateTime());
        }
    }
};




struct TwoThreeNode {
    DateTime data1, data2;
    TwoThreeNode* left;
    TwoThreeNode* middle;
    TwoThreeNode* right;
    bool isTwoNode;

    TwoThreeNode(DateTime val)
            : data1(val), left(nullptr), middle(nullptr), right(nullptr), isTwoNode(true) {}

    TwoThreeNode(DateTime val1, TwoThreeNode* l, TwoThreeNode* m, TwoThreeNode* r)
            : data1(val1), data2(), left(l), middle(m), right(r), isTwoNode(true) {}

    TwoThreeNode(DateTime val1, DateTime val2, TwoThreeNode* l, TwoThreeNode* m, TwoThreeNode* r)
            : data1(val1), data2(val2), left(l), middle(m), right(r), isTwoNode(false) {}
};

struct TwoThreeTree {
    TwoThreeNode* root;

    TwoThreeTree() : root(nullptr) {}

    void insert(DateTime value) {
        if (!root) {
            root = new TwoThreeNode(value);
        } else {
            insertRec(root, value);
        }
    }

    // Recursive insert helper function
    void insertRec(TwoThreeNode*& node, DateTime value) {
        if (node->isTwoNode) {
            if (value < node->data1) {
                node->data2 = node->data1;
                node->data1 = value;
            } else {
                node->data2 = value;
            }
            node->isTwoNode = false;
        } else {
            if (value < node->data1) {
                if (!node->left) {
                    node->left = new TwoThreeNode(value);
                } else {
                    insertRec(node->left, value);
                }
            } else if (value < node->data2) {
                if (!node->middle) {
                    node->middle = new TwoThreeNode(value);
                } else {
                    insertRec(node->middle, value);
                }
            } else {
                if (!node->right) {
                    node->right = new TwoThreeNode(value);
                } else {
                    insertRec(node->right, value);
                }
            }

            if (!node->isTwoNode) {
                if (node->right && !node->right->isTwoNode) {
                    splitNode(node);
                }
            }
        }
    }

    // Split node function
    void splitNode(TwoThreeNode*& node) {
        TwoThreeNode* newLeft = new TwoThreeNode(node->data1);
        TwoThreeNode* newRight = new TwoThreeNode(node->data2);

        newLeft->left = node->left;
        newLeft->right = node->middle;
        newRight->left = node->right->left;
        newRight->right = node->right->middle;

        DateTime middleValue = node->right->data1;

        delete node;
        node = new TwoThreeNode(middleValue);
        node->left = newLeft;
        node->middle = newRight;
        node->right = nullptr;
        node->isTwoNode = true;
    }

    // Fill with random function
    void fillWithRandom(int count) {
        srand(time(nullptr));
        for (int i = 0; i < count; ++i) {
            DateTime randomDate = generateRandomDateTime();
            insert(randomDate);
        }
    }


    void remove(DateTime value) {
        root = removeRec(root, value);
        if (root && root->left == nullptr && root->middle == nullptr && root->right == nullptr && !root->isTwoNode) {
            TwoThreeNode* oldRoot = root;
            root = new TwoThreeNode(root->data1);
            root->left = oldRoot->left;
            delete oldRoot;
        }
    }

    TwoThreeNode* removeRec(TwoThreeNode* node, DateTime value) {
        if (!node) return nullptr;

        if (node->left == nullptr && node->middle == nullptr && node->right == nullptr) {  // Leaf node
            if (node->isTwoNode) {
                if (node->data1 == value) return nullptr;
                return node;
            } else {
                if (node->data1 == value) {
                    node->data1 = node->data2;
                    node->isTwoNode = true;
                } else if (node->data2 == value) {
                    node->isTwoNode = true;
                }
                return node;
            }
        }

        if (node->isTwoNode) {
            if (value < node->data1) {
                node->left = removeRec(node->left, value);
                return balance(node);
            } else {
                node->middle = removeRec(node->middle, value);
                return balance(node);
            }
        } else {
            if (value < node->data1) {
                node->left = removeRec(node->left, value);
                return balance(node);
            } else if (value < node->data2) {
                node->middle = removeRec(node->middle, value);
                return balance(node);
            } else {
                node->right = removeRec(node->right, value);
                return balance(node);
            }
        }
    }


    TwoThreeNode* balance(TwoThreeNode* node) {
        if (node->left && node->left->isTwoNode == false) {
            if (node->isTwoNode) {
                node->right = new TwoThreeNode(node->data1, node->left->data2, node->left->middle, node->left->right, node->middle);
                node->data1 = node->left->data1;
                node->middle = node->left->left;
                node->left = nullptr;
                node->isTwoNode = false;
            } else {
                if (node->right && node->right->isTwoNode == false) {
                    node->middle = new TwoThreeNode(node->data2, node->right->data1, node->middle, node->right->left, node->right->middle);
                    node->data2 = node->right->data2;
                    node->right = node->right->right;
                } else {
                    node->middle = new TwoThreeNode(node->data2, node->middle->data1, node->middle->left, node->middle->middle, node->middle->right);
                    node->data2 = node->data1;
                    node->data1 = node->left->data2;
                    node->middle = node->left->right;
                    node->left->isTwoNode = true;
                }
            }
        } else if (node->middle && node->middle->isTwoNode == false) {
            if (node->isTwoNode) {
                node->right = new TwoThreeNode(node->data1, node->middle->data2, node->middle->middle, node->middle->right, node->right);
                node->data1 = node->middle->data1;
                node->middle = node->middle->left;
                node->isTwoNode = false;
            } else {
                if (node->right && node->right->isTwoNode == false) {
                    node->middle = new TwoThreeNode(node->data2, node->right->data1, node->middle, node->right->left, node->right->middle);
                    node->data2 = node->right->data2;
                    node->right = node->right->right;
                } else {
                    node->middle = new TwoThreeNode(node->data2, node->middle->data1, node->middle->left, node->middle->middle, node->middle->right);
                    node->data2 = node->data1;
                    node->data1 = node->left->data2;
                    node->middle = node->left->right;
                    node->left->isTwoNode = true;
                }
            }
        } else if (node->right && node->right->isTwoNode == false) {
            node->middle = new TwoThreeNode(node->data2, node->right->data1, node->middle, node->right->left, node->right->middle);
            node->data2 = node->right->data2;
            node->right = node->right->right;
        }

        return node;
    }

    TwoThreeNode* search(DateTime value) {
        return searchRec(root, value);
    }

    TwoThreeNode* searchRec(TwoThreeNode* node, DateTime value) {
        if (!node) return nullptr;
        if (value == node->data1 || (!node->isTwoNode && value == node->data2)) return node;
        if (value < node->data1) return searchRec(node->left, value);
        if (node->isTwoNode || value < node->data2) return searchRec(node->middle, value);
        return searchRec(node->right, value);
    }

    vector<DateTime> searchRange(DateTime start, DateTime end) {
        vector<DateTime> result;
        searchRangeRec(root, start, end, result);
        return result;
    }

    void searchRangeRec(TwoThreeNode* node, DateTime start, DateTime end, vector<DateTime>& result) {
        if (!node) return;
        if (node->data1 >= start && node->data1 <= end) result.push_back(node->data1);
        if (!node->isTwoNode && node->data2 >= start && node->data2 <= end) result.push_back(node->data2);
        if (node->data1 > start) searchRangeRec(node->left, start, end, result);
        if (node->isTwoNode || node->data2 > start) searchRangeRec(node->middle, start, end, result);
        if (!node->isTwoNode || node->data2 < end) searchRangeRec(node->right, start, end, result);
    }

    void applyToAll(void(*func)(DateTime&)) {
        applyToAllRec(root, func);
    }

    void applyToAllRec(TwoThreeNode* node, void(*func)(DateTime&)) {
        if (node) {
            func(node->data1);
            applyToAllRec(node->left, func);
            applyToAllRec(node->middle, func);
            if (!node->isTwoNode) func(node->data2);
            applyToAllRec(node->right, func);
        }
    }

    void printInOrder() {
        printInOrderRec(root);
    }

    void printInOrderRec(TwoThreeNode* node) {
        if (node) {
            printInOrderRec(node->left);
            cout << node->data1 << endl;
            printInOrderRec(node->middle);
            if (!node->isTwoNode) cout << node->data2 << endl;
            printInOrderRec(node->right);
        }
    }
};




// Function prototypes for interactive and demonstration modes
void demonstrationMode();
void demonstrationModeForLinkedList();
void demonstrationModeForArrayList();
void demonstrationModeForBST();
void demonstrationModeForAVL();
void demonstrationModeForTwoThreeTree();

DateTime enterDateTime();

void interactiveMode();
void handleLinkedList();
void handleArrayList();
void handleBST();
void handleAVLTree();
void handle23Tree();

void benchmarkMode();
void benchmarkLinkedList();
void benchmarkArrayList();
void benchmarkBST();
void benchmarkAVL();
void benchmarkTwoThreeTree();



int main() {
    int mode;
    mode = getIntInput("Choose mode:\n"
                       "1. Interactive Mode\n"
                       "2. Demonstration Mode\n"
                       "3. Benchmark Mode\n"
                       "0. Exit\n", 0, 3);
    switch (mode) {
        case 1:
            interactiveMode();
            break;
        case 2:
            demonstrationMode();
            break;
        case 3:
            benchmarkMode();
            break;
        case 0:
            cout << "Thanks for using program!" << endl;
    }
    return 0;

}

void interactiveMode() {
    int choice;
    do {
        choice = getIntInput("Choose data structure:\n"
                             "1. Linked List\n"
                             "2. Array List\n"
                             "3. Binary Search Tree\n"
                             "4. AVL Tree\n"
                             "5. 2-3 Tree\n"
                             "0. Exit\n", 0, 5);
        switch (choice) {
            case 1: handleLinkedList(); break;
            case 2: handleArrayList(); break;
            case 3: handleBST(); break;
            case 4: handleAVLTree(); break;
            case 5: handle23Tree(); break;
            case 0: cout << "Exiting...\n"; break;
        }
    } while (choice != 0);
}

void demonstrationMode() {
    cout << "\n--- Demonstration Mode ---\n";
    demonstrationModeForLinkedList();
    demonstrationModeForArrayList();
    demonstrationModeForBST();
    demonstrationModeForAVL();
    demonstrationModeForTwoThreeTree();
}

void benchmarkMode() {
    benchmarkLinkedList();
    benchmarkArrayList();
    benchmarkBST();
    benchmarkAVL();
    benchmarkTwoThreeTree();
}


const string options =  "1. Insert\n"
                        "2. Insert random\n"
                        "3. Remove\n"
                        "4. Search\n"
                        "5. Search Range\n"
                        "6. Print List\n"
                        "7. Apply to All\n"
                        "8. Fill with Random\n"
                        "0. Back to Main Menu\n";

void handleLinkedList() {
    LinkedList list;
    DateTime dt;
    DateTime start, end;
    int choice;
    do {
        choice = getIntInput("\nLinked List Operations:\n" + options, 0, 8);
        switch (choice) {
            case 1:
                dt = enterDateTime();
                list.insert(dt);
                cout << "Inserted: " << dt << endl;
                break;
                case 2:
                dt = generateRandomDateTime();
                list.insert(dt);
                cout << "Inserted: " << dt << endl;
                break;
            case 3:
                dt = generateRandomDateTime();
                list.remove(dt);
                cout << "Removed: " << dt << endl;
                break;
            case 4:
                dt = generateRandomDateTime();
                if (auto result = list.search(dt)) {
                    cout << "Found: " << result->data << endl;
                } else {
                    cout << "Not Found\n";
                }
                break;
            case 5:
                start = generateRandomDateTime();
                end = generateRandomDateTime();
                cout << "Range Search from " << start << " to " << end << ":\n";
                list.searchRange(start, end);
                break;
            case 6:
                cout << "List in Order:\n";
                list.printInOrder();
                break;
            case 7:
                list.applyToAll(printDateTime);
                break;
            case 8:
                size_t count;
                cout << "Enter count: ";
                cin >> count;
                list.fillWithRandom(count);
                break;
            case 0: cout << "Back to Main Menu\n"; break;
        }
    } while (choice != 0);
}

void handleArrayList() {
    ArrayList list;
    int choice;
    DateTime dt;
    DateTime start, end;
    do {
        choice = getIntInput("\nArray List Operations:\n" + options, 0, 8);
        switch (choice) {
            case 1:
                dt = enterDateTime();
                list.insert(dt);
                cout << "Inserted: " << dt << endl;
                break;
            case 2:
                dt = generateRandomDateTime();
                list.insert(dt);
                cout << "Inserted: " << dt << endl;
                break;
            case 3:
                dt = generateRandomDateTime();
                list.remove(dt);
                cout << "Removed: " << dt << endl;
                break;
            case 4:
                dt = generateRandomDateTime();
                if (auto result = list.search(dt)) {
                    cout << "Found: " << *result << endl;
                } else {
                    cout << "Not Found\n";
                }
                break;
            case 5:
                start = generateRandomDateTime();
                end = generateRandomDateTime();
                cout << "Range Search from " << start << " to " << end << ":\n";
                list.searchRange(start, end);
                break;
            case 6:
                cout << "List in Order:\n";
                list.printInOrder();
                break;
            case 7:
                list.applyToAll(printDateTime);
                break;
            case 8:
                size_t count;
                cout << "Enter count: ";
                cin >> count;
                list.fillWithRandom(count);
                break;
             case 0:
                 cout << "Back to Main Menu\n";
                 break;
        }
    } while (choice != 0);
}

void handleBST() {
    BST tree;
    int choice;
    DateTime dt;
    DateTime start, end;
    do {
        cout << "\nBinary Search Tree Operations:\n";
        choice = getIntInput("\nBinary Search Tree Operations:\n" + options, 0, 8);
        cin >> choice;
        switch (choice) {
                case 1:
                    dt = enterDateTime();
                    tree.insert(dt);
                    cout << "Inserted: " << dt << endl;
                    break;
                case 2:
                    dt = generateRandomDateTime();
                    tree.insert(dt);
                    cout << "Inserted: " << dt << endl;
                    break;
                case 3:
                    dt = generateRandomDateTime();
                    tree.remove(dt);
                    cout << "Removed: " << dt << endl;
                    break;
                case 4:
                    dt = generateRandomDateTime();
                    if (auto result = tree.search(dt)) {
                        cout << "Found: " << result->data << endl;
                    } else {
                        cout << "Not Found\n";
                    }
                    break;
                case 5:
                    start = generateRandomDateTime();
                    end = generateRandomDateTime();
                    cout << "Range Search from " << start << " to " << end << ":\n";
                    tree.searchRange(start, end);
                    break;
                case 6:
                    cout << "List in Order:\n";
                    tree.printInOrder();
                    break;
                case 7:
                    tree.applyToAll(printDateTime);
                    break;
                case 8:
                    size_t count;
                    cout << "Enter count: ";
                    cin >> count;
                    tree.fillWithRandom(count);
                    break;
            case 0:
                cout << "Back to Main Menu\n";
                break;
        }
    } while (choice != 8);
}

void handleAVLTree() {
    AVL tree;
    int choice;
    DateTime dt;
    DateTime start, end;
    do {
        choice = getIntInput("\nAVL Tree Operations:\n" + options, 0, 8);
        switch (choice) {
            case 1:
                dt = enterDateTime();
                tree.insert(dt);
                cout << "Inserted: " << dt << endl;
                break;
            case 2:
                dt = generateRandomDateTime();
                tree.insert(dt);
                cout << "Inserted: " << dt << endl;
                break;
            case 3:
                dt = generateRandomDateTime();
                tree.remove(dt);
                cout << "Removed: " << dt << endl;
                break;
            case 4:
                dt = generateRandomDateTime();
                if (auto result = tree.search(dt)) {
                    cout << "Found: " << result->data << endl;
                } else {
                    cout << "Not Found\n";
                }
                break;
            case 5:
                start = generateRandomDateTime();
                end = generateRandomDateTime();
                cout << "Range Search from " << start << " to " << end << ":\n";
                tree.searchRange(start, end);
                break;
            case 6:
                cout << "List in Order:\n";
                tree.printInOrder();
                break;
            case 7:
                tree.applyToAll(printDateTime);
                break;
            case 8:
                size_t count;
                cout << "Enter count: ";
                cin >> count;
                tree.fillWithRandom(count);
                break;
            case 0:
                cout << "Back to Main Menu\n";
                break;
        }
    } while (choice != 8);
}

void handle23Tree() {
    TwoThreeTree tree;
    int choice;
    DateTime dt;
    DateTime start, end;
    do {
        choice = getIntInput("\nArray List Operations:\n" + options, 0, 8);
        switch (choice) {
            case 1:
                dt = enterDateTime();
                tree.insert(dt);
                cout << "Inserted: " << dt << endl;
                break;
            case 2:
                dt = generateRandomDateTime();
                tree.insert(dt);
                cout << "Inserted: " << dt << endl;
                break;
            case 3:
                dt = generateRandomDateTime();
                cout << "Removed: " << dt << endl;
                break;
            case 4:
                dt = generateRandomDateTime();
                if (auto result = tree.search(dt)) {
                    cout << "Found: " << result->data1 << endl;
                } else {
                    cout << "Not Found\n";
                }
                break;
            case 5:
                start = generateRandomDateTime();
                end = generateRandomDateTime();
                cout << "Range Search from " << start << " to " << end << ":\n";
                tree.searchRange(start, end);
                break;
            case 6:
                cout << "List in Order:\n";
                tree.printInOrder();
                break;
            case 7:
                tree.applyToAll(printDateTime);
                break;
            case 8:
                size_t count;
                cout << "Enter count: ";
                cin >> count;
                tree.fillWithRandom(count);
                break;
            case 0: cout << "Back to Main Menu\n"; break;
        }
    } while (choice != 0);
}




void demonstrationModeForLinkedList() {
    cout << "\n--- Linked List ---\n";
    LinkedList list;
    list.fillWithRandom(5);

    cout << "1. Initial list:\n";
    loadingAnimation();
    loadingAnimation();
    list.printInOrder();

    cout << "\n2. Insert a random DateTime:\n";
    loadingAnimation();
    DateTime dt1 = generateRandomDateTime();
    list.insert(dt1);
    list.printInOrder();

    cout << "\n3. Remove the inserted DateTime:\n";
    loadingAnimation();
    list.remove(dt1);
    list.printInOrder();

    cout << "\n4. Search for a specific DateTime:\n";
    loadingAnimation();
    auto result = list.search(dt1);
    if (result) {
        cout << "Found: " << result->data << endl;
    } else {
        cout << "Not Found\n";
    }

    cout << "\n5. Search within a range(01.01.2022 00:00:00 - 01.01.2023 00:00:00):\n";
    loadingAnimation();
    loadingAnimation();
    DateTime start(2022, 1, 1, 0, 0, 0);
    DateTime end(2023, 1, 1, 0, 0, 0);
    auto rangeResult = list.searchRange(start, end);
    for (const auto& dt : rangeResult) {
        cout << dt << endl;
    }

    cout << "\n6. Print in-order:\n";
    loadingAnimation();
    list.printInOrder();

    cout << "\n7. Apply to all elements (printing each):\n";
    loadingAnimation();
    list.applyToAll([](DateTime& dt) { cout << dt << endl; });
}

void demonstrationModeForArrayList() {
    cout << "\n--- Array List ---\n";
    loadingAnimation();
    ArrayList list;
    list.fillWithRandom(5);

    cout << "1. Initial list:\n";
    loadingAnimation();
    list.printInOrder();

    cout << "\n2. Insert a random DateTime:\n";
    loadingAnimation();
    loadingAnimation();
    DateTime dt1 = generateRandomDateTime();
    list.insert(dt1);
    list.printInOrder();

    cout << "\n3. Remove the inserted DateTime:\n";
    loadingAnimation();
    list.remove(dt1);
    list.printInOrder();

    cout << "\n4. Search for a specific DateTime:\n";
    loadingAnimation();
    auto result = list.search(dt1);
    if (result) {
        cout << "Found: " << *result << endl;
    } else {
        cout << "Not Found\n";
    }

    cout << "\n5. Search within a range(01.01.2022 00:00:00 - 01.01.2023 00:00:00):\n";
    loadingAnimation();
    loadingAnimation();
    DateTime start(2022, 1, 1, 0, 0, 0);
    DateTime end(2023, 1, 1, 0, 0, 0);
    auto rangeResult = list.searchRange(start, end);
    for (const auto& dt : rangeResult) {
        cout << dt << endl;
    }

    cout << "\n6. Print in-order:\n";
    loadingAnimation();
    list.printInOrder();

    cout << "\n7. Apply to all elements (printing each):\n";
    loadingAnimation();
    list.applyToAll([](DateTime& dt) { cout << dt << endl; });
}

void demonstrationModeForBST() {
    cout << "\n--- Binary Search Tree ---\n";
    loadingAnimation();
    BST tree;
    tree.fillWithRandom(5);

    cout << "1. Initial tree:\n";
    loadingAnimation();
    tree.printInOrder();

    cout << "\n2. Insert a random DateTime:\n";
    loadingAnimation();
    loadingAnimation();
    DateTime dt1 = generateRandomDateTime();
    tree.insert(dt1);
    tree.printInOrder();

    cout << "\n3. Remove the inserted DateTime:\n";
    loadingAnimation();
    tree.remove(dt1);
    tree.printInOrder();

    cout << "\n4. Search for a specific DateTime:\n";
    loadingAnimation();
    auto result = tree.search(dt1);
    if (result) {
        cout << "Found: " << result->data << endl;
    } else {
        cout << "Not Found\n";
    }

    cout << "\n5. Search within a range(01.01.2022 00:00:00 - 01.01.2023 00:00:00):\n";
    loadingAnimation();
    loadingAnimation();
    DateTime start(2022, 1, 1, 0, 0, 0);
    DateTime end(2023, 1, 1, 0, 0, 0);
    auto rangeResult = tree.searchRange(start, end);
    for (const auto& dt : rangeResult) {
        cout << dt << endl;
    }

    cout << "\n6. Print in-order:\n";
    loadingAnimation();
    tree.printInOrder();

    cout << "\n7. Apply to all elements (printing each):\n";
    loadingAnimation();
    tree.applyToAll([](DateTime& dt) { cout << dt << endl; });
}

void demonstrationModeForAVL() {
    cout << "\n--- AVL Tree ---\n";
    loadingAnimation();
    AVL tree;
    tree.fillWithRandom(5);

    cout << "1. Initial tree:\n";
    loadingAnimation();
    tree.printInOrder();

    cout << "\n2. Insert a random DateTime:\n";
    loadingAnimation();
    loadingAnimation();
    DateTime dt1 = generateRandomDateTime();
    tree.insert(dt1);
    tree.printInOrder();

    cout << "\n3. Remove the inserted DateTime:\n";
    loadingAnimation();
    tree.remove(dt1);
    tree.printInOrder();

    cout << "\n4. Search for a specific DateTime:\n";
    loadingAnimation();
    auto result = tree.search(dt1);
    if (result) {
        cout << "Found: " << result->data << endl;
    } else {
        cout << "Not Found\n";
    }

    cout << "\n5. Search within a range(01.01.2022 00:00:00 - 01.01.2023 00:00:00):\n";
    loadingAnimation();
    loadingAnimation();
    DateTime start(2022, 1, 1, 0, 0, 0);
    DateTime end(2023, 1, 1, 0, 0, 0);
    auto rangeResult = tree.searchRange(start, end);
    for (const auto& dt : rangeResult) {
        cout << dt << endl;
    }

    cout << "\n6. Print in-order:\n";
    loadingAnimation();
    tree.printInOrder();

    cout << "\n7. Apply to all elements (printing each):\n";
    loadingAnimation();
    tree.applyToAll([](DateTime& dt) { cout << dt << endl; });
}

void demonstrationModeForTwoThreeTree() {
    cout << "\n--- 2-3 Tree ---\n";
    loadingAnimation();
    TwoThreeTree tree;
    tree.fillWithRandom(5);

    cout << "1. Initial tree:\n";
    loadingAnimation();
    tree.printInOrder();

    cout << "\n2. Insert a random DateTime:\n";
    loadingAnimation();
    loadingAnimation();
    DateTime dt1 = generateRandomDateTime();
    tree.insert(dt1);
    tree.printInOrder();

    cout << "\n3. Remove the inserted DateTime:\n";
    loadingAnimation();
    tree.printInOrder();

    cout << "\n4. Search for a specific DateTime:\n";
    loadingAnimation();
    auto result = tree.search(dt1);
    if (result) {
        cout << "Found: " << result->data1 << endl;
    } else {
        cout << "Not Found\n";
    }

    cout << "\n5. Search within a range(01.01.2022 00:00:00 - 01.01.2023 00:00:00):\n";
    loadingAnimation();
    loadingAnimation();
    DateTime start(2022, 1, 1, 0, 0, 0);
    DateTime end(2023, 1, 1, 0, 0, 0);
    auto rangeResult = tree.searchRange(start, end);
    for (const auto& dt : rangeResult) {
        cout << dt << endl;
    }

    cout << "\n6. Print in-order:\n";
    loadingAnimation();
    tree.printInOrder();

    cout << "\n7. Apply to all elements (printing each):\n";
    loadingAnimation();
    tree.applyToAll([](DateTime& dt) { cout << dt << endl; });
}


template <typename T>
void benchmarkDataStructure(T& ds, const string& name) {
    cout << "\n\n\n\n\n\n\n\n";
    cout << "\n--- " << name << " ---\n";

    DateTime startRange(2022, 1, 1, 0, 0, 0);
    DateTime endRange(2023, 1, 1, 0, 0, 0);

    auto startTimeTotal = high_resolution_clock::now();
    auto startTimeFill = high_resolution_clock::now();
    ds.fillWithRandom(10);
    BenchmarkMax memoryBenchmarkFill("fill with 100 random for " + name);
    auto endTimeFill = high_resolution_clock::now();

    auto startTimeInsert = high_resolution_clock::now();
    auto randomDateTime = generateRandomDateTime();
    ds.insert(randomDateTime);
    BenchmarkMax memoryBenchmarkInsert("insert random for " + name);
    auto endTimeInsert = high_resolution_clock::now();

    auto startTimeRemove = high_resolution_clock::now();
    ds.remove(randomDateTime);
    BenchmarkMax memoryBenchmarkRemove("remove random for " + name);
    auto endTimeRemove = high_resolution_clock::now();

    auto startTimeSearch = high_resolution_clock::now();
    auto randomDateTimeSearch = generateRandomDateTime();
    ds.search(randomDateTimeSearch);
    BenchmarkMax memoryBenchmarkSearch("search random for " + name);
    auto endTimeSearch = high_resolution_clock::now();

    auto startTimeSearchRange = high_resolution_clock::now();
    ds.searchRange(startRange, endRange);
    BenchmarkMax memoryBenchmarkSearchRange("search range for " + name);
    auto endTimeSearchRange = high_resolution_clock::now();

    auto startTimePrint = high_resolution_clock::now();
    ds.printInOrder();
    BenchmarkMax memoryBenchmarkPrint("print for " + name);
    auto endTimePrint = high_resolution_clock::now();

    auto startTimeApply = high_resolution_clock::now();
    ds.applyToAll([](DateTime& dt) { });
    BenchmarkMax memoryBenchmarkApply("apply to all for " + name);
    auto endTimeApply = high_resolution_clock::now();
    auto endTimeTotal = high_resolution_clock::now();



    auto durationTotal = duration_cast<duration<double, milli>>(endTimeTotal - startTimeTotal).count();
    auto durationFill = duration_cast<duration<double, milli>>(endTimeFill - startTimeFill).count();
    auto durationInsert = duration_cast<duration<double, nano>>(endTimeInsert - startTimeInsert).count();
    auto durationRemove = duration_cast<duration<double, nano>>(endTimeRemove - startTimeRemove).count();
    auto durationSearch = duration_cast<duration<double, nano>>(endTimeSearch - startTimeSearch).count();
    auto durationSearchRange = duration_cast<duration<double, nano>>(endTimeSearchRange - startTimeSearchRange).count();
    auto durationPrint = duration_cast<duration<double, milli>>(endTimePrint - startTimePrint).count();
    auto durationApply = duration_cast<duration<double, nano>>(endTimeApply - startTimeApply).count();


    cout << "Total time: " << durationTotal << " milliseconds\n";
    cout << "Fill with Random: " << durationFill << " milliseconds\n";
    cout << "Insert: " << durationInsert << " nanoseconds\n";
    cout << "Remove: " << durationRemove << " nanoseconds\n";
    cout << "Search: " << durationSearch << " nanoseconds\n";
    cout << "Search Range: " << durationSearchRange << " nanoseconds\n";
    cout << "Print In-Order: " << durationPrint << " milliseconds\n";
    cout << "Apply to All: " << durationApply << " nanoseconds\n";


}

void benchmarkLinkedList() {
    LinkedList list;
    benchmarkDataStructure(list, "Linked List");
}

void benchmarkArrayList() {
    ArrayList list;
    benchmarkDataStructure(list, "Array List");
}

void benchmarkBST() {
    BST tree;
    benchmarkDataStructure(tree, "Binary Search Tree");
}

void benchmarkAVL() {
    AVL tree;
    benchmarkDataStructure(tree, "AVL Tree");
}

void benchmarkTwoThreeTree() {
    TwoThreeTree tree;
    benchmarkDataStructure(tree, "2-3 Tree");
}

