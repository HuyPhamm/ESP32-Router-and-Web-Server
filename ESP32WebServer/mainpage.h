const char MAIN_page[] PROGMEM = R"====(
<!DOCTYPE html>
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
        .zigbee-node {
            border: 2px solid red;
            padding: 15px;
            margin-top: 20px;
            width: 250px;
            height: 70px;
            background-color: rgba(255, 255, 255, 0.8);
            border-radius: 8px;
            box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.2);
            float: left;
            margin-left: 20px;
            cursor: pointer; /* Thêm con trỏ chuột để cho biết có thể click */
        }
        .zigbee-node h3 {
            margin: 0;
            padding: 0;
            color: #333;
        }
        .zigbee-node p {
            margin: 5px 0;
            color: #000000;
        }
        h1 {
            color: #ffffff; 
            margin-bottom: 10px;
        }
        p {
            margin: 0; 
        }
        .zigbee-node-status {
            font-size: 24px; 
            font-weight: bold; 
            margin-top: 20px; 
        }
        .connected {
            color: green;
        }
        .disconnected {
            color: red;
        }
        @media (max-width: 400px) {
            body {
                font-size: 14px;
            }
            .container {
                padding: 10px;
                width: 100%;
            }
            .zigbee-node {
                width: 40%;
                height: auto;
                margin: 30px 0;
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
        function getZigbeeNodeStatus() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    var ZigbeeNodeStatus = JSON.parse(this.responseText);

                    // Get the status element
                    var statusElement = document.getElementById("Connected");

                    // Check the connection status and update the text and class
                    if (ZigbeeNodeStatus.Connected === "Connected") {
                        statusElement.innerHTML = "Connected";
                        statusElement.className = "zigbee-node-status connected";
                    } else {
                        statusElement.innerHTML = "Disconnected";
                        statusElement.className = "zigbee-node-status disconnected";
                    }
                }
            };
            xhttp.open("GET", "/ZigbeeNodeStatus", true);
            xhttp.send();
        }

        // Update status 
        setInterval(getZigbeeNodeStatus, 1000);

        // Fetch data initially
        window.onload = getZigbeeNodeStatus;

        // Function to redirect to a new page when Zigbee Node is clicked
        function goToZigbeePage() {
            window.location.href = "/zigbee-node-page"; // Điều hướng đến trang mới
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
        <div class="zigbee-node" onclick="goToZigbeePage()">
            <h3>Zigbee Node</h3>
            <span id="Connected" class="zigbee-node-status disconnected">Unknown</span>
        </div>
    </div>
</body>
</html>
)====";
