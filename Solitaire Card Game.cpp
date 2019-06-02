#include "Stack.h"
#include "Spider.h"
#include "stdio.h"

void check_initialized(int initialized) {
	if (!initialized) {
		printf("You must initialize the game first.\n");
		printf("Stopping Program\n");
		exit(1);
	}
}

int main() {
	stack_test();

	struct spider* s = NULL;
	/*const int INIT = lookup_symbol("init");
	const int WON = lookup_symbol("won");
	const int QUIT = lookup_symbol("quit");

	const int PRINT = lookup_symbol("print");
	const int PRINTFACEUP = lookup_symbol("printfaceup");

	const int GETSTOCK = lookup_symbol("getstock");

	const int TESTFINDSEQ = lookup_symbol("testfindseq");

	const int MOVE = lookup_symbol("move");
*/
	int initialized = 0;

	while (1) {
		char* cmd = (char*)malloc(sizeof(char) * 100);
		
		if (cmd == INIT) {
			int seed = 0;
			int level = 0;
			scanf("%d", &seed);
			scanf("%d", &level);
			spider_init_random(level, seed);
			spider_print(s);
			initialized += 1;
		}
		else if (cmd == WON) {
			check_initialized(initialized);
			bool won = spider_has_won(s);
			if (won) {
				printf("Congrats! You have won the game! Dude you rock!\n");
				break;
			}
			else {
				printf("You have not won yet, keep playing or input \"quit\" to quit.\n");
			}

		}
	}
}