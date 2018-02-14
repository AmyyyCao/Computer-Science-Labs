#include <stdio.h>

int main(int argc, char **argv)
{
	int n, row, col;
	
	printf("Enter the number of rows in the triangle: ");
	scanf("%d", &n);
	
	//first for loop creates the rows
	for (int row = 1; row <= n; row++) {
	
		//creates the base of the triangle with all "^" when it is the last row.
		if (row == n) {
			for (col = 1; col <= (2 * n) - 1; col++) {
				printf("^");
			}
		}
		
		//creates the rest of the triangle
		else {
			//creates the left side of the triangle
			for (int col = 1; col <= n; col++) {
				(col == (n-row+1)) ? printf("^") : printf(" ");
			}
			
			//creates the right side of the triangle
			for (int col = n; col <= (n * 2 - 1); col++) {
				(col == (n + row - 2)) ? printf("^") : printf(" ");
			}
			
			//ensures that each row prints on a new line
			printf("\n");
		}
	}
	
	printf("\n");
	return 0;
}