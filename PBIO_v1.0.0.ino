#define SensorAO A0

const unsigned int MAX_MESSAGE_LENGTH = 12;

int calibration_value = 0;
bool exporting = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SensorAO, INPUT_PULLUP);
}

void loop() {
  // read Serial if needed
  String command = "";
  if (Serial.available()) {
    command =Serial.readString();
    command.trim();
  }

  if (command != '\0') {
    Serial.println(command);
    if (command.equals("calibrate")) {
      calibration_value = analogRead(SensorAO);
      Serial.println("INFO: CALIBRATION VALUE SET");
      Serial.print("ABOUT: CALIB_VAL_");
      Serial.println(calibration_value);
    } else if (command.equals("run")) {
      exporting = true;
      Serial.println("INFO: NOW RUNNING");
      if (calibration_value == 0) {
        Serial.println("WARNING: NO REFERENCE POINT PROVIDED, DATA MIGHT BE UNRELIABLE");
      }
    } else if (command.equals("stop")) {
      exporting = false;
      Serial.println("INFO: STOP RUNNING");
    } else if (command.equals("about")) {
      Serial.print("ABOUT: CALIB_VAL_");
      Serial.println(calibration_value);
    } else if (command.equals("")) {} else {
      Serial.println("WARNING: SERIAL COMMAND UNDEFINED - DO YOU MEAN calibrate, run, about OR stop ?");
    }
  }

  if (exporting) {
    int valueAnalog = readSensorValue();
    exportValues(valueAnalog);
  }
}

void exportValues(int sensorValue) {
  Serial.print("BEGIN_DATA:");
  Serial.print(sensorValue);
  Serial.println(":END_DATA");
}

int readSensorValue() {
  int valueAnalog = analogRead(SensorAO);
  return valueAnalog - calibration_value;
}

String readSerial() {
  /*
  while (Serial.available() > 0) {
    // Var(s) to hold the incoming message
    static char message[MAX_MESSAGE_LENGTH];
    static unsigned int message_pos = 0;

    // Read the next byte in the serial receive buffer
    char inByte = Serial.read();

    // If inByte correspond to the terminating character fill the message with blanks
    // And check if the message does not exced the MAX_MESSAGE_LENGTH
    if (inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH -1 )) {
        // Add the byte to the message
        message[message_pos] = inByte;
        message_pos++;
    }
    else {
      // Add null character to the end of the message
      message[message_pos] = '\0';
      message_pos = 0;
      return message;
    }
  }
  // Return null chars if no message is being received
  return '\0';
  */
}
