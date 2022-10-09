
//----------------------------
#include <WiFi.h>
#include <HTTPClient.h>
//----------------------------

//--------------------------------------------

#define RXD2 16
#define TXD2 17
int analogPinX = 35;
int analogPinY = 34; 
int X_value,Y_Value;
//--------------------------------------------

//---------------------------------------------------------------------
//
//
//ENTER_GOOGLE_DEPLOYMENT_ID
const char * ssid = "Kobekeo_Network";
const char * password = "Zoinks1398.";
String GOOGLE_SCRIPT_ID = "AKfycbwgr-4Nd6BF9EO2Wr00D8dKJQtetk5sjSqPGa2m8flkQyBd6rxRAcq_T1b8qGtZvvwH";
//---------------------------------------------------------------------

const int sendInterval = 2000;
String param;
/************************************************************************************
 *  setup function starts
 **********************************************************************************/
 void setup() {
  //--------------------------------------------
  Serial.begin(115200);
  //start serial communication with Serial Monitor
  //--------------------------------------------
  //start serial communication with Neo6mGPS

  delay(10);
  //--------------------------------------------
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("OK");
  //--------------------------------------------
}
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM



/************************************************************************************
 *  loop function starts
 **********************************************************************************/
void loop() {
    X_value = analogRead(analogPinX);
    Y_Value = analogRead(analogPinY);
    param  = "X_coord="+String(X_value);
    param += "&Y_coord="+String(Y_Value);

    
    Serial.println(param);
    write_to_google_sheet(param);

  
  delay(sendInterval);
}
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM




/************************************************************************************
 *  loop function starts
 **********************************************************************************/

//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM




/************************************************************************************
 *  loop function starts
 **********************************************************************************/
void write_to_google_sheet(String params) {
   HTTPClient http;
   String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"+params;
   //Serial.print(url);
    Serial.println("Postring GPS data to Google Sheet");
    //---------------------------------------------------------------------
    //starts posting data to google sheet
    http.begin(url.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET();  
    Serial.print("HTTP Status Code: ");
    Serial.println(httpCode);
    //---------------------------------------------------------------------
    //getting response from google sheet
    String payload;
    if (httpCode > 0) {
        payload = http.getString();
        Serial.println("Payload: "+payload);     
    }
    //---------------------------------------------------------------------
    http.end();
}
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
