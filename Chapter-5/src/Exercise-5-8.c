/*
 * This program converts a given date (month, day) into the corresponding
 * day of the year and vice versa.
 * Author	: Dhruv Ajudiya
 * Created	: 8 October 2024
 * Modified	: 8 October 2024
 */

/** REQUIRED HEADER FILES */
#include <stdio.h>

/** MACRO DEFINITIONS */
#define MONTHS_IN_YEAR		12	/* Number of months in a year */
#define DAYS_IN_LEAP_YEAR	366	/* Number of days in a leap year */
#define DAYS_IN_NONLEAP_YEAR	365	/* Number of days in a non-leap year */

/** FUNCTION PROTOTYPES */
int dayOfYear(int iYear, int iMonth, int iDay);
void monthDay(int iYear, int iYearDay, int *iMonth, int *iDay);

/** GLOBAL VARIABLES */
static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, /* Non-leap year */
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}  /* Leap year */
};

/** MAIN PROGRAM */
/*
 * main: Prompts the user for input and demonstrates the dayOfYear and monthDay
 *       functions with proper input validation.
 */
int main(void)
{
	int iYear, iMonth, iDay, iYearDay; /* Store year, month, day, and day of the year */

	/* Convert month/day to day of the year */
	printf("Enter the day, month and year: ");
	scanf("%d %d %d", &iDay, &iMonth, &iYear);

	iYearDay = dayOfYear(iYear, iMonth, iDay);
	if (iYearDay == -1)
		printf("Error: Invalid date entered\n");
	else
		printf("%dth day of the year %d\n", iYearDay, iYear);

	/* Convert day of the year to month/day */
	printf("\nEnter the day of the year and year: ");
	scanf("%d %d", &iYearDay, &iYear);

	monthDay(iYear, iYearDay, &iMonth, &iDay);
	if (iMonth == -1 && iDay == -1)
		printf("Error: Invalid year or day of the year entered\n");
	else
		printf("Day: %d, Month: %d\n", iDay, iMonth);

	return 0;
} /* End main() */

/*
 * dayOfYear	: Converts the given month and day into the corresponding day of the year,
 *		  with proper error checking for leap years and invalid dates.
 * Input	: iYear (the year to check for leap year)
 *		  iMonth (the month number)
 *		  iDay (the day number)
 * Return	: Day of the year if valid input, -1 for invalid input.
 * Author	: Dhruv Ajudiya
 * Created	: 8 October 2024
 * Modified	: 8 October 2024
 */
int dayOfYear(int iYear, int iMonth, int iDay)
{
	int iLeapYear, iMonthIndex; /* Store leap year status and index for month */

	if (iYear < 1)
		return -1;

	iLeapYear = ((iYear % 4 == 0) && (iYear % 100 != 0)) || (iYear % 400 == 0);

	if (iMonth < 1 || iMonth > MONTHS_IN_YEAR || iDay < 1 || iDay > daytab[iLeapYear][iMonth])
		return -1; /* Invalid month or day */

	/* Calculate day of the year */
	for (iMonthIndex = 1; iMonthIndex < iMonth; iMonthIndex++) {
		iDay += daytab[iLeapYear][iMonthIndex];
	}

	return iDay;
} /* End dayOfYear() */

/*
 * monthDay	: Converts the given day of the year into the corresponding month and day,
 *		  with error checking for invalid year and day of the year.
 * Input	: iYear (the year to check for leap year)
 *		  iYearDay (the day of the year to convert)
 * Output	: iMonth (pointer to store the month result)
 *		  iDay (pointer to store the day result)
 * Author	: Dhruv Ajudiya
 * Created	: 8 October 2024
 * Modified	: 8 October 2024
 */
void monthDay(int iYear, int iYearDay, int *iMonth, int *iDay)
{
	int iLeapYear, iMonthIndex; /* Store leap year status and index for month */

	if (iYear < 1) {
		*iMonth = -1;
		*iDay = -1;
		return;
	}

	iLeapYear = ((iYear % 4 == 0) && (iYear % 100 != 0)) || (iYear % 400 == 0);

	/* Check if the day of the year is valid */
	if (iYearDay < 1 || iYearDay > (iLeapYear ? DAYS_IN_LEAP_YEAR : DAYS_IN_NONLEAP_YEAR)) {
		*iMonth = -1;
		*iDay = -1;
		return; /* Invalid day of the year */
	}

	/* Calculate month and day */
	for (iMonthIndex = 1; iYearDay > daytab[iLeapYear][iMonthIndex]; iMonthIndex++) {
		iYearDay -= daytab[iLeapYear][iMonthIndex];
	}

	*iMonth = iMonthIndex;
	*iDay = iYearDay;
} /* End monthDay() */
