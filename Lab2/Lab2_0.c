#include <stdio.h>
#include <math.h>
#include <string.h>

int main(int argc, char **argv)
{
	char bandOne, bandTwo, bandMult, bandTol;
	int a, b, c, d, i, j;
	double firstNumber, secondNumber, multiplier, tolerance;
	double resistance, combined;
	
	// Asks for the four inputs
	printf("Please enter the 1st band: \n");
	scanf(" %c", &bandOne);
	
	printf("Please enter the 2nd band: \n");
	scanf(" %c", &bandTwo);
	
	printf("Please enter the multiplier band: \n");
	scanf(" %c", &bandMult);
	
	printf("Please enter the tolerance band: \n");
	scanf(" %c", &bandTol);
	
	char band_u[] = {'K', 'B', 'R', 'O', 'E', 'G', 'U', 'V', 'Y', 'W', 'L', 'S'};
	char band_l[] = {'k', 'b', 'r', 'o', 'e', 'g', 'u', 'v', 'y', 'w', 'l', 's'};
	
	// Array of the full color names
	char color_arr[12][10] = {
		{"Black"},
		{"Brown"},
		{"Red"},
		{"Orange"},
		{"Yellow"},
		{"Green"},
		{"Blue"},
		{"Violet"},
		{"Grey"},
		{"White"},
		{"Gold"},
		{"Silver"}
	};
		
	// Array with each band's numerical value
	// Includes 1st and 2nd band, multiplier, and tolerance values
	double resistance_arr[12][4] = {
		{0, 0, 1, 0},
		{1, 1, 10, 1},
		{2, 2, 100, 2},
		{3, 3, 1000, 0},
		{4, 4, 10000, 0},
		{5, 5, 100000, 0.5},
		{6, 6, 1000000, 0.25},
		{7, 7, 10000000, 0.1},
		{8, 8, 0, 0.05},
		{9, 9, 0, 0},
		{0, 0, 0.1, 5},
		{0, 0, 0.01, 10}
	};
	
	// This loop runs through all of the possible indexes of the arrays
	for(i = 0; i < 12; i++){
	
		// This condition checks if any of the user's inputs match with the values stored in band_u and band_l.
		// If there is a match, "i" retains the index of the value. The index will be used to find subsequent values.
		if (bandOne == band_l[i] || bandOne == band_u[i]) {
				
			// This assigns the index corresponding to the user's input to the letter a
			a = i;
			// This assigns the resistance value found at position [i][0] in the resistance array to the variable firstNumber
			firstNumber = resistance_arr[i][0];
		}
		
		if (bandTwo == band_l[i] || bandTwo == band_u[i]) {
			b = i;
			secondNumber = resistance_arr[i][1];
		}

		if (bandMult == band_l[i] || bandMult == band_u[i]) {
			c = i;
			multiplier = resistance_arr[i][2];
		}

		if (bandTol == band_l[i] || bandTol == band_u[i]) {
			d = i;
			tolerance = resistance_arr[i][3];
		}
	
	}
	
	// The calculations for final resistance
	combined = (firstNumber * 10) + secondNumber;
	resistance = multiplier * (combined);
	
	
	// Printing the colors of the resistance band
	printf("Resistor bands: ");

	// Each full color name was stored inside the array as a set of characters
	// The loop calls the color back as individual characters
	for (j=0; j < strlen(color_arr[a]); j++){
		printf("%c", color_arr[a][j]);
	}
	
	printf(" ");
	
	for (j=0; j < strlen(color_arr[b]); j++){
		printf("%c", color_arr[b][j]);
	}
	
	printf(" ");
	
	for (j=0; j < strlen(color_arr[c]); j++){
		printf("%c", color_arr[c][j]);
	}
	
	printf(" ");
	
	for (j=0; j < strlen(color_arr[d]); j++){
		printf("%c", color_arr[d][j]);
	}
	
	printf("\n");
	
	
	// prints the Resistance statement with the appropriate units
	if (multiplier >= 100000) {
		printf("Resistance: %.2lf MOhms +/- %.2lf%% \n", resistance/1000000, tolerance);
	}
	
	else if (multiplier >= 1000) {
		printf("Resistance: %.2lf KOhms +/- %.2lf%% \n", resistance/1000, tolerance);
	}
	
	else {
		printf("Resistance: %.2lf Ohms +/- %.2lf%% \n", resistance, tolerance);
	}

	return 0;
}
