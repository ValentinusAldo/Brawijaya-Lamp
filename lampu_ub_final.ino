/*
====================================================
                 PROGRAM LAMPU UB
====================================================

Sensor Tangan 1  -> Pin 5
Sensor Tangan 2  -> Pin 6

Lampu Hijau      -> Pin 10
Lampu Merah      -> Pin 11

Buzzer           -> Pin 12

====================================================
LOGIKA OUTPUT
====================================================

Lampu Hijau ON   -> Pin 10 HIGH
Lampu Merah ON   -> Pin 11 HIGH

Semua Lampu OFF  -> Pin 10 LOW
                    Pin 11 LOW

====================================================
ALUR PROGRAM
====================================================

1. Salah satu sensor aktif:
   - Lampu merah berkedip
   - Buzzer bunyi 2Hz
   - Timer 3 detik dimulai

2. Jika sensor kedua tidak aktif
   dalam 3 detik:
   - Semua mati
   - Kembali idle

3. Jika sensor kedua aktif
   dalam 3 detik:
   - Lampu merah mati
   - Lampu hijau menyala
   - Buzzer 100Hz
   - Tahan 3 detik

4. Setelah 3 detik:
   - Semua mati
   - Kembali idle

====================================================
CATATAN
====================================================

- Sensor hanya impuls (trigger)
- Tidak perlu di-hold
- Sensor XKC-Y25-T12V:
  HIGH = mendeteksi

====================================================
*/

const int sensor1Pin = 5;
const int sensor2Pin = 6;

const int greenLampPin = 10;
const int redLampPin   = 11;

const int buzzerPin = 12;

// ====================================================
// STATE MACHINE
// ====================================================

enum State {
  IDLE,
  WAIT_SECOND_SENSOR,
  SUCCESS
};

State currentState = IDLE;

// ====================================================
// TIMER
// ====================================================

unsigned long stateStartTime = 0;
unsigned long blinkTimer = 0;

bool blinkState = false;

// Menyimpan sensor pertama
int firstSensor = 0;

// Untuk deteksi impuls
bool lastSensor1 = LOW;
bool lastSensor2 = LOW;

// ====================================================
// SETUP
// ====================================================

void setup() {

  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);

  pinMode(greenLampPin, OUTPUT);
  pinMode(redLampPin, OUTPUT);

  pinMode(buzzerPin, OUTPUT);

  allOff();
}

// ====================================================
// LOOP
// ====================================================

void loop() {

  bool sensor1 = digitalRead(sensor1Pin);
  bool sensor2 = digitalRead(sensor2Pin);

  // Deteksi rising edge (impuls)
  bool sensor1Trigger = (sensor1 == HIGH && lastSensor1 == LOW);
  bool sensor2Trigger = (sensor2 == HIGH && lastSensor2 == LOW);

  // Simpan status sebelumnya
  lastSensor1 = sensor1;
  lastSensor2 = sensor2;

  switch (currentState) {

    // ==================================================
    // KONDISI AWAL
    // ==================================================
    case IDLE:

      // Sensor 1 trigger
      if (sensor1Trigger) {

        firstSensor = 1;

        currentState = WAIT_SECOND_SENSOR;

        stateStartTime = millis();
      }

      // Sensor 2 trigger
      else if (sensor2Trigger) {

        firstSensor = 2;

        currentState = WAIT_SECOND_SENSOR;

        stateStartTime = millis();
      }

      break;

    // ==================================================
    // MENUNGGU SENSOR KE-2
    // ==================================================
    case WAIT_SECOND_SENSOR:

      redBlink();
      buzzer2Hz();

      // Jika sensor kedua terdeteksi
      if (
        (firstSensor == 1 && sensor2Trigger) ||
        (firstSensor == 2 && sensor1Trigger)
      ) {

        currentState = SUCCESS;

        stateStartTime = millis();

        redLampOff();
        greenLampOn();

        tone(buzzerPin, 100); // 100Hz
      }

      // Timeout 3 detik
      if (millis() - stateStartTime >= 3000) {

        allOff();

        currentState = IDLE;
      }

      break;

    // ==================================================
    // KONDISI SUKSES
    // ==================================================
    case SUCCESS:

      // Tahan 3 detik
      if (millis() - stateStartTime >= 3000) {

        allOff();

        currentState = IDLE;
      }

      break;
  }
}

// ====================================================
// FUNGSI LAMPU
// ====================================================

void greenLampOn() {
  digitalWrite(greenLampPin, HIGH);
}

void greenLampOff() {
  digitalWrite(greenLampPin, LOW);
}

void redLampOn() {
  digitalWrite(redLampPin, HIGH);
}

void redLampOff() {
  digitalWrite(redLampPin, LOW);
}

// ====================================================
// SEMUA OFF
// ====================================================

void allOff() {

  greenLampOff();
  redLampOff();

  noTone(buzzerPin);
}

// ====================================================
// BLINK LAMPU MERAH
// ====================================================

void redBlink() {

  // 2Hz -> toggle tiap 250ms

  if (millis() - blinkTimer >= 250) {

    blinkTimer = millis();

    blinkState = !blinkState;

    if (blinkState) {
      redLampOn();
    }
    else {
      redLampOff();
    }
  }
}

// ====================================================
// BUZZER 2Hz
// ====================================================

void buzzer2Hz() {

  if (blinkState) {
    tone(buzzerPin, 1000);
  }
  else {
    noTone(buzzerPin);
  }
}