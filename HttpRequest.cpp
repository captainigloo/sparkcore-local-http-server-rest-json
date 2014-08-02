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
 
#include "HttpRequest.h"
#include <spark_wiring_usbserial.h>

void HttpRequest::setURL(const char *const aURL) {
    strncpy(fURL, aURL, MAX_URL_LENGTH);
}

#ifdef USE_HEADERS
void HttpRequest::setHeaderField(const char *const aField) {
    strncpy(fHeaderField, aField, MAX_HEADER_FIELD_LENGTH);
}

void HttpRequest::setHeaderValue(const char *const aValue) {

    char *const pH = static_cast<char *const>(malloc(strlen(fHeaderField) + 1));  // len + '\0'
    memcpy(pH, fHeaderField, strlen(fHeaderField) + 1);

    char *const pV = static_cast<char *const>(malloc(strlen(aValue) + 1));  // len + '\0'
    memcpy(pV, aValue, strlen(aValue) + 1);

//        fHeaders.insert(std::pair<char*, char*>(pH, pV));
    fHeaders[pH] = pV;
}
#endif

HttpRequest::HttpRequest() {
    memset(&fSettings, 0, sizeof(fSettings)); // remplissage de 0s
/*
    fSettings.on_message_begin = onMessageBegin;
    fSettings.on_headers_complete = onHeadersComplete;
    fSettings.on_message_complete = onMessageComplete;
*/
    fSettings.on_url = onUrl;
#ifdef USE_HEADERS
    fSettings.on_header_field = onHeaderField;
    fSettings.on_header_value = onHeaderValue;
#endif
    http_parser_init(&fParser, HTTP_REQUEST);
    fParser.data = static_cast<void*>(this);
}
    
HttpRequest::~HttpRequest() {
/// @todo vider les fHdeaders pour Ã©viter les fuites mÃ©moire !!!
}
    
void HttpRequest::parse(const char aChar) {
    if (1 != http_parser_execute(&fParser, &fSettings, &aChar, 1)) {
        Serial.print("Error in http_parser_execute, line ");
        Serial.print(__LINE__ - 2);
        abort();
    }
}
    
const char* HttpRequest::URL() const { 
    return fURL; 
}
    
#ifdef USE_HEADERS
void HttpRequest::printHeaders() const {
//        for (std::map<const char*, char*, ltstr>::const_iterator it = fHeaders.begin(); it != fHeaders.end(); ++it) {
    for (auto it = fHeaders.begin(); it != fHeaders.end(); ++it) {
        Serial.print(it->first);
        Serial.print("=");
        Serial.println(it->second);
    }    
}
#endif

/*
int HttpRequest::onMessageBegin(http_parser* parser) {
//    HttpRequest *const pHR = static_cast<HttpRequest*const>(parser->data);
//    pHR->init();
//    Serial.println("***MESSAGE BEGIN***");
    return 0;
}

int HttpRequest::onHeadersComplete(http_parser* parser) {
//    HttpRequest *const pHR = static_cast<HttpRequest*const>(parser->data);
//    Serial.println("***HEADER COMPLETE***");
    return 0;
}

int HttpRequest::onMessageComplete(http_parser* parser) {
//    HttpRequest *const pHR = static_cast<HttpRequest*const>(parser->data);
//    Serial.println("***MESSAGE COMPLETE***");
    return 0;
}
*/

int HttpRequest::onUrl(http_parser* parser, const char *at, size_t len) {
    static char c[MAX_URL_LENGTH];

    if (len) {
        if (strlen(c) + len > MAX_URL_LENGTH)
            return 1;   // overflow
        strncat(c, at, len);
        return 0;
    }
    HttpRequest *const pHR = static_cast<HttpRequest*const>(parser->data);
    pHR->setURL(c);
    c[0] = '\0';
    return 0; 
}

#ifdef USE_HEADERS
int HttpRequest::onHeaderField(http_parser* parser, const char *at, size_t len) {
    static char c[MAX_HEADER_FIELD_LENGTH];
    
    if (len) {
        if (strlen(c) + len > MAX_HEADER_FIELD_LENGTH)
            return 1;   // overflow
        strncat(c, at, len);
        return 0;
    }
    HttpRequest *const pHR = static_cast<HttpRequest*const>(parser->data);
    pHR->setHeaderField(c);
    c[0] = '\0';
    return 0; 
}

int HttpRequest::onHeaderValue(http_parser* parser, const char *at, size_t len) {
    static char c[MAX_HEADER_VALUE_LENGTH] = "";
    
    if (len) {
        if (strlen(c) + len > MAX_HEADER_VALUE_LENGTH)
            return 1;   // overflow
        strncat(c, at, len);
        return 0;
    }
    HttpRequest *const pHR = static_cast<HttpRequest*const>(parser->data);
    pHR->setHeaderValue(c);
    c[0] = '\0';
    return 0; 
}
#endif
