#include "WiFi.h"

#define authcodeindex "authcode"
#define stateindex "state"
#define requesttimeoutindex "requesttimeout"
#define errorindex "error"

#define authcodeaddress 0
#define authcodelength 128

#define defaulterrordelay 60      //in seconds
#define fatalerrordelay 60*30     //in seconds
#define defaultdelay 60           //in seconds


void pair()
{

  String answer;
  
  Serial.println("php pair() start");
  Serial.print("php connecting to ");
  Serial.println(serverhostname);
  
  WiFiClient SpyderHub;
  const int httpPort = 80;
  if (!SpyderHub.connect(serverhostname, httpPort))
  {
    Serial.println("php connection failed");
    Serial.println("_________________________________");
    return;
  }
  
  String url = "/pair.php";
  url += "?type=";
  url += type;
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  SpyderHub.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + serverhostname + "\r\n" + "Connection: close\r\n\r\n");
  delay(1000);

  Serial.println("___________Answer:___________");
  while (SpyderHub.available())
  {
    answer = SpyderHub.readStringUntil('\r');
    Serial.print(answer);
  }
  Serial.println();
  Serial.println("_____________________________");

////////////////////////////////////////
// search for #START
  Serial.println("Search for #START");

  if (answer.indexOf("#START") == -1)
  {
    Serial.println("#START not found");

    hibernate(fatalerrordelay);
  }
  else
  {
    Serial.println("#START found");
  }

////////////////////////////////////////
  Serial.println("split:");
  
  String answerdatasubstring = answer.substring(answer.indexOf("#DATA") + 6, answer.indexOf("#END") - 1);
  Serial.println(answerdatasubstring);
  
  Serial.println("---");

  int lastindex = 0;
  int count = 0;
  while(true) {
    int currentindex = answerdatasubstring.indexOf("=>", lastindex);
    if (currentindex == -1) break;
    lastindex = currentindex + 1;
    count++;
  }
  Serial.print("Count: ");
  Serial.println(count);
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
  Serial.print("Sizeof: ");
  Serial.println(sizeof(answerdata));
  Serial.println("---");

// search for error
  for (int i = 0; i < count; i++)
  {
    if (answerdata[i][0] == "error")
    {
      Serial.print("ERROR: ");
      Serial.println(answerdata[i][1]);

      String errorsstring = "TYPEINVALID        ";    // error every 20 chars
      int e = errorsstring.indexOf(answerdata[i][1]);
      if (e == -1)
      {
        delay(defaulterrordelay * 1000);
        return pair();
      }
      switch (e / 20)
      {
        case 0:
          Serial.println("Current type is not supported by server, halting program.");
          hibernate(fatalerrordelay);
        default:
          hibernate(fatalerrordelay);
      }
    }
    else
    {
      Serial.println("No ERROR");
    }
  }

// search for authcode
  bool authcodefound = false;
  for (int i = 0; i < count; i++)
  {
    if (answerdata[i][0] == authcodeindex)
    {
      writeEEPROM(authcodeaddress, authcodelength, answerdata[i][1]);
      authcodefound = true;
      break;
    }
  }
  if (!authcodefound)
  {
    Serial.println("ERROR: authcode not found");
    hibernate(fatalerrordelay);
  }
  

// search for requesttimeout
  bool requesttimeoutfound = false;
  for (int i = 0; i < count; i++)
  {
    if (answerdata[i][0] == requesttimeoutindex)
    {
      requesttimeout = answerdata[i][1].toInt();
      if (requesttimeout == 0) requesttimeout = defaultdelay;
      requesttimeoutfound = true;
      break;
    }
  }
  if (!requesttimeoutfound)
  {
    Serial.println("ERROR: requesttimeout not found");
    requesttimeout = defaultdelay;
  }
  
  
  for (int i = 0; i < count; i++)
  {
    Serial.print(answerdata[i][0]);
    Serial.print("\t");
    Serial.println(answerdata[i][1]);
  }

  Serial.println("---");
////////////////////////////////////////
  Serial.println("closing pair() connection");
  Serial.println("_________________________________");
}



String getstate()
{
  return interact(0, ""); //returns "" on failure
}

void putstate(String state)
{
  interact(1, state);
}


String interact(int requesttype, String state)
{

  String answer;
  
  Serial.println("php interact() start");
  Serial.print("php connecting to ");
  Serial.println(serverhostname);
  
  WiFiClient SpyderHub;
  const int httpPort = 80;
  if (!SpyderHub.connect(serverhostname, httpPort))
  {
    Serial.println("php connection failed");
    Serial.println("_________________________________");
    return "";
  }
  
  String url = "/interact.php";
  url += "?authcode=";
  String authtoken = readEEPROM(authcodeaddress, authcodelength);
  url += authtoken.substring(0, authcodelength); //TODO: temporary solution, check on readEEPROM why we get 3 unknown chars at the end of the read string
  if (requesttype == 1)
  {
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
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  SpyderHub.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + serverhostname + "\r\n" + "Connection: close\r\n\r\n");
  delay(1000);
  
  Serial.println("___________Answer:___________");
  while (SpyderHub.available())
  {
    answer = SpyderHub.readStringUntil('\r');
    Serial.print(answer);
  }
  Serial.println();
  Serial.println("_____________________________");

////////////////////////////////////////
//search for #START
  Serial.println("Search for #START");

  if (answer.indexOf("#START") == -1)
  {
    Serial.println("#START not found");

    hibernate(defaulterrordelay);
  }
  else
  {
    Serial.println("#START found");
  }

////////////////////////////////////////
//processing answer
  Serial.println("split:");
  
  String answerdatasubstring = answer.substring(answer.indexOf("#DATA") + 6, answer.indexOf("#END") - 1);
  Serial.println(answerdatasubstring);
  
  Serial.println("---");

  int lastindex = 0;
  int count = 0;
  while(true) {
    int currentindex = answerdatasubstring.indexOf("=>", lastindex);
    if (currentindex == -1) break;
    lastindex = currentindex + 1;
    count++;
  }
  Serial.print("Count: ");
  Serial.println(count);
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
  Serial.print("Sizeof: ");
  Serial.println(sizeof(answerdata));
  Serial.println("---");

////////////////////////////////////////
// search for error
  for (int i = 0; i < count; i++)
  {
    if (answerdata[i][0] == errorindex)
    {
      Serial.print("ERROR: ");
      Serial.println(answerdata[i][1]);

      String errorsstring = "default             AUTHFAILED          REQUESTTYPEINVALID  TYPEMISMATCH        ";    // error every 20 chars
      int e = errorsstring.indexOf(answerdata[i][1]);
      if (e == -1) {
        //unrecognized error
        e = 0;
      }
      switch (e / 20)
      {
        case 1:
          Serial.println("Authentication failed, requesting new authcode.");
          pair();
          lightsleep(requesttimeout);
          return interact(requesttype, state);
        case 3:
          Serial.println("Type mismatch, requesting new authcode.");
          pair();
          lightsleep(requesttimeout);
          return interact(requesttype, state);
        case 2:
          Serial.println("FATALERROR: requesttype invalid");
        case 0:
        default:
          hibernate(fatalerrordelay);
      }
    }
    else
    {
      Serial.println("No ERROR");
    }
  }

////////////////////////////////////////
// search for state
  String returnstate = "";
  if (requesttype == 0)
  {
    bool statefound = false;
    for (int i = 0; i < count; i++)
    {
      if (answerdata[i][0] == stateindex)
      {
        returnstate = answerdata[i][1];
        statefound = true;
        break;
      }
    }
    if (!statefound)
    {
      Serial.println("ERROR: state not found");
      hibernate(fatalerrordelay);
    }
  }

////////////////////////////////////////
// search for requesttimeout
  bool requesttimeoutfound = false;
  for (int i = 0; i < count; i++)
  {
    if (answerdata[i][0] == requesttimeoutindex)
    {
      requesttimeout = answerdata[i][1].toInt();
      if (requesttimeout == 0) requesttimeout = defaultdelay;
      requesttimeoutfound = true;
      break;
    }
  }
  if (!requesttimeoutfound)
  {
    Serial.println("ERROR: requesttimeout not found");
    requesttimeout = defaultdelay;
  }

  
  for (int i = 0; i < count; i++)
  {
    Serial.print(answerdata[i][0]);
    Serial.print("\t");
    Serial.println(answerdata[i][1]);
  }

  Serial.println("---");
////////////////////////////////////////
  Serial.println("closing interact() connection");
  Serial.println("_________________________________");
  return returnstate;
}

void resetauthcode()
{
  String empty = "";
  for (int i = 0; i < authcodelength; i++) 
  {
    empty += '\0';
  }
  writeEEPROM(authcodeaddress, authcodelength, empty);

}
