#include "BLEDevice.h"
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define HM_MAC1 "D4:36:39:B5:F8:8D" 
#define HM_MAC2 "18:93:D7:4A:00:D0"
 
static BLEUUID serviceUUID("0000FFE0-0000-1000-8000-00805F9B34FB");
static BLEUUID charUUID("0000FFE1-0000-1000-8000-00805F9B34FB");
 
static boolean connect1 = true;
static boolean connect2 = true;
static boolean connected  = false;
 
static BLEAddress *ServerAddressHM1;
static BLEAddress *ServerAddressHM2;

static BLERemoteCharacteristic* pRemoteCharacteristic;
BLEClient*  pClient;

// UART mềm cho Lora tryền thông
SoftwareSerial LoraSerial(27, 26); //TX, RX

#define M0 12
#define M1 14  

StaticJsonDocument<100> Bluetooth; // Dùng để chứa dữ liệu JSON cho BLE khi nhận về
StaticJsonDocument<100> Lora;      // Dùng để chứa dữ liệu JSON cho LORA khi nhận về

String jsonData = "";  // Biến toàn cục để lưu trữ dữ liệu nhận dược từ BLE node

//    BLE Callbacks: Dữ liệu từ BLE node được gửi về 
static void notifyCallback 
(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify)
{
  for (int i = 0; i < length; i++)
    jsonData += char(pData[i]);

  // Kiểm tra nếu chuỗi đã hoàn thành (dấu ngoặc đóng của JSON: '}')
  DeserializationError error = deserializeJson(Bluetooth, jsonData);

  // Tách riêng dữ liệu nhiệt độ và độ ẩm
  float temperature = Bluetooth["Temperature_BLE"];
  float humidity = Bluetooth["Humidity_BLE"];

  // In ra dữ liệu nhiệt độ và độ ẩm
  Serial.print("Temperature BLE: ");
  Serial.println(temperature);
  Serial.print("Humidity BLE: ");
  Serial.println(humidity);

}
/* 
bool connectToHM1(BLEAddress pAddress)
{
  Serial.println(pAddress.toString().c_str());
  pClient = BLEDevice::createClient();
  pClient->connect(pAddress);
  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
 
  if (pRemoteService == nullptr)
    return false;
  pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
  if (pRemoteCharacteristic == nullptr) 
    return false;
  pRemoteCharacteristic->registerForNotify(notifyCallback);
  return true;
}
*/

// Connect BLE node HM10 bằng địa chỉ MAC
bool connectToHM2(BLEAddress pAddress)
{
  Serial.println(pAddress.toString().c_str());
  pClient = BLEDevice::createClient();
  pClient->connect(pAddress);
  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
 
  if (pRemoteService == nullptr)
    return false;
  pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
  if (pRemoteCharacteristic == nullptr) 
    return false;
  pRemoteCharacteristic->registerForNotify(notifyCallback);
  return true;
}

void setup(){
  Serial.begin(115200);
  LoraSerial.begin(9600);
  Serial.println("Start");
  BLEDevice::init("");
  pinMode(M0, OUTPUT);        
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);       // Set 2 chân M0 và M1 xuống LOW 
  digitalWrite(M1, LOW);       // để hoạt động ở chế độ Normal
  //ServerAddressHM1 = new BLEAddress(HM_MAC1);
}
 
void loop(){
  if(connect2 == true){
      ServerAddressHM2 = new BLEAddress(HM_MAC2);
      if(connectToHM2(*ServerAddressHM2)){
        connect2 = false;
      }
  }
  LoraReciveData(); 
}

// Hàm nhận dữ liệu từ Lora node gửi về HUB
void LoraReciveData(){
  if(LoraSerial.available()){
    String data = LoraSerial.readStringUntil('\n');

    // Chuyển đổi chuỗi JSON thành đối tượng JsonDocument
    DeserializationError error = deserializeJson(Lora, data);

    float temperature = Lora["Temperature_Lora"];
    float humidity = Lora["Humidity_Lora"];

    // In các giá trị ra màn hình nối tiếp
    Serial.print("Temperature LORA: ");
    Serial.print(temperature);
    Serial.println(" C");
    Serial.print("Humidity LORA: ");
    Serial.print(humidity);
    Serial.println(" %");
  }
}