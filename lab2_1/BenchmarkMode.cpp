#include <iostream>
#include "struct.h"
#include <string>
#include <fstream>

using namespace std;
using namespace chrono;


time_t generateRandomTime() {
    // Get the current system time
    auto currentTime = system_clock::now();
    // Convert current time to time_t
    time_t currentTimestamp = system_clock::to_time_t(currentTime);
    return currentTimestamp;
}

string generateRandomString(int length) {
    const string characters = "abcdefghijklmnopqrstuvwxyz";
    string result;
    for (int i = 0; i < length; ++i) {
        result += characters[rand() % characters.size()];
    }
    return result;
}

double calculateBufferSize(const vector<Monster>& buffer, int num) {
    // Calculate the size of a single element in bytes
    size_t elementSize = sizeof(buffer[0]);

    // Calculate the total size of the buffer vector in bytes
    size_t totalSizeBytes = elementSize * num;

    // Convert the total size to megabytes
    double totalSizeMB = static_cast<double>(totalSizeBytes) / (1024.0 * 1024.0);

    return totalSizeMB;
}



void benchmarkMode() {
    cout << "\nYou are now in the benchmark dbMode, time of each operation will be written afterwards\n";

    string txt = "Benchmark.txt", bin = "Benchmark.bin";
    fstream benchmarkTxt(txt, ios::app), benchmarkBin(bin, ios::app | ios::binary);
    vector<Monster> benchmarkVector;

    int num = getIntInput("Enter a number of element for database(from 1 to 1000): ", 1, 1000);



    auto startTime = high_resolution_clock::now();



    for (int dbMode = 2; dbMode >= 0; dbMode--) {
        vector<Monster> buffer;
        buffer.reserve(num);
        string file = txt;
        if (dbMode == 2) {
            cout << "\n\n@@@@@    START BENCHMARK IN .txt DATABASE     @@@@@\n";
        } else if (dbMode == 1) {
            cout << "\n\n@@@@@    START BENCHMARK IN .bin DATABASE    @@@@@\n";
            file = bin;
        } else {
            cout << "\n\n@@@@@    START BENCHMARK IN LOCAL DATABASE    @@@@@\n";
            buffer.clear();
        }

        auto startTimeInsert = high_resolution_clock::now();
        for (int i = 0; i < num; i++) {
            insertMonster(buffer, false);
        }
        auto endTimeInsert = high_resolution_clock::now();


        auto startTimeLoad = high_resolution_clock::now();
        if (dbMode != 0) {
            loadData((dbMode == 2) ? txt : bin, buffer, (dbMode == 2) ? txtDatabase : binDatabase);
        } else {
            benchmarkVector = buffer;
        }
        auto endTimeLoad = high_resolution_clock::now();



        auto startTimeStoreData = high_resolution_clock::now();
        if (dbMode != 0) {
            storeData((dbMode == 2) ? txt : bin, buffer, dbMode == 2 ? txtDatabase : binDatabase);
        } else {
            buffer = benchmarkVector;
        }
        auto endTimeStoreData = high_resolution_clock::now();



        auto startTimeSelectByAll = high_resolution_clock::now();

        auto startTimeSearchByNameEnding = high_resolution_clock::now();
        string nameToLookFor = generateRandomString(rand() % 10 + 1);
        cout << "Looking for name ending:" << nameToLookFor << endl;
        searchByNameEnding(buffer, nameToLookFor);
        auto endTimeSearchByNameEnding = high_resolution_clock::now();

        auto startTimeSearchBySpecialAttackType = high_resolution_clock::now();
        string specialAttackTypes[4] = {"Fire", "Ice", "Fire", "Electric"};
        int randomSearch = rand() % 3 + 1;
        cout << "Looking for monster with that special attack type:" << specialAttackTypes[randomSearch] << endl;
        searchBySpecialAttackType(buffer, specialAttackTypes[randomSearch]);
        auto endTimeSearchBySpecialAttackType = high_resolution_clock::now();

        auto startTimeSearchBySpecialAttackPercentage = high_resolution_clock::now();
        double minSpecialAttackChance = static_cast<double>(rand()) / RAND_MAX;
        cout << "Looking for monster with that special attack chance and higher:" << minSpecialAttackChance << endl;
        searchBySpecialAttackPercentage(buffer, minSpecialAttackChance);
        auto endTimeSearchBySpecialAttackPercentage = high_resolution_clock::now();

        auto startTimeSearchByAppearanceTime = high_resolution_clock::now();
        time_t startT = generateRandomTime();
        time_t endT = startT + 7200;
        cout << "Looking for monster with that appearance time range : " << formatTime(startT) << " --- " << formatTime(endT) << endl;
        searchByAppearanceTime(buffer, startT, endT);
        auto endTimeSearchByAppearanceTime = high_resolution_clock::now();

        auto endTimeSelectByAll = high_resolution_clock::now();


        auto endTime = high_resolution_clock::now();



        auto durationTotal = duration_cast<milliseconds>(endTime - startTime).count();
        auto durationInsert = duration_cast<milliseconds>(endTimeInsert - startTimeInsert).count();
        auto durationRecord = duration_cast<milliseconds>(endTimeLoad - startTimeLoad).count();
        auto durationRestore = duration_cast<milliseconds>(endTimeStoreData - startTimeStoreData).count();
        auto durationSearchByNameEnding = duration_cast<milliseconds>(endTimeSearchByNameEnding - startTimeSearchByNameEnding).count();
        auto durationSearchBySpecialAttackType = duration_cast<milliseconds>(endTimeSearchBySpecialAttackType - startTimeSearchBySpecialAttackType).count();
        auto durationSearchBySpecialAttackPercentage = duration_cast<milliseconds>(endTimeSearchBySpecialAttackPercentage - startTimeSearchBySpecialAttackPercentage).count();
        auto durationSearchByAppearanceTime = duration_cast<milliseconds>(endTimeSearchByAppearanceTime - startTimeSearchByAppearanceTime).count();
        auto durationSelectByAll = duration_cast<milliseconds>(endTimeSelectByAll - startTimeSelectByAll).count();

        cout << "\n---------------------------\n";
        cout << "\nTime insert: " << durationInsert << " milliseconds\n" <<
             "\nRecording time: " << durationRecord << " milliseconds\n" <<
             "\nRestore time: " << durationRestore << " milliseconds\n" <<
             "\nSelect time by monster name: " << durationSearchByNameEnding << " milliseconds\n" <<
             "\nSelect time by special attack type: " << durationSearchBySpecialAttackType << " milliseconds\n" <<
             "\nSelect time by special attack percentage: " << durationSearchBySpecialAttackPercentage << " milliseconds\n" <<
             "\nSelect time by monster appearance time: " << durationSearchByAppearanceTime << " milliseconds\n" <<
             "\nTotal select by criteria time: " << durationSelectByAll << " milliseconds\n" <<
             "\nTotal db time: " << durationTotal / 1000.0 << "seconds\n";

        if (dbMode == 0) {
            cout << "\nSize: " << calculateBufferSize(buffer, num) << " Mb \n";
        }
        cout << "\n---------------------------\n";

    }
    benchmarkBin.close();
    benchmarkTxt.close();


    cout << "\n\n    BENCHMARK IS ENDED UP WITH THE ABOVE-MENTIONED RESULTS    \n";

}

