
#include<LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#include <SoftwareSerial.h>
SoftwareSerial gps(10,11); // RX, TX
//String str="";
//char str[70];

String gpsString="";
char *test="$GPGGA";
String latitude="No Range ";
String longitude="No Range ";
int temp=0,i;
boolean gps_status=0;

void setup()
{
lcd.begin(16,2);
Serial.begin(9600);
gps.begin(9600);
lcd.print("GPS Tracking");
lcd.setCursor(0,1);
lcd.print(" System ");
delay(2000);
//gsm_init();
lcd.clear();
//Serial.println("AT+CNMI=2,2,0,0,0");
lcd.print("GPS Initializing");
lcd.setCursor(0,1);
lcd.print(" No GPS Range ");

get_gps();
delay(2000);

lcd.clear();
lcd.print("GPS Range Found");
lcd.setCursor(0,1);
lcd.print("GPS is Ready");
delay(2000);

lcd.clear();
lcd.print("System Ready");
temp=0;
}

void loop()
{
//serialEvent();
if(temp)
{
get_gps();
//tracking();
}
}

void gpsEvent()
{
gpsString="";
while(1)
{
while (gps.available()>0) //checking serial data from GPS
{
char inChar = (char)gps.read();
gpsString+= inChar; //store data from GPS into gpsString
i++;
if (i < 7)
{
if(gpsString[i-1] != test[i-1]) //checking for $GPGGA sentence
{
i=0;
gpsString="";
}
}
if(inChar=='\r')
{
if(i>65)
{
gps_status=1;
break;
}
else
{
i=0;
}
}
}
if(gps_status)
break;
}
}

void get_gps()
{
gps_status=0;
int x=0;
while(gps_status==0)
{
gpsEvent();
int str_lenth=i;
latitude="";
longitude="";
int comma=0;
while(x<str_lenth)
{
if(gpsString[x]==',')
comma++;
if(comma==2) //extract latitude from string
latitude+=gpsString[x+1];
else if(comma==4) //extract longitude from string
longitude+=gpsString[x+1];
x++;
}
int l1=latitude.length();
latitude[l1-1]=' ';
l1=longitude.length();
longitude[l1-1]=' ';
lcd.clear();
lcd.print("Lat:");
lcd.print(latitude);
lcd.setCursor(0,1);
lcd.print("Long:");
lcd.print(longitude);
i=0;x=0;
str_lenth=0;
delay(2000);
}
}