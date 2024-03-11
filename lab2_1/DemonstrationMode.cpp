#include <iostream>
#include "struct.h"
#include <string>
#include <ctime>
#include <fstream>

using namespace std;
using namespace chrono;


void demoMode() {
    vector<Monster> localStorage, demoDB;
    cout << "\n**** DEMONSTRATION MODE *****\n";

    cout << "\n\n@@@@@ INSERTING 10 MONSTERS TO LOCAL DATABASE @@@@@\n\n";
    loadingAnimation();
    loadingAnimation();
    loadingAnimation();
    for (int i = 0; i < 10; i++) {
        insertMonster(localStorage, false);
    }
    cout << "\n**** Monsters successfully inserted! ****\n";

    cout << "\n\n@@@@@ SAVING THE DATABASE @@@@@\n\n";
    loadingAnimation();
    demoDB = localStorage;
    cout << "\n**** Database successfully written to local storage! ****\n";

    cout << "\n\n@@@@@ RECORDING THE LOCAL DATABASE @@@@@\n\n";
    loadingAnimation();
    localStorage = demoDB;
    cout << "\n**** Database was recorded successfully! ****\n";

    cout << "\n\n@@@@@ PRINTING THE DATABASE @@@@@\n\n";
    loadingAnimation();
    SelectAllMonsters(localStorage);
    cout << "\n**** All the monsters were successfully read! ****\n";

    cout << "\n\n@@@@@ SELECTING MONSTER WITH THE LETTER 'm' IN THE NAME @@@@@\n\n";
    loadingAnimation();
    searchByNameEnding(localStorage, "m");

    cout << "\n\n@@@@@ SELECTING MONSTER WITH THE SPECIAL ATTACK TYPE 'Fire' @@@@@\n\n";
    loadingAnimation();
    searchBySpecialAttackType(localStorage, "Fire");

    cout << "\n\n@@@@@ SELECTING MONSTER WITH THE SPECIAL ATTACK CHANCE HIGHER THAN '0.5' @@@@@\n\n";
    loadingAnimation();
    searchBySpecialAttackPercentage(localStorage, 0.5);

    cout << "\n\n@@@@@ SELECTING MONSTER WITH THE TIME APPEARANCE FROM NOW TO 3 HOURS IN THE FUTURE @@@@@\n\n";
    auto currentTime = system_clock::now();
    auto threeHoursInFuture = currentTime + hours(3);
    time_t threeHoursInFutureT = system_clock::to_time_t(threeHoursInFuture);
    time_t currentTimeT = system_clock::to_time_t(currentTime);
    loadingAnimation();
    searchByAppearanceTime(localStorage, currentTimeT, threeHoursInFutureT);



    cout << "\n\n@@@@@ UPDATING MONSTER`S TO 'Monster_1' WITH RANDOM ID IN LOCAL DATABASE @@@@@\n\n";
    loadingAnimation();
    int randomNum = rand() % 10 + 1;
    localStorage[randomNum].name = "Monster_1";
    cout << "\n**** Name changed successfully! ****\n";

    cout << "\n\n@@@@@ DELETING MONSTER WITH RANDOM ID FROM THE LOCAL DATABASE @@@@@\n\n";
    loadingAnimation();
    randomNum = rand() % 10 + 1;
    localStorage.erase(localStorage.begin() + randomNum);
    cout << "\n**** Element with ID 5 was deleted! ****\n";

    cout << "\n\n@@@@@ SAVING THE DATABASE @@@@@\n\n";
    loadingAnimation();
    demoDB = localStorage;
    cout << "\n**** Database was successfully written to local storage! ****\n";

    cout << "\n\n@@@@@ PRINTING THE DATABASE @@@@@\n\n";
    loadingAnimation();
    SelectAllMonsters(localStorage);
    cout << "\n**** All the monsters were successfully read! ****\n";

    cout << "\n\n@@@@@ EXIT @@@@@\n\n";
}