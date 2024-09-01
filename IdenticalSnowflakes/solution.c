#include <stdio.h>
#include <stdlib.h>

#define MAX_SNOWFLAKES 100000
#define MAX_SNOWFLAKE_ARMS 6

#define index(n) (n % MAX_SNOWFLAKES)
#define t_snowflake struct snowflake

typedef struct snowflake {
	int arms[6];
	struct snowflake* next;
} snowflake;

int calc_hashcode(int arms[])
{
	int i, sum;
	// it should work to just sum the armlengths to get the snowflakes that are more likely to be identical
	for (i = 0; i < MAX_SNOWFLAKE_ARMS; i++)
	{
		sum += arms[i];
	}
	return sum;
}

void add_to_hash_table(snowflake* snowflakes[])
{
	int i, snowflake_code;
	snowflake* next_snowflake = malloc(sizeof(snowflake));

	for (i = 0; i < MAX_SNOWFLAKE_ARMS; i++)
	{
		scanf("%d", &next_snowflake->arms[i]);
	}

	snowflake_code = calc_hashcode(next_snowflake->arms);

	if (snowflakes[index(snowflake_code)] == NULL)
	{
		snowflakes[index(snowflake_code)] = next_snowflake;
	}
	else
	{
		snowflakes[index(snowflake_code)]->next = next_snowflake;
	}
}

int check_left(snowflake* first_snowflake, snowflake* second_snowflake)
{
	int i, j, counter, offset;

	for (i = 0; i < 6; i++)
	{
		j = 0;
		for (offset = 5; offset >= 0; offset--)
		{
			if (first_snowflake->arms[j] == second_snowflake->arms[(i + offset) % 6])
			{
				counter++;
			}
			j++;
		}

		if (counter == 6)
			return 1;

		counter = 0;
	}
	return 0;	
}

int check_right(snowflake* first_snowflake, snowflake* second_snowflake)
{
	int i, counter, offset;

	for (i = 0; i < MAX_SNOWFLAKE_ARMS; i++)
	{
		for (offset = 0; offset < 6; offset++)
		{
			if (first_snowflake->arms[offset] == second_snowflake->arms[(i + offset) % 6])
			{
				counter++;
			}
		}

		if (counter == 6)
			return 1;

		counter = 0;
	}
	
	return 0;
}

int check_for_identical_snowflakes(snowflake* first_snowflake, snowflake* second_snowflake)
{
	if (check_left(first_snowflake, second_snowflake) == 1)
		return 1;
	else if (check_right(first_snowflake, second_snowflake) == 1)
		return 1;
	else
		return 0;
}

int main(void)
{
	// first read the total number of snowflakes from the first line of the input
	int total_snowflakes, i, j;
	static t_snowflake* snowflakes[MAX_SNOWFLAKES];
	scanf("%d", &total_snowflakes);
	printf("Using %d snowflakes\n", total_snowflakes);

	// parse input
	for (i = 0; i < total_snowflakes; i++)
	{
		add_to_hash_table(snowflakes);
	}

	for (i = 0; i < MAX_SNOWFLAKES; i++)
	{
		snowflake* current_snowflake = snowflakes[i];
		
		while (current_snowflake != NULL)
		{
			snowflake* compare_snowflake = current_snowflake->next;

			while (compare_snowflake != NULL)
			{
				if (check_for_identical_snowflakes(current_snowflake, compare_snowflake) == 1)
				{
					printf("exactly Twin snowflakes found\n");
					return 0;
				}
				compare_snowflake = compare_snowflake->next;
			}

			current_snowflake = current_snowflake->next;
		}
	}
	
	printf("No two snowflakes are alike\n");
	return 0;
}
