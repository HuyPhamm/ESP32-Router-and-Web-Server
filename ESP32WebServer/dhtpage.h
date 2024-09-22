const char DHT_page[] PROGMEM = R"====(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32 WebServer</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f4;
            margin: 0;
            padding: 0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
        }
        .container {
            text-align: center;
            background-color: #2cb3f1;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0px 0px 15px rgba(0, 0, 0, 0.1);
            max-width: 1200px;
        }
        .sensor-data {
            color: #ffffff;
            margin-top: 20px;
        }
        h1 {
            color: #ffffff;
            margin-bottom: 10px;
        }
    </style>
    <script>
        function getSensorData() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    var sensorData = JSON.parse(this.responseText);
                    document.getElementById("temperature").innerHTML = sensorData.temperature;
                    document.getElementById("humidity").innerHTML = sensorData.humidity;
                }
            };
            xhttp.open("GET", "/sensor", true);
            xhttp.send();
        }

        setInterval(getSensorData, 1000);
        window.onload = getSensorData;
    </script>
</head>
<body>
    <div class="container">
        <h1>Sensor Data</h1>
        <div class="sensor-data">
            <p>Temperature: <span id="temperature">--</span> °C</p>
            <p>Humidity: <span id="humidity">--</span> %</p>
        </div>
    </div>
</body>
</html>
)====";
