#include <stdio.h>
int factorialResult;
//factorial function
int factorial(int number) {
	
	int result;
	
    //clunky, but should take care of the case where n is equal to 0
    if (number == 0) {
        result = 0;
    }
    
    //executes the factorial equation
    else {
        for (int i = 1; i <= number; i++) {
            number = number * i;
        }
		result = number;
    }
	
	return result;
}

//choose function; uses factorial function
int choose(int n, int r) {
	
    factorialResult = factorial(n) / (factorial(r) * factorial(n - r));
	return factorialResult;
}

//prints the number of spaces required after each number
//int spaces(number) {
//    if (number >= 100) {
//        printf("  ");
//    }
//    
//    else if (number >= 10) {
//        printf("   ");
//    }
//    
//    else {
//        printf("    ");
//    }
//	return number;
//}



int main(int argc, char **argv)
{	
	int n, r;
	scanf("%d %d", &n, &r);
	choose(n, r);
	printf("%d", factorialResult);
	
	
//	int row, rowsT, col;
//	
//    printf("Enter the number of rows: \n");
//    scanf("%d", &rowsT);
//    
//	for (int row = 0; row < rowsT; row++) {
//		for (int col = row; col >= 0; col--) {
//			printf("%d", choose(row, col));
//
//		}
//	}
	
	
	
			//^^ put in later
			//passes the factorial value into the spaces function and prints
			//printf("%c", spaces(choose(row, i)));
	
	
	
	
	
	
	
	
	
//    for (int row = 0; row < rowsT; row++) {
//        for (int col = 0; col < rowsT; col++) {
//            //generates the correct factorials for each row, along with the required spaces
//            for (int i = row; i >= 0; i--) {
//                printf("%d", choose(row, i));
//                //passes the factorial value into the spaces function and prints
////                printf("%c", spaces(choose(row, i)));
//            }
//        }
//    }
    
    
    return 0;
}

