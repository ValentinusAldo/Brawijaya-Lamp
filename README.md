# Brawijaya-Lamp
Program Lampu UB
1. Deteksi salah satu sensor tangan > lampu merah hidup kedap-kedip dan Suara bunyi hidup 2Hz selama 3 detik
2. Tidak mendeteksi sensor tangan ke-2 selama 3 detik Ketika kondisi 1 > lampu merah dan bunyi berhenti (Kondisi semula)
3. Deteksi sensor tangan ke-2 Ketika kondisi 1> Lampu hijau menyala, bunyi 100Hz dan lampu merah mati (3 detik)
4. Setelah 3 detik kedua sensor di deteksi > Kondisi semula atau keadaan awal (tidak terjadi apa-apa)

Sensor Tangan 1 (liquid sensor) > xkc-y25-t12v (pin 5)
Sensor Tangan 2 (liquid sensor) > xkc-y25-t12v (pin 6)
Sensor Arus (2 pin) > Lampu merah dan hijau (pin 10 dan 11)
Aktuator (Buzzer) > (Pin 12)

*Lampu Hijau Hidup (Pin 10 HIGH)
*Lampu Merah Hidup (Pin 11 HIGH)
*Lampu Keduanya Mati (Pin 10 dan 11 LOW)
*Sensor tangan hanya impuls untuk menghidupkan kondisi bukan harus di Hold
