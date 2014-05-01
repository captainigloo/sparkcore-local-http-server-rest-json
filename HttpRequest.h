/**
 * @file
 * @copyright Copyright Â© 2014 by Marc Sibert
 * @author Marc Sibert
 * 
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar. See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */ 
#ifndef __HTTP_REQUEST__
#define __HTTP_REQUEST__

/**
 * See @url https://github.com/joyent/http-parser
 **/
#include "http_parser.h"
#include <string.h>

#define MAX_URL_LENGTH 512

// #define USE_HEADERS
#ifdef USE_HEADERS
#define MAX_HEADER_FIELD_LENGTH 512
#define MAX_HEADER_VALUE_LENGTH 512
#endif

class HttpRequest {
private:
    http_parser fParser;
    http_parser_settings fSettings;
    
    char fURL[MAX_URL_LENGTH];
#ifdef USE_HEADERS
    char fHeaderField[MAX_HEADER_FIELD_LENGTH];
#endif    
    struct ltstr
    {
      bool operator()(const char* s1, const char* s2) const
      {
        return strcmp(s1, s2) < 0;
      }
    };

#ifdef USE_HEADERS
    std::map<const char*, char*, ltstr> fHeaders;
#endif
//    static int onMessageBegin(http_parser* parser);
//    static int onHeadersComplete(http_parser* parser);
//    static int onMessageComplete(http_parser* parser);
    static int onUrl(http_parser* parser, const char *at, size_t len);
#ifdef USE_HEADERS
    static int onHeaderField(http_parser* parser, const char* at, size_t len);
    static int onHeaderValue(http_parser* parser, const char *at, size_t len);
#endif

protected:
    void setURL(const char *const aURL);
#ifdef USE_HEADERS
    void setHeaderField(const char *const aField);
    void setHeaderValue(const char *const aValue);
#endif

public:
    HttpRequest();
    ~HttpRequest();
    void parse(const char aChar);
    
/**
 * Return the URL after parsing the http request.
 * @return the parsed URL.
 */
    const char* URL() const;
#ifdef USE_HEADERS
    void printHeaders() const;
#endif

};

#endif // __HTTP_REQUEST__
