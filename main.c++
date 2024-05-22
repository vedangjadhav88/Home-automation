#include <ESP8266WiFi.h> // esp8266 library
#include <FirebaseArduino.h> // firebase library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args) write(args);
#else
#define printByte(args) print(args,BYTE);
#endif
byte h1[]={B00000,B00100,B01110,B11111,B01110,B01110,B00000,B00000};
LiquidCrystal_I2C lcd(0x27,20,4);
#define FIREBASE_HOST "myhome-e0a6f.firebaseio.com" // the project name address from
firebase id
#define FIREBASE_AUTH "ddtv24JnQ3lD25UZ4qXP8bFdFVvlhdRiJrM4qQNa" // the secret
key generated
#define WIFI_SSID "JV" // input your home or public wifi name
#define WIFI_PASSWORD "012345678" //password of wifi ssid
int HALL_LIGHT = D0; //ESP8266 IO pins
int BEDROOM_LIGHT = D7;
int KITCHEN_LIGHT = D8;
int HALL_TV = D3;
int BEDROOM_FAN = D4;
int WASHROOM_LIGHT = D5;
int REL = D6;
int fanb;
String fanbs;
void setup()
{
lcd.init(); // initialize the lcd
lcd.backlight();
Serial.begin(115200);
delay(1000);
pinMode(HALL_LIGHT, OUTPUT);
pinMode(BEDROOM_LIGHT, OUTPUT);
pinMode(KITCHEN_LIGHT, OUTPUT);
pinMode(HALL_TV, OUTPUT);
pinMode(BEDROOM_FAN, OUTPUT);
pinMode(WASHROOM_LIGHT, OUTPUT);
pinMode(REL, OUTPUT);
WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //try to connect with wifi
Serial.print("Connecting to ");
Serial.print(WIFI_SSID);
while (WiFi.status() != WL_CONNECTED)
{
Serial.print(".");
delay(500);
lcd.createChar(0,h1);
lcd.setCursor(4, 0);
lcd.print("Welcome in")
lcd.setCursor(1, 1);
lcd.write(0);
lcd.print("Smart Home");
lcd.write(0);
delay(2000);
lcd.clear();
}
Serial.println();
Serial.print("Connected to ");
Serial.println(WIFI_SSID);
Serial.print("IP Address is : ");
Serial.println(WiFi.localIP()); //print local IP address
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // connect to firebase
}
void loop()
{
if (Firebase.failed())
{
Serial.print("Firebase failed!!!");
}
int tempC=analogRead(A0);
tempC= map(tempC,0,1023,0,50);
String tempCs =String(tempC);
Firebase.setString("myhome/P",tempCs);
lcd.setCursor(0,0);
lcd.print("Temp: ");
lcd.print(tempCs);
lcd.print(" ");
lcd.print((char)223);
lcd.print("C");
char array[10];
Firebase.getString("myhome/Z").toCharArray(array,10);
fanbs= array[8];
fanb=fanbs.toInt();
fanb=map(fanb,0,9,0,1023);
/* Serial.print("\n");
Serial.print(fanb);*/
Serial.print("\n");
if( array[1] == '1')
{
Serial.println("Hall Lights Turned ON");
digitalWrite(HALL_LIGHT, HIGH);
}
if( array[1] == '0')
{
Serial.println("Hall Lights Turned OFF");
digitalWrite(HALL_LIGHT, LOW);
}
if( array[2] == '1')
{
Serial.println("Bedroom Lights Turned ON");
digitalWrite(BEDROOM_LIGHT, HIGH);
}
if( array[2] == '0')
{
Serial.println("Bedroom Lights Turned OFF");
digitalWrite(BEDROOM_LIGHT, LOW);
}
if( array[3] == '1')
{
Serial.println("Kitchen Lights Turned ON");
digitalWrite(KITCHEN_LIGHT, HIGH);
}
if( array[3] == '0')
{
Serial.println("Kitchen Lights Turned OFF");
digitalWrite(KITCHEN_LIGHT, LOW);
}
if( array[4] == '1')
{
Serial.println("Hall TV Turned ON");
digitalWrite(HALL_TV, HIGH);
}
if( array[4] == '0')
{
Serial.println("Hall TV Turned OFF");
digitalWrite(HALL_TV, LOW);
}
if( array[5] == '1')
{
Serial.println("Bedroom Fan Turned ON");
analogWrite(BEDROOM_FAN, fanb);
}
if( array[5] == '0')
{
Serial.println("Bedroom Fan Turned OFF");
digitalWrite(BEDROOM_FAN, LOW);
}
if( array[6] == '1')
{
Serial.println("Washroom lights Turned ON");
digitalWrite(WASHROOM_LIGHT, HIGH);
}
if( array[6] == '0')
{
Serial.println("Washroom lights Turned OFF");
digitalWrite(WASHROOM_LIGHT, LOW);
}
if( array[7] == '1')
{
Serial.println("Relay Turned ON");
digitalWrite(REL, HIGH);
}
if( array[7] == '0')
{
Serial.println("Relay Turned OFF");
digitalWrite(REL, LOW);
}
}