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
  //TODO: error if no requesttimeout & print requesttimeout
  if (answerrequesttimeout != NULL) {
    requesttimeout = answerrequesttimeout;
    if (answerrequesttimeout == 0) requesttimeout = defaultdelay;
  }
  else {
    #ifdef debugmode
      Serial.println("ERROR: requesttimeout not found");
    #endif
    requesttimeout = defaultdelay;
  }

  #ifdef debugmode
    Serial.println("---");
  
    Serial.println("error:" + String("\t") + String(answererror));
    Serial.println("authcode:" + String("\t") + String(answerauthcode));
    Serial.println("requesttimeout:" + String("\t") + String(answerrequesttimeout));
  #endif

  #ifdef debugmode
    Serial.println("---");
  #endif

////////////////////////////////////////
  #ifdef debugmode
    Serial.println("closing pair() connection");
    Serial.println("_________________________________");
  #endif
}



String getstate() {
  return interact(0, ""); //returns "" on failure
}

void putstate(String state) {
  interact(1, state);
}


String interact(int requesttype, String state) {

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
  if (requesttype == 1) {
    url += "&state=";
    url += state;
  }
  String requesttypes[] = {
    "GET",
    "PUT",
  };
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
//processing answer
  #ifdef debugmode
    Serial.println("split:");
  #endif
  
  String answerdatasubstring = answer.substring(answer.indexOf("#DATA") + 6, answer.indexOf("#END") - 1);
  #ifdef debugmode
    Serial.println(answerdatasubstring);
    
    Serial.println("---");
  #endif

  int lastindex = 0;
  int count = 0;
  while(true) {
    int currentindex = answerdatasubstring.indexOf("=>", lastindex);
    if (currentindex == -1) break;
    lastindex = currentindex + 1;
    count++;
  }
  #ifdef debugmode
    Serial.println("Count: " + String(count));
  #endif
  String answerdata[count][2];

  lastindex = 0;
  count = 0;
  while(true) {
    int currentindex = answerdatasubstring.indexOf("[", lastindex);
    if (currentindex == -1) break;
    answerdata[count][0] = answerdatasubstring.substring(
      currentindex + 1,
      answerdatasubstring.indexOf("]", currentindex)
    );
    answerdata[count][1] = answerdatasubstring.substring(
      answerdatasubstring.indexOf("=>", currentindex) + 2, 
      answerdatasubstring.indexOf("\n", currentindex)
    );
    lastindex = currentindex + 1;
    count++;
  }
  #ifdef debugmode
    Serial.println("Sizeof: " + String(sizeof(answerdata)));
    Serial.println("---");
  #endif

////////////////////////////////////////
// search for error
  for (int i = 0; i < count; i++) {
    if (answerdata[i][0] == errorindex) {
      #ifdef debugmode
        Serial.println("ERROR: " + String(answerdata[i][1]));
      #endif

      String errorsstring = "default             AUTHFAILED          REQUESTTYPEINVALID  TYPEMISMATCH        ";    // error every 20 chars
      int e = errorsstring.indexOf(answerdata[i][1]);
      if (e == -1) {
        //unrecognized error
        e = 0;
      }
      switch (e / 20) {
        case 1:
          #ifdef debugmode
            Serial.println("Authentication failed, requesting new authcode.");
          #endif
          pair();
          lightsleep(requesttimeout);
          return interact(requesttype, state);
        case 3:
          #ifdef debugmode
            Serial.println("Type mismatch, requesting new authcode.");
          #endif
          pair();
          lightsleep(requesttimeout);
          return interact(requesttype, state);
        case 2:
          #ifdef debugmode
            Serial.println("FATALERROR: requesttype invalid");
          #endif
        case 0:
        default:
          hibernate(fatalerrordelay);
      }
    }
    else {
      #ifdef debugmode
        Serial.println("No ERROR");
      #endif
    }
  }

////////////////////////////////////////
// search for state
  String returnstate = "";
  if (requesttype == 0) {
    bool statefound = false;
    for (int i = 0; i < count; i++) {
      if (answerdata[i][0] == stateindex) {
        returnstate = answerdata[i][1];
        statefound = true;
        break;
      }
    }
    if (!statefound) {
      #ifdef debugmode
        Serial.println("ERROR: state not found");
      #endif
      hibernate(fatalerrordelay);
    }
  }

////////////////////////////////////////
// search for requesttimeout
  bool requesttimeoutfound = false;
  for (int i = 0; i < count; i++) {
    if (answerdata[i][0] == requesttimeoutindex) {
      requesttimeout = answerdata[i][1].toInt();
      if (requesttimeout == 0) requesttimeout = defaultdelay;
      requesttimeoutfound = true;
      break;
    }
  }
  if (!requesttimeoutfound) {
    #ifdef debugmode
      Serial.println("ERROR: requesttimeout not found");
    #endif
    requesttimeout = defaultdelay;
  }

  
  for (int i = 0; i < count; i++) {
    #ifdef debugmode
      Serial.println(answerdata[i][0] + String("\t") + String(answerdata[i][1]));
    #endif
  }

  #ifdef debugmode
    Serial.println("---");
  #endif
////////////////////////////////////////
  #ifdef debugmode
    Serial.println("closing interact() connection");
    Serial.println("_________________________________");
  #endif
  return returnstate;
}

void resetauthcode() {
  String empty = "";
  for (int i = 0; i < authcodelength; i++) {
    empty += '\0';
  }
  writeEEPROM(authcodeaddress, authcodelength, empty);

}
