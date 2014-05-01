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

#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

#include <spark_wiring_stream.h>

/**
 * Virtual class to produce implementable ones.
 * @see printBody() MUST be define.
 */ 
class HttpResponse {
private:
/// HTTP status.
    unsigned fStatus;
/// Content-Type header value. NULL means unknown.
    const char* fContentType;
/// Content-Length header value. -1 means unknown.
    long fContentLength;

protected:
/**
 * Print the current body data to the dÃ©fined stream (TCP Client).
 * This method MUST be redefined in each subclass.
 * @param aStream The stream where data are writen to.
 * @return The Stream after writing on.
 */
    virtual Stream& printBody(Stream& aStream) const = 0;

public:
/**
 * Constructor setting all default values.
 * - HTTP Status set to 200 (OK) ;
 * - Content-Type set to a default value.
 * - Content-Length set as unknown (not sent).
 */
    HttpResponse() :
        fStatus(200),
        fContentType(DEFAULT_CONTENT_TYPE),
        fContentLength(-1) {
    }
    
/**
 * Let define a value for Content-Type header.
 * @param aVal A pointer to a string giving the new type.
 * @note The original string must exists until the end of header sending.
 * @return The used object to be cascaded.
 */
    HttpResponse& contentType(const char *const aVal) {
        fContentType = aVal;
        return *this;
    }
    
/**
 * Let define a value for Content-Length header.
 * @param aVal A long unsigned integer giving the new value.
 * @return The used object to be cascaded.
 */
    HttpResponse& contentLength(const long unsigned& aVal) {
        fContentLength = aVal;
        return *this;
    }

/**
 * Let define a value for HTTP Status.
 * @param aVal An unsigned integer giving the new value.
 * @return The used object to be cascaded.
 */
    HttpResponse& status(const unsigned& aVal) {
        fStatus = aVal;
        return *this;
    }
    
/**
 * operator<< defined as friend to let use the following :
 * @code stream << HttpResponse;
 */
    friend void operator<<(Stream& aStream, const HttpResponse& aResponse);

/**
 * A static string containing the default Content-Type value.
 */
    static const char *const DEFAULT_CONTENT_TYPE;
    
};



/**
 * Class used to produce static pages, like html ones or fix images.
 **/
class HttpResponseStatic : public HttpResponse {
private:
/// Reference on the body content.
    const void *const fBody;
/// Length of the body content.
    const size_t fLength;
    
protected:
    Stream& printBody(Stream& aStream) const { 
        if (fBody && fLength)
            aStream.write(static_cast<const uint8_t *const>(fBody), fLength); 
        return aStream;
    }

public:
    HttpResponseStatic(const void *const aBody, const size_t aLength, const char *const aContentType = NULL ) :
        HttpResponse(),
        fBody(aBody),
        fLength(aLength)
    { 
        if (aContentType)
            contentType(aContentType);
    }
    
};

class Err204 : public HttpResponseStatic {
public:
    Err204() :
        HttpResponseStatic(NULL, 0) {
            status(204);
        };
};

extern Err204 err204;

#endif // __HTTP_RESPONSE_H__
