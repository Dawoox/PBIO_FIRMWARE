#define Sensor1 A0
#define Sensor2 A1
#define Sensor3 A2

unsigned long lastMillis;
int numberOfCapturePerSecond = 25;
int timeBetweenCaptureInMillis = (1/numberOfCapturePerSecond) * 100;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Sensor1, INPUT_PULLUP);
  pinMode(Sensor2, INPUT_PULLUP);
  pinMode(Sensor3, INPUT_PULLUP);
}

void loop() {
  // check if we aren't running too fast
  if (millis() - lastMillis >= timeBetweenCaptureInMillis*10UL) {
    lastMillis = millis(); // reset the last execution time
    int values[3] = {0, 0, 0};
    readSensor(values);
    exportValues(values);
  }
  // if so do nothing
}

void readSensor(int (& values) [3]) {
  values[0] = analogRead(Sensor1);
  values[1] = analogRead(Sensor2);
  values[2] = analogRead(Sensor3);
}

void exportValues(int (& values) [3]) {
  String data;
  for (int x = 0; x < 3; x++) {
    String dataToAdd = String(values[x]);
    data.concat(dataToAdd);
    if (x < 2) {
      String separator = ":";
      data.concat(separator);
    }
  }
  Serial.println(data);
}
