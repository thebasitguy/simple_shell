#include "shell.h"

/**
 * main - entry point.
 *
 * Return: Always 0
 */

int main(void)
{
	time_t currentTime;
	char *timeString;

	time(&currentTime);

	timeString = ctime(&currentTime);

	timeString[strcspn(timeString, "\n")] = '\0';

	printf("Current time: %s\n", timeString);

	return (0);
}

