// Импортируем нужные библиотеки для подключения к сети, создания сервера и управления датчиком температуры.

#include <Arduino.h>

#include <ESP8266WiFi.h> 
#include <ESP8266WebServer.h>
#include "DHT.h"


#define DHTTYPE DHT11   

const char* ssid = "TP-Link_DDF0";  // Имя Wi-Fi сети
const char* password = "11715689";  // Пароль для сети

ESP8266WebServer server(80); // Создаем объект сервера через который будем создавать сервер
uint8_t DHTPin = D1;  // Пин к которому подключим датчик температуры и будем брать из него значения

DHT dht(DHTPin, DHTTYPE); // Создаем объект датчика температуры для работы                

float Temperature; // Переменная где будем хранить температуру
float Humidity; // Переменная где будем хранить влажность



// Самая сложная функция. Отвечает за графический вывод. Помог друг.
String SendHTML(float Temperaturestat,float Humiditystat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<meta http-equiv=\"Content-type\" content=\"text/html; charset=utf-8\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,600\" rel=\"stylesheet\">\n";
  ptr +="<title></title>\n";
  ptr +="<style>html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #333333;}\n";
  ptr +="body{margin-top: 50px;}\n";
  ptr +="h1 {margin: 50px auto 30px;}\n";
  ptr +=".side-by-side{display: inline-block;vertical-align: middle;position: relative;}\n";
  ptr +=".humidity-icon{background-color: #3498db;width: 30px;height: 30px;border-radius: 50%;line-height: 36px;}\n";
  ptr +=".humidity-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
  ptr +=".humidity{font-weight: 300;font-size: 60px;color: #3498db;}\n";
  ptr +=".temperature-icon{background-color: #f39c12;width: 30px;height: 30px;border-radius: 50%;line-height: 40px;}\n";
  ptr +=".temperature-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
  ptr +=".temperature{font-weight: 300;font-size: 60px;color: #f39c12;}\n";
  ptr +=".superscript{font-size: 17px;font-weight: 600;position: absolute;right: -20px;top: 15px;}\n";
  ptr +=".data{padding: 10px;}\n";
  ptr +="</style>\n";
  //ptr +="<meta http-equiv=\"refresh\" content=\"2\" >\n";
  ptr +="<script>\n";
  ptr +="setInterval(loadDoc,200);\n";
  ptr +="function loadDoc() {\n";
  ptr +="var xhttp = new XMLHttpRequest();\n";
  ptr +="xhttp.onreadystatechange = function() {\n";
  ptr +="if (this.readyState == 4 && this.status == 200) {\n";
  ptr +="document.getElementById(\"webpage\").innerHTML =this.responseText}\n";
  ptr +="};\n";
  ptr +="xhttp.open(\"GET\", \"/\", true);\n";
  ptr +="xhttp.send();\n";
  ptr +="}\n";
  ptr +="</script>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
   ptr +="<div id=\"webpage\">\n";
   ptr +="<h1>ESP8266. Информация о температуре в помещении:</h1>\n";
   ptr +="<div class=\"data\">\n";
   ptr +="<div class=\"side-by-side temperature-icon\">\n";
   ptr +="<svg version=\"1.1\" id=\"Layer_1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n";
   ptr +="width=\"9.915px\" height=\"22px\" viewBox=\"0 0 9.915 22\" enable-background=\"new 0 0 9.915 22\" xml:space=\"preserve\">\n";
   ptr +="<path fill=\"#FFFFFF\" d=\"M3.498,0.53c0.377-0.331,0.877-0.501,1.374-0.527C5.697-0.04,6.522,0.421,6.924,1.142\n";
   ptr +="c0.237,0.399,0.315,0.871,0.311,1.33C7.229,5.856,7.245,9.24,7.227,12.625c1.019,0.539,1.855,1.424,2.301,2.491\n";
   ptr +="c0.491,1.163,0.518,2.514,0.062,3.693c-0.414,1.102-1.24,2.038-2.276,2.594c-1.056,0.583-2.331,0.743-3.501,0.463\n";
   ptr +="c-1.417-0.323-2.659-1.314-3.3-2.617C0.014,18.26-0.115,17.104,0.1,16.022c0.296-1.443,1.274-2.717,2.58-3.394\n";
   ptr +="c0.013-3.44,0-6.881,0.007-10.322C2.674,1.634,2.974,0.955,3.498,0.53z\"/>\n";
   ptr +="</svg>\n";
   ptr +="</div>\n";
   ptr +="<div class=\"side-by-side temperature-text\">Температура</div>\n";
   ptr +="<div class=\"side-by-side temperature\">";
   ptr +=(int)Temperaturestat;
   ptr +="<span class=\"superscript\">°C</span></div>\n";
   ptr +="</div>\n";
   ptr +="<div class=\"data\">\n";
   ptr +="<div class=\"side-by-side humidity-icon\">\n";
   ptr +="<svg version=\"1.1\" id=\"Layer_2\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n\"; width=\"12px\" height=\"17.955px\" viewBox=\"0 0 13 17.955\" enable-background=\"new 0 0 13 17.955\" xml:space=\"preserve\">\n";
   ptr +="<path fill=\"#FFFFFF\" d=\"M1.819,6.217C3.139,4.064,6.5,0,6.5,0s3.363,4.064,4.681,6.217c1.793,2.926,2.133,5.05,1.571,7.057\n";
   ptr +="c-0.438,1.574-2.264,4.681-6.252,4.681c-3.988,0-5.813-3.107-6.252-4.681C-0.313,11.267,0.026,9.143,1.819,6.217\"></path>\n";
   ptr +="</svg>\n";
   ptr +="</div>\n";
   ptr +="<div class=\"side-by-side humidity-text\">Влажность</div>\n";
   ptr +="<div class=\"side-by-side humidity\">";
   ptr +=(int)Humiditystat;
   ptr +="<span class=\"superscript\">%</span></div>\n";
   ptr +="</div>\n";
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}


void handle_OnConnect() 
{
  Temperature = dht.readTemperature(); // получить значение температуры
  Humidity = dht.readHumidity();       // получить значение влажности
  server.send(200, "text/html", SendHTML(Temperature,Humidity));  // Отправляем на клиенту значения температуры и влажности
}

void handle_NotFound()
{
  server.send(404, "text/plain", "Not found"); //Если пользователь введет неверный адрес ему вернется сообщение что такого адреса нет
}



void setup() {
  Serial.begin(9600);

  delay(100);
  pinMode(DHTPin, INPUT); 
  dht.begin();    // запускаем датчик влажности
  Serial.println("Подключение к сети:\n");
  Serial.println(ssid);
  WiFi.begin(ssid, password); // подкючение к Wi-Fi

  while (WiFi.status() != WL_CONNECTED) {  // ожидание подключения к сети
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("Успешно подключено к сети");
  Serial.print("IP сервера: ");  Serial.println(WiFi.localIP()); // вывод ip адреса для подключения к серверу
  server.on("/", handle_OnConnect); // обработчик главной страницы
  server.onNotFound(handle_NotFound); // обработчик несуществующих страниц
  server.begin(); // запуск сервера
  Serial.println("Сервер начал работу");
}


void loop() {
  server.handleClient(); //Сервер начинает обрабатывать запросы.
}


