#include <stdio.h>
#include <stdlib.h>
int main(void) {
    int num, positive = 0, negative = 0, zero = 0; // Variable num is used to store the number inputted.
    int sizeNumber;  // Variable to store the number of inputs required.
    char msgSize[] = "How many numbers: ";
    char msgNumber[] = "Enter a number: ";
    char posMsg[] = "Positive: %2d\n";
    char negMsg[] = "Negative: %2d\n";
    char zeroMsg[] = "Zero:     %2d\n";
    char lineDivider[] = "------------\n";
    char fmt[] = "%d";
    _asm {
        // Receiving the number of inputs required. 
        lea eax, msgSize
        push eax
        call printf   // Prints "How many numbers: ".
        pop eax
        lea eax, sizeNumber
        push eax
        lea eax, fmt
        push eax
        call scanf    // Receives inputed value for the number of inputs required.
        add esp, 8

        // Calculating the number of zeros, positive and negative numbers.
        mov ebx, 1    // Loops from 1 to 'sizeNumber'.
        floop: cmp ebx, sizeNumber // Checks if ebx is less than or equal to the variable 'sizeNumber'.
            jle Begin
            jg End
            Begin: push ebx   // Beginning of loop.
                inc ebx
                lea eax, msgNumber
                push eax
                call printf   // Prints "Enter a number: ".
                add esp, 8

                lea eax, num
                push eax
                lea eax, fmt
                push eax
                call scanf    // Accepts an integer.
                add esp, 8

                mov eax, num
                cmp eax, 0    // Checks if number is less than, greater than or equal to zero.
                je Zero
                jg positiveNum
                jl negativeNum

                Zero :        // Executes if the number is equal to zero.
                    mov eax, zero
                    add eax, 1
                    mov zero, eax
                    jmp floop

                positiveNum : // Executes if the number is greater than zero.
                    mov eax, positive
                    add eax, 1
                    mov positive, eax
                    jmp floop

                negativeNum : // Executes if the number is less than zero.
                    mov eax, negative
                    add eax, 1
                    mov negative, eax
                    jmp floop

            End : nop  // End of loop.
        // Printing the values.
        lea eax, lineDivider  // Prints a line to separate the inputs and the results.
        push eax
        call printf
        pop eax

        //Printing the number of positive numbers.
        push positive
        lea eax, posMsg
        push eax
        call printf
        add esp, 8

        //Printing the number of negative numbers.
        push negative
        lea eax, negMsg
        push eax
        call printf
        add esp, 8

        //Printing the number of zeros.
        push zero
        lea eax, zeroMsg
        push eax
        call printf
        add esp, 8
    }
    return 0;
}
