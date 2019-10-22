const char * serverhostname = "SpyderHub";
//const char * hostip = "192.168.177.22";

int value = 123;


void php()
{
  Serial.println("php start");
  Serial.print("php conecting to ");
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
  url += "testvalue=";
  url += "&A1=";
  url += value;

  Serial.print("Requesting URL: ");
  Serial.println(url);

  SpyderHub.print(String("GET ") + url + "HTTP/1.1\r\n" + "Host: " + serverhostname + "\r\n" + "Connection: close\r\n\r\n");
  delay(1000);

  while (SpyderHub.available())
  {
    String line = SpyderHub.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");

  Serial.println("_________________________________");
}
