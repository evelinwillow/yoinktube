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

	struct yoink_response response;

	response.size = 0;
	response.content = calloc ( 1, 1 );

	struct yoink_parameters parameters =
	{
		.url = "https://www.google.com/",
		.body = "",
		.useCustomBody = 0,
		.beVerbose = 1,
		.doDumpToLog = 1,
		.doDumpToStdout = 0,
		.useragent = "Dark Secret Ninja/1.0",
		.response = &response
	};	
	
	FILE *log = fopen ( YOINK_LOGNAME, "w" );

	curl_global_init ( CURL_GLOBAL_ALL );

	signal ( SIGINT, yoink_sigint_handler );
	
	fprintf ( log, "%s\n", "" );
	
	fprintf ( log, "URL		-> %s\n", parameters.url );
	fprintf ( log, "POST		-> %s\n", parameters.body );	
	fprintf ( log, "useCustomBody	-> %d\n", parameters.useCustomBody );
	fprintf ( log, "beVerbose	-> %d\n", parameters.beVerbose );
	fprintf ( log, "doDumpToLog	-> %d\n", parameters.doDumpToLog );
	fprintf ( log, "doDumpToStdout  -> %d\n", parameters.doDumpToStdout );
	fprintf ( log, "User Agent	-> %s\n", parameters.useragent );
	fprintf ( log, "\n%s\n", "Yoinking in progress..." );

	if ( YOINK_SUCCESS == yoink_request ( &parameters ) )
	{
		fprintf ( log, "%s\n", "Yoinking successful!");
		fprintf ( log, "Received %d bytes and saved to %s\n", ( int ) parameters.response -> size, YOINK_FILENAME );
			
		if ( 1 == parameters.doDumpToStdout )
			fprintf ( stdout, "\nDumping data:\n%s\n\n", parameters.response -> content );
		
		if ( 1 == parameters.doDumpToLog )
			fprintf ( log, "\nDumping data:\n%s\n\n", parameters.response -> content );


		FILE *file = fopen ( YOINK_FILENAME, "w" );
		fprintf ( file, "%s\n", parameters.response -> content );  

		free ( parameters.response -> content );
		curl_global_cleanup ();
		return EXIT_SUCCESS;
	}
	else
	{
		fprintf ( stderr, "Failed to yoink data from %s :C\n", parameters.url );

		free ( parameters.response -> content );
		curl_global_cleanup ();
		return SKILL_ISSUE;
	}

	return EXIT_SUCCESS;
}
