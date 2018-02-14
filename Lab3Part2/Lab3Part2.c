#include <stdio.h>

int main(int argc, char **argv)
{
	double firstNumber, secondNumber, sum, difference, product, division;
	char operator;

	// Asks user to input two numbers and an operator
	printf("Enter first number: \n");
	scanf(" %lf", &firstNumber);
	
	printf("Enter second number: \n");
	scanf(" %lf", &secondNumber);
	
	printf("Enter calculation command (one of a, s, m, or d): ");
	scanf(" %c", &operator);
	
	
	// Series of "if" conditions that execute the calculation depending on the inputted operator
	if (operator == 'a') {
		sum = firstNumber + secondNumber;
		printf("Sum of %.2lf and %.2lf is %.2lf \n", firstNumber, secondNumber, sum);
	}
	
	else if (operator == 's') {
		difference = firstNumber - secondNumber;
		printf("Difference of %.2lf from %.2lf is %.2lf \n", firstNumber, secondNumber, difference);
	}
	
	else if (operator == 'm') {
		product = firstNumber * secondNumber;
		printf("Product of %.2lf and %.2lf is %.2lf \n", firstNumber, secondNumber, product);
	}
	
	// First check to see if 0 (invalid value for secondNumber) is used in the division
	else if (operator == 'd' && secondNumber == 0) {
		printf("Error, trying to divide by zero \n");
	}
	
	else if (operator == 'd') {
		division = firstNumber / secondNumber;
		printf("Division of %.2lf by %.2lf is %.2lf \n", firstNumber, secondNumber, division);
	}
	
	// All other conditions cannot result in a valid calcuation
	else {
		printf("Error, unknown calculation command given \n");
	}
	
	return 0;
}
