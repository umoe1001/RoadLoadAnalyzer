#include <SPIFFS.h>
#include <WiFi.h>
#include <ESP_Mail_Client.h>

#define WIFI_SSID "..."
#define WIFI_PASSWORD "..."

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

#define AUTHOR_EMAIL "esp32links@gmail.com"
#define AUTHOR_PASSWORD "acgr eqsm sgdk onmn "

#define RECIPIENT_EMAIL "oezcanumar@web.de"

const int triggerPin = 25;
const int echoPin = 26;
const int sampleNumber = 1350; // change this to the maximum if I want to record with 10 Hz than I need ca. 5400 Measurments

//define sound speed in cm/uS
#define SOUND_SPEED 0.034

long duration;
float distanceCm;
unsigned long startTime;

struct Measurement {
  unsigned long timestamp;
  float distance;
};

Measurement measurements[sampleNumber];
int distanceIndex = 0;

SMTPSession smtp;
void smtpCallback(SMTP_Status status);
void sendemail(Measurement data[], int length);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Starts the serial communication
  pinMode(triggerPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  Serial.println();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /*  Set the network reconnection option */
  MailClient.networkReconnect(true);

  /** Enable the debug via Serial port
   * 0 for no debugging
   * 1 for basic level debugging
   *
   * Debug port can be changed via ESP_MAIL_DEFAULT_DEBUG_PORT in ESP_Mail_FS.h
   */
  smtp.debug(1);

  smtp.callback(smtpCallback);
  /* Declare the Session_Config for user defined session credentials */
  startTime = millis();
  

}

void loop() {
  // put your main code here, to run repeatedly:
  // Clears the trigPin
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED/2;
  unsigned long currentTime = millis();
  Serial.print(" cm, Timestamp: ");
  Serial.println(currentTime);
  Serial.println(distanceCm);

  // Save distance to array
  if (distanceIndex < sampleNumber) {
    distanceIndex++;
    measurements[distanceIndex].distance = distanceCm;
    measurements[distanceIndex].timestamp = currentTime;
  }

  // Check if -- seconds have passed
  if (millis() - startTime >= sampleNumber*100) {
    sendEmail(measurements, distanceIndex);
    distanceIndex = 0;
    startTime = millis();
  }
  
  delay(100);
}

/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status){
  /* Print the current status */
  Serial.println(status.info());

  /* Print the sending result */
  if (status.success()){

    Serial.println("----------------");
    ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
    ESP_MAIL_PRINTF("Message sent failed: %d\n", status.failedCount());
    Serial.println("----------------\n");

    for (size_t i = 0; i < smtp.sendingResult.size(); i++)
    {
      /* Get the result item */
      SMTP_Result result = smtp.sendingResult.getItem(i);

      // In case, ESP32, ESP8266 and SAMD device, the timestamp get from result.timestamp should be valid if
      // your device time was synched with NTP server.
      // Other devices may show invalid timestamp as the device time was not set i.e. it will show Jan 1, 1970.
      // You can call smtp.setSystemTime(xxx) to set device time manually. Where xxx is timestamp (seconds since Jan 1, 1970)
      
      ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
      ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
      ESP_MAIL_PRINTF("Date/Time: %s\n", MailClient.Time.getDateTimeString(result.timestamp, "%B %d, %Y %H:%M:%S").c_str());
      ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients.c_str());
      ESP_MAIL_PRINTF("Subject: %s\n", result.subject.c_str());
    }
    Serial.println("----------------\n");

    // You need to clear sending result as the memory usage will grow up.
    smtp.sendingResult.clear();
  }
}

void sendEmail(Measurement data[], int length) {
  Session_Config config;
  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_EMAIL;
  config.login.password = AUTHOR_PASSWORD;
  config.time.ntp_server = F("pool.ntp.org,time.nist.gov");
  config.time.gmt_offset = 1;
  config.time.day_light_offset = 1;

  SMTP_Message message;
  message.sender.name = F("ESP32 Sensor");
  message.sender.email = AUTHOR_EMAIL;
  message.subject = F("Distance Measurements RIGHT - ESP32");
  message.addRecipient(F("Recipient"), RECIPIENT_EMAIL);

  String textMsg = "Distance measurements (cm) over 30 seconds:\n";
  for (int i = 0; i < length; i++) {
    textMsg += String(data[i].timestamp)+", "+ String(data[i].distance) + " cm\n";
  }

  message.text.content = textMsg.c_str();
  message.text.charSet = "utf-8";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  if (!smtp.connect(&config)) {
    Serial.println("Failed to connect to mail server");
    return;
  }

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.println("Failed to send email");
  } else {
    Serial.println("Email sent successfully!");
  }
}
