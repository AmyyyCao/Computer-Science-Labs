#include <stdio.h>

int row, rowsT;

int choose(int n, int r) {
	factorial(n) / (factorial(r) * factorial(n - r));
}

int factorial(int n) {
	//clunky, but should take care of the case where n is equal to 0
	if (n == 0) {
		n = 0;
	}
	
	//executes the factorial equation
	else {
		for (i = n; i > 0; i--) {
			n *= i;
		}
	}
}

//prints the number of spaces required after each number
int spaces(number) {
	if (number >= 100) {
		printf("  ");
	}
	
	else if (number >= 10) {
		printf("   ");
	}
	
	else {
		printf("    ");
	}
}



int main(int argc, char **argv)
{
	printf("Enter the number of rows: \n");
	scanf("%d", &rowsT);
	
	for (row = 0; row <= rowsT; row++) {
		for (col = 0; col <= rowsT; col++) {
			//generates the correct factorials for each row, along with the required spaces
			for (i = row; i = 0; i--) {
				printf("%d", choose(n, i));
				//passes the factorial value into the spaces function and prints
				printf("%c", spaces(choose(n, i)));
			}
		}
	}
	
	
	return 0;
}
