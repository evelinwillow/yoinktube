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
#include "include/post.h"

static size_t
_yoinktube_write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	struct yoinktube_request_response *mem = ( struct yoinktube_request_response * ) userp;
 
	char *ptr = realloc ( mem -> memory, mem -> size + realsize + 1 );
	if ( !ptr )
	{
		/* out of memory! */
		printf("not enough memory (realloc returned NULL)\n");

		return 0;
	}
 
	mem -> memory = ptr;
	memcpy ( &( mem -> memory [ mem -> size ] ), contents, realsize );
	mem -> size += realsize;
	mem -> memory [ mem -> size ] = 0;
 
	return realsize;
}
 
int yoinktube_request ( struct yoinktube_request_params *params )
{
	CURL *curl;
	CURLcode res;
 
	params -> response -> memory = malloc(1);
	params -> response -> size = 0;
 
	curl = curl_easy_init();

	if(curl)
	{
		curl_easy_setopt ( curl, CURLOPT_URL, params -> url );
		curl_easy_setopt ( curl, CURLOPT_WRITEFUNCTION, _yoinktube_write_callback ); 
		curl_easy_setopt ( curl, CURLOPT_POSTFIELDS, params -> body );
 
		res = curl_easy_perform ( curl );
		
		if ( res != CURLE_OK )
		{
			fprintf
			(
				stderr,
				"curl_easy_perform() failed: %s\n",
				curl_easy_strerror ( res )
			);

			exit(1);
		}
 
		/* always cleanup */
		curl_easy_cleanup ( curl );
	}
 
	curl_global_cleanup ();
	return 0;
}

void yoinktube_sigint_handler ( int signal )
{
	curl_global_cleanup ();
}
