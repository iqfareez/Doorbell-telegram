#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "iqf11"; // replace with your wifi SSID
const char* password = "meow4000"; // replace with your wifi password

const int familyPin = 15;
const int friendPin = 5;
const int postmanPin = 22;

void setup() {
  Serial.begin(115200);
  pinMode(familyPin, INPUT_PULLUP);
  pinMode(friendPin, INPUT_PULLUP);
  pinMode(postmanPin, INPUT_PULLUP);
  delay(200);

  WiFi.mode(WIFI_STA); //Optional
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}

void sendMessage(String person)  {
  // Paste the bot token from BotFather
  // WARNING: Don't expose this token to anyone
  // I'll revoke this token after finishes this tutorial
  String botToken = "5772967563:AAGwMe7xApmNTAQuwa-j9bj9AuiGYIczM-Y"; 
  
  // Chat id (can be also channel id or group id)
  String chatId = "5251644666";
  
  // message formatted in markdown
  String message = "*" + person + "* at your front door\\.";
  
  // Construct the request URL
  String url = "https://api.telegram.org/bot" + botToken + "/sendMessage?chat_id=" + chatId + "&text=" + message + "&parse_mode=MarkdownV2";
  
  HTTPClient http;
  Serial.println(url);
  http.begin(url); // print url (for debugging)
  int status = http.GET(); // send the request
  Serial.println(status); // should get 200 if the request is successful
  http.end();

}

void loop() {


  int inputFamily = digitalRead(familyPin);
  int inputPizza = digitalRead(friendPin);
  int inputPostman = digitalRead(postmanPin);

  if (inputFamily == LOW) {
    Serial.println("Family is pressed");
    sendMessage("Family");
    delay(1000);
  }

  if (inputPizza == LOW) {
    Serial.println("Friend is pressed");
    sendMessage("Friend");
    delay(1000);
  }

  if (inputPostman == LOW) {
    Serial.println("postman is pressed");
    sendMessage("Postman");
    delay(1000);
  }

  // the delay is placed to avoid button spamming
}
