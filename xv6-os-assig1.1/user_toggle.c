#include "types.h"
#include "stat.h"
#include "user.h"


int
main(int argc, char *argv[])
{
	int x = toggle();
	if (x == 0) // don't print the trace
	{
		printf(1, "# Print trace: OFF\n");
	}

	else if (x == 1) // print the trace
	{
		printf(1, "# Print trace: ON\n");
	}

	else
	{
		printf(1, "x = %d", x);
	}
	exit();
}