#include <stdio.h>

#ifndef YOINKTUBE_YOINK_H
#define YOINKTUBE_YOINK_H

#define YOINK_INTERRUPT "Interrupt received! Cleaning up..."
#define YOINK_FAILURE  "curl_easy_perform () failed: %s\n"

#define YOINK_FILENAME "yoink_"__TIME__".out"
#define YOINK_LOGNAME "yoink_"__TIME__".log"

struct yoink_response
{
  char *content;
  size_t size;
};

struct yoink_parameters
{
  const char *url;
  const char *body;
  const char *useragent;
  int useCustomBody;
  int beVerbose;
  unsigned int doDumpToLog:1;
  unsigned int doDumpToStdout:1;
  struct yoink_response *response;
};

enum YOINK_RESULT {
    YOINK_SUCCESS,
    YOINK_ERROR,
};

int yoink_request ( struct yoink_parameters* );
void yoink_sigint_handler ( int );

#endif
