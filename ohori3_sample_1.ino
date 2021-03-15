#include <SPI.h>
//
SPI の設定を保持する SPISettings クラスのインスタンスを生成する
SPISettings mySPISettings = SPISettings(4000000, MSBFIRST, SPI_MODE0);
long rcv1;
long rcv2;
long rcv3;
long rcv4;
void setup() {
Serial.begin(9600);
SPI.begin();
delay (500);
}
void loop() {
// 現在の設定を退避し、指定した設定をマイコンに反映させ SPI 通信を開始する
SPI.beginTransaction(mySPISettings);
// 制御するデバイスに通信の開始を通知する
di gitalWrite(SS, LOW);
delay (20);
32 バイトを送受信する
//RATE 0b00000000000000001010000010001010 0x0000a08a
//ACCY 0b00000000000000001010000110001010 0x0000a18a
//ACCX 0b00000000000000001010001010001010 0x0000a28a
rcv1=SPI.transfer(0x00
rcv2=SPI.transfer(0x00);
rcv3=SPI.transfer(0xA 0
rcv4=SPI.transfer(0x8A);
制御するデバイスに通信の終了を通知する
digitalWrite(SS, HIGH);
SPI 通信を終了し設定を以前の状態に戻す
SPI.endTransaction();
//
シリアルポートに書き出す処理
Serial.println(rcv1,BIN);
Serial.println(rcv2,BIN);
Serial.println(rcv3,BIN);
Serial.println(rcv4,BIN);
delay (200);
}
