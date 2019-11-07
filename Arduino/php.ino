#include "WiFi.h"

#define authcodeindex "authcode"
#define authcodelength 128
#define defaulterrordelay 60

int value0 = 123;
String value1 = "testvalue";
String value2 = "hallo";
int value3 = 151;


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
  url += "&subtype=";
  url += subtype;
  
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

    while(1);     //todo: go to deepsleep
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

      int errorsint[] = {1};
      String errorsstring = "TYPEINVALID        ";    // jeder ERROR 20 Zeichen
      int e = errorsstring.indexOf(answerdata[i][1]);
      if (e == -1)
      {
        delay(defaulterrordelay * 1000);
        return pair();
      }
      switch (errorsint[e / 20])
      {
        case 1:
          Serial.println("Current type is not supported by server, halting program.");
          while(1);     //todo: go to deepsleep
          break;
        default:
          delay(defaulterrordelay * 1000);      //todo: go to deepleep
          return pair();
      }
    }
    else
    {
      Serial.println("No ERROR");
    }
  }

// search the authcode
  for (int i = 0; i < count; i++)
  {
    if (answerdata[i][0] == authcodeindex)
    {
      writeEEPROM(0, authcodelength, answerdata[i][1]);
      break;
    }
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





void phprequest()
{  
  
  String answer;
  
  Serial.println("php start");
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
  
  String url = "/arduinotest.php";
  url += "?A0=";
  url += value0;
  url += "&A1=";
  url += value1;
  url += "&A2=";
  url += value2;
  url += "&A3=";
  url += value3;
  
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
  
  for (int i = 0; i < count; i++)
  {
    Serial.print(answerdata[i][0]);
    Serial.print("\t");
    Serial.println(answerdata[i][1]);
  }

  Serial.println("---");
////////////////////////////////////////
  Serial.println("closing connection");
  Serial.println("_________________________________");
}
