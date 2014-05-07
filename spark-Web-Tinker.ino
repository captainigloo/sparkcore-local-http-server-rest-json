#include "http_parser.h"
#include "HttpResponse.h"
#include "HttpRequest.h"
#include "slre.h"
#include <map>
#include <list>
char json[128];
char myIpString[24];
char maMacString[32];

class Welcome : public HttpResponse {
protected:
//Formatage page accueil  ---------------------------------------------------------------------------------------
    Stream& printBody(Stream& aStream) const {
        aStream.print(
"<!DOCTYPE html PUBLIC '-//W3C//DTD HTML 4.01//EN' \
	'http://www.w3.org/TR/html4/strict.dtd'> \
 <html> \
    <head> \
    <meta http-equiv='Content-Type' content='text/html; charset=utf-8' /> \
    <title> \
    Sparkcore \
    </title> \
    </head> \
    <body bgcolor='#A9D300'> \
        <h1>Serveur Spark Core</h1>\n");
        //aStream.print("<p>IP : \n");
        //aStream.print(myIpString);
        //aStream.print("</p><p>MAC : \n");
        //aStream.print(maMacString);
        //aStream.print("</p><p>DeviceID : \n");
        //aStream.print(Spark.deviceID());
        //aStream.print("</p><p>SSID : \n");
        //aStream.print(Network.SSID());
        //aStream.print("</p> \n");
        aStream.print("<p>D0 : <a href='/D0/on'>On</a> - <a href='/D0/off'>Off</a> -  état : \n");
        aStream.print(digitalRead(0));
        aStream.print("</p><p>D1 : <a href='/D1/on'>On</a> - <a href='/D1/off'>Off</a> -  état : \n");
        aStream.print(digitalRead(1));
        aStream.print("</p><p>D2 : <a href='/D2/on'>On</a> - <a href='/D2/off'>Off</a> -  état : \n");
        aStream.print(digitalRead(2));
        aStream.print("</p><p>D3 : <a href='/D3/on'>On</a> - <a href='/D3/off'>Off</a> -  état : \n");
        aStream.print(digitalRead(3));
        aStream.print("</p><p>D4 : <a href='/D4/on'>On</a> - <a href='/D4/off'>Off</a> -  état : \n");
        aStream.print(digitalRead(4));        
        aStream.print("</p><p>D5 : <a href='/D5/on'>On</a> - <a href='/D5/off'>Off</a> -  état : \n");
        aStream.print(digitalRead(5));         
        aStream.print("</p><p>D6 : <a href='/D6/on'>On</a> - <a href='/D6/off'>Off</a> -  état : \n");
        aStream.print(digitalRead(6));         
        aStream.print("</p><p>D7 : <a href='/D7/on'>On</a> - <a href='/D7/off'>Off</a> -  état : \n");
        aStream.print(digitalRead(7));     
        aStream.print("</p><p><a href='/json'>Voir retour json</a></p> \
    </body>\n \
</html>\n");
        return aStream;
    }
public:
};

const Welcome welcome;

void flashGreen(const unsigned aDelay = 500) {
    RGB.control(true);
    
    RGB.color(0, 255, 0);
    delay(aDelay);
    RGB.color(0,0,0);

    RGB.control(false);
}

void flashRed(const unsigned aDelay = 500) {
    RGB.control(true);
    
    RGB.color(255, 0, 0);
    delay(aDelay);
    RGB.color(0,0,0);

    RGB.control(false);
}

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
                //Serial.println("Debug : Requete sur index.htm");
//URL JSON ------------------------------------------------------------------------------------------------------
            } else if ((slre_match("^/json$", hr.URL(), strlen(hr.URL()), caps, 1) >= 0)) { 
                    sprintf(json,"{\"D0\":%ld\,\"D1\":%ld,\"D2\":%ld,\"D3\":%ld,\"D4\":%ld,\"D5\":%ld,\"D6\":%ld,\"D7\":%ld}",digitalRead(0),digitalRead(1),digitalRead(2),digitalRead(3),digitalRead(4),digitalRead(5),digitalRead(6),digitalRead(7));
                    //sprintf(json,"{\"D0\":%d\,\"D1\":%d,\"D2\":%d,\"D3\":%d,\"D4\":%d,\"D5\":%d,\"D6\":%d,\"D7\":%d}",pinD0,pinD1,pinD2,pinD3,pinD4,pinD5,pinD6,pinD7);
                    HttpResponseStatic resp(json, strlen(json));
                    client << resp.status(400);
//web/URL REST D0 -----------------------------------------------------------------------------------------------
            } else if ((slre_match("^/D0/(on|off)$", hr.URL(), strlen(hr.URL()), caps, 1) >= 0)) { 
                pinMode(D0, OUTPUT);
                if (!strcmp(caps[0].ptr, "on")) {
                    digitalWrite(D0, HIGH);
                    //client << err204.status(204);
                    //pinD0 = digitalRead(D0);
                    //Test fonction publish
                    //Spark.publish("D0","On");
                    client << welcome;
                    flashGreen();
                } else if (!strcmp(caps[0].ptr, "off")) {
                    digitalWrite(D0, LOW);
                    //client << err204.status(204);
                    //pinD0 = digitalRead(D0);
                    //Test fonction publish
                    //Spark.publish("D0","Off");
                    client << welcome;
                    flashRed();
                } else {
                    const char lib[] = "<html>Le paramètre doit-être 'on' ou 'off'.</html>";
                    HttpResponseStatic resp(lib, strlen(lib));
                    client << resp.status(400);
                }
//URL REST D1 -----------------------------------------------------------------------------------------------
            } else if ((slre_match("^/D1/(on|off)$", hr.URL(), strlen(hr.URL()), caps, 1) >= 0)) { 
                pinMode(D1, OUTPUT);
                if (!strcmp(caps[0].ptr, "on")) {
                    digitalWrite(D1, HIGH);
                    //client << err204.status(204);
                    //pinD1 = digitalRead(D1);
                    //Test fonction publish
                    //Spark.publish("D1","On");
                    client << welcome;
                    flashGreen();
                } else if (!strcmp(caps[0].ptr, "off")) {
                    digitalWrite(D1, LOW);
                    //client << err204.status(204);
                    //pinD1 = digitalRead(D1);
                    //Test fonction publish
                    //Spark.publish("D1","Off");
                    client << welcome;
                    flashRed();
                } else {
                    const char lib[] = "<html>Le paramètre doit-être 'on' ou 'off'.</html>";
                    HttpResponseStatic resp(lib, strlen(lib));
                    client << resp.status(400);
                }
//URL REST D2 -----------------------------------------------------------------------------------------------
            } else if ((slre_match("^/D2/(on|off)$", hr.URL(), strlen(hr.URL()), caps, 1) >= 0)) { 
                pinMode(D2, OUTPUT);
                if (!strcmp(caps[0].ptr, "on")) {
                    digitalWrite(D2, HIGH);
                    //client << err204.status(204);
                    //pinD2 = digitalRead(D2);
                    client << welcome;
                    flashGreen();
                } else if (!strcmp(caps[0].ptr, "off")) {
                    digitalWrite(D2, LOW);
                    //client << err204.status(204);
                    //pinD2 = digitalRead(D2);
                    client << welcome;
                    flashRed();
                } else {
                    const char lib[] = "<html>Le paramètre doit-être 'on' ou 'off'.</html>";
                    HttpResponseStatic resp(lib, strlen(lib));
                    client << resp.status(400);
                }
//URL REST D3 -----------------------------------------------------------------------------------------------
            } else if ((slre_match("^/D3/(on|off)$", hr.URL(), strlen(hr.URL()), caps, 1) >= 0)) { 
                pinMode(D3, OUTPUT);
                if (!strcmp(caps[0].ptr, "on")) {
                    digitalWrite(D3, HIGH);
                    //client << err204.status(204);
                    //pinD3 = digitalRead(D3);
                    client << welcome;
                    flashGreen();
                } else if (!strcmp(caps[0].ptr, "off")) {
                    digitalWrite(D3, LOW);
                    //client << err204.status(204);
                    //pinD3 = digitalRead(D3);
                    client << welcome;
                    flashRed();
                } else {
                    const char lib[] = "<html>Le paramètre doit-être 'on' ou 'off'.</html>";
                    HttpResponseStatic resp(lib, strlen(lib));
                    client << resp.status(400);
                }
//URL REST D4 -----------------------------------------------------------------------------------------------
            } else if ((slre_match("^/D4/(on|off)$", hr.URL(), strlen(hr.URL()), caps, 1) >= 0)) { 
                pinMode(D4, OUTPUT);
                if (!strcmp(caps[0].ptr, "on")) {
                    digitalWrite(D4, HIGH);
                    //client << err204.status(204);
                    //pinD4 = digitalRead(D4);
                    client << welcome;
                    flashGreen();
                } else if (!strcmp(caps[0].ptr, "off")) {
                    digitalWrite(D4, LOW);
                    //client << err204.status(204);
                    //pinD4 = digitalRead(D4);
                    client << welcome;
                    flashRed();
                } else {
                    const char lib[] = "<html>Le paramètre doit-être 'on' ou 'off'.</html>";
                    HttpResponseStatic resp(lib, strlen(lib));
                    client << resp.status(400);
                }
//URL REST D5 -----------------------------------------------------------------------------------------------
            } else if ((slre_match("^/D5/(on|off)$", hr.URL(), strlen(hr.URL()), caps, 1) >= 0)) { 
                pinMode(D5, OUTPUT);
                if (!strcmp(caps[0].ptr, "on")) {
                    digitalWrite(D5, HIGH);
                    //client << err204.status(204);
                    //pinD5 = digitalRead(D5);
                    client << welcome;
                    flashGreen();
                } else if (!strcmp(caps[0].ptr, "off")) {
                    digitalWrite(D5, LOW);
                    //client << err204.status(204);
                    //pinD5 = digitalRead(D5);
                    client << welcome;
                    flashRed();
                } else {
                    const char lib[] = "<html>Le paramètre doit-être 'on' ou 'off'.</html>";
                    HttpResponseStatic resp(lib, strlen(lib));
                    client << resp.status(400);
                }
//URL REST D6 -----------------------------------------------------------------------------------------------
            } else if ((slre_match("^/D6/(on|off)$", hr.URL(), strlen(hr.URL()), caps, 1) >= 0)) { 
                pinMode(D6, OUTPUT);
                if (!strcmp(caps[0].ptr, "on")) {
                    digitalWrite(D6, HIGH);
                    //client << err204.status(204);
                    //pinD6 = digitalRead(D6);
                    client << welcome;
                    flashGreen();
                } else if (!strcmp(caps[0].ptr, "off")) {
                    digitalWrite(D6, LOW);
                    //client << err204.status(204);
                    //pinD6 = digitalRead(D6);
                    client << welcome;
                    flashRed();
                } else {
                    const char lib[] = "<html>Le paramètre doit-être 'on' ou 'off'.</html>";
                    HttpResponseStatic resp(lib, strlen(lib));
                    client << resp.status(400);
                }
//URL REST D7 -----------------------------------------------------------------------------------------------
            } else if ((slre_match("^/D7/(on|off)$", hr.URL(), strlen(hr.URL()), caps, 1) >= 0)) { 
                pinMode(D7, OUTPUT);
                if (!strcmp(caps[0].ptr, "on")) {
                    digitalWrite(D7, HIGH);
                    //client << err204.status(204);
                    //pinD7 = digitalRead(D7);
                    client << welcome;
                    flashGreen();
                } else if (!strcmp(caps[0].ptr, "off")) {
                    digitalWrite(D7, LOW);
                    //client << err204.status(204);
                    //pinD7 = digitalRead(D7);
                    client << welcome;
                    flashRed();
                } else {
                    const char lib[] = "<html>Le paramètre doit-être 'on' ou 'off'.</html>";
                    HttpResponseStatic resp(lib, strlen(lib));
                    client << resp.status(400);
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
//Récupérer IP ----------------------------------------------------------------------------------------------
    IPAddress myIp = Network.localIP();
    sprintf(myIpString, "%d.%d.%d.%d", myIp[0], myIp[1], myIp[2], myIp[3]);
    Spark.variable("ipAddress", myIpString, STRING);
//Récupérer MAC----------------------------------------------------------------------------------------------    
    byte Mac[6];
    Network.macAddress(Mac);
    sprintf(maMacString, "%02X:%02X:%02X:%02X:%02X:%02X", Mac[5], Mac[4], Mac[3], Mac[2], Mac[1], Mac[0]);
    Spark.variable("MAC", maMacString, STRING);
//Démarrer serveur Web---------------------------------------------------------------------------------------    
    ws.begin();
    flashGreen();
}

void loop() {
    ws.loop();
}
