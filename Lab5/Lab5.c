//  Copyright © 2018 Song You. All rights reserved.

#include <stdio.h>

//factorial function
int factorial(int number) {
    int result;
	
    //takes care of the case where n is equal to 0
    if (number == 0) {
        result = 1;
    }
    
    //executes the factorial equation for all numbers other than 0
    else {
        result = 1;
        for (int i = 1; i <= number; i++) {
            result = result * i;
        }
    }
    return result;
}

//choose function; uses factorial function
int choose(int n, int r) {
    return factorial(n) / (factorial(r) * factorial(n - r));
}

//prints the number of spaces required after each number
int spaces(int n) {
    if (n < 10) {
        printf("     ");
    }
    else if (n < 100) {
        printf("    ");
    }
    else {
        printf("   ");
    }
    return n;
}

//prints Pascal's Triangle
void triangle(int rowsT) {
	for (int row = 0; row < rowsT; row++) {
            
		//prints the spaces in front of each row to create a centered triangle
		for (int i = 2; i <= (rowsT-row); i++) {
			printf("   ");
		}
		//prints the numbers as well as the spaces in between them
		for (int i = row; i >= 0; i--) {
			printf("%d", choose(row, i));
			spaces(choose(row, i));
		}
		printf("\n");
	}
}

int main(int argc, char **argv)
{
	int rowsT;
    do {
        //asks for user input
        printf("Enter the number of rows: ");
        scanf("%d", &rowsT);
		
		triangle(rowsT);
    }
	
	while (rowsT >= 0 && rowsT <= 12);
    
    return 0;
}