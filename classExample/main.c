#include <stdio.h>

int main(void)
{
	int day1, mo1;
	int day2, mo2;
	int TADAAA = 0;
	
	printf("Enter 1st date: "\n);
	scanf("%d/%d", &day1, &mo1);
	
	printf("Enter 2nd date: "\n);
	scanf("%d/%d", &day2, &mo2);
	
	
	if (mo1 < mo2) {
		TADAAA = -1;
	}
	
	else if (mo2 > mo1) {
		TADAAA = 1;
	}
	
	else {
		if (day1 < day2) {
			TADAAA = -1;
		}
		else if (day2 < day1) {
			TADAAA = 1;
		}
		else {
			TADAAA = 0;
		}
	}
	
	if (TADAAA == 1) {
		printf("%d/%d is earlier than %d/%d\n", day2, mo2, day1, mo1);
	}
	
	else if (TADAAA = -1) {
		printf("%d/%d is earlier than %d/%d\n", day1, mo1, day2, mo2);
	}
	
	else {
		printf("DATES ARE SAME.")
	}
	
}
