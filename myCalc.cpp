#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <stack>
using namespace std;

void printHelp()
{
    printf("=======================\n");
    printf("Welcome to myCalc 1.0 !\n");
    printf("=======================\n");
    printf("Press <ESC> to quit\n");
    printf("Press <ENTER> to calculate answer\n");
}

int main(int argc, char const *argv[])
{
    /* code */
    stack<char> myStack;
    string myRPN;
    float myAnswer = 0.0;

    printHelp();
    char ch = _getch();
    while (ch != 0x1B) // if not <ESC> key, continue loop
    {
        // Only allow math operator, dot and numbers. Special keys like backspace, ENTER and equal sign are also allowed.
        // 0x08 = backspace
        // 0x0D = ENTER
        if ( (ch >= 0x28 && ch < 0x39) || (ch == 0x08) || (ch == 0x0D))
        {
            printf("%c",ch);
            if (ch == 0x08)
            {
                printf("%c",0x20);
                printf("%c",ch);
            }
            else if (ch == 0x0D)
            {
                // printf("\x1b[2K"); //clear line
                printf("%c\nAnswer is %lf\n", ch, myAnswer);
            }
        }
        else if (ch == 'h')
        {
            printHelp();
        }
        ch = _getch();
    }

    return 0;
}
