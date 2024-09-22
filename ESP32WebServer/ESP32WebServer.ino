#include "WiFi.h"
#include "WebServer.h"
#include "mainpage.h"
#include "ZigbeePage.h"

const char* ssid = "ESP32_WiFi";
const char* password = "12345678";

const char* wifi_ssid = "HoangHuy";
const char* wifi_password = "hoanghuy2002";

IPAddress local_ip(192,168,1,3);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

unsigned long previousMillis = 0; // Lưu thời gian từ lần gửi cuối
const long interval = 1000; // Khoảng thời gian 5 giây để xác định mất kết nối

bool isConnected = false; // Biến trạng thái kết nối
bool accessZigbeeConnected = false;      

void handleRoot() {
  String htmlContent = MAIN_page;
  server.send(200, "text/html", htmlContent);
}

void handleNode() {
  String jsonResponse;
  unsigned long currentMillis = millis(); // Lấy thời gian hiện tại
  
  // Kiểm tra có dữ liệu từ Serial
  if (Serial.available() > 0 && accessZigbeeConnected == true) {
    previousMillis = currentMillis; // Cập nhật thời gian khi có dữ liệu
    isConnected = true;             // Đặt trạng thái là "Connected"
    Serial.read();
  }

  // Kiểm tra nếu vượt qua 5 giây không có dữ liệu từ Serial
  if (currentMillis - previousMillis >= interval) {
    isConnected = false; // Không còn kết nối sau 5 giây
  }

  // Trả về trạng thái kết nối dưới dạng JSON
  if (isConnected) {
    jsonResponse = "{\"Connected\":\"Connected\"}";
  } else {
    jsonResponse = "{\"Connected\":\"Disconnected\"}";
  }

  // Gửi phản hồi JSON cho client
  server.send(200, "application/json", jsonResponse);
}

void handleZigbeeNodePage() {
  String jsonZigbeeResponse;
  String zigbeePage = Zigbee_page;
  String state = server.arg("state");

  // Update accessZigbeeConnected based on the state from the button
  if (state == "Connected") {
    accessZigbeeConnected = true;
  } else if (state == "Disconnected") {
    accessZigbeeConnected = false;
  }

  if (isConnected) {
    jsonZigbeeResponse = "{\"Connected\":\"Connected\"}";
  } else {
    jsonZigbeeResponse = "{\"Connected\":\"Disconnected\"}";
  }
  server.send(200, "text/html", zigbeePage);
  // Gửi phản hồi JSON cho Zigbee Page
  server.send(200, "application/json", jsonZigbeeResponse);
}

void setup() {
  // Khởi tạo kết nối WiFi
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.begin(wifi_ssid, wifi_password);
  Serial.print("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("..");
  }
  Serial.println();
  // Cấu hình route cho trang chính "/"
  server.on("/", handleRoot);
  server.on("/ZigbeeNodeStatus", handleNode);
  server.on("/zigbee-node-page", handleZigbeeNodePage); 
  
  // Bắt đầu server
  server.begin();
  Serial.print("Server is Starting:");
  Serial.println((WiFi.localIP().toString()));
}

void loop() {
  // Xử lý các yêu cầu của client
  server.handleClient();
}
