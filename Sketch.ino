// Pin untuk LED
const int redLED = 9;
const int greenLED = 10;
const int blueLED = 11;

// Pin untuk push button
const int modeButton = 2;

// Pin untuk potensiometer
const int potPin = A0;

// Variabel untuk mode dan kecerahan
int currentMode = 0;
int brightness = 0;

// Variabel untuk debouncing
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  // Inisialisasi pin LED sebagai output
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  
  // Inisialisasi pin button sebagai input dengan pull-up internal
  pinMode(modeButton, INPUT_PULLUP);
  
  // Inisialisasi serial monitor
  Serial.begin(9600);
  Serial.println("Sistem Lampu Dekorasi Interaktif");
  Serial.println("Tombol: Ganti Mode | Potensiometer: Atur Kecerahan");
}

void loop() {
  // Baca nilai potensiometer untuk kecerahan (0-1023)
  int potValue = analogRead(potPin);
  
  // Konversi nilai potensiometer ke kecerahan LED (0-255)
  brightness = map(potValue, 0, 1023, 0, 255);
  
  // Baca status tombol
  int modeButtonState = digitalRead(modeButton);
  
  // Cek tombol mode
  if (modeButtonState == LOW) {
    if ((millis() - lastDebounceTime) > debounceDelay) {
      changeMode();
    }
    lastDebounceTime = millis();
  }
  
  // Terapkan mode LED saat ini
  applyMode();
  
  // Tampilkan nilai potensiometer dan mode di serial monitor
  Serial.print("Potensiometer: ");
  Serial.print(potValue);
  Serial.print(" | Kecerahan: ");
  Serial.print(brightness);
  Serial.print(" | Mode: ");
  Serial.println(currentMode);
  
  delay(100); // Delay untuk stabilisasi pembacaan
}

void changeMode() {
  currentMode = (currentMode + 1) % 5; // Mode 0-4
  Serial.print("Mode berubah ke: ");
  Serial.println(currentMode);
}

void applyMode() {
  // Matikan semua LED terlebih dahulu
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  
  // Terapkan mode sesuai dengan currentMode
  switch (currentMode) {
    case 0: // Mode 0: LED Merah dengan kecerahan terkontrol
      analogWrite(redLED, brightness);
      break;
    case 1: // Mode 1: LED Hijau dengan kecerahan terkontrol
      analogWrite(greenLED, brightness);
      break;
    case 2: // Mode 2: LED Biru dengan kecerahan terkontrol
      analogWrite(blueLED, brightness);
      break;
    case 3: // Mode 3: Semua LED dengan kecerahan terkontrol (warna putih)
      analogWrite(redLED, brightness);
      analogWrite(greenLED, brightness);
      analogWrite(blueLED, brightness);
      break;
    case 4: // Mode 4: Mode Berkedip dengan kecerahan terkontrol
      static unsigned long lastBlinkTime = 0;
      static bool blinkState = false;
      
      if (millis() - lastBlinkTime > 500) { // Kedip setiap 500ms
        blinkState = !blinkState;
        lastBlinkTime = millis();
        
        if (blinkState) {
          analogWrite(redLED, brightness);
          analogWrite(greenLED, brightness);
          analogWrite(blueLED, brightness);
        } else {
          digitalWrite(redLED, LOW);
          digitalWrite(greenLED, LOW);
          digitalWrite(blueLED, LOW);
        }
      }
      break;
  }
}
