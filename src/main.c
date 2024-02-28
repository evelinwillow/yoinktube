#include <stdlib.h>
#include <signal.h>

#include <curl/curl.h>

#include "post.c"

#include "include/main.h"
#include "include/post.h"

#define SKILL_ISSUE EXIT_FAILURE

int main ( int argc, char *argv[] )
{
	( void ) argc;
	( void ) argv;

	struct yoinktube_request_params *params;

	if ( NULL == ( params = calloc ( 1, sizeof ( struct yoinktube_request_params* ) ) ) )
		puts ( "girl damn" );

	if ( NULL == ( params -> url = calloc ( 1, sizeof ( char ) * MAX_URL_LENGTH ) ) )
		puts ( "girl fuck" );

	if ( NULL == ( params -> body = calloc ( 1, sizeof ( char ) * MAX_BODY_LENGTH ) ) )
		puts ( "girl shit" );

	if ( NULL == ( params -> response = calloc ( 1, sizeof ( struct yoinktube_request_response* ) ) ) )
		puts ( "girl nooo" );

	puts ( "post allocation of memory for params" );

	curl_global_init(CURL_GLOBAL_ALL);

	signal ( SIGINT, yoinktube_sigint_handler );

	puts ( "post init of sigint handler" );

	strncpy ( params -> url, "https://www.google.com", MAX_URL_LENGTH -1);

	puts ( "post writing url" );

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
