#include "WiFi.h"
#include "WebServer.h"
#include "mainpage.h"
#include "ZigbeePage.h"
#include "LoraPage.h"
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

const char* ssid = "ESP32_WiFi";
const char* password = "12345678";

const char* wifi_ssid = "HoangHuy";
const char* wifi_password = "hoanghuy2002";

IPAddress local_ip(192,168,2,2);
IPAddress gateway(192,168,2,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

unsigned long previousMillis = 0; // Lưu thời gian từ lần gửi cuối
const long interval = 2000; // Khoảng thời gian 5 giây để xác định mất kết nối

bool isConnected = false; // Biến trạng thái kết nối
bool isConnectedLora = false;

bool accessZigbeeConnected = true;    
bool accessLoraConnected = true;   

SoftwareSerial LoraSerial(26, 27); //TX, RX

#define M0 12
#define M1 14      

float temperature,humidity;
int light;
int humi_solid;
// Tạo một đối tượng JsonDocument cho LORA có dung lượng 100 byte
StaticJsonDocument<200> Lora;

void handleRoot() {
  String htmlContent = MAIN_page;
  server.send(200, "text/html", htmlContent);
}

void handleZigbeeNode() {
  String jsonResponse;
  unsigned long currentMillis = millis(); // Lấy thời gian hiện tại
  
  // Kiểm tra có dữ liệu từ Serial
  if (LoraSerial.available() && accessZigbeeConnected == true) {
    isConnected = true;             // Đặt trạng thái là "Connected"
    String line = LoraSerial.readStringUntil('\n');

    // Chuyển đổi chuỗi JSON thành đối tượng JsonDocument
    DeserializationError error = deserializeJson(Lora, line);

    temperature = Lora["Temperature_Lora"];
    humidity = Lora["Humidity_Lora"];
    previousMillis = currentMillis; // Cập nhật thời gian khi có dữ liệu
    // In các giá trị ra màn hình nối tiếp
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }


  // Kiểm tra nếu vượt qua 5 giây không có dữ liệu từ Serial
  if (currentMillis - previousMillis >= interval) {
    isConnected = false; // Không còn kết nối sau 5 giây
  }
  
  // Trả về trạng thái kết nối dưới dạng JSON
  jsonResponse = "{\"Connected\":\"" + String(isConnected ? "Connected" : "Disconnected") + "\",";
  jsonResponse += "\"Temperature\":" + String(temperature) + ",";
  jsonResponse += "\"Humidity\":" + String(humidity) + "\}";
  // Gửi phản hồi JSON cho client
  server.send(200, "application/json", jsonResponse);
}

void handleLoraNode() {
  String jsonResponse;
  unsigned long currentMillis = millis(); // Lấy thời gian hiện tại
  
  // Kiểm tra có dữ liệu từ Serial
  if (Serial.available() && accessLoraConnected == true) {
    isConnectedLora = true;             // Đặt trạng thái là "Connected"
    previousMillis = currentMillis; // Cập nhật thời gian khi có dữ liệu
    // In các giá trị ra màn hình nối tiếp
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  
  // Kiểm tra nếu vượt qua 5 giây không có dữ liệu từ Serial
  if (currentMillis - previousMillis >= interval) {
    isConnectedLora = false; // Không còn kết nối sau 5 giây
  }
  // Trả về trạng thái kết nối dưới dạng JSON
  jsonResponse = "{\"Connected\":\"" + String(isConnectedLora ? "Connected" : "Disconnected") + "\",";
  jsonResponse += "\"Temperature\":" + String(temperature) + ",";
  jsonResponse += "\"Humidity\":" + String(humidity) + "\}";
  // Gửi phản hồi JSON cho client
  server.send(200, "application/json", jsonResponse);
}

void handleZigbeeNodePage() {
  String jsonZigbeeResponse;
  String zigbeePage = Zigbee_page;
  String state = server.arg("state");

  // Nếu nhận được trạng thái "Connecting", chờ phản hồi trong 3 giây
  if (state == "Connecting") {
    unsigned long startMillis = millis();
    bool responseReceived = false;

    // Chờ dữ liệu từ Zigbee node trong 3 giây
    while (millis() - startMillis < 3000) {
      if (LoraSerial.available()) {
        responseReceived = true;
        isConnected = true;
        break;
      }
    }

    if (responseReceived) {
      // Nếu nhận được phản hồi từ Zigbee, chuyển sang trạng thái "Connected"
      accessZigbeeConnected = true;
      server.send(200, "application/json", "{\"Connected\":\"Connected\"}");
    } else {
      // Nếu không có phản hồi, vẫn giữ trạng thái "Disconnected"
      accessZigbeeConnected = false;
      server.send(200, "application/json", "{\"Connected\":\"Disconnected\"}");
    }
  }
  else if (state == "Disconnected") {
    // Ngay lập tức chuyển sang "Disconnected" khi ấn nút
    accessZigbeeConnected = false;
    server.send(200, "application/json", "{\"Connected\":\"Disconnected\"}");
  }

  // Gửi lại trang Zigbee
  server.send(200, "text/html", zigbeePage);
}

void handleLoraNodePage(){
  String jsonLoraResponse;
  String LoraPage = Lora_page;
  String state = server.arg("state");

  // Nếu nhận được trạng thái "Connecting", chờ phản hồi trong 3 giây
  if (state == "Connecting") {
    unsigned long startMillis = millis();
    bool responseReceived = false;

    // Chờ dữ liệu từ Lora node trong 3 giây
    while (millis() - startMillis < 3000) {
      if (Serial.available()) {
        responseReceived = true;
        isConnectedLora = true;
        break;
      }
    }

    if (responseReceived) {
      // Nếu nhận được phản hồi từ Lora, chuyển sang trạng thái "Connected"
      accessLoraConnected = true;
      server.send(200, "application/json", "{\"Connected\":\"Connected\"}");
    } else {
      // Nếu không có phản hồi, vẫn giữ trạng thái "Disconnected"
      accessLoraConnected = false;
      server.send(200, "application/json", "{\"Connected\":\"Disconnected\"}");
    }
  }
  else if (state == "Disconnected") {
    // Ngay lập tức chuyển sang "Disconnected" khi ấn nút
    accessLoraConnected = false;
    server.send(200, "application/json", "{\"Connected\":\"Disconnected\"}");
  }

  // Gửi lại trang Lora
  server.send(200, "text/html", LoraPage);
}

void setup() {
  // Khởi tạo kết nối WiFi
  Serial.begin(115200);
  LoraSerial.begin(9600);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.begin(wifi_ssid, wifi_password);
  Serial.print("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("..");
  }
  Serial.println();

  // Cấu hình Cho LORA ở chế độ Normal
  pinMode(M0, OUTPUT);        
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);       // Set 2 chân M0 và M1 xuống LOW 
  digitalWrite(M1, LOW);       // để hoạt động ở chế độ Normal

  // Cấu hình route cho trang chính "/"
  server.on("/", handleRoot);
  server.on("/ZigbeeNodeStatus", handleZigbeeNode);
  server.on("/zigbee-node-page", handleZigbeeNodePage); 
  server.on("/LoRaNodeStatus", handleLoraNode);
  server.on("/lora-node-page",handleLoraNodePage);

  // Bắt đầu server
  server.begin();
  Serial.print("Server is Starting:");
  Serial.println((WiFi.localIP().toString()));
}

void loop() {
  // Xử lý các yêu cầu của client
  server.handleClient();
}