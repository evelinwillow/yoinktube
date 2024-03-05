#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#include "include/yoink.h"

static size_t _yoink_write_callback ( void *data, size_t size, size_t nmemb, void *userp )
// Writeback function for our request. Currently this does nothing other than printing the response and size.
{
	size_t realsize = size * nmemb;
	struct yoink_response *memory = ( struct yoink_response * ) userp;
	
	printf ( "Handling %d bytes!\n", ( int ) realsize );

	char *buffer = realloc( memory -> content, memory -> size + realsize + 1 );

	if ( !buffer )
	{
		fprintf ( stderr, "%s\n", "TODO write an out of memory error message" );

		return 0;
	}

	memory -> content = buffer;
	memcpy ( &( memory -> content [ memory -> size ] ), data, realsize );
	memory -> size += realsize;
	memory -> content [ memory -> size ] = 0;
	// Didn't we reallocate the buffer - is the old one not freed? I thought they get replaced instead of actually resized. 

	// TODO implement more sensible handling of data maybe, yes?

	return realsize;
}
 
int yoink_request ( struct yoink_parameters *parameters )
// This function takes a struct containing an URL and a body to post, sets all the required curl options, and then carries out the POST. Currently, nothing is done with the data that's received.
{
	CURL *curl;
	CURLcode result;

	if ( ( curl = curl_easy_init () ) )
	{
		curl_easy_setopt ( curl, CURLOPT_URL, parameters -> url );
		curl_easy_setopt ( curl, CURLOPT_WRITEFUNCTION, _yoink_write_callback ); 
		curl_easy_setopt ( curl, CURLOPT_POSTFIELDS, parameters -> body );
		curl_easy_setopt ( curl, CURLOPT_POST, 1);
		curl_easy_setopt ( curl, CURLOPT_WRITEDATA, ( void* ) parameters -> response );

		result = curl_easy_perform ( curl );
	
		if ( result != CURLE_OK )
		{
			fprintf ( stderr, YOINK_FAILURE, curl_easy_strerror ( result ) );

			return YOINK_ERROR;
		}

	}
	
	// always cleanup
	curl_easy_cleanup ( curl );
 
	return 0;
}

void yoink_sigint_handler ( int signal )
// Sigint handler; i tried sending a sigint once and it did in fact not int. though.
{
	( void ) signal;

	fprintf ( stderr, "%s\n", YOINK_INTERRUPT );

	curl_global_cleanup ();
}
