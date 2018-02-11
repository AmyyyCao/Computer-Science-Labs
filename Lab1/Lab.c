#include <stdio.h>
#include <math.h>

int main(int argc, char **argv)
{
    //final answer will have a decimal, so we use the double type
	double numberOne, numberTwo, numberThree, mean, varSum, variance, stdev = 0;
	
    //calculating the mean
	printf("Enter three numbers: \n");
	scanf("%lf %lf %lf", &numberOne, &numberTwo, &numberThree);
	mean = (numberOne + numberTwo + numberThree) / 3;

    //calculating the variance
	varSum = pow((numberOne-mean),2) +
             pow((numberTwo-mean),2)+pow((numberThree-mean),2);
	variance = varSum / 2;
    
    //calculating the standard deviation
	stdev = sqrt(variance);
	
	printf("The mean is %.2lf and the standard deviation is %.2lf", mean, stdev);
	
	return 0;
}
