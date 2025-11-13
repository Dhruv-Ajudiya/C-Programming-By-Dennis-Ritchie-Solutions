#include <stdio.h>
#include <stdlib.h>
#include "error_handling.h"

void handleError(int iErrorCode)
{
	switch(iErrorCode) {
	case ERROR_INVALID_INPUT:
		printf("\nError: Invalid input. Please enter valid input.\n");
		break;
	default:
		printf("\nError: Unknown error code %d\n", iErrorCode);
		break;
	}
	exit(EXIT_FAILURE);
}
