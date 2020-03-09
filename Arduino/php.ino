#include "WiFi.h"

#define authcodeaddress 0
#define authcodelength 128

#define defaulterrordelay 60      //in seconds
#define fatalerrordelay 60*30     //in seconds
#define defaultdelay 60           //in seconds


enum REQEUSTTYPES {
  REQUESTTYPE_GET,
  REQUESTTYPE_PUT,
  REQUESTTYPE_UPDATE,
};
const String requesttypes[] = {
  "GET",
  "PUT",
  "UPDATE",
};



void pair() {

  String answer;
  
  #ifdef debugmode
    Serial.println("php pair() start");
    Serial.println("php connecting to " + String(serverhostname));
  #endif
  
  WiFiClient SpyderHub;
  const int httpPort = 80;
  if (!SpyderHub.connect(serverhostname, httpPort)) {
      Serial.println("php connection failed");
    #ifdef debugmode
      Serial.println("_________________________________");
    #endif
    return;
  }
  
  String url = "/pair.php";
  url += "?type=";
  url += type;
  
  #ifdef debugmode
    Serial.println("Requesting URL: " + String(url));
  #endif
  
  SpyderHub.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + serverhostname + "\r\n" + "Connection: close\r\n\r\n");
  delay(1000);

  #ifdef debugmode
    Serial.println("___________Answer:___________");
  #endif
  while (SpyderHub.available()) {
    answer = SpyderHub.readStringUntil('\r');
    #ifdef debugmode
      Serial.print(answer);
    #endif
  }
  #ifdef debugmode
    Serial.println();
    Serial.println("_____________________________");
  #endif

////////////////////////////////////////
//search for #START
  #ifdef debugmode
    Serial.println("Search for #START");
  #endif

  if (answer.indexOf("#START") == -1) {
    Serial.println("#START not found");
    hibernate(fatalerrordelay);
  }
  else {
    #ifdef debugmode
      Serial.println("#START found");
    #endif
  }

////////////////////////////////////////
//#DEBUG
  if (answer.indexOf("#DEBUG") == -1) {
    #ifdef debugmode
      Serial.println("DEBUG:");
      Serial.println("No DEBUG");
    #endif
  }
  else {
    String answerdebugsubstring = answer.substring(answer.indexOf("#DEBUG") + 7, answer.indexOf("#DATA") -1);
    #ifdef debugmode
      Serial.println("DEBUG:");
      Serial.println(answerdebugsubstring);
    #endif
  }

////////////////////////////////////////
//#DATA
  #ifdef debugmode
    Serial.println("DATA:");
    Serial.println("split:");
  #endif
  
  String answerdatasubstring = answer.substring(answer.indexOf("#DATA") + 6, answer.indexOf("#END") - 1);
  #ifdef debugmode
    Serial.println(answerdatasubstring);
    
    Serial.println("---");
  #endif


  DynamicJsonDocument pairdata(JSONCAPACITY);
  deserializeJson(pairdata, answerdatasubstring);
  
//////////////error//////////////
  String answererror = pairdata["error"];
  if (pairdata.containsKey("error")) {
    Serial.println("ERROR: " + String(answererror));
  }
  else {
    #ifdef debugmode
      Serial.println("No ERROR");
    #endif
  }

//////////////authcode//////////////
  String answerauthcode = pairdata["authcode"];
  if (pairdata.containsKey("authcode")) {
    writeEEPROM(authcodeaddress, authcodelength, answerauthcode);
  }
  else {
    Serial.println("ERROR: authcode not found");
    hibernate(fatalerrordelay);
  }

//////////////requesttimeout//////////////
  int answerrequesttimeout = pairdata["requesttimeout"].as<int>();
  if (pairdata.containsKey("requesttimeout")) {
    requesttimeout = answerrequesttimeout;
    if (answerrequesttimeout == 0) requesttimeout = defaultdelay;
    #ifdef debugmode
      Serial.println("New requesttimeout: " + String(requesttimeout) + String("s"));
    #endif
  }
  else {
    Serial.println("ERROR: requesttimeout not found");
    requesttimeout = defaultdelay;
  }

////////////////////////////////////////

  #ifdef debugmode
    Serial.println("---");

    //print all data
    Serial.println("error:" + String("\t\t") + String(answererror));
    Serial.println("authcode:" + String("\t") + String(answerauthcode));
    Serial.println("requesttimeout:" + String("\t") + String(answerrequesttimeout) + String("s"));
    
    Serial.println("---");
  #endif

////////////////////////////////////////
  #ifdef debugmode
    Serial.println("closing pair() connection");
    Serial.println("_________________________________");
  #endif

////////////////////////////////////////
//send jsonstructure
  putdata(jsonstructure);
}



String getdata() {
  return interact(REQUESTTYPE_GET, "");
}

void putdata(String data) {
  interact(REQUESTTYPE_PUT, data);
}

void updatedata(String data) {
  interact(REQUESTTYPE_UPDATE, data);
}



String interact(int requesttype, String data) {

  String answer;
  
  #ifdef debugmode
    Serial.println("php interact() start");
    Serial.println("php connecting to " + String(serverhostname));
  #endif
  
  WiFiClient SpyderHub;
  const int httpPort = 80;
  if (!SpyderHub.connect(serverhostname, httpPort)) {
    Serial.println("php connection failed");
    #ifdef debugmode
      Serial.println("_________________________________");
    #endif
    return "";
  }
  
  String url = "/interact.php";
  url += "?authcode=";
  String authtoken = readEEPROM(authcodeaddress, authcodelength);
  url += authtoken.substring(0, authcodelength); //TODO: temporary solution, check on readEEPROM why we get 3 unknown chars at the end of the read string
  if (!data.equals("")) {
    url += "&data=";
    url += data;
  }
  url += "&requesttype=";
  url += requesttypes[requesttype];
  url += "&type=";
  url += type;
  
  #ifdef debugmode
    Serial.println("Requesting URL: " + String(url));
  #endif
  
  SpyderHub.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + serverhostname + "\r\n" + "Connection: close\r\n\r\n");
  delay(1000);
  
  #ifdef debugmode
    Serial.println("___________Answer:___________");
  #endif
  while (SpyderHub.available()) {
    answer = SpyderHub.readStringUntil('\r');
    #ifdef debugmode
      Serial.print(answer);
    #endif
  }
  #ifdef debugmode
    Serial.println();
    Serial.println("_____________________________");
  #endif

////////////////////////////////////////
//search for #START
  #ifdef debugmode
    Serial.println("Search for #START");
  #endif

  if (answer.indexOf("#START") == -1) {
    Serial.println("#START not found");
    hibernate(defaulterrordelay);
  }
  else {
    #ifdef debugmode
      Serial.println("#START found");
    #endif
  }

////////////////////////////////////////
//#DEBUG
  if (answer.indexOf("#DEBUG") == -1) {
    #ifdef debugmode
      Serial.println("DEBUG:");
      Serial.println("No DEBUG");
    #endif
  }
  else {
    String answerdebugsubstring = answer.substring(answer.indexOf("#DEBUG") + 7, answer.indexOf("#DATA") -1);
    #ifdef debugmode
      Serial.println("DEBUG:");
      Serial.println(answerdebugsubstring);
    #endif
  }

////////////////////////////////////////
//#DATA
  #ifdef debugmode
    Serial.println("DATA:");
    Serial.println("split:");
  #endif
  
  String answerdatasubstring = answer.substring(answer.indexOf("#DATA") + 6, answer.indexOf("#END") - 1);
  #ifdef debugmode
    Serial.println(answerdatasubstring);
    
    Serial.println("---");
  #endif


  DynamicJsonDocument interactdata(JSONCAPACITY);
  deserializeJson(interactdata, answerdatasubstring);
  
//////////////error//////////////
  String answererror = interactdata["error"];
  if (interactdata.containsKey("error")) {
    String errors = "default             AUTHFAILED          TYPEMISMATCH        JSONINVALID         REQUESTTYPEINVALID  ";  //error every 20 chars
    int e = errors.indexOf(answererror);
    if (e == -1) e = 0; //unrecognized error
    switch (e / 20) {
        case 1:
          #ifdef debugmode
            Serial.println("ERROR: Authentication failed, requesting new authcode.");
          #endif
          pair();
          return interact(requesttype, data);
        case 2:
          #ifdef debugmode
            Serial.println("ERROR: Type mismatch, requesting new authcode.");
          #endif
          pair();
          return interact(requesttype, data);
        case 3:
          Serial.println("ERROR: JSON isn´t deserializable, check the JSON formatting.");
          #ifdef debugmode
            Serial.println("Your JSON:");
            Serial.println(answerdatasubstring);
          #endif
          hibernate(fatalerrordelay);
          break;
        case 4:
          Serial.println("ERROR: Requesttype invalid");
          hibernate(fatalerrordelay);
          break;
        case 0:
        default:
          Serial.println("ERROR: unknown error");
          #ifdef debugmode
            Serial.println("The ERROR:");
            Serial.println(answererror);
          #endif
          hibernate(fatalerrordelay);
    }
  }
  else {
    #ifdef debugmode
      Serial.println("No ERROR");
    #endif
  }

//////////////data//////////////
  String returndata = interactdata["data"];

//////////////requesttimeout//////////////
  int answerrequesttimeout = interactdata["requesttimeout"].as<int>();
  if (interactdata.containsKey("requesttimeout")) {
    requesttimeout = answerrequesttimeout;
    if (answerrequesttimeout == 0) requesttimeout = defaultdelay;
    #ifdef debugmode
      Serial.println("New requesttimeout: " + String(requesttimeout) + String("s"));
    #endif
  }
  else {
    Serial.println("ERROR: requesttimeout not found");
    requesttimeout = defaultdelay;
  }

////////////////////////////////////////

  #ifdef debugmode
    Serial.println("---");

    //TODO: perhaps print all data
  
    //Serial.println("---");  
  #endif
////////////////////////////////////////
  #ifdef debugmode
    Serial.println("closing interact() connection");
    Serial.println("_________________________________");
  #endif
  return returndata;  //returns the data for client
}



void resetauthcode() {
  String empty = "";
  for (int i = 0; i < authcodelength; i++) {
    empty += '\0';
  }
  writeEEPROM(authcodeaddress, authcodelength, empty);

}
