#include <iostream>
#include <stack>
#include <sstream>

using namespace std;


double power(double base, int topower){
    if (topower == 0) {
        return 1.0;
    } else if (topower == 1) {
        return base;
    } else {
        double result = 1.0;
        while (topower > 0) {
            result *= base;
            topower--;
        }
        return result;
    }
}


int priority(char op) {
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/' || op == '%')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return -1;
}

bool isOperator(char c) {
    return c == '*' || c == '/' || c == '%' || c == '^';
}

bool isUnary(char c) {
    return c == '+' || c == '-';
}

string infixToPostfix(string expression) {
    stack<char> operators;
    stringstream postfix;
    string numBuffer;

    for (size_t i = 0; i < expression.size(); ++i) {
        char c = expression[i];

        if (isdigit(c) || c == '.') {
            numBuffer += c;
        } else {
            if (!numBuffer.empty()) {
                postfix << numBuffer << " ";
                numBuffer.clear();
            }

            if (c == '(') {
                operators.push(c);
            } else if (c == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    postfix << operators.top() << " ";
                    operators.pop();
                }
                operators.pop();
            } else if (isOperator(c)) {
                while (!operators.empty() && priority(c) <= priority(operators.top())) {
                    postfix << operators.top() << " ";
                    operators.pop();
                }
                operators.push(c);
            } else if (isUnary(c)) {
                if (i == 0 || expression[i - 1] == '(') {
                    operators.push(c);
                } else {
                    cout << "Error: Invalid use of unary operator!" << endl;
                    return "";
                }
            }
        }
    }

    if (!numBuffer.empty()) {
        postfix << numBuffer << " ";
    }

    while (!operators.empty()) {
        postfix << operators.top() << " ";
        operators.pop();
    }

    return postfix.str();
}


double evaluatePostfix(string postfix) {
    stack<double> operands;

    stringstream ss(postfix);
    string token;

    while (ss >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && isdigit(token[1]))) {
            operands.push(stod(token)); // string to double
        } else {
            double operand2 = operands.top();
            operands.pop();

            double operand1 = operands.top();
            operands.pop();

            double result = 0.0;

            switch (token[0]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 != 0) {
                        result = operand1 / operand2;
                    } else {
                        cout << "Division by zero!" << endl;
                        return 0;
                    }
                    break;
                case '%':
                    if (operand2 != 0) {
                        result = fmod(operand1, operand2); // double % double
                    } else {
                        cout << "Modulo by zero!" << endl;
                        return 0;
                    }
                    break;
                case '^':
                    result = power(operand1, operand2);
                    break;
                default:
                    cout << "Invalid operator!" << endl;
                    return 0;
            }

            operands.push(result);
        }
    }

    return operands.top();
}


int main() {
    string input = "(-95^3)*(7%2)/3";
//    string input = "";

    cin >> input;
    string postfixExpression = infixToPostfix(input);
    cout << "Postfix expression: " << postfixExpression << endl;
    double res = evaluatePostfix(postfixExpression);
    cout << "Result: " << res << endl;

    return 0;
}
