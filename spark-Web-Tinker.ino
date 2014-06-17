#include "http_parser.h"
#include "HttpResponse.h"
#include "HttpRequest.h"
#include "slre.h"
#include <map>
#include <list>
class Welcome : public HttpResponse {
protected:
//Formatage page accueil  ---------------------------------------------------------------------------------------
    Stream& printBody(Stream& aStream) const {
        aStream.print("<html> \
    <head> \
    <title> \
    Sparkcore \
    </title> \
    </head> \
    <body> \
        <p><a href='/json/dig'>Json Digital</a></p> \
        <p><a href='/json/ana'>Json Analog</a></p> \
    </body>\n \
    </html>\n");
        return aStream;
    }
public:
};

class Help :  public HttpResponse {
protected:
    //Formatage page aide  ---------------------------------------------------------------------------------------
    Stream& printBody(Stream& aStream) const {
    aStream.print("<html> \
    <head> \
    <title> \
    Sparkcore \
    </title> \
    </head> \
    <body> \
        <p>Le paramètre doit-être 'ana' ou 'dig' pour l'url /json/.</p> \
        <p>Le paramètre doit-être 'on' ou 'off' pour l'url /D0/ à /D7/.</p> \
    </body>\n \
    </html>\n");
        return aStream;
    }
public:
};

const Help help;
const Welcome welcome;
// "Class WebServer" impléments TCPServer et fourni toutes les methodes pour le serveur http .
class WebServer : public TCPServer {
private:

protected:

public:
// Port d'écoute TCP/80.
    WebServer() : TCPServer(80) {}    
    WebServer(const unsigned aPort) : TCPServer(aPort) {}    
// Doît-être utilisé dans la fonction boucle loop() .
    void loop() {
        char jsonD[64];
        char jsonA[96];
        if (TCPClient client = available()) {
            
            HttpRequest hr;
            while (int nb = client.available()) {
                Serial.println(nb);
                for (int i = nb; i > 0; --i) {
                    const char buf = client.read();
                    Serial.print(buf);
                    hr.parse(buf);    
                }
                Serial.println();
            }
            Serial.print("URL : "); Serial.println(hr.URL());
#ifdef USE_HEADERS
            hr.printHeaders();
#endif
            struct slre_cap caps[4];
//Gestion des URL -----------------------------------------------------------------------------------------------
            if (slre_match("^/(|index.htm)$", hr.URL(), strlen(hr.URL()), NULL, 0) >= 0) {
                client << welcome;
//URL JSON --------------------------------------------------------------------------------------------------
            } else if ((slre_match("^/json/(ana|dig)$", hr.URL(), strlen(hr.URL()), caps, 1) >= 0)) { 
                pinMode(D0, OUTPUT);
                if (!strcmp(caps[0].ptr, "dig")) {
                    sprintf(jsonD,"{\"D0\":%ld\,\"D1\":%ld,\"D2\":%ld,\"D3\":%ld,\"D4\":%ld,\"D5\":%ld,\"D6\":%ld,\"D7\":%ld}",digitalRead(0),digitalRead(1),digitalRead(2),digitalRead(3),digitalRead(4),digitalRead(5),digitalRead(6),digitalRead(7));
                    HttpResponseStatic resp(jsonD, strlen(jsonD));
                    client << resp.status(400);
                } else if (!strcmp(caps[0].ptr, "ana")) {
                    sprintf(jsonA,"{\"A0\":%ld\,\"A1\":%ld,\"A2\":%ld,\"A3\":%ld,\"A4\":%ld,\"A5\":%ld,\"A6\":%ld,\"A7\":%ld}",analogRead(0),analogRead(1),analogRead(2),analogRead(3),analogRead(4),analogRead(5),analogRead(6),analogRead(7));
                    HttpResponseStatic resp(jsonA, strlen(jsonA));
                    client << resp.status(400);
                } else {
                    client << help;
                }                    
//URL REST D0 -----------------------------------------------------------------------------------------------
            } else if ((slre_match("^/D0/(on|off)$", hr.URL(), strlen(hr.URL()), caps, 1) >= 0)) { 
                pinMode(D0, OUTPUT);
                if (!strcmp(caps[0].ptr, "on")) {
                    digitalWrite(D0, HIGH);
                    client << welcome;
                } else if (!strcmp(caps[0].ptr, "off")) {
                    digitalWrite(D0, LOW);
                    client << welcome;
                } else {
                    client << help;
                }
//URL REST D1 -----------------------------------------------------------------------------------------------
            } else if ((slre_match("^/D1/(on|off)$", hr.URL(), strlen(hr.URL()), caps, 1) >= 0)) { 
                pinMode(D1, OUTPUT);
                if (!strcmp(caps[0].ptr, "on")) {
                    digitalWrite(D1, HIGH);
                    client << welcome;
                } else if (!strcmp(caps[0].ptr, "off")) {
                    digitalWrite(D1, LOW);
                    client << welcome;
                } else {
                    client << help;
                }
//URL REST D2 -----------------------------------------------------------------------------------------------
            } else if ((slre_match("^/D2/(on|off)$", hr.URL(), strlen(hr.URL()), caps, 1) >= 0)) { 
                pinMode(D2, OUTPUT);
                if (!strcmp(caps[0].ptr, "on")) {
                    digitalWrite(D2, HIGH);
                    client << welcome;
                } else if (!strcmp(caps[0].ptr, "off")) {
                    digitalWrite(D2, LOW);
                    client << welcome;
                } else {
                    client << help;
                }
//URL REST D3 -----------------------------------------------------------------------------------------------
            } else if ((slre_match("^/D3/(on|off)$", hr.URL(), strlen(hr.URL()), caps, 1) >= 0)) { 
                pinMode(D3, OUTPUT);
                if (!strcmp(caps[0].ptr, "on")) {
                    digitalWrite(D3, HIGH);
                    client << welcome;
                } else if (!strcmp(caps[0].ptr, "off")) {
                    digitalWrite(D3, LOW);
                    client << welcome;
                } else {
                    client << help;
                }
//URL REST D4 -----------------------------------------------------------------------------------------------
            } else if ((slre_match("^/D4/(on|off)$", hr.URL(), strlen(hr.URL()), caps, 1) >= 0)) { 
                pinMode(D4, OUTPUT);
                if (!strcmp(caps[0].ptr, "on")) {
                    digitalWrite(D4, HIGH);
                    client << welcome;
                } else if (!strcmp(caps[0].ptr, "off")) {
                    digitalWrite(D4, LOW);
                    client << welcome;
                } else {
                    client << help;
                }
//URL REST D5 -----------------------------------------------------------------------------------------------
            } else if ((slre_match("^/D5/(on|off)$", hr.URL(), strlen(hr.URL()), caps, 1) >= 0)) { 
                pinMode(D5, OUTPUT);
                if (!strcmp(caps[0].ptr, "on")) {
                    digitalWrite(D5, HIGH);
                    client << welcome;
                } else if (!strcmp(caps[0].ptr, "off")) {
                    digitalWrite(D5, LOW);
                    client << welcome;
                } else {
                    client << help;
                }
//URL REST D6 -----------------------------------------------------------------------------------------------
            } else if ((slre_match("^/D6/(on|off)$", hr.URL(), strlen(hr.URL()), caps, 1) >= 0)) { 
                pinMode(D6, OUTPUT);
                if (!strcmp(caps[0].ptr, "on")) {
                    digitalWrite(D6, HIGH);
                    client << welcome;
                } else if (!strcmp(caps[0].ptr, "off")) {
                    digitalWrite(D6, LOW);
                    client << welcome;
                } else {
                    client << help;
                }
//URL REST D7 -----------------------------------------------------------------------------------------------
            } else if ((slre_match("^/D7/(on|off)$", hr.URL(), strlen(hr.URL()), caps, 1) >= 0)) { 
                pinMode(D7, OUTPUT);
                if (!strcmp(caps[0].ptr, "on")) {
                    digitalWrite(D7, HIGH);
                    client << welcome;
                } else if (!strcmp(caps[0].ptr, "off")) {
                    digitalWrite(D7, LOW);
                    client << welcome;
                } else {
                    client << help;
                }
//URL Inconnue ----------------------------------------------------------------------------------------------
            } else {
                char lib[1024];
                lib[0] = '\0';
                strcat(lib, "<html><h1>Not Found</h1>");
                strcat(lib, "URL: ");
                strcat(lib, hr.URL());
                strcat(lib, "</html>");
                HttpResponseStatic resp(lib, strlen(lib));
                client << resp.status(404);
            }
            client.flush();
            delay(100);
            client.stop();
        }   
    };
};

WebServer ws;

void setup() {

    Serial.begin(9600);
    delay(1000);
    Serial.println(Network.localIP());
    Serial.println(Network.subnetMask());
    Serial.println(Network.gatewayIP());
    Serial.println(Network.SSID());
    //Serial.println(Spark.deviceID());

    ws.begin();
}

void loop() {
    ws.loop();

}



