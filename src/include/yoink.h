#include <stdio.h>

#ifndef YOINKTUBE_YOINK_H
#define YOINKTUBE_YOINK_H

struct yoink_response
{
  char *content;
  size_t size;
};

struct yoink_parameters
{
  const char *url;
  const char *body;
};

int yoink_request ( struct yoink_parameters* );
void yoink_sigint_handler ( int );

#endif
