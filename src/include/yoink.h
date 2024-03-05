#include <stdio.h>

#ifndef YOINKTUBE_YOINK_H
#define YOINKTUBE_YOINK_H

#define YOINK_INTERRUPT "Interrupt received! Cleaning up..."
#define YOINK_FAILURE  "curl_easy_perform () failed: %s\n"

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

enum YOINK_RESULT {
    YOINK_SUCCESS,
    YOINK_ERROR,
};

int yoink_request ( struct yoink_parameters* );
void yoink_sigint_handler ( int );

#endif
