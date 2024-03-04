#include <stdio.h>

#ifndef YOINKTUBE_POST_H
#define YOINKTUBE_POST_H

struct yoinktube_request_response
{
  char *memory;
  size_t size;
};

struct yoinktube_request_params
{
  const char *url;
  const char *body;
  struct yoinktube_request_response *response;
};

int yoinktube_request ( struct yoinktube_request_params* );
void yoinktube_sigint_handler ( int );

#endif
