#include <stdio.h>
#include <papi.h>

int main()
{
	const PAPI_component_info_t *cmpinfo = NULL;
	if (PAPI_library_init(PAPI_VER_CURRENT) != PAPI_VER_CURRENT) exit(1);
	if ((cmpinfo = PAPI_get_component_info(1)) == NULL) exit(1);
	printf("This component supports %d Preset Events and %d Native events.\n",
	cmpinfo->num_preset_events, cmpinfo->num_native_events);
	return 0;
}
