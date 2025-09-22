# Lampu-Dekorasi-Arduino-IoT

![Arduino](https://img.shields.io/badge/Arduino-00979D?style=flat&logo=arduino&logoColor=white)
![IoT](https://img.shields.io/badge/IoT-Project-blue)

Proyek inovasi lampu dekorasi interaktif menggunakan Arduino Uno dengan kontrol potensiometer untuk mengatur kecerahan dan push button untuk mengubah mode.

## 🎯 Fitur Utama
- **5 Mode Lampu Berbeda**: Dari mode tunggal hingga kombinasi semua LED
- **Kontrol Kecerahan Analog**: Menggunakan potensiometer untuk mengatur intensitas cahaya
- **Push Button untuk Mode**: Satu tombol untuk mengubah mode operasi
- **Debouncing**: Mencegah pembacaan ganda saat tombol ditekan
- **Serial Monitor**: Menampilkan status mode, kecerahan, dan nilai potensiometer

## 🛠️ Komponen yang Dibutuhkan
| Komponen | Jumlah | Keterangan |
|----------|--------|------------|
| Arduino Uno | 1 | Mikrokontroler utama |
| LED Merah | 1 | Untuk output visual |
| LED Hijau | 1 | Untuk output visual |
| LED Biru | 1 | Untuk output visual |
| Push Button | 1 | Untuk input kontrol mode |
| Potensiometer 10KΩ | 1 | Untuk input kontrol kecerahan |
| Resistor 220Ω | 3 | Pembatas arus untuk LED |
| Kabel Jumper | 10 | Untuk koneksi |
| Breadboard | 1 | Tempat memasang komponen |

## 🔌 Skema Koneksi
| Komponen | Pin Arduino | Keterangan |
|----------|-------------|------------|
| LED Merah | Pin 9 (PWM) | Output dengan kontrol kecerahan |
| LED Hijau | Pin 10 (PWM) | Output dengan kontrol kecerahan |
| LED Biru | Pin 11 (PWM) | Output dengan kontrol kecerahan |
| Push Button | Pin 2 | Input dengan pull-up internal |
| Potensiometer | Pin A0 | Input analog (0-1023) |
| Semua Katoda LED | GND | Ground |

**Catatan**: 
- Hubungkan kaki panjang (anoda) LED ke pin Arduino melalui resistor
- Hubungkan kaki pendek (katoda) LED ke GND
- Push button menggunakan pull-up internal, sehingga tidak perlu resistor eksternal
- Potensiometer terhubung antara 5V (salah satu kaki) dan GND (kaki lainnya), dengan kaki tengah terhubung ke pin A0

## 📝 Kode Program
Kode program terdiri dari beberapa fungsi utama:

### Fungsi Setup
```cpp
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
```

### Fungsi Loop
```cpp
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
```

### Fungsi Perubahan Mode
```cpp
void changeMode() {
  currentMode = (currentMode + 1) % 5; // Mode 0-4
  Serial.print("Mode berubah ke: ");
  Serial.println(currentMode);
}
```

### Fungsi Penerapan Mode
```cpp
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
```

## 📊 Mode Lampu yang Tersedia
| Mode | Kombinasi LED | Deskripsi |
|------|--------------|-----------|
| Mode 0 | LED Merah | Hanya LED merah yang menyala dengan kecerahan terkontrol |
| Mode 1 | LED Hijau | Hanya LED hijau yang menyala dengan kecerahan terkontrol |
| Mode 2 | LED Biru | Hanya LED biru yang menyala dengan kecerahan terkontrol |
| Mode 3 | Semua LED | Semua LED menyala dengan kecerahan terkontrol (warna putih) |
| Mode 4 | Mode Berkedip | Semua LED berkedip bersama dengan kecerahan terkontrol |

## 📹 Video Demo
Lihat video demonstrasi proyek di: [https://youtu.be/zTkN7UBKcCE](https://youtu.be/zTkN7UBKcCE)

## Rangkaian Digital
<img width="827" height="468" alt="image" src="https://github.com/user-attachments/assets/f326b8aa-63c5-48a3-947f-35d82ab21ebe" />

## Output 
<img width="660" height="372" alt="image" src="https://github.com/user-attachments/assets/e2bfc072-0ef7-4e11-bfe9-c0696cbbcb26" />

## 👨‍💻 Tim Pengembang
Proyek ini dikembangkan oleh **Kelompok 5** sebagai tugas kelompok mata kuliah Internet of Things:

| Nama | NIM | Peran |
|------|-----|------|
| Hanif Luqmanul Hakim | 2022310035 | Ketua, Programmer |
| Bagas Aditya | 2022310063 | Programmer |
| Dedy Wijaya | 2022310052 | Hardware Specialist |
| Muhammad Iqbal | 2022310089 | Documentation |
| Rayan Ikmal Amala | 2022310043 | Testing |

---
**luqmanaru**

Proyek ini dikembangkan sebagai tugas kelompok mata kuliah Internet of Things 1. Semua komponen dan kode dirancang untuk simulasi lampu dekorasi interaktif menggunakan Arduino Uno dengan input analog dan digital.
