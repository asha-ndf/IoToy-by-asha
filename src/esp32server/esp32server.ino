#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
WebServer server(80);
#include "secret.h"
#include "webpages.h"
#include "modes.h"
#include "motor.h"

#define MPIN1 33 //A5
#define MPIN2 32 //A4

volatile int nowmode = 0;

// WiFi情報
const char *host = secret_host;
const char *ssid = secret_ssid;
const char *pass = secret_pass;



// 初期化
void setup()
{
  // シリアルポートの初期化
  Serial.begin(9600);
  Serial.println("\n\n");
  // WiFiのアクセスポイントに接続
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  // ESP32のIPアドレスを出力
  Serial.println("WiFi Connected.");
  Serial.print("IP = http://");
  Serial.println(WiFi.localIP());
  /*use mdns for host name resolution*/
  if (!MDNS.begin(host))
  {
    Serial.println("Error setting up MDNS responder!");
  } else {
    Serial.println("mDNS responder started");
  }
  // モーターの初期化
  initMotor(MPIN1, MPIN2);


  // 処理するアドレスを定義
  server.on("/", webRoot);
  server.on("/set", webMode);
  server.onNotFound(web404);
  // Webサーバーを起動
  server.begin();
  xTaskCreatePinnedToCore(subProcess, "subProcess", 4096, NULL, 1, NULL, 0);
}

// 処理ループ
void loop()
{
  server.handleClient();
}
