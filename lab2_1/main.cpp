//Інформація про монстрів у комп’ютерній грі.
// Зберігаються наступні дані про кожного монстра: ім’я; кількість одиниць здоров’я (ціле число, не більше 50000);
// кількість одиниць атаки (ціле число, не більше 2000); шанс виконати спеціальну атаку (дійсне число від 0 до 1),
// тип спеціальної атаки – збільшити пошкодження, повторити атаку, вилікувати себе, паралізувати супротивника;
// дата та час появи у грі.
//
// Критерії пошуку:
//Монстри з іменем, що завершується на заданий фрагмент тексту;
// монстри із заданим типом спеціальної атаки та шансом виконання не менше заданого;
// монстри, що з’явились у грі під час заданого діапазону часу.


#include <iostream>
#include "struct.h"
#include <vector>
#include <thread>


using namespace std;
using namespace chrono;



void loadingAnimation() {
    for (int i = 0; i < 3; ++i) {
        cout << "Loading.";
        this_thread::sleep_for(chrono::milliseconds(250));
        cout << "\r";
        cout.flush();

        cout << "Loading..";
        this_thread::sleep_for(chrono::milliseconds(250));
        cout << "\r";
        cout.flush();

        cout << "Loading...";
        this_thread::sleep_for(chrono::milliseconds(250));
        cout << "\r";
        cout.flush();
    }
}



time_t getTimeInput(const string& prompt) {
    struct tm timeinfo = {0};
    string input;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (true) {
        cout << "Enter the date and time (YYYY MM DD HH MM SS) (example 2024 10 10 12 30 45): ";

        // Read the entire line of input
        getline(cin, input);
        cout << "Input received: " << input << endl; // Debugging output

        istringstream ss(input);
        ss >> timeinfo.tm_year >> timeinfo.tm_mon >> timeinfo.tm_mday
           >> timeinfo.tm_hour >> timeinfo.tm_min >> timeinfo.tm_sec;

        if (ss.fail()) {
            cerr << "Invalid input format. Please enter the date and time in the format: YYYY MM DD HH MM SS\n";
        } else {
            timeinfo.tm_year -= 1900;
            timeinfo.tm_mon -= 1;

            // Convert struct tm to time_t
            time_t result = mktime(&timeinfo);
            if (result == -1) {
                cerr << "Invalid date and time. Please enter a valid date and time.\n";
            } else {
                return result;
            }
        }
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

double getDoubleInput(const string& prompt, double minValue, double maxValue) {
    double value;
    bool inputIsValid;
    do {
        cout << prompt;
        if (cin >> value && value >= minValue && value <= maxValue) {
            inputIsValid = true;
        } else {
            cerr << "\n### Invalid input. Please enter a valid number between "
                 << minValue << " and " << maxValue << ". ###\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            inputIsValid = false;
        }
    } while (!inputIsValid);
    return value;
}

string getStringInput(const string& prompt) {
    string value;
    cout << prompt;
    cin >> value;
    return value;
}

string formatTime(time_t t) {
    char buffer[80]; // Buffer to hold formatted time
    tm* localTime = localtime(&t);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime); // Format time
    return buffer;
}

void DatabaseManagement(const string& filename, const string& DatabaseType);
void localDatabase();


void benchmarkMode();



void demoMode();



int main() {
    srand(time(nullptr));
    int mode;
    string filename;
    mode = getIntInput("Select database mode:\n"
                              "1. Database user management\n"
                              "2. Demonstration mode \n"
                              "3. Benchmark mode:\n", 1, 3);

    switch (mode)
    {
        case 1:
            int modeManagement;
            modeManagement = getIntInput("Select a number of database:\n"
                "1. Local Database \n"
                "2. Database in .txt format\n"
                "3. Database in .bin format\n", 1, 3);
            switch (modeManagement)
            {
                case 1:
                    localDatabase();
                    break;
                case 2:
                    filename = "database.txt";
                    DatabaseManagement(filename, txtDatabase);
                    break;
                case 3:
                    filename = "database.bin";
                    DatabaseManagement(filename, binDatabase);
                    break;
            }
            break;
        case 2:
            demoMode();
            break;
        case 3:
            benchmarkMode();
            break;
    }
}

void loadData(const string& source, vector<Monster>& storage, const string& DatabaseType) {
    ofstream clearFile(source, ios::trunc);
    clearFile.close();
    ios_base::openmode fileMode = DatabaseType == txtDatabase ? ios::out : ios::out | ios::binary;
    ofstream dataFile(source, fileMode);

    if (!dataFile.is_open())
    {
        cerr << "\n### Error opening the file '" << source << "'! ###\n";
        return;
    }

    for (const Monster& monster : storage)
    {
        dataFile << monster.id << ' ' << monster.name << ' ' << monster.health << ' '
                 << monster.attack << ' ' << monster.specialAttackChance << ' '
                 << monster.specialAttackType << ' ' << monster.appearanceTime << '\n';
    }

    dataFile.close();
}


void insertMonster(vector<Monster>& monsterCollection, bool isUserMode) {
    Monster newMonster;
    if (isUserMode) {
        newMonster.initializeFromUserInput();
    } else {
        newMonster = benchmarkGenerationMonster();
    }


    if (monsterCollection.empty()){
        newMonster.id = 1;
    } else {
        newMonster.id = monsterCollection.back().id + 1;
    }
    monsterCollection.push_back(newMonster);
    newMonster.printMonsterData();
}


void storeData(const string& filename, vector<Monster>& monsterData, const string& DatabaseType) {
    ios_base::openmode fileMode = (DatabaseType == "txt") ? ios::out : ios::out | ios::binary;
    ofstream outputFile(filename, fileMode);

    if (!outputFile.is_open()) {
        cerr << "\n### Error: Unable to open the file '" << filename << "'! ###\n";
        return;
    }

    for (const Monster& monster : monsterData) {
        formatTime(monster.appearanceTime);
        outputFile << monster.id << ' ' << monster.name << ' ' << monster.health << ' '
                   << monster.attack << ' ' << monster.specialAttackChance << ' '
                   << monster.specialAttackType << ' ' << formatTime(monster.appearanceTime) << '\n';
    }

    outputFile.close();
}



void SelectAllMonsters(vector<Monster>& readVector) {
    if (readVector.empty()) {
        cout << "\n There is nothing to read, db is clear!\n";
    } else {
        cout << "\nAll the monsters:\n";
        for (size_t i = 0; i < readVector.size(); ++i) {
            readVector[i].printMonsterData();
        }
    }
}


void searchByNameEnding(vector<Monster>& localDatabase, const string& fragment) {
    vector<Monster> result;

    for (auto& monster : localDatabase) {
        // Check if the name ends with the given fragment
        if (monster.name.size() >= fragment.size() && monster.name.substr(monster.name.size() - fragment.size()) == fragment) {
            result.push_back(monster);
            monster.printMonsterData();
        }
    }

    if (result.empty()) {
        cout << "No monsters found within the specified name ending." << endl;
    }
}

void searchBySpecialAttackType(vector<Monster>& database, const string& specialAttackType) {
    vector<Monster> result;

    for (auto& monster : database) {
        // Check if the monster's special attack type matches the given type
        if (monster.specialAttackType == specialAttackType) {
            result.push_back(monster);
            monster.printMonsterData();
        }
    }

    if (result.empty()) {
        cout << "No monsters found within the specified special attack type." << endl;
    }
}

void searchBySpecialAttackPercentage( vector<Monster>& database, double minSpecialAttackChance) {
    vector<Monster> result;

    for (auto& monster : database) {
        // Check if the monster's special attack percentage is greater than or equal to the minimum value
        if (monster.specialAttackChance >= minSpecialAttackChance) {
            result.push_back(monster);
            monster.printMonsterData();
        }
    }

    if (result.empty()) {
        cout << "No monsters found within the specified special attack percentage ." << endl;
    }
}

void searchByAppearanceTime(vector<Monster>& monsters, time_t startTime, time_t endTime) {
    vector<Monster> result;

    for (auto& monster : monsters) {
        // Check if the appearance time is within the specified range
        if (monster.appearanceTime >= startTime && monster.appearanceTime <= endTime) {
            result.push_back(monster);
            monster.printMonsterData();
        }
    }

    if (result.empty()) {
        cout << "No monsters found within the specified time range." << endl;
    }
}


void selectMonsterBy(vector<Monster>& localDatabase) {
    int choice;
    cout << "Choose search criteria:\n"
            "1. Search by name ending\n"
            "2. Search by special attack type\n"
            "3. Search by special attack chance\n"
            "4. Search by appearance time range\n"
            "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            searchByNameEnding(localDatabase, getStringInput("Enter the fragment of the name to search for: "));
            break;
        }
        case 2: {
            searchBySpecialAttackType(localDatabase, getStringInput("Enter the special attack type to search for: "));
            break;
        }
        case 3: {
            searchBySpecialAttackPercentage(localDatabase, getDoubleInput("Enter the minimum special attack percentage to search for (between 0.0 and 1.0):", 0.0, 1.0));
            break;
        }
        case 4: {
            time_t startTime = getTimeInput("");
            time_t endTime = getTimeInput("");
            searchByAppearanceTime(localDatabase, startTime, endTime);
            break;
        }
        default:
            cout << "Invalid choice\n";
            break;
    }

}


void updateMonster(vector<Monster>& localDatabase) {
    if (localDatabase.empty()) {
        cout << "\n### The database is empty! ###\n";
        return;
    }

    int idModify = getIntInput("\nEnter the ID of the item you want to change: ", 0, 1000);
    int updateNumber;
    bool found = false;

    for (auto& monster : localDatabase) {
        if (monster.id == idModify) {
            found = true;
            cout << "\n There is a monster with that ID: \n";
            monster.printMonsterData();
            do {
                cout << "\nWhat updates you wanna make?\n"
                     << "1. Monster name\n"
                     << "2. Monster health\n"
                     << "3. Monster attack\n"
                     << "4. Monster chance of special attack\n"
                     << "5. Monster type of special attack\n"
                     << "0. Exit\n";
                updateNumber = getIntInput("Enter operation: ", 0, 5);

                switch (updateNumber) {
                    case 0:
                        cout << "\n=== No changes made. ===\n";
                        break;
                    case 1:
                        monster.name = getStringInput("Enter a new name: ");
                        cout << "\n=== Monster name has been updated ===\n";
                        break;
                    case 2:
                        monster.health = getIntInput("Enter a new unit: ", 0, 50000);
                        cout << "\n=== Monster health has been updated ===\n";
                        break;
                    case 3:
                        monster.attack = getIntInput("Enter a new monster attack: ", 0, 2000);
                        cout << "\n=== Monster attack has been updated ===\n";
                        break;
                    case 4:
                        monster.specialAttackChance = getDoubleInput("Enter a new chance of special attack: ", 0.0, 1.0);
                        cout << "\n=== Monster special Attack Chance has been updated  ===\n";
                        break;
                    case 5:
                        monster.specialAttackType = getStringInput("Enter a new type of special attack: ");
                        cout << "\n=== Monster special Attack type has been updated  ===\n";
                        break;
                    default:
                        cout << "\n### Invalid operation! Please enter a valid operation number. ###\n";
                        break;
                }
            } while (updateNumber != 0);
        }
    }

    if (!found) {
        cout << "\n### Product with ID " << idModify << " does not exist! ###\n";
    }

}


void deleteMonster(vector<Monster>& localDatabase) {
    int deleteNumber;
    cout << "\nSelect operation for delete:\n"
            "1. Delete element in database buffer\n"
            "2. Delete all database buffer\n"
            "0. Exit\n";
    deleteNumber = getIntInput("Enter operation: ", 0, 2);

    switch (deleteNumber) {
        case 0:
            return;
        case 1: {
            int delId;
            delId = getIntInput("Enter the ID of the monster you want to be deleted: ", 0, 1000);

            auto it = find_if(localDatabase.begin(), localDatabase.end(), [&](const Monster& monster) {
                return monster.id == delId;
            });

            if (it != localDatabase.end()) {
                localDatabase.erase(it);
                cout << "\n=== Monster with ID " << delId << " deleted! ===\n";
            } else {
                cout << "\n### Monster with ID " << delId << " not found! ###\n";
            }
            break;
        }
        case 2:
            localDatabase.clear();
            cout << "\n=== Database buffer cleared successfully! ===\n";
            break;
        default:
            cout << "\n### Invalid operation! Please enter a valid operation number. ###\n";
            break;
    }
}

Monster benchmarkGenerationMonster() {
    Monster randomElement;
    const int maxID = 1000; // Maximum ID value
    randomElement.id = rand() % maxID + 1; // Generate random ID between 1 and maxID
    randomElement.name = "Monster_" + to_string(randomElement.id); // Random name based on id
    randomElement.health = rand() % 50001; // Random health between 0 and 50000
    randomElement.attack = rand() % 2001;   // Random attack between 0 and 2000
    randomElement.specialAttackChance = (rand() % 1001) / 1000.0; // Random double between 0 and 1
    // Sample special attack types
    string specialTypes[] = {"Fire", "Ice", "Poison", "Electric"};
    randomElement.specialAttackType = specialTypes[rand() % 4]; // Randomly choose a special attack type

    // Generate appearance time
    randomElement.appearanceTime = time(nullptr) + (rand() % 86400);  // Add a random number of seconds (up to 1 day)

    return randomElement;
}



void localDatabase() {
    vector<Monster> localDb;
    vector<Monster> Database;
    vector<Monster> tmp;
    int dbManagment;

    do {
        cout << "\nHere you can manage the text database. Please select an option: \n"
                "1. INSERT monster \n"
                "2. Record database to the file\n"
                "3. Restore database to the database buffer\n"
                "4. SELECT all the monsters\n"
                "5. SELECT monster by criteria\n"
                "6. UPDATE monster\n"
                "7. DELETE all database buffer\n"
                "0. Exit\n";
        dbManagment = getIntInput("Please enter a number of option: ", 0, 7);

        switch (dbManagment) {
            case 1:
                insertMonster(localDb, true);
                break;
            case 2:
                Database = localDb;
                break;
            case 3:
                Database = tmp;
                break;
            case 4:
                SelectAllMonsters(localDb);
                break;
            case 5:
                selectMonsterBy(localDb);
                break;
            case 6:
                updateMonster(localDb);
                break;
            case 7:
                deleteMonster(localDb);
                break;
        }
    } while (dbManagment != 0);

}