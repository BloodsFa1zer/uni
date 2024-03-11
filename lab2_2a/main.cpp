#include <iostream>
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

const int FIXED_ARRAY = 1;
const int DYNAMIC_ARRAY = 2;
const int LINKED_LIST = 3;
static const int MAX_SIZE = 10000; // Maximum size of the stack

void loadingAnimation() {
    for (int i = 0; i < 3; ++i) {
        cout << "Loading.";
        this_thread::sleep_for(milliseconds(250));
        cout << "\r";
        cout.flush();

        cout << "Loading..";
        this_thread::sleep_for(milliseconds(250));
        cout << "\r";
        cout.flush();

        cout << "Loading...";
        this_thread::sleep_for(milliseconds(250));
        cout << "\r";
        cout.flush();
    }
}





bool isValidIPv4(const string& input) {
    stringstream ss(input);
    string octet;
    int num;
    int numOctets = 0;

    // Split the input string by '.'
    while (getline(ss, octet, '.')) {
        // Check if the octet is a valid number
        if (!(stringstream(octet) >> num)) {
            return false;
        }
        // Check if the number is in the range [0, 255]
        if (num < 0 || num > 255) {
            return false;
        }
        numOctets++;
    }

    return numOctets == 4;
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


// Struct to represent an IPv4 address
struct IPv4Address {
    int octet1;
    int octet2;
    int octet3;
    int octet4;

    IPv4Address(int o1, int o2, int o3, int o4) : octet1(o1), octet2(o2), octet3(o3), octet4(o4) {}

    IPv4Address() : octet1(0), octet2(0), octet3(0), octet4(0) {}

    // Function to convert IPv4Address to string
    string toString() const {
        stringstream ss;
        ss << octet1 << "." << octet2 << "." << octet3 << "." << octet4;
        return ss.str();
    }

};

IPv4Address createIPv4Address(const string& ipAddressStr) {
    stringstream ss(ipAddressStr);
    cout << ipAddressStr << endl;
    int octet1, octet2, octet3, octet4;
    char dot;
    ss >> octet1 >> dot >> octet2 >> dot >> octet3 >> dot >> octet4;
    return IPv4Address{octet1, octet2, octet3, octet4};
}

// Function to generate a random IPv4Address
IPv4Address generateRandomIPv4Address() {
    // Initialize a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 255);

    // Generate random octets
    IPv4Address address;
    address.octet1 = distribution(gen);
    address.octet2 = distribution(gen);
    address.octet3 = distribution(gen);
    address.octet4 = distribution(gen);

    return address;
}

template <int MAX_SIZE>
struct FixedArray {
    IPv4Address data[MAX_SIZE]; // Array to store stack elements
    int top = -1; // Index of the top element (-1 means stack is empty)

    // Default constructor
    FixedArray() {
        // Initialize data with default IPv4Address values
        for (int i = 0; i < MAX_SIZE; ++i) {
            data[i] = IPv4Address(0, 0, 0, 0); // Initialize with zeros (or any default value)
        }
    }

    void create_empty() {
        top = -1; // Reset top index to indicate an empty stack
    }

    void push(const IPv4Address& element) {
        if (top >= MAX_SIZE - 1) {
            cerr << "Error: Stack overflow!" << endl;
        } else {
            top++;
            data[top] = element; // Increment top and add element to stack
        }
    }

    void pop() {
        if (top < 0) {
            cerr << "Error: Stack underflow!" << endl;
        } else {
            --top; // Decrement top to remove the top element
        }
    }

    IPv4Address peek() {
        if (top < 0) {
            cerr << "Error: Stack is empty!" << endl;
            return IPv4Address(0,0,0,0); // Return a default IPv4 address indicating an error
        } else {
            return data[top]; // Return the top element without removing it
        }
    }

    int countSize() const {
        int count = 0;
        for (int i = 0; i <= top; ++i) {
            ++count;
        }
        return count;
    }

    bool is_empty() const {
        return top == -1;
    }
};

struct DynamicArray {
    vector<IPv4Address> data; // Vector to store stack elements

    void create_empty() {
        data.clear(); // Clear the vector to make it empty
    }

    void push(const IPv4Address& element) {
        data.push_back(element); // Add element to the end of the vector
    }

    void pop() {
        if (data.empty()) {
            cerr << "Error: Stack underflow!" << endl;
        } else {
            data.pop_back(); // Remove the last element from the vector
        }
    }

    IPv4Address peek() {
        if (data.empty()) {
            cerr << "Error: Stack is empty!" << endl;
            return IPv4Address(0,0,0,0); // Return a default IPv4 address indicating an error
        } else {
            return data.back(); // Return the last element without removing it
        }
    }

    int countSize() const {
        return data.size(); // Get the size of the vector
    }

    bool is_empty() {
        return data.empty(); // Stack is empty if the vector is empty
    }
};

struct Node {
    IPv4Address data; // Data stored in the node
    Node* next; // Pointer to the next node in the list

    // Constructor to initialize Node with data
    Node(const IPv4Address& d) : data(d), next(nullptr) {}
};


struct LinkedList {
    Node* head; // Pointer to the first node in the list

    // Constructor to initialize an empty list
    LinkedList() : head(nullptr) {}

    void create_empty() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp; // Free memory occupied by nodes
        }
    }

    void push(const IPv4Address& element) {
        Node* newNode = new Node(element); // Create a new node with the given element
        newNode->next = head; // Set the next pointer of the new node to the current head
        head = newNode; // Update the head to point to the new node
    }

    void pop() {
        if (!head) {
            cerr << "Error: Stack underflow!" << endl;
            return;
        }
        Node* temp = head; // Store the current head in a temporary variable
        head = head->next; // Move the head to the next node
        delete temp; // Free memory occupied by the previous head
    }

    IPv4Address peek() {
        if (!head) {
            cerr << "Error: Stack is empty!" << endl;
            return IPv4Address(0,0,0,0); // Return a default IPv4 address indicating an error
        }
        return head->data; // Return the data stored in the current head
    }

    int countSize() const {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    bool is_empty() {
        return !head; // Stack is empty if the head pointer is null
    }
};

void userManagementMode(int DataTYPE);
void demonstrationMode();
void benchmarkMode();

int main() {
    srand(time(0));
    cout << "You have to choose mode, you wanna see working:\n"
            "1. User Management Mode\n"
            "2. Demonstration Mode\n"
            "3. Benchmark Mode\n";
    int option;
    option = getIntInput("Choose an option: ", 1, 3);
    switch(option) {
        case 1:
            int modeManagement;
            modeManagement = getIntInput("Select a number of database:\n"
                                         "1. Fixed-size Array \n"
                                         "2. Dynamic-size Array\n"
                                         "3. Linked-list\n", 1, 3);
            switch (modeManagement) {
                case 1:
                    userManagementMode(FIXED_ARRAY);
                    break;
                case 2:
                    userManagementMode(DYNAMIC_ARRAY);
                    break;
                case 3:
                    userManagementMode(LINKED_LIST);
                    break;
            }
            break;
        case 2:
            demonstrationMode();
            break;
        case 3:
            benchmarkMode();
            break;
    }
}

void userManagementMode(int DataTYPE) {

    IPv4Address ipAddr(0, 0, 0, 0);
    string input;

    FixedArray<MAX_SIZE> fixed;
    DynamicArray dynamic;
    LinkedList linkedList;

    int operation;
    cout << "\nHere you can manage stack.\n";
    do {
        cout << "\n\n" << endl;
        cout << "Choose an option:" << endl;
        cout << "1. Create an empty stack" << endl;
        cout << "2. Push an element onto the stack" << endl;
        cout << "3. Pop an element from the stack" << endl;
        cout << "4. Peek at the top element of the stack" << endl;
        cout << "5. Check if the stack is empty" << endl;
        cout << "0. Exit" << endl;

        operation = getIntInput("Please enter a number of operation: ", 0, 5);

        switch (operation) {
            case 0:
                break;
            case 1:
                switch (DataTYPE) {
                    case FIXED_ARRAY:
                        fixed.create_empty(); // Filling the array with default IPv4Address
                        cout << "Empty stack created using fixed-size array." << endl;
                        break;
                    case DYNAMIC_ARRAY:
                       dynamic.create_empty(); // Clearing the dynamic array
                        cout << "Empty stack created using dynamic array." << endl;
                        break;
                    case LINKED_LIST:
                        linkedList.create_empty(); // Clearing the list
                        cout << "Empty stack created using linked list." << endl;
                        break;
                    default:
                        cerr << "Invalid data structure type." << endl;
                        break;
                }
                break;
            case 2:
                do {
                    cout << "Enter the IP address to push onto the stack (format: XXX.XXX.XXX.XXX): ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, input);
                    if (!isValidIPv4(input)) {
                        cerr << "Invalid IPv4 address format. Please try again." << endl;
                    }
                    ipAddr = createIPv4Address(input);

                } while (!isValidIPv4(input));
                cout << "IPv4 address pushed onto the stack successfully." << endl;
                switch (DataTYPE) {
                    case FIXED_ARRAY:
                        if (fixed.countSize() < MAX_SIZE) {
                            fixed.push(ipAddr);
                        } else {
                            cerr << "Error: Stack overflow! Cannot push element onto the stack." << endl;
                        }
                        break;
                    case DYNAMIC_ARRAY:
                        if (dynamic.countSize() < MAX_SIZE) {
                            dynamic.push(ipAddr);
                        } else {
                            cerr << "Error: Stack overflow! Cannot push element onto the stack." << endl;
                        }
                        break;

                    case LINKED_LIST:
                        if (linkedList.countSize() < MAX_SIZE) {
                            linkedList.push(ipAddr);
                        } else {
                            cerr << "Error: Stack overflow! Cannot push element onto the stack." << endl;
                        }
                        break;

                    default:
                            cerr << "Error: Invalid data type selected." << endl;
                        break;
                }
                break;
            case 3:
                switch (DataTYPE) {
                    case FIXED_ARRAY:
                        if (!fixed.is_empty()) {
                            fixed.pop(); // Pop an element from the fixed-size array stack
                            cout << "Element popped from the stack successfully." << endl;
                        } else {
                            cerr << "Error: Stack is empty! Cannot pop element from the stack." << endl;
                        }
                        break;
                    case DYNAMIC_ARRAY:
                        if (!dynamic.is_empty()) {
                            dynamic.pop(); // Pop an element from the dynamic array stack
                            cout << "Element popped from the stack successfully." << endl;
                        } else {
                            cerr << "Error: Stack is empty! Cannot pop element from the stack." << endl;
                        }
                        break;
                    case LINKED_LIST:
                        if (!linkedList.is_empty()) {
                            linkedList.pop(); // Pop an element from the linked list stack
                            cout << "Element popped from the stack successfully." << endl;
                        } else {
                            cerr << "Error: Stack is empty! Cannot pop element from the stack." << endl;
                        }
                        break;
                    default:
                        cerr << "Invalid data structure type." << endl;
                        break;
                }
                break;
            case 4:
                switch (DataTYPE) {
                    case FIXED_ARRAY:
                        if (!fixed.is_empty()) {
                            cout << "Top element of the stack: " << fixed.peek().toString()
                                 << endl; // Peek at the top element of the fixed-size array stack
                        } else {
                            cerr << "Error: Stack is empty! Cannot peek at the top element." << endl;
                        }
                        break;
                    case DYNAMIC_ARRAY:
                        if (!dynamic.is_empty()) {
                            cout << "Top element of the stack: " << dynamic.peek().toString()
                                 << endl; // Peek at the top element of the dynamic array stack
                        } else {
                            cerr << "Error: Stack is empty! Cannot peek at the top element." << endl;
                        }
                        break;
                    case LINKED_LIST:
                        if (!linkedList.is_empty()) {
                            cout << "Top element of the stack: " << linkedList.peek().toString()
                                 << endl; // Peek at the top element of the linked list stack
                        } else {
                            cerr << "Error: Stack is empty! Cannot peek at the top element." << endl;
                        }
                        break;
                    default:
                        cerr << "Invalid data structure type." << endl;
                        break;
                }
                break;
            case 5:
                switch (DataTYPE) {
                    case FIXED_ARRAY:
                        if (fixed.is_empty()) {
                            cout << "Stack is empty." << endl; // Check if the fixed-size array stack is empty
                        } else {
                            cout << "Stack is not empty." << endl;
                        }
                        break;
                    case DYNAMIC_ARRAY:
                        if (dynamic.is_empty()) {
                            cout << "Stack is empty." << endl; // Check if the dynamic array stack is empty
                        } else {
                            cout << "Stack is not empty." << endl;
                        }
                        break;
                    case LINKED_LIST:
                        if (linkedList.is_empty()) {
                            cout << "Stack is empty." << endl; // Check if the linked list stack is empty
                        } else {
                            cout << "Stack is not empty." << endl;
                        }
                        break;
                    default:
                        cerr << "Invalid data structure type." << endl;
                        break;
                }
                break;
        }
    } while (operation != 0);
}

void demonstrationMode() {
    srand(static_cast<unsigned int>(time(nullptr)));
    DynamicArray dynamic;
    cout << "\n**** DEMONSTRATION MODE *****\n";


    cout << "\n\n@@@@@ CREATING AN EMPTY STACK OF DYNAMIC-SIZE ARRAY @@@@@\n\n";
    loadingAnimation();
    dynamic.create_empty();
    cout << "\n**** Stack successfully created! ****\n";


    cout << "\n\n@@@@@ PUSHING 5 IPv4Addresses TO DYNAMIC-SIZE ARRAY @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    for (int i = 0; i < 5; i++) {
        dynamic.push(generateRandomIPv4Address());
    }

    for (const auto& address : dynamic.data) {
        cout << address.octet1 << "." << address.octet2 << "." <<
             address.octet3 << "." << address.octet4 << endl;
    }
    cout << "\n**** Data successfully pushed! ****\n";


    cout << "\n\n@@@@@ POPING THE ELEMENT FROM THE DYNAMIC-SIZE ARRAY @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    cout << dynamic.data[dynamic.countSize() - 1].octet1 << "." << dynamic.data[dynamic.countSize() - 1].octet2 << "." <<
    dynamic.data[dynamic.countSize() - 1].octet3 << "." << dynamic.data[dynamic.countSize() - 1].octet4 << endl;
    dynamic.pop();
    cout << "\n**** Element successfully poped from array! ****\n";

    cout << "\n\n@@@@@ PEEKING AN ELEMENT FROM THE DYNAMIC-SIZE ARRAY @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    cout << dynamic.peek().octet1 << "." << dynamic.peek().octet2 << "." << dynamic.peek().octet3 << "." << dynamic.peek().octet4 << endl;
    cout << "\n**** Element was peeked successfully! ****\n";

    cout << "\n\n@@@@@ CHECKING IF DYNAMIC-ARRAY SIZE STACK IS EMPTY @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();

    if (dynamic.is_empty()) {
        cout << "Stack is empty!" << endl;
    } else {
        cout << "Stack is not empty, there are " << dynamic.countSize() << " elements" << endl;
    }
    cout << "\n**** Array was successfully checked for being empty or not read! ****\n";


    cout << "\n\n@@@@@ EXIT @@@@@\n\n";
}

void totalMemoryUsageMB(int numberOfElements, size_t ArrayMemoryUsage) {
    size_t elementSizeBytes = sizeof(IPv4Address);
    size_t totalMemoryUsageBytes = ArrayMemoryUsage + elementSizeBytes * numberOfElements;
    double totalMemoryUsageMB = static_cast<double>(totalMemoryUsageBytes) / (1024 * 1024);
    cout << "Memory usage of the array: " << totalMemoryUsageMB << " MB" << endl;
}


void benchmarkMode() {

    cout << "\nYou are now in the benchmark mode, time of each operation will be written afterwards\n";
    FixedArray<MAX_SIZE> fixed;
    DynamicArray dynamic;
    LinkedList linkedList;

    int num = getIntInput("Enter a number of element for stack creation(from 1 to 10000): ", 1, 1000);



    for (int arrMode = 2; arrMode >= 0; arrMode--) {
        if (arrMode == 2) {
            cout << "\n\n@@@@@    START BENCHMARK FOR FIXED-SIZE ARRAY     @@@@@\n";
        } else if (arrMode == 1) {
            cout << "\n\n@@@@@    START BENCHMARK FOR DYNAMIC-SIZE ARRAY     @@@@@\n";
        } else {
            cout << "\n\n@@@@@    START BENCHMARK FOR LINKED LIST    @@@@@\n";
        }

        auto startTime = high_resolution_clock::now();

        auto startTimeCreateEmptyStack = high_resolution_clock::now();
            if(arrMode == 2) {
                fixed.create_empty();
            } else if (arrMode == 1) {
                dynamic.create_empty();
            } else {
                linkedList.create_empty();
            }
        auto endTimeCreateEmptyStack = high_resolution_clock::now();

        auto startTimePushElements = high_resolution_clock::now();
        for (int i = 0; i < num; i++) {
            if(arrMode == 2) {
                fixed.push(generateRandomIPv4Address());
            } else if (arrMode == 1) {
                dynamic.push(generateRandomIPv4Address());
            } else {
                linkedList.push(generateRandomIPv4Address());
            }
        }
        auto endTimePushElements = high_resolution_clock::now();



        auto startTimePopElement = high_resolution_clock::now();
        if(arrMode == 2) {
            fixed.pop();
        } else if (arrMode == 1) {
            dynamic.pop();
        } else {
            linkedList.pop();
        }
        auto endTimePopElement = high_resolution_clock::now();



        auto startTimePeekElement = high_resolution_clock::now();
        if(arrMode == 2) {
            fixed.peek();
        } else if (arrMode == 1) {
            dynamic.peek();
        } else {
            linkedList.peek();
        }
        auto endTimePeekElement = high_resolution_clock::now();


        auto startTimeIfStackIsEmpty = high_resolution_clock::now();
        if(arrMode == 2) {
            fixed.is_empty();
        } else if (arrMode == 1) {
            dynamic.is_empty();
        } else {
            linkedList.is_empty();
        }
        auto endTimeIfStackIsEmpty = high_resolution_clock::now();


        auto endTime = high_resolution_clock::now();

        auto durationTotal = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTime - startTime).count();
        auto durationCreateEmptyStack = std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(endTimeCreateEmptyStack - startTimeCreateEmptyStack).count();
        auto durationPushElements = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(endTimePushElements - startTimePushElements).count();
        auto durationPopElement = std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(endTimePopElement - startTimePopElement).count();
        auto durationPeekElement = std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(endTimePeekElement - startTimePeekElement).count();
        auto durationIfStackIsEmpty =  std::chrono::duration_cast<std::chrono::duration<double, std::nano>>(endTimeIfStackIsEmpty - startTimeIfStackIsEmpty).count();


        cout << "\n---------------------------\n";
        cout << "\nTime creating empty stack: " << durationCreateEmptyStack / 1000.0 << " milliseconds\n" <<
             "\nTime pushing elements: " << durationPushElements << " milliseconds\n" <<
             "\nTime poping element: " << durationPopElement / 1000.0 << " milliseconds\n" <<
             "\nTime peeking element: " << durationPeekElement / 1000.0 << " milliseconds\n" <<
             "\nTime checking if stack is empty: " << durationIfStackIsEmpty / 1000.0 << " milliseconds\n" <<
             "\nTotal array time: " << durationTotal / 1000.0 << "seconds\n";

        if (arrMode == 2) {
            totalMemoryUsageMB(fixed.countSize(), sizeof(fixed));
        } else if (arrMode == 1) {
            totalMemoryUsageMB(dynamic.countSize(), sizeof(dynamic));
        } else {
            totalMemoryUsageMB(linkedList.countSize(), sizeof(linkedList));
        }
        cout << "\n---------------------------\n";

    }



    cout << "\n\n    BENCHMARK IS ENDED UP WITH THE ABOVE-MENTIONED RESULTS    \n";

}