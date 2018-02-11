#include <stdio.h>
#include <math.h>

char command;
int number, decimal, binary, decimalFinal = 0, binaryFinal = 0, a, rem;
int binaryRemainder, decimalRemainder, base = 1, two = 2;
int n, yes;

//conversion from decimal to binary function
int toBinary(decimal) {
	
	while (decimal > 0) {
		decimalRemainder = decimal % 2;
		decimal /= 2;
		
		binaryFinal += decimalRemainder * base;
		base *= 10;
	}

	return binaryFinal;
}
	
//conversion from binary to decimal function
int toDecimal(binary) {

	while (binary > 0) {
		binaryRemainder = binary % 10;
		binary /= 10;

		decimalFinal += binaryRemainder * base;
		base *= 2;
	}
	
	return decimalFinal;
	
}


int main(int argc, char **argv)
{
	printf("Enter B for conversion of Binary to Decimal, OR Enter D for conversion of Decimal to Binary: \n");
	scanf("%c", &command);

	printf("Enter your number: \n");
	scanf("%d", &number);

	//if else statement decides which function to run
	if (command == 'B') {
		toDecimal(number);
		printf("%d in binary = %d in decimal\n", number, decimalFinal);
	}
	
	else if (command == 'D') {
		toBinary(number);
		printf("%d in decimal = %d in binary\n", number, binaryFinal);
	}
	
	else {
		printf("Invalid input; Goodbye\n");
	}
	
	return 0;
}
