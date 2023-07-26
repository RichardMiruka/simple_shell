#include "main_unique.h"

/**
 * reverse_string - Reverses a string in-place.
 * @s: Input string to be reversed.
 *
 * Description: This function takes an input string and reverses it in-place,
 *              meaning it modifies the original string directly.
 * Return: No return value (void).
 */
void reverse_string(char *s)
{
	int count = 0, i, j;
	char *str, temp;

	/* Calculate the length of the input string */
	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	/* Use two pointers to swap characters from both ends */
	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			/* Swap characters at positions j and j - 1 */
			temp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = temp;
		}
	}
}
