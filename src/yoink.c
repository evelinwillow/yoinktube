/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 * SPDX-License-Identifier: curl
 *
 ***************************************************************************/
/* <DESC>
 * Make an HTTP POST with data from memory and receive response in memory.
 * </DESC>
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

#include "include/yoink.h"

static size_t _yoink_write_callback ( void *data, size_t size, size_t nmemb, void *userp )
{
	size_t realsize = size * nmemb;
	struct yoink_response *memory = ( struct yoink_response * ) userp;

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

	printf ( "Handling %d bytes!\n", ( int ) realsize );
	fprintf ( stdout, "Dumping data to stdout:\n%s\n", ( char* ) data );

	return realsize;
}
 
int yoink_request ( struct yoink_parameters *parameters )
{
	CURL *curl;
	CURLcode result;

	struct yoink_response response = { 0 };
 
	if ( ( curl = curl_easy_init () ) )
	{
		curl_easy_setopt ( curl, CURLOPT_URL, parameters -> url );
		curl_easy_setopt ( curl, CURLOPT_WRITEFUNCTION, _yoink_write_callback ); 
		curl_easy_setopt ( curl, CURLOPT_POSTFIELDS, parameters -> body );
		curl_easy_setopt ( curl, CURLOPT_WRITEDATA, ( void* ) &response );

		result = curl_easy_perform ( curl );
	
		if ( result != CURLE_OK )
		{
			fprintf
			(
				stderr,
				"curl_easy_perform () failed: %s\n",
				curl_easy_strerror ( result )
			);

			exit ( 1 );
		}

		free ( response.content );

		/* always cleanup */
		curl_easy_cleanup ( curl );
	}
 
	curl_global_cleanup ();
	return 0;
}

void yoink_sigint_handler ( int signal )
{
	( void ) signal;
	curl_global_cleanup ();
}
