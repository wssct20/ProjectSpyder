#include "WiFi.h"

//TODO: delete if interact is changed
#define authcodeindex "authcode"
#define stateindex "state"
#define requesttimeoutindex "requesttimeout"
#define errorindex "error"

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
    #ifdef debugmode
      Serial.println("php connection failed");
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
    #ifdef debugmode
      Serial.println("#START not found");
    #endif

    hibernate(fatalerrordelay);
  }
  else {
    #ifdef debugmode
      Serial.println("#START found");
    #endif
  }

////////////////////////////////////////
//#DEBUG
  String debugsubstring = answer.substring(answer.indexOf("#DEBUG") + 7, answer.indexOf("#DATA") -1);
  #ifdef debugmode
    Serial.println("DEBUG:");
    Serial.println(debugsubstring);
  #endif

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


  DynamicJsonDocument pairdata(2500);
  deserializeJson(pairdata, answerdatasubstring);
  
//////////////error//////////////
  String answererror = pairdata["error"];
  if (answererror != NULL) {
    #ifdef debugmode
      Serial.println("ERROR: " + String(answererror));
    #endif
  }
  else {
    #ifdef debugmode
      Serial.println("No ERROR");
    #endif
  }

//////////////authcode//////////////
  String answerauthcode = pairdata["authcode"];
  if (answerauthcode != NULL) {
    writeEEPROM(authcodeaddress, authcodelength, answerauthcode);
  }
  else {
    #ifdef debugmode
      Serial.println("ERROR: authcode not found");
    #endif
    hibernate(fatalerrordelay);
  }

//////////////requesttimeout//////////////
  int answerrequesttimeout = pairdata["requesttimeout"].as<int>();
  if (answerrequesttimeout != NULL) {
    requesttimeout = answerrequesttimeout;
    if (answerrequesttimeout == 0) requesttimeout = defaultdelay;
    #ifdef debugmode
      Serial.println("new requesttimeout: " + String(requesttimeout));
    #endif
  }
  else {
    #ifdef debugmode
      Serial.println("ERROR: requesttimeout not found");
    #endif
    requesttimeout = defaultdelay;
  }

////////////////////////////////////////

  #ifdef debugmode
    Serial.println("---");

    //print all data
    Serial.println("error:" + String("\t") + String(answererror));
    Serial.println("authcode:" + String("\t") + String(answerauthcode));
    Serial.println("requesttimeout:" + String("\t") + String(answerrequesttimeout));
    
    Serial.println("---");
  #endif

////////////////////////////////////////
  #ifdef debugmode
    Serial.println("closing pair() connection");
    Serial.println("_________________________________");
  #endif
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
    #ifdef debugmode
      Serial.println("php connection failed");
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
    #ifdef debugmode
      Serial.println("#START not found");
    #endif

    hibernate(defaulterrordelay);
  }
  else {
    #ifdef debugmode
      Serial.println("#START found");
    #endif
  }

////////////////////////////////////////
//#DEBUG
  String debugsubstring = answer.substring(answer.indexOf("#DEBUG") + 7, answer.indexOf("#DATA") -1);
  #ifdef debugmode
    Serial.println("DEBUG:");
    Serial.println(debugsubstring);
  #endif

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


  DynamicJsonDocument interactdata(2500);
  deserializeJson(interactdata, answerdatasubstring);
  
//////////////error//////////////
//TODO: check if answer from programminghoch10
  String answererror = interactdata["error"];
  if (answererror != NULL) {
    #ifdef debugmode
      Serial.println("ERROR: " + String(answererror));
    #endif
  }
  else {
    #ifdef debugmode
      Serial.println("No ERROR");
    #endif
  }

//////////////data//////////////
//TODO

//////////////requesttimeout//////////////
  int answerrequesttimeout = interactdata["requesttimeout"].as<int>();
  if (answerrequesttimeout != NULL) {
    requesttimeout = answerrequesttimeout;
    if (answerrequesttimeout == 0) requesttimeout = defaultdelay;
    #ifdef debugmode
      Serial.println("new requesttimeout: " + String(requesttimeout));
    #endif
  }
  else {
    #ifdef debugmode
      Serial.println("ERROR: requesttimeout not found");
    #endif
    requesttimeout = defaultdelay;
  }

////////////////////////////////////////

  #ifdef debugmode
    Serial.println("---");

    //TODO: perhaps print all data
  
    Serial.println("---");  
  #endif
////////////////////////////////////////
  #ifdef debugmode
    Serial.println("closing interact() connection");
    Serial.println("_________________________________");
  #endif
//  return returnstate; //TODO: note when editing data
  return "currently not working";
}



void resetauthcode() {
  String empty = "";
  for (int i = 0; i < authcodelength; i++) {
    empty += '\0';
  }
  writeEEPROM(authcodeaddress, authcodelength, empty);

}
