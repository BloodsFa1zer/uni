#include <iostream>
#include "struct.h"
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

void DatabaseManagement(const string& filename, const string& DatabaseType) {

    // Determine the file mode based on the database type
    ios_base::openmode fileMode;
    if (DatabaseType == "txt") {
        fileMode = ios::out | ios::app;
    } else if (DatabaseType == "binary") {
        fileMode = ios::out | ios::app | ios::binary;
    } else {
        cerr << "\n### There is no such database: " << DatabaseType << ". ###\n";
    }


    fstream outputFile(filename, fileMode);
    if (!outputFile.is_open())
    {
        cerr << "\n### Failed to open the specified file: " << filename << ". ###\n";
        return;
    }

    vector<Monster> tempStorage;

    storeData(filename, tempStorage, txtDatabase);
    int operation;

    cout << "\nHere you can manage the text database.\n";
    do {
        cout << "Please select a operation: \n"
                "1. INSERT monster \n"
                "2. Record database to the file\n"
                "3. Restore database to the database buffer\n"
                "4. SELECT all the monsters\n"
                "5. SELECT monster by criteria\n"
                "6. UPDATE monster\n"
                "7. DELETE all database buffer or DELETE monster\n"
                "0. Exit\n";

        operation = getIntInput("Please enter a number of operation: ", 0, 7);

        switch (operation) {
            case 0:
                break;
            case 1:
                insertMonster(tempStorage, true);
                break;
            case 2:
                loadData(filename, tempStorage, DatabaseType);
                storeData(filename, tempStorage, DatabaseType);
                break;
            case 3:
                storeData(filename, tempStorage, DatabaseType);
                break;
            case 4:
                SelectAllMonsters(tempStorage); // Select * From monster
                break;
            case 5:
                selectMonsterBy(tempStorage);
                break;
            case 6:
                updateMonster(tempStorage);
                cout << "!!! DO NOT FORGET TO SAVE DATABASE AFTER UPDATING MONSTER DATA !!!" << endl;
                break;
            case 7:
                deleteMonster(tempStorage);
                cout << "!!! DO NOT FORGET TO SAVE DATABASE AFTER DELETING MONSTER !!!" << endl;
                break;
        }
    } while (operation != 0);

    cout << "\n***** " << filename << " has been created/updated! *****\n";
    outputFile.close();
}
