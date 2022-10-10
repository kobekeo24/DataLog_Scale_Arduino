#include <LiquidCrystal_I2C.h>


//----------------------------
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
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
int nDevices = 0;
String X_string = "X_coord=";
String Y_string = "Y_coord=";
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
/************************************************************************************
 *  setup function starts
 **********************************************************************************/
 void setup() {
    Wire.begin();
    lcd.begin();
    lcd.backlight();
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
  lcd.setCursor(0,0);
  lcd.print(X_string);
  lcd.setCursor(0,1);
  lcd.print(Y_string);
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
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(X_string);
  lcd.setCursor(0,1);
  lcd.print(Y_string);
  
  lcd.setCursor(X_string.length()+2,0);
  lcd.print(X_value);
  lcd.setCursor(Y_string.length()+2,1);
  lcd.print(Y_Value);

  //write_to_google_sheet(param);

  
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
