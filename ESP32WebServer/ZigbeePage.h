const char Zigbee_page[] PROGMEM = R"====(
<html></html>
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
        .Zigbee-data {
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
        .Zigbee-data p {
            font-size: 36px; /* Adjust the size as needed */
            font-weight: bold;
            color: black; /* Change color if needed */
        }
        h1 {
            color: #ffffff; 
            margin-bottom: 10px;
        }
        p {
            margin: 0; 
        }
        /* New CSS for temperature and humidity section */
       .sensor-data {
            margin-top: 50px; /* Dữ liệu cách từ Zigbee Node */
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            gap: 40px;
            width: 100%;
        }
        .sensor-item {
            display: flex;
            align-items: center; /* Centers items vertically */
            justify-content: space-between; /* Adds space between icon and text */
            gap: 100px;
            width: 100%;
            padding: 10px;
            padding-left: 600px; /* Adjust this value to move items to the right */
        }

        .sensor-item img {
            width: 100px;
            height: 100px;
        }

        .sensor-item p {
            font-size: 50px;
            font-weight: bold;
            color: black;
            line-height: 50px;
            text-align: left;
            flex-grow: 1; /* Ensure the text takes up remaining space */
        }
        /* CSS for the Connect/Disconnect Button */
        .status-button {
            position: absolute;
            top: 20px;
            right: 20px;
            padding: 10px 20px;
            font-size: 18px;
            font-weight: bold;
            color: white;
            background-color: red;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            width: 150px; /* Đặt kích thước cố định cho nút */
            text-align: center; /* Giữ văn bản ở giữa */
        }
        .status-button.connected {
            background-color: green;
        }
        @media (max-width: 400px) {
            .sensor-item {
                flex-direction: column; /* Xếp icon và chữ theo hàng dọc trên điện thoại */
                justify-content: center;
                align-items: center;
                padding-left: 0; /* Xóa padding-left để tránh tràn rìa điện thoại */
                gap: 10px; /* Giảm khoảng cách giữa icon và chữ */
                width: 100%; /* Đảm bảo phần tử chiếm hết chiều rộng */
            }
            .sensor-item img {
                width: 70px; /* Smaller icons on mobile */
                height: 70px;
            }
            .sensor-item p {
                font-size: 35px; /* Giảm kích thước chữ trên điện thoại */
                text-align: center;
            }
            .status-button {
                position: absolute;
                top: 480px;
                right: 90px;
            }
        }
    </style>
      <script>
        function toggleConnectionStatus() {
        var button = document.getElementById("statusButton");
        var newStatus = button.innerHTML === "Disconnected" ? "Connected" : "Disconnected";

        // Send a request to the ESP32 to update the connection status
        var xhr = new XMLHttpRequest();
        xhr.open("GET", "/zigbee-node-page?state=" + newStatus, true);
        xhr.send();

        // Update the button appearance
        button.innerHTML = newStatus;
        if (newStatus === "Connected") {
            button.classList.remove("disconnected");
            button.classList.add("connected");
        } else {
            button.classList.remove("connected");
            button.classList.add("disconnected");
        }
    }
        // Hàm này dùng để lấy trạng thái Zigbee từ ESP32 và cập nhật giao diện
        function updateConnectionStatus() {
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function() {
            if (xhr.readyState == 4 && xhr.status == 200) {
                var response = JSON.parse(xhr.responseText);
                var button = document.getElementById("statusButton");
                
                // Cập nhật nút dựa trên phản hồi JSON từ ESP32
                if (response.Connected === "Connected") {
                    button.innerHTML = "Connected";
                    button.classList.remove("disconnected");
                    button.classList.add("connected");
                } else {
                    button.innerHTML = "Disconnected";
                    button.classList.remove("connected");
                    button.classList.add("disconnected");
                }
            }
        };
        xhr.open("GET", "/zigbee-node-page", true);
        xhr.send();
    }
        setInterval(updateConnectionStatus, 1000);
      </script>
</head>
<body>
    <div class="container">
        <h1>ESP32 Hub WebServer</h1>
        <p>Welcome to your ESP32 web server!</p>
    </div>
    <div class="Zigbee-data">
        <p>Zigbee Node.</p>
        <div class="sensor-data">
            <div class="sensor-item">
                <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGQAAABkCAYAAABw4pVUAAAACXBIWXMAAA
                sTAAALEwEAmpwYAAALgUlEQVR4nO1de1BU1xk/ah0lTlvHpulM+0fa/tWknXamaaYRTCKI4LP4gAg+eIggEpdERAyk
                PhqhGp+FdCROm05NKtTH+EceojEaHyiISKJRUZBdCK9VdhfOtxhjmvF0vvXey7l3Dyvv3dx7fzPfLHvv3nPP+X585z
                vnO+d+lxATJkyYMDFUYIyNAoDnAWA7AJRTSm9TSr8BgC4AsALAOQDY6na7wxljY3yVJZXzFgBcAoAOAGDS5yXp+CST
                yR7AGAsCgGwkQFLcI4VS2kopXdPe3v59viy32/0bSunZXpZR1tXV9bue6mVIAEA0pfTL3hIhUGobpXQGlkUpTaCU3u
                vj9fcppUnE6GCMjaSU5lNKH/SXDE6pDyilpf0tC6+rq6t7mRicjJKBEjGY0tHR8b+ioiKPpRkOlNL8nhTjcnawIx+c
                Y+tz/skWxbzBIkNXewT/xmN4Dn/TGyVfu1rP8jbuZdF/WsemvpDp+cz/y17PcdHva2trbxJCfkkM6DMeiBRy7Eg5Wz
                B3A5s8McOnxM7byI6VVvgk48iH51nk5NXC6yMmr2alH50XXpeZmbmBEDKeGGU0RQUOvLOTssKdBx9JhFYKdx30XOtl
                GV/cUpExZdKr7KU56z2f8jE8j7/TXnvq1KljhJBwYgQAwFrRf6WWjNnTX2c7dx9ln1Q1sy9a73vk+MUmz7HZ03K9SN
                GWt2nDv5Xz6Sk72JeNrZ7j+Inf5XPYnWmvtdlsVkJIHCHkx0Tvkz4qmGdgN8UrODPrX+xyy9fsposJ5XLzPbYq6x3V
                NR8fvaAqMyZqnXKurrZRde7mjQblXEzUei9CHA7HXYmQZ4ieAQ9nzl4OnPcZSMYN54MeyZClxvFARUrc/I3M5ep29B
                EvrlZ8hcgi8bjn/Ive5zs7O7+VCJlG9Ax4GA5RO94Pzqm6KV+WoZXPm75SdV+8k8b/fPl47c0G1T1v1NiUc+hXBBbS
                JREyn+gZAFCubTwOY2XloH/oLRmy7Px7qXL9htffUcrdvOk9oQ9pbGhR+ZAtef/xIsRqtd6SCIklegal9I628Qtj3l
                CUc+JSc58JQUcvX4/zFN4KpoVm+Rxl4Xn8nbZOJ0+eLDWEhVBK72sbzyvtSmvvuyvFwbd8rVIwX/YnH1eqyucFj584
                flHoX9LT09dJhEQSPQMEjeeV1FcyZOHL0JaPFoDdF1oHOnD8xO8iy0Cpqam5JpGB8nuiZ4AfCOmLuFyub2JiYrI4Qn
                5E9AwIYEIwlFNYWFjIkRFG9A4YICHvXmMs8zRjr36qloES4nK57mvIeIkQ8gOid8AACVkjIGOghKDP0HRTKE8SIwAG
                aiHX+2chVqvVipM9/NvhcLitVms9Dm1Xrlwpj6Z4yzAGGf70IUSt9J4kzBDdVIAREilN9uRJX6Q0tH2cGBHgf0JMmI
                QEMMC0kO8WIV2pi33K1aiZ7NikSaw0JEQlZpflJ0KOPe9NhkmIPy1kjmkhAUVIVw9idlkmIfoAmBYSWACTkMACmIQE
                FsCchwQWwJyHBBbAnIcEFsD0IYEFMAkJLIBJSGABTEICC2ASElgAcx4SWABzHhJYAHMeElgA04cEFsAkJHDAGBtrEh
                IguHv37k8BoMJfhISGhlrMjXISMBcVpbS5p93nk4eBkLa2NseCBQtwh7uxAQBPiR70BEmqL9UMy74slPb2dnd1dfWz
                xKjo6Oj4OaW0RawcJyvYcYCFhXQ/ETt9kmVQ9mX9bfv+HjMF2e12x759+35FjAbMhQgAF0VKaWhoYcnxW1RKDA+2sA
                Pzk/u9L2vBxGWq8lIS3mQNtmYhKY2NjdbY2NifECMBAApFyrh+rV6VgwQlK2IFq02I77f/QGlMimerIlZ4pW/S5jiR
                5cyZM+8TQoKIEYCZPkW5sGzWZk/ysG6ryGAl85YNiAhe3KmL2X/nL2NTgi3KPfB+mLlBWxesX15e3lpCyCii97R9oq
                7K0e5kiQv/2v3QfoiFnV+UNGhk8HIqLslTvnyvtOTtzOl0CbrOhsagoKA/ED2DUhov6iK2bylRFBQRnMHKFiYOCRk8K
                byl4ABCVK+ioqIiQoh+/Qml9HNto8vPX2GhIa8oyjkU/WjnPRiC3Zd8T8xv8ln1DS9CmpqaWkaNGoVJL0cQvcHtdk8R
                /RdilyErJicybVjIkH0K7+hXLt8ltJLs7OxNhJBfEL0BAPZ6jWZOVSsKmRqcwaxJAxtN9VVuJcZ7Bg9yHSovXPMipLKy
                sowQMpPoMHVfu7axOVlvK8rYOSt1WMmQZfPM5Uod/vzaP7wIwefXx44du4gQ8gTR01DXa1bcdkdJs4cy0LlGVz+lJj5B
                qQPm/sURn7auGRkZmBZ2ItELKKWrtY386P3u1H2pU9L9QkaXJImhLyt1wYSb2roeOnSoWHpuXR/OHQDe1TZy1/b9ihLe
                jvJPd9Ulye6oFKUumI5WW9eKiorTUnheHwkEpPdxqBqJoxpZCSdih2YS2NVLOR67VKnLK+kFXoRg7hOJkKeIHiDKVM2n
                fq1LTPArIbUJ3X4E6yWIArdLhDxH9AAAoNpGzgjPVpRwe9kSvxJiT16i1GVmeLYXIU6n866ucixSSr/VNpLP/klT/EsI
                TekmBOvlI3FyFNEDAMCtbSSfDdThZwtp5yxk+pQ1Igu5JxESTfQAfOWQtpF8qP2Wn31IXWK3D8F6CXyIU1eJk0WjLEta
                9ygLo6/+JOTTuCSlLhkrCnxlstaHhQBAsbaR2zYXK0rYE5XiV0KKuHnI9i3FonjWWYmQOUQPAIBcbSMxMb6ySBTm35l6
                Spjvmfrhw4dLdDXKEsWyWltus/AXVnmUEOqJZfnHj9zk5iD4Dqq2tjtehHDJMPURz2KMjRaNtPho747Z/gmfbJ3VHe3N
                XbNHOAcZN27cYomQp4leAADv+VoPiQyxMNswr4fUJ8Z7lozlOpw9/ZkXIeXl5XIcSz+xLERnZ2eEtrEoqUlbFYWsHcYV
                Q5TsiDTVZgdR/XJycvK4EZY+or3ciyKvaht8qapGtaZ+cJjW1PfPT1buife/WOm9WtjU1NQ8evTohRIhfyRG2XXCD4Gn
                BmewcwuHdl6Cu1pwN2T3ULdEaB0FBQVvcd2V/nafMMa+Rym9om24w+FkSxdv7g5fhFiGjBQkg9+XhdtWRfuybDZbg7R0
                Gyetqeunu+rNzkVrfZMqnIKWMtjd14HoZSrLwBeD4Y5JbV2wfhaLZb1hku9LL4/3UkTNdauKFJTXItMGvBsFR1O8A5fJ
                uHHdKuyquHdMya/G06d18LvfnU7nZZEyrPVNqu5L3s24bdbyPm+EwEnf1pmpHmvjy8NuSmQZUtyqfsKECfG6HOr6gsvl
                etLhcHi91RMkn7Jt8z7V6EvZEBGW7lmDx4Ak7qu6k/wwdI+f+B0DhRib4sMh/Ghqx5slQp8hP0kVFha20jDvmNLCbrf/
                1ul0gkg5AMCqKq+ztKXbvBTbH8F5Bg6xfT1BJT3Wxr8pYSQxGioqKp7BNeueFAUAnhl0zpo9nlhTX0jA3+N1ZWe8Z+C8
                2O32jvj4+LUcGbgy+BgxKoqLi39ts9nqfSnNE5Bsvc2OHin3hMhx3QIf7pHX5vETv+NxPI9RW1GgUOAzbmm6qXmEkB8S
                o2Pu3LlPlJWVfdjTi+0HW/A+OJoaP378Eo6MOYZ5cX0v8VhmZqYFRzpDSUZDQ0ODtD00TuMzjNtN+cDIoKCgZ/Pz87dZ
                rVbbYBLR2NjYVFRUtJsLp/OjKeM58D5iwpgxY6bl5ubmX7hw4YzT6fyqPyTgegZuBcWoLRcolGW6YeYZg4QRhJCf4WwZ
                /6sxnIHLqVVVVWXYrdntdpdMFCoed4fgcXymA3+HK30Ca0CZIT2Eo+8Z+BBihBRtfU5al4jrh0RL12M5JhGDTM7j0nJq
                sOSM53BERUvfI6U18Kel35skmDBhwgQZVPwftzkpP21UYYEAAAAASUVORK5CYII=" alt="Temperature Icon">
                <p>Temperature: 25 C</p>
            </div>
            <div class="sensor-item">
                <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGQAAABkCAYAAABw4pVUAAAACXBIWXMAAAsTA
                AALEwEAmpwYAAAYB0lEQVR4nO1dCXATaXbWJrubTbKVbOXYXFuVTTabSlWqkmzVZncrmWRms9lkMoMks2COgYEZmDEMLD
                CDJdtqCcs3BnPblmQzwDAYD8cAxla3fBtQy/eB8X3jGx/4AIx1WHqp93ul8YC6JVstZAa+qr+gCuPu/r/+3/1ei0Qv8RJ
                P4lV1ydfFEbl/J6H0b4oVdKiY0h8TK/QnpRRzRaoyFElVBqNUacgRK+gMMUXrJAp9jISiN0ki9D+Vqq995+WO+ohX1SXf
                kipzXsONDVIaKiUUbZNQNEiUhrl1scWP3zlUZnnvWCVsS66BnZp6sj5IqYWQE9Ww5XD53MZE4+yqyHwz+T8UDVIlPSKlk
                Cz9O28o9X/9kiAvEBx86belVM7/Sin6MylF42ba1yfcmN2hrQdFZg/EXRuBg8wUJBm8X4n6+6C+NAB7z7QSolaqci3zBB
                naVkToZRJ51l++JOcJrFTnfVesoOOkKsMokrD5UKkl/FwX7NffX9TmJ3mxkNCoK0Pwa90dWB2Vb8XrSZWGYnGE/vUXnpiV
                Ycz3xAr6OJ6G4OgC80enmiEhZ0xwEpJ4yFFd6IOtRyvsEkrvkKoMDRIqZ6Varf6tF4qcFers38MTIaH0trWxxeawsx1wkJ
                l8ZkQkuVkx1+7B+yeq7RIlMydRMneCqJyfiF4ESClGLFUaBlZG5lnknyIRgSMhyc2KyxolukZC0Q6xikkPVuf+keiriGB1y
                bclSuY8Pui2lFp7Yo7w+iFJwEVl3oXgmEKLVMWMr1AwvxB9lSBWMP8kVTJdq6LzLZGX+gO+2UlergP0BGxPqSX6ZYWCiUEr
                UPS8Q6zUr5dQjOWdQ2W2/TnjPm2O6kIv7DnZDCHJ1fBuEgtvxRfDmuh8+NW+XPQzIDgqD9bHFcHb+2/Ae0fLYae2HuRn24m
                57AsxaPEFqXKtQSrm5nPtZEoU9B40K3enNzqWoisSsscALa93D7Gwcl8uBKkY2Hn8FhzIrIXzhe2QX9UHbMMQ1LSNwu3OMS
                hrGoaSugHINvWA7nojUCfLYUNcIXEM34orgu3JNbDvQt+S9FbstXsowqxSFdOykjL8hej5AnxNQunjxRRtl5/tWPTDKy/0w
                tYj5YSATfuL4DTTDNWto/DYbIOloG/kIdBld0F9phKkKgbWxxXDrrQGWOyJ3Z89BuvjS6xolARF0H8vel4gUegTpErGpjjf
                vagHps73wKYDtyBIycDBC3VQ3zUODocDhMTEAzNcZ7th68ESWK3Og526erLR3t5jon4CNh1krVIlPfpchGBWUPodKKZwcxf
                jA2w5UgorVQZIudYA9yZmwN+YszuIeNt2+CYER+VD6Jk2SDJ45wsdZCbg7QNGJKVXrLj+Z6LlrcC9F1Moyz/8uJnoB0V6Of
                SPPvQ7Ee6IwRODBsGmA0aiK7w6KTn3YV1csVWiNNT9MjTv90XL0bRFawoVuFfyOGccthwugzVReVBcOwCBxvj0LKhOVxIxF
                pHR5RUp8ddHYVVUvkVM0Rmi5QR8QyQU3bn5UKnNGwsm5uowrI8tgl0njDA4/mjRm2e3O+DBzCwM35+G3pEJ6BoaJ6tn+D70
                j07C+PQjMFsWbwCgvrpU0kl0GCp9b0hRX+oHCcXMSSLod0XLBRKKycQ3xRurBUPhKLPjztWAxWb3erOmZ2ahrX8Uypp6wFD
                ZAkxFs8dVVNcOtzsHYXB8CubmvL9WbfsYrFbnwvaUGq9ibOgbSZW0Wawy/OOyiE1hOMQbDxzJWB2ZC8ev3CFvuSd89vl1iD
                +iA5qt84oAhmflVbfCne4hePjY7BUp7f1T8FZsAYScqPLot+C/b0pi0UepCWikOPijS78rVdL921Jq7N6IKTwZSIY3liyKn
                g3bZPCT18TwxpqtQJc1gaGiGdjGbmjpvQdD49Mw/WgWLLY5mLPPv/1W2xw8NlthbOoREV817f1QUNP2JWLwd9R1DMCsxerx
                HnqGH8Da6HzYkVrn8WXDaECQkrFJFPT7ASMEQ+i/isyz7NfziyoUZagz4s5VezwZj2YtRCzh5r21LZQQgiszK9erTXSnF0Y
                mHxJyDAtPTFUrdA/fB09o7LkPq/YZSMTAEym70hpBStEPXlcwfxqQ5BLmMzCX4ek4ozWFCtyTzhgcn4b86lbXpn18mXER8v
                b7e3x2Eh/NWqCuc+BLJ6aqtY+cMj7cuD0IQSoDUeD8zzoBa6ILMUV84pkTghddE1to8eRMoZ+Bpq0na6p9YPRLG9Xce48o4
                vd3hbtIKausASEwPj0DN+o7XdfCv8+Y+U9f8tU7sC6uEDxJA8zxSCna+kzjXUERV/8YrQq8OK/euHaPOH2e/Iymu/dcm1NY
                0wajU184iGxZlYuQbbsjQCjY5uxEl7gsstp2XoVvsc4Rr/6D5FoPp2SS5FEkEcyBZ6o7gqMLLJ5Mwq1HyiA8rYxXiS88GSW
                3O4hYeRKbQj5ykXL7TpNQnDx1/eK6dnjMo6dQn2Bw0pNFKTvTDhIl8/iZhOpJqY7SMOZJyWEsC2NTfOEQ1BkLyeBS2gUlRh
                chH4ZHgdDoGBxz3Qfb0M1reGDQc/NBI/8poSdRMlikCv02vxOC5TIYr8JcBd9NbT5ghNRrDZwPhifBqcBRTLk7GU7gBq3dv
                MNFSktbBwiNxp5hFyn4dy6MTj4maQHqs17e59+eUusIUtKV/ieEYi5sTiq1espn4NEeGueO2pY333VtwMjEA48blsMUuAiJ
                UCeC0EALzmlu48LwCxeOXq6Hd5JYXkIiLw0Apn6DlMwP/FveSdFmTGny6o6j5eRo8zl9C60pb2CzzYFk7VZCyM9+LoGunl4
                QGuhUokeP93WzvhPsHMoPxTCmjNWXB3n3YU10kVlM0Qq/ESJR6H+O4oqvohCTPWizY3KJ600sqetwWTZo7XiLS1f1rlMSvf
                8o+APdQ+Oul6VvZILz50I1pbBDw+/Bb0+tQ+/9lj8JicFaW76bQGX/TmIxpxPXt+B04ElZDCwWC7yxahMh5N/+OwiGhkdAa
                JAX5vb8C4N/cj1HbkUvrIkp4A0+KjK6iU+CISa/EBKkYqqwkoOPECxIwBw4F4wNXb8xMTs4RQIfzmZ+7jolB49qwR/AkL7z
                pbnHod8ezFhAqmRg38U+3kJvlCgoWfzSnyFR0lasQucr1UFHsLptlDOE7nzQzkH3Is0TZmYewy/E6wkhr/zyVzA27jketZQ
                sotMCrO3o5/y5XSdY2J3OnzdZF1c8K1bQlOCEzDfL0BCbxV3jhHVTaBJyVYdgPsMZceVzwDwh7XSG65Sc0J0BfwBD9XivuV
                UthCB3OMO0wLtJJn4D51ilXULR5wQnBDuXsFmGL3aFiRqsm+JC6W/MSgyh+4LpBw/g1f8LJoS8+nowTE5Ng9BAUeXJBMY6s
                FXqXI8R4KB9htuCE4JtZGvjingVOlYUHvzMvbmLb5kz04f5DF9xLPUU/PS/guC1dRGwLeE67DtdAek5TdA5OAVCAHMrznA9
                hle46r1QamBunWtP0EWQKplHwhNC6Y95cgjRWcosbHd78w9mzK43DpNLvqKxcwjE8suwUsXAtuRq2KG9TcpL0T/IKGgDIeC
                MCNd2uA+OosmOIlrFo9jVl9FBpOF1NfMHwhKi0J9671gFb0UJlmtieac7YEGCkxBU7r7AYp0jhW6bD7JPNfiEn+skm8R1H4
                tBdVsfuV+0DLmwKaGIhNy59iTm6j1CyJtUzl8JSgh2u273EHrGwmestfVkSlqsSysJdYIuvwtrovI5u61+rWuAtxOKfE5oO
                eNb6MByIeTQTdh7upVzT1CcISErFNn/ICghQSqmCDtd+QjhM3mxTMdJCJfV4i0SzteQ7lvOTcia34TeEd8K71r6RlzpXi7s
                SWFhz8kmXleAEBLB/KuwhChzb2GjJB8hWM+EVeieQty+luvuO10J2JnraRPa+hYXCeA00ytbOH9Gpi3l9UXQkyeEKJlXhCW
                EMtDYB85HCJqA5c3uLSgsKHCdkEXEr9whPaeJKHA+fwijzehN+wIMfOL9opPIhR1Hb/IWQGCBB9Eh4Tn/LCgh2HSPTfl8hK
                yLLSQFzJ4ivBhV9QWdg1PEmkIF/vQbOQEb9t8ghXi+AovsnDEtLrx7oJhkCPnKg5AQsfL63whKiFih12IzJB8hbyfeIM0y7
                oDOlTe5Bm+RUdBGrClU4Kgz5jus+mBdbBGsj86F8SnfLDmEMz+CuRsurInOg/AM7raL6CvD8yJLnf0nAhNCx23Yf8vMRwi2
                kemyG93eOKZnv4hjudczi0V+VR+xppzjM4i9/4EWNoSE+2xhYeATlTneb0O3e8tx8qGZXDP6yhCv+MQAY0hI9TeEJSQiZzP
                ODuEjBCPB2EbGBSwiwAesaBEuueRwOIjH3No3Ce/tVrliXKUVvoms+w9mPKYJSNGDkiGnk2tPQk+3glRlGBCUDEIIxfwM3w
                YMKXNdHBsssaeP6+V0FqnlVbV4Vdu7WLALSoa27pQLVo3Cle/HNrkN8cW8evWD1DpYH5tfLjghWNKChGDBtCcFxlVpgiETT
                3kGX7FpQclQXb178ekNjA3drlQuFxIyasj0IT5CthxmraEa1h6awn4kPClKZgSn6ngKn+CbwxX7ceas+RSlLyhYUDK0J0y9
                pN+x0ADhCiyiqFwfU8AbNsF0dqiGhYSL9Y5QLWuXpbL/IywhFJ2x5UiFjY8QbD2OPF3J+bCoIJ0PO/XoMQgN+xMlQ82tiy8
                Zwnpfp0PIVSvW0jtBfB2uSC/qlYiTVRD32W24MeQATV6XQ641PZRrb/xQMEKwSwjnTfH1S2DkE81R7HZ1ByzXNFTOE4IV6f
                5AjqFwySVDU4++yGqiH8KF1KwG2HKYOzm179MmoD6ugPweC9y6B3BzyAEJF+9Y5VpTW2iSQD2J2AaMOgLnTXHdCJKFYiuL7
                fbocOHCKLDQsNnmYPXG7aBOOAK9/d73L6IYcuoOPB1cytxqs8O66HyQfeLeIYy60AVyrQmymqYJGc5V0GsF6nS5NVxnuigS
                ClIl0+YppoX9eRge5woiohjIW1C16Gv0l4uUxaJj4It4G18SDf0f7NrFnvUnnz0+a4iQca783pfIcK6s5gf473OyFFaYxh6
                xgg5bHVVg5kvlYsswxrWwr4IL2OHkzFlPPhRelywF1e39rlAJV70Y6qj3k26QCMFT0kE/DuEnKyCZ6XRLhnOdLR0CmYa17t
                WYfuQzITijED1PDFN4chKxfJ8v1I6ZOOxuWi6wOxxEr03wvCBFNf2wKjLX7VgO1dk7EHWuFkoG7byE4Dqc1WKTa029O1JKv
                u0zKTiWdevRSt64Fpp82FPIp0ueN8yYbbAxvtBty3T0xS4I05UC0/HYIxm4ivpsoDxdYZFp2DShKuAdmJ7kIwXHVaCsxab8
                rwLScprgrfiip0IlidkjINeVQgaH3uBa1xqnQaZl7Xs1rMT3U6I01OOMQj5CUM/guArVqUrBh8g8a9zpGicJOJw092WrcgI
                Up2rgcFbroshwrvTiuw65zjSx+2SZbzNTcHonDozEGYV8pGA4BcdVXL7BHYJY7ph6ZCFR5Z1uiqsjM1uJv1HYZ10SIeg0Rp
                +rsci1JoNPhGCDPE7v3HKknNdzx4WzQ/DtwgkJzxusNjuEp5WTsVHYGbXwuRKu3yMm7sWa8SWR4Vz6tkdoddlDNaZ1Pp4S+
                sdiinbw1fs6F5qJOK4CJyQ8L3A4HJCYWUuSXpgE+5KoMkwCdboGjmS3+USGc50s6cXQytTetBLfElliikkPji408+UEnGtb
                Sg0ZV4ETEp4HMlKuNRBLMebq05GJ6AudQJ2qJNaSEIQQ0ZVRa5ZpTZ/4RAjOtcVRqt6M18AKjJDjVbA2Kp8kd5azmErMrCV
                kYGvak89xIGcMwnRlkFk5KggZzpXd+pCIrr0pt3wbS0u+YkDRdk+tbvOkTJHZITiugs+TDxQmH5qJzkAx5e5kEAfwk9sQf+
                EO3BSQDOc6wbTPyXWmnl3Hmd/xiRQxRUcHqQxWbyeyYekMtr6duHqHlIYuF9N2Y3whUeBP6gznir3SD3KNCXLaHglOBi4Ug
                eHppVaZxvihz/3rONd2TUyRxduhkjg7BMdVYIgFNyNQmJm1Qbq+iViCeHqftKYWilzFx1WQmtflFzIWxrrCdKbpXcfLfSvQ
                xgpvqYppWB9/w+IuEupu4ewQHFeByR7s3B2ZeHaBRrvdQWJTeCpwKPOTTt9TivxiF0ScLBdMkXOtm8MOiPy02ixLZWNFvgK
                HrkiVzMDbB1mrN5aX67RcHiATEjC5hX3g/hyIabXZSQj9vaQSEijE2JSne0WPHCO56cW9fiXDuS7UjKGPY5allPy5z6S8qc
                r5IebfNyYaLYsduq/87C5pM8DKRKybxW5XX0tCnWYspl011xtIcgljbOgbeTtMmZyO9DIo6vfv6fjilABE4SnRsKkiobKLO
                IB/XWyxJY6nw4j7xAwSeY6tx1j7tCuZJT19pY3DpA7LU387hjsauu+TggusDlmHv0fFwLuHTCTT561IJafDMAkReDqKns3p
                cJ2S6jE0g23yZFaYzzJh+aRUaajFAZn7lvhVBFSk2HqMYgULrFepc+c/8vWbMeQhh2/C7mQWZLoy2HnsFmw5WEzmc81/Z4o
                hdVPbTlQDDlrjaz3jWzGX75LQur91h7tToj5bbQ5NZWNEQo6Qxbm26KfsOdm0pKH8T67466OkRBM3GcuSdp9sJOvDj1vI2x
                +R0U1qahejw7gWmvF7kllHsqHjmZLhXJ+WDaMumfTZL3FXsYJzUnB6J19r9fJZkySfszoy1ybTsJDT+jAghBQPzOHptO1Nv
                RUkEho41xZHqeKg/vlPWPj+Bif5YaH+2rD/Js5OtIQkFdP7zlbNBoIM5zqqb5uTa01XRP4ACdsr6PellGEaB0bOf4cqsB8E
                S1ognsiHwSjaIVUyemm44fvh2tIqXeHdgJGB62LtOMi1rFlwsfWkwl8RQZ8QU4wlOKrQjE0vXB6yv1fM1WF47ziZuGAPUjK
                N0gjmDfLynCn5lkxjsl1tnAooISUDcyTVK9Pe+neRv4EzbsUKOgqb61fuy7WGHK92qC76/ztViTn3Ab/isDGRNUsoPVpkVT
                ilGz9G47w33ACZxuhAOR5IQnBFnauZlaWyYaJnBayuxxmFUvLdW70Dh39hKT+OOOJrgUhaxELLi4yPOlRqkyqZOanSMC1R0
                qn4AWN39yRLZTdSpyoCqj+c61h2myNUY0wXBQJvRuj/FiexSSmDEedNoSjBqTo4yGV3eiMZV4F5ChxDi7Mf583bSeJ1owWH
                G49mMZrESOqmJNaCE7jRNwlSGQbECvqUmNJLg9WXvsl3H7JUoyw6o/ZxoMnApS3ogTBf8+5CjRXEeVM44gir76Wq3HoUbwv
                b2DiWHTuXpCq6QKzQHyZmd7jh+4u5tiyVVcZm3l4WhKQV3YWItNKbouWK4PCCP8Rx5zghAXP7UkXOf0jCmR/h6UKDwdPb7w
                32phr3RH1asywIwZB/uM50XfQiQ57Kro1IL7MEmgxcSVebbbJUNln0IkOWwv4LeumFvUuruRJyoXMaqjHtFr3ICEmr/gbmJ
                C7V3g8oGRjURPM7NOWWW2vwhUKY1lScYuiwB5KQzKpR9NRn1OqSr4tedISmGreiHsG6qUARcuBKk1WuMQk/t/F5xJ6jJd+R
                a9nH5ytGAkKGoXMWk1SOUK3xtUDvxbKBTGM8Enm2yhyIU3KMbpsL05XWBnoPlhVCNabvynWmh2eMg8+UjOwWrGQ0OuSprPC
                DmJ93yDTsB3KdyUZ3zDyzCG/kJ1UWuUbAjt2vFAC+hj0ckWerLP6uPMES1cPXSQ/iEOqwQD/6ssWeoyXfCdOZ2uIu1FuL+u
                f8RkZqbqcdzdyPtEZhp9B9FRF2vPx7WAwdk1FrcU5pEGrdGLLDsfl07exLq2qRSj5Ma6pWpJdZPq+fEIQM7N6NzajF1rax0
                FSTsBNMXwSoLzV+U6Zjj2E/x+GsZpu37dBPLuxN1BZ0O/D3hGlNBT43f77okOvYH8t1pSY0Tw9cabRiTa6ngjoUTVcbpuC4
                vt2OJT5hutK7oVrjmkA/y1cKe1OMr8h0pgyU/+hZR35aM3s4u2VOk98NaYV3QVvYA8dy2hyx5+tmcdYJDjUL07FFGOJ/GaP
                ysygLTTH9J6Z/ZanGk+FppfrwtFKjXFeaG6plz4dqjCocFOBz78dLiJYN/h/mGIP3ImTmyAAAAABJRU5ErkJggg==" alt="Humidity Icon">
                <p>Humidity: 60 %</p>
            </div>
        </div>
        <button id="statusButton" class="status-button disconnected" onclick="toggleConnectionStatus()">Disconnected</button>
    </div>
</body>
</html>
)====";

