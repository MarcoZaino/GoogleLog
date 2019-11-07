/*
 * GoogleLog
 * Logs param to google sheet
 */

#ifndef GoogleLog_H
#define GoogleLog_H

#include "Arduino.h"
#include "HTTPSRedirect.h"
#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"

class GoogleLogClass{
  public:
    void service(String sheet_id, String Sheet_name, String fingerprint);
    void update(unsigned long google_update_interval, String google_sheet_payload);

  private:
    //Google scripts
    const char* gl_host = "script.google.com";
    int gl_httpsPort = 443;
  
    // Write to Google Spreadsheet
    String gl_url;
    String gl_payload_base;
    String gl_payload;
    String gl_payload_tail = "\"}";
    HTTPSRedirect *gl_client = nullptr;
    String gl_sid;
    String gl_fp;
    unsigned long interval;
    unsigned long previousMillis;
};
extern GoogleLogClass GoogleLog;
#endif
