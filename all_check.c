#include "all_check.h"
acheck_t buffer[MAX_SIZE];

static uint32_t buffer_max = 0;
const char* get_parent_path(const char* path) {
	const char* last_slash = strrchr(path, '/');
	if (last_slash != NULL) {
		return path;
	}
	else {
		return NULL;
	}
}

void all_check_show_check(void)
{
	for (int i = 0; i < MAX_SIZE; ++i) {
		if (buffer[i].func) {
			printf("[all_check]%s %d false counter(%u) \r\n", buffer[i].func, buffer[i].line, buffer[i].counter);	\
		}
		else {
			return;
		}
	}
}