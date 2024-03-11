#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "include/parseopt.h"

struct parsedOptargs
parse_optargs ( int argc, char * argv[] )
{
	int index;
	int c;

	char *url = NULL;

	bool useCustomBody = false;

	opterr = 0;

	while ((c = getopt (argc, argv, "bu:")) != -1)
		switch (c)
		{
			case 'u':
				url = optarg;
				break;
			case 'b':
				useCustomBody = true;
				break;
			case '?':
				if (optopt == 'u')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
			default:
				abort ();
		}

	struct parsedOptargs parsed = 
	{
		.url = url,
		.useCustomBody = useCustomBody
	};

	for (index = optind; index < argc; index++)
		printf ("Non-option argument %s\n", argv[index]);

	return parsed;
}
