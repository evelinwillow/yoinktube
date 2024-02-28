#include <stdlib.h>
#include <signal.h>

#include "post.c"

#define SKILL_ISSUE EXIT_FAILURE;

int main ( int argc, char *argv[] )
{
	( void ) argc;
	( void ) argv;

	int ret;

	struct yoinktube_request_params* params;

	params = ( struct yoinktube_request_params* ) calloc ( 1, sizeof ( struct yoinktube_request_params ) );

	//signal ( SIGINT, yoinktube_sigint_handler );
	
	if ( yoinktube_request ( params ) )
	{
		printf ( "%s\n", "Successfully did the thingie!" );
		
		return EXIT_SUCCESS;
	}
	else
	{
		printf ( "%s\n", "Girl nooooo... :c" );

		return SKILL_ISSUE;
	}

	return EXIT_SUCCESS;
}
