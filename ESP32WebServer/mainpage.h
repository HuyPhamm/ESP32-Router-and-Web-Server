const char MAIN_page[] PROGMEM = R"====(
<html>
<head>
    <title>ESP32 WebServer</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f4;
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: flex-start; 
            align-items: center;
            flex-direction: column; 
            height: 100vh;
        }
        .container {
            text-align: center;
            background-color: #2cb3f1;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0px 0px 15px rgba(0, 0, 0, 0.1);
            width: 100%;
            max-width: 1200px;
            margin-top: 10px; 
            display: flex;
            flex-direction: column;
            justify-content: flex-start; 
            height: auto; 
        }
        .content-box {
            text-align: center;
            background-color: #2cb3f1; 
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0px 0px 15px rgba(0, 0, 0, 0.1);
            width: 100%;
            max-width: 1200px;
            margin-top: 10px; 
            height: 1000px; 
            position: relative;
        }
        .content-box p {
            margin: 0;
            color: #131212; 
        }
        .node {
            border: 2px solid rgb(0, 0, 0);
            padding: 15px;
            margin-top: 20px;
            width: 245px;
            height: 70px;
            background-color: rgba(255, 255, 255, 0.8);
            border-radius: 8px;
            box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.2);
            float: left;
            margin-left: 20px;
            cursor: pointer; /* Thêm con trỏ chuột để cho biết có thể click */
        }
        .node h3 {
            margin: 0;
            padding: 5;
            color: #333;
        }
        .node span {
            display: block;
            margin-top: 5px;
            font-weight: bold;
        }
        .connected {
            color: green;
            font-size: 20px;
            font-weight: bold;
        }
        .disconnected {
            color: red;
            font-size: 20px;
            font-weight: bold;
        }       
        h1 {
            color: #ffffff; 
            margin-bottom: 10px;
        }
        p {
            margin: 0; 
        }
        @media (max-width: 400px) {
            body {
                font-size: 14px;
            }
            .container {
                padding: 10px;
                width: 100%;
            }
            .node {
                width: 40%;
                height: auto;
                margin: 8px 0;
            }
            .content-box {
                width: 100%;
                padding: 10px;
            }
            h1 {
                font-size: 24px;
            }
        }
    </style>
    <script>
        // Function to get Zigbee status from the ESP32
        function getNodeStatus(nodeId, statusUrl, statusElementId) {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    var nodeStatus = JSON.parse(this.responseText);
                    var statusElement = document.getElementById(statusElementId);

                    if (nodeStatus.Connected === "Connected") {
                        statusElement.innerHTML = "Connected";
                        statusElement.className = "connected";
                    } else {
                        statusElement.innerHTML = "Disconnected";
                        statusElement.className = "disconnected";
                    }
                }
            };
            xhttp.open("GET", statusUrl, true);
            xhttp.send();
        }

        // Periodically update all node statuses
        function updateAllStatuses() {
            getNodeStatus("Zigbee", "/ZigbeeNodeStatus", "ZigbeeStatus");
            getNodeStatus("LoRa", "/LoRaNodeStatus", "LoRaStatus");
            //getNodeStatus("WiFi", "/WiFiNodeStatus", "WiFiStatus");
            //getNodeStatus("BLE", "/BLENodeStatus", "BLEStatus");
        }

        setInterval(updateAllStatuses, 1000);
        window.onload = updateAllStatuses;

        function goToNodePage(node) {
            window.location.href = `/${node}-node-page`;
        }
    </script>
</head>
<body>
    <div class="container">
        <h1>ESP32 Hub WebServer</h1>
        <p>Welcome to your ESP32 web server!</p>
    </div>

    <div class="content-box">
        <p>This is a new content box underneath the ESP32 Hub WebServer box.</p>
        <div class="node" onclick="goToNodePage('zigbee')">
            <h3>Zigbee Node</h3>
            <span id="ZigbeeStatus" class="connected">Connected</span>
        </div>
        <div class="node" onclick="goToNodePage('lora')">
            <h3>LoRa Node</h3>
            <span id="LoRaStatus" class="disconnected">Disconnect</span>
        </div>
        <div class="node" onclick="goToNodePage('wifi')">
            <h3>WiFi Node</h3>
            <span id="WiFiStatus" class="disconnected">Disconnect</span>
        </div>
        <div class="node" onclick="goToNodePage('ble')">
            <h3>BLE Node</h3>
            <span id="BLEStatus" class="disconnected">Disconnect</span>
        </div>
    </div>
</body>
</html>
)====";
