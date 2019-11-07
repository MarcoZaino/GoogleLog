#include "GoogleLog.h"

void GoogleLogClass::service(String sheet_id, String Sheet_name, String fingerprint){
  interval = 1;
  gl_sid=sheet_id;
  gl_fp=fingerprint;
  gl_url = "/macros/s/" + gl_sid + "/exec";
  // Fetch Google Calendar events for 1 week ahead
  // String url2 = String("/macros/s/") + GScriptId + "/exec?cal";
  // Read from Google Spreadsheet
  // String url3 = String("/macros/s/") + GScriptId + "/exec?read";
  gl_payload_base =  "{\"command\": \"appendRow\",\"sheet_name\": \"" + Sheet_name + "\",\"values\": \"";
  gl_payload = "";
}

void GoogleLogClass::update(unsigned long google_update_interval, String google_sheet_payload){
  interval = google_update_interval;
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    //Do update
    // Use HTTPSRedirect class to create a new TLS connection
    gl_client = new HTTPSRedirect(gl_httpsPort);
    gl_client->setPrintResponseBody(true);
    gl_client->setContentTypeHeader("application/json");
    
    Serial.print("Connecting to ");
    Serial.println(gl_host);
  
    // Try to connect for a maximum of 5 times
    bool flag = false;
    for (int i=0; i<5; i++){
      int retval = gl_client->connect(gl_host, gl_httpsPort);
      if (retval == 1) {
         flag = true;
         break;
      }
      else
        Serial.println("Connection failed. Retrying...");
    }
  
    if (!flag){
      Serial.print("Could not connect to server: ");
      Serial.println(gl_host);
      Serial.println("Exiting...");
      return;
    }
    
    if (gl_client->verify(&gl_fp[0], &gl_host[0])) {
      Serial.println("Certificate match.");
    } else {
      Serial.println("Certificate mis-match");
    }
  
    gl_payload=gl_payload_base+google_sheet_payload+gl_payload_tail;
    Serial.println(gl_payload);
    gl_client->POST(&gl_url[0], gl_host, &gl_payload[0]);
  
    // delete HTTPSRedirect object
    delete gl_client;
    gl_client = nullptr;
  }
}

GoogleLogClass GoogleLog;
