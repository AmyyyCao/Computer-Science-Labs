#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	int amount;
	int quarters, dimes, nickels, cents;
	int quartersRemainder, dimesRemainder, nickelsRemainder;
	
	quarters = 0;
	dimes = 0;
	nickels = 0;
	cents = 0;
	
	quartersRemainder = 0;
	dimesRemainder = 0;
	nickelsRemainder = 0;
	
	
	//continues to do the actions while (amount >= 1 && amount <= 99)
	do {
			
		//calls for user input
		printf("Please give an amount in cents less than 100: ");
		scanf("%d", &amount);
		
		//exits the loop if either condition is not met
		if (amount <= 0 || amount >= 100) { break; }
		
		printf("%d cents:", amount);
		
		//finds the number of coins of each denomination that go into the input amount
		quarters = amount / 25;
		quartersRemainder = amount % 25;
		dimes = quartersRemainder / 10;
		dimesRemainder = quartersRemainder % 10;
		nickels = dimesRemainder / 5;
		nickelsRemainder = dimesRemainder % 5;
		cents = nickelsRemainder;
	
	
		
		//if there is at least one quarter, a phrase will be printed. if there are no quarters, the quarters phrase will not be printed.
		while (quarters != 0) {
			printf(" %d", quarters);

			//if there is no remainder, no comma is printed.
			if (quartersRemainder == 0) {
				printf(" quarters");
			}
			
			//if there is more than one quarter, the word is changed to be plural. else, it remains singular.
			else if (quarters > 1) {
				printf(" quarters,");
			}
			
			else {
				printf(" quarter,");
			}
			
			quarters = 0;
		}
		
		
		//if there is at least one dime, a phrase will be printed. the same printing process is repeated with dimes
		while (dimes != 0) {

			printf(" %d", dimes);
			
			if (dimesRemainder == 0) {
				printf(" dime");
			}
			
			else if (dimes > 1) {
				printf(" dimes,");
			}
			
			else {
				printf(" dime,");
			}
			
			dimes = 0;
		}
		
		
		//if there is at least one nickel, a phrase will be printed.
		while (nickels != 0) {
			
			printf(" %d", nickels);
			
			if (nickelsRemainder == 0) {
				printf(" nickel");
			}
			
			else if (nickels > 1) {
				printf(" nickels,");
			}
			
			else {
				printf(" nickel,");
			}
			
			nickels = 0;
		}
		
		
		//if there is at least one cent, a phrase will be printed.
		while (cents != 0) {
			
			printf(" %d", cents);
			(cents >= 2) ? printf(" cents") : printf(" cent");
	
			cents = 0;
		}
		
		printf(".\n");
		
	}
	
	while (amount >= 1 || amount <= 99);
	
	printf("Goodbye.");
}



//(arrayNAme[0]>1) ? strcpy(quarter, "quarters") : strcpy(quarter, "quarter");
//^ same as if/else, just using different syntax.