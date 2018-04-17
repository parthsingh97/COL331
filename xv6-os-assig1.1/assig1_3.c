#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
	int x = toggle(); // This toggles the system trace on or off
	printf(1, "sum of 2 and 3 is: %d\n",add(2,3));
	printf(1, "toggle is: %d\n",x);
	exit();
}
