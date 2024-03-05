#include <stdlib.h>
#include <signal.h>

#include <curl/curl.h>

#include "yoink.c"

#include "include/main.h"
#include "include/yoink.h"

int main ( int argc, char *argv[] )
{
	( void ) argc;
	( void ) argv;

	struct yoink_parameters parameters =
	{
			.url = "https://wttr.in/",
		.body = "",
	};

	curl_global_init ( CURL_GLOBAL_ALL );

	signal ( SIGINT, yoink_sigint_handler );

	fprintf ( stdout, "%s\n", "Yoinking in progress..." );

	if ( YOINK_SUCCESS == yoink_request ( &parameters ) )
	{
		fprintf ( stdout, "Successfully yoinked data from %s!\n", parameters.url );
		

		curl_global_cleanup ();
		return EXIT_SUCCESS;
	}
	else
	{
		fprintf ( stderr, "Failed to yoink data from %s :C\n", parameters.url );
	
		curl_global_cleanup ();
		return SKILL_ISSUE;
	}

	return EXIT_SUCCESS;
}
