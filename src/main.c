#include <stdlib.h>
#include <signal.h>

#include "post.c"

int main ( int argc, char *argv[] )
{
	( void ) argc;
	( void ) argv;

	signal ( SIGINT, yoinktube_sigint_handler );

	abort();
}
