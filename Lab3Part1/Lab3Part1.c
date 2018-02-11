#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	int amount;
	int quarters, dimes, nickels, cents;
	int quartersRemainder, dimesRemainder, nickelsRemainder;
	char quarters_arr[20], dimes_arr[20], nickels_arr[20], cents_arr[20];
	
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
			//if there is more than one quarter, the word is changed to be plural. else, it remains singular.
			(quarters >= 2) ? strcpy(quarters_arr, " quarters,") : strcpy(quarters_arr, " quarter,");
			if (quartersRemainder == 0) { strcpy(quarters_arr, " quarters"); } //if there is no remainder, no comma is printed.
			
			printf(" %d%s", quarters, quarters_arr);
			quarters = 0;
		}
		
		
		//if there is at least one dime, a phrase will be printed.
		while (dimes != 0) {
			//repeat with dimes
			(dimes >= 2) ? strcpy(dimes_arr, " dimes,") : strcpy(dimes_arr, " dime,");
			if (dimesRemainder == 0) { strcpy(dimes_arr, " dime"); }
			
			printf(" %d%s", dimes, dimes_arr);
			dimes = 0;
		}
		
		
		//if there is at least one nickel, a phrase will be printed.
		while (nickels != 0) {
			//repeat with nickels
			(nickels >= 2) ? strcpy(nickels_arr, " nickels,") : strcpy(nickels_arr, " nickel,");
			if (nickelsRemainder == 0) { strcpy(nickels_arr, " nickel"); }
			
			printf(" %d%s", nickels, nickels_arr);
			nickels = 0;
		}
		
		
		//if there is at least one cent, a phrase will be printed.
		while (cents != 0) {
			//repeat with cents
			(cents >= 2) ? strcpy(cents_arr, " cents") : strcpy(cents_arr, " cent");
		
			printf(" %d%s", cents, cents_arr);
			cents = 0;
		}
		
		printf(".\n");
		
	}
	
	while (amount >= 1 || amount <= 99);
	
	printf("Goodbye.");
}



//(arrayNAme[0]>1) ? strcpy(quarter, "quarters") : strcpy(quarter, "quarter");
//^ same as if/else, just using different syntax.