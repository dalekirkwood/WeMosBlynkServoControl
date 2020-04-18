/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  You can send/receive any data using WidgetTerminal object.

  App project setup:
    Terminal widget attached to Virtual Pin V1
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h> // Library for Servo


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "XJLjQA5iqql1ySgfxuAh1Bh2Ka47RiH8";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "NufyBears";
char pass[] = "NufNufBear1";

int rudPos = 90;
Servo rudderServ;

// Attach virtual serial terminal to Virtual Pin V1
WidgetTerminal terminal(V1);

// You can send commands from Terminal to your hardware. Just use
// the same Virtual Pin as your Terminal Widget
BLYNK_WRITE(V1)
{
  // if you type "Marco" into Terminal Widget - it will respond: "Polo:"
  if (String("Marco") == param.asStr()) {
    terminal.println("You said: 'Marco'") ;
    terminal.println("I said: 'Polo'") ;
  } else {

    // Send it back
    terminal.print("You said:");
    terminal.write(param.getBuffer(), param.getLength());
    terminal.println();
  }

  // Ensure everything is sent
  terminal.flush();
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  rudderServ.attach(4);

  int newRudPos = pinValue;
  delay(100);
     
// Turn Up Volume
 if ( newRudPos > rudPos ) 
 
    {
      int increment = newRudPos - rudPos;
      for (int i = 0; increment > i; i++) 
        { 
        int newAmount = rudPos + i;
        rudderServ.write(newAmount); 
        terminal.println(i);
          delay(10d);
        }
            rudderServ.detach();
     }

// Turn Down Volume
      if ( newRudPos < rudPos ) 
 
    {
      int increment = rudPos - newRudPos;
      for (int i = 0; increment > i; i++) 
      { 
        int newAmount = rudPos - i;
        rudderServ.write(newAmount); 
        terminal.println(i);
        delay(10);        
      }
            rudderServ.detach();
    }
    

  rudPos = newRudPos;
    //rudderServ.detach();
    terminal.println("Servo Detached");



}

void setup()
{
  // Debug console
  Serial.begin(9600);


  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

    // Clear the terminal content
  terminal.clear();

  rudderServ.attach(4);
  rudPos = rudderServ.read();
  terminal.println("Rudder Position ");
  terminal.println(rudPos);
  

/*  if (rudPos > 90) { 
//    for (int i = 0; rudPos - 90; i++) 
//    { 
//      rudderServ.write(90 + i);
//      delay(100); 
    }
    }

  if (rudPos < 90) { 
    for (int i = 0; 90 - rudPos; i++) 
    { 
      rudderServ.write(rudPos + i);
      delay(100); 
    }
    }*/
  
  rudderServ.detach();



  // This will print Blynk Software version to the Terminal Widget when
  // your hardware gets connected to Blynk Server
  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println(F("-------------"));
  terminal.println(F("Type 'Marco' and get a reply, or type"));
  terminal.println(F("anything else and get it printed back."));
  terminal.flush();
}

void loop()
{
  Blynk.run();
}
