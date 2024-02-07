//#include <iostream>
//#include <cstdlib>
//
//using namespace std;
//
//int Solve(char str[], int s);
//
//int main() {
//    const int n = 100;
//    char str[n];
//    cout << "Enter string: ";
//    cin >> str;
//    int s = strlen(str);
//    cout << Solve(str, s);
//    return 0;
//}
//
//int Solve(char str[], int s) {
//    int answer = atoi(str);
//
//    char buff[1];
//    for (int i = 1; i < s; i++) {
//        if (str[i] == '+') {
//            buff[0] = str[i+1];
//            answer += atoi(buff);
//        }
//        else {
//            buff[0] = str[i+1];
//            answer -= atoi(buff);
//        }
//    }
//    return answer;
//}
//
//
////#include <iostream>
////#include <vector>
////
////using namespace std;
////
////bool isNumberPrime(int num) {
////
////    for (int i = 2; i < num; i++) {
////        if (num % i == 0) {
////            return false;
////        }
////    }
////    return true;
////}
////
////int AppropriateNumber(int num) {
////    bool prime = true;
////    for (int j = 2; j * j <= num; j++) {
////        if (num % j == 0) {
////            prime = false;
////            break;
////        }
////
////    }
////
////    if (prime) {
////        cout << "1/" << num;
////        return num;
////    }
////    return 0;
////}
////
////int main() {
////    cout << "Enter your Number. It Must be simple!" << endl;
////    int num;
////    cin >> num;
////    if (!isNumberPrime(num)) {
////    }
////    int i = 2;
////    int sumDown = 1, sumUp = 0;
////    vector<int> primeNums;
////    while (num >= i) {
////        int gotNum = AppropriateNumber(i);
////        i++;
////        if (gotNum != 0) {
////            primeNums.push_back(gotNum);
////            if (gotNum != num) {
////                cout << " + ";
////            } else {
////                cout << " = ";
////            }
////        }
////    }
////
////    for (int j = 0; j <= primeNums.size() - 1; j++) {
////        if (j > 1) {
////            sumUp = 1 * sumDown + (sumUp * primeNums[j]);
////        } else {
////            sumUp += 1 * primeNums[j];
////        }
////        sumDown *= primeNums[j];
////    }
////
////    cout << sumUp << "/" << sumDown << endl;
////
////    return 0;
////}
////
////
//////bool isPrime(int n){
//////    //since 0 and 1 is not prime return false.
//////    if(n==1||n==0)return false;
//////
//////    //Run a loop from 2 to square root of n.
//////    for(int i=2; i*i<=n; i++){
//////        // if the number is divisible by i, then n is not a prime number.
//////        if(n%i==0)return false;
//////    }
//////    //otherwise, n is prime number.
//////    return true;
//////}
//////
//////
//////// Driver code
//////int main()
//////{
//////    int N = 100;
//////
//////    //check for every number from 1 to N
//////    for(int i=1; i<=N; i++){
//////        //check if current number is prime
//////        if(isPrime(i)) {
//////            cout << i << " ";
//////        }
//////    }
//////
//////    return 0;
//////}


//#include <iostream>
//#include <vector>
//
//bool isPerfect(int num) {
//    int sum = 1; // Починаємо з 1, оскільки 1 завжди є дільником
//    for (int i = 2; i * i <= num; ++i) {
//        if (num % i == 0) {
//            sum += i;
//            if (i * i != num) {
//                sum += num / i;
//            }
//        }
//    }
//    return sum == num;
//}
//
//std::vector<int> findPerfectNumbers(int N) {
//    std::vector<int> perfectNumbers;
//
//    for (int i = 2; i < N; ++i) {
//        if (isPerfect(i)) {
//            perfectNumbers.push_back(i);
//        }
//    }
//
//    return perfectNumbers;
//}
//
//int main() {
//    int N;
//    std::cout << "Введіть число N: ";
//    std::cin >> N;
//
//    std::vector<int> result = findPerfectNumbers(N);
//
//    std::cout << "Досконалі числа, менше ніж " << N << ": ";
//    for (int num : result) {
//        std::cout << num << " ";
//    }
//    std::cout << std::endl;
//
//    return 0;
//}


#include <iostream>

using namespace std;

//bool isPalindrome(int number) {
//    int originalNumber = number;
//    int reversedNumber = 0;
//
//    while (number > 0) {
//        int digit = number % 10;
//        reversedNumber = reversedNumber * 10 + digit;
//        number /= 10;
//    }
//
//    return originalNumber == reversedNumber;
//}
//
//void findPalindromeSquares(int limit) {
//    for (int i = 1; i <= limit; ++i) {
//        int square = i * i;
////        int squareRoot = static_cast<int>(sqrt(i));
//
//        if (isPalindrome(i) && isPalindrome(square)) {
//            std::cout << i << "^2 = " << square << " (паліндром)" << std::endl;
//        }
//    }
//}

//int main() {
//    char words[] = "string fdfmdf? fmwid, s. But i do wanna touch!";
////    int limit;
////    std::cout << "Введіть максимальне значення: ";
////    std::cin >> limit;
////
////    std::cout << "Цілі числа-паліндроми та їхні квадрати та корені:" << std::endl;
////    findPalindromeSquares(limit);
//
//    return 0;
//}


//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//bool isNumberPrime(int num) {
//
//    for (int i = 2; i < num; i++) {
//        if (num % i == 0) {
//            return false;
//        }
//    }
//    return true;
//}
//
//int AppropriateNumber(int num) {
//    bool prime = true;
//    for (int j = 2; j * j <= num; j++) {
//        if (num % j == 0) {
//            prime = false;
//            break;
//        }
//
//    }
//
//    if (prime) {
//        cout << "1/" << num;
//        return num;
//    }
//    return 0;
//}
//
//int main() {
//    cout << "Enter your Number. It Must be simple!" << endl;
//    int num;
//    cin >> num;
//    if (!isNumberPrime(num)) {
//    }
//    int i = 2;
//    int sumDown = 1, sumUp = 0;
//    vector<int> primeNums;
//    while (num >= i) {
//        int gotNum = AppropriateNumber(i);
//        i++;
//        if (gotNum != 0) {
//            primeNums.push_back(gotNum);
//            if (gotNum != num) {
//                cout << " + ";
//            } else {
//                cout << " = ";
//            }
//        }
//    }
//
//    for (int j = 0; j <= primeNums.size() - 1; j++) {
//        if (j > 1) {
//            sumUp = 1 * sumDown + (sumUp * primeNums[j]);
//        } else {
//            sumUp += 1 * primeNums[j];
//        }
//        sumDown *= primeNums[j];
//    }
//
//    cout << sumUp << "/" << sumDown << endl;
//
//    return 0;
//}

//bool isPrime(int n) {
//    //since 0 and 1 is not prime return false.
//    if (n == 1 || n == 0) {
//        return false;
//    }
//
//    //Run a loop from 2 to square root of n.
//    for (int i = 2; i * i <= n; i++) {
//        // if the number is divisible by i, then n is not a prime number.
//        if (n % i == 0) {
//            return false;
//        }
//    }
//
//    //otherwise, n is prime number.
//    return true;
//}
//
//
//// Driver code
//int main()
//{
//    int N = 100;
//    int sum = 0;
//
//    //check for every number from 1 to N
//    for(int i=1; i<=N; i++){
//        //check if current number is prime
//        if(isPrime(i)) {
//            sum += i;
//        }
//    }
//
//    cout << sum << endl;
//
//    return 0;
//}


#include <stdio.h>

// Структура для представлення раціональної дробі
 struct Rational {
    int numerator;   // Чисельник
    int denominator; // Знаменник
};

// Функція для знаходження найбільшого спільного дільника (НСД) двох чисел
int gcd(int a, int b) {
    // b > a
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Функція для скорочення раціональної дробі
Rational reduceFraction(Rational fraction) {
    // Знаходимо НСД чисельника і знаменника
    int commonFactor = gcd(fraction.numerator, fraction.denominator);

    // Ділимо чисельник і знаменник на НСД, щоб скоротити дріб
    fraction.numerator /= commonFactor;
    fraction.denominator /= commonFactor;

    return fraction;
}

int main() {
    // Приклад використання функції для скорочення раціональної дробі
    Rational fraction = {14, 28}; // Раціональна дріб 12/18

    printf("Дріб до скорочення: %d/%d\n", fraction.numerator, fraction.denominator);

    // Застосовуємо функцію для скорочення дробу
    fraction = reduceFraction(fraction);

    printf("Скорочений дріб: %d/%d\n", fraction.numerator, fraction.denominator);

    return 0;
}

//int gcd(int a, int b) {
//    while (b != 0) {
//        int temp = b;
//        b = a % b;
//        a = temp;
//    }
//    return a;
//}
//
//// Функція для знаходження НСК
//int lcm(int a, int b) {
//    // Знаходимо НСД
//    int commonFactor = gcd(a, b);
//
//    // Знаходимо НСК
//    int result = (a * b) / commonFactor;
//
//    return result;
//}
//
//int main() {
//    int num1 = 24;
//    int num2 = 48;
//
//    // Знаходимо НСК для num1 і num2
//    int result = lcm(num1, num2);
//
//    printf("НСК(%d, %d) = %d\n", num1, num2, result);
//
//    return 0;
//}


//#include <stdio.h>
//
//// Структура для представлення дати
//typedef struct {
//    int day;
//    int month;
//    int year;
//} Date;
//
//// Функція для визначення, чи рік є високосним
//int isLeapYear(int year) {
//    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
//}
//
//// Функція для обчислення порядкового номера дня року
//int dayOfYear(Date date) {
//    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//    int ordinalDay = date.day;
//
//    for (int i = 1; i < date.month; i++) {
//        ordinalDay += daysInMonth[i];
//
//        // Додаємо один день до лютого, якщо рік високосний
//        if (i == 2 && isLeapYear(date.year)) {
//            ordinalDay++;
//        }
//    }
//
//    return ordinalDay;
//}
//
//int main() {
//    Date currentDate = {16, 12, 2023}; // Приклад введеної дати (16 грудня 2023 року)
//
//    // Обчислюємо порядковий номер дня року
//    int result = dayOfYear(currentDate);
//
//    printf("Порядковий номер дня року для %02d.%02d.%04d: %d\n", currentDate.day, currentDate.month, currentDate.year, result);
//
//    return 0;
//}
