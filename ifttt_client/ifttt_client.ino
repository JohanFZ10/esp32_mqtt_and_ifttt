#include <WiFi.h>
#include <HTTPClient.h>


const char * ssid = "xxxx";
const char * password = "xxxxx";

String server = "http://maker.ifttt.com";
String eventName = "xxxxxx";
String IFTTT_Key = "xxxxxxxx";
String IFTTTUrl="http://maker.ifttt.com/trigger/temp_data/with/key/e272MXJrh4_et5KUm56LmYHjJrNRtj9BjxUT5u6Njr7";

int value1;
int value2;
int value3;

int voltajepin=33;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("ESP32, Connected !!!");
}


void sendDataToSheet(void)
{
  String url = server + "/trigger/" + eventName + "/with/key/" + IFTTT_Key + "?value1=" + String((int)value1) + "&value2="+String((int)value2) +"&value3=" + String((int)value3);  
  Serial.println(url);
  //Start to send data to IFTTT
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");
  http.begin(url); //HTTP

  Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();
  // httpCode will be negative on error
  if(httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();

}

void loop() {
  value1 = analogRead(voltajepin)*3.3/4095;
  value2 = analogRead(voltajepin)*3.3/1023;
  value3 = analogRead(voltajepin)*3.3/2000; 

  Serial.print("Values are ");
  Serial.print(value1);
  Serial.print(' ');
  Serial.print(value2);
  Serial.print(' ');
  Serial.println(value3);
  Serial.print(' '); 

  sendDataToSheet();
  delay(10000);
}