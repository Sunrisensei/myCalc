#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <stack>
#include <queue>
using namespace std;

void printHelp()
{
    printf("=======================\n");
    printf("Welcome to myCalc 1.0 !\n");
    printf("=======================\n");
    printf("Press \'c\' to clear number\n");
    printf("Press <ENTER> to the final RPN string\n");
    printf("Press \'h\' to clear current number\n");
    printf("Press <ESC> to quit\n");
}

bool checkPEMDASops(char op)
{
    if (op == '(' || op == ')' || op == '^' || op == '*' || op == '/' || op == '+' || op == '-')
        return true;
    return false;
}

// PEMDAS ranking
// P - 4
// E - 3
// M or D - 2
// A or S - 1
// return 0 if not PEMDAS operator. Means something wrong.
char getPrecedenceRank(char op)
{
    // PEMDAS character only
    if (checkPEMDASops(op))
    {
        switch (op)
        {
            case '(':
            case ')':
                 return 4;
            case '^':
                return 3;
            case '*':
            case '/':
                return 2;
            case '+':
            case '-':
                return 1;
        }
    }
    return 0;
}

// Check precedence for RPN, following PEMDAS rules
// op1 from input, op2 from top of stack
// op1 higher precedence than op2, return 1
// op1 same or lower precedence than op2, return 0
// If either character not PEMDAS, return -1
char checkPrecedence(char op1, char op2)
{
    if (checkPEMDASops(op1) && checkPEMDASops(op2))
        if (getPrecedenceRank(op1) > getPrecedenceRank(op2))
            return 1;
        else
            return 0;
    if (checkPEMDASops(op1) == false)
        printf("op1 \"%c\" is not PEMDAS", op1);
    if (checkPEMDASops(op2) == false)
        printf("op2 \"%c\" is not PEMDAS", op2);
    return -1;
}

int main(int argc, char const *argv[])
{
    /* code */
    stack<char> myStack;
    queue<char> myQueue;
    string myRPN;
    int countOpenParenthesis = 0;
    float myAnswer = 0.0;

    printHelp();
    char ch = _getch();
    while (ch != 0x1B) // if not <ESC> key, continue loop
    {
        // Only allow math operator, dot and numbers. Special keys like backspace, ENTER and equal sign are also allowed.
        // 0x08 = backspace - not allowed in traditional calculator
        // 0x0D = ENTER
        if ( (ch >= 0x28 && ch < 0x39) || (ch == 'c') || (ch == 'C') || (ch == 0x0D))
        {
            printf("%c",ch);
            // C for CLEAR
            if (ch == 'c' || ch == 'C')
            {
                printf("\x1b[2K"); //clear line
                // Empty myQueue if not
                if (myQueue.size())
                {
                    while (!myQueue.empty())
                        myQueue.pop();
                }
                printf("%c", 0x0D);
            }
            // ENTER
            else if (ch == 0x0D)
            {
                printf("\nRPN string \"%s\"", myRPN.c_str());
                printf("\nmyStack.size() is \"%i\"", myStack.size());
                printf("\nmyQueue.size() is \"%i\"", myQueue.size());
            }
            // Numbers 0-9
            else if (ch >= 0x30 && ch < 0x39)
            {
                myQueue.push(ch);
            }
            // PEMDAS 7 operators ( ) ^ * + - /
            else if (checkPEMDASops(ch))
            {
                // Transfer string in myQueue to myRPN string
                while (!myQueue.empty())
                {
                    myRPN.push_back(myQueue.front());
                    myQueue.pop();
                }
                myRPN.append(" ");
                printf("\n%c\n", ch);
                if (myStack.empty())
                    myStack.push(ch);
                else
                {
                    // If ')' is pressed, pop out all the symbols in myStack until '('
                    if (ch ==0x29)
                    {
                        // Ignore the ')' if previously no '(' entered before.
                        if (countOpenParenthesis > 0)
                        {
                            --countOpenParenthesis;
                            while (myStack.top() != '(')
                            {
                                myRPN.push_back(char(myStack.top()));
                                myRPN.append(" ");
                                myStack.pop();
                            }
                            myStack.pop(); // Clear the '('
                            printf("\n)\n");
                        }
                    }
                    else if (checkPrecedence(ch, myStack.top()))
                    {
                        myStack.push(ch);
                        // Keep track of the '(' previously entered. To prevent ')' pressed without '(' previously.
                        if (ch ==0x28)
                        {
                            ++countOpenParenthesis;
                        }
                        printf("\n%c\n", ch);
                    }
                    else
                    {
                        // pop out to the RPN string
                        myRPN.push_back(char(myStack.top()));
                        myRPN.append(" ");
                        myStack.pop();
                        myStack.push(ch);
                        printf("\n%c\n", ch);
                    }
                }
            }
        }
        else if (ch == 'h' || ch == 'H')
        {
            printf("\n");
            printHelp();
        }
        ch = _getch();
    }

    return 0;
}
