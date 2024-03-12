#include <stdlib.h>
#include <signal.h>

#include <curl/curl.h>

#include "yoink.c"
#include "parseopt.c"

#include "include/main.h"
#include "include/yoink.h"

int main ( int argc, char *argv[] )
{
	struct yoink_response response;

	struct parsedOptargs parsed = parse_optargs ( argc, argv );

	if ( NULL == parsed.url )
		parsed.url = "https://www.google.com";

	response.size = 0;
	response.content = calloc ( 1, 1 );

	FILE *log = fopen ( YOINK_LOGNAME, "w" );

	struct yoink_parameters parameters =
	{
		.url = parsed.url,
		.body = "{context: {client: {clientName: 'ANDROID', clientVersion: '19.04.33', androidSdkVersion: '34', userAgent: 'com.google.android.youtube/19.04.33 (Linux; U; Android 14 gzip)' screenDensityFloat: 1, screenHeightPoints: 1080, screenPixelDensity: 1, screenWidthPoints: 1920,}, query: 'Boykisser', params: 'EgIQAQ%3D%3D'}",
		.useCustomBody = parsed.useCustomBody,
		.beVerbose = 1,
		.doDumpToLog = parsed.doDump,
		.doDumpToStdout = parsed.doDump,
		.useragent = "evelinwillow/1.0",
		.response = &response,
	};

	if ( NULL != parsed.url )
		printf ( "%s\n", parsed.url );

	parameters.logfile = log;

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
