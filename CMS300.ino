#include <SPI.h>

/*SPIの設定を行う*/
/*
 * 書式
SPISettings::SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode);
SPISettings::SPISettings();
引数
clock  通信の最大スピード。20MHzまで対応可能なSPIチップのときは、20000000を使う。
bitOrder  MSBFIRSTもしくはLSBFIRST。
dataMode  SPI_MODE0もしくはSPI_MODE1、SPI_MODE2、SPI_MODE3。
パラメータを省略した形式では、clock=4000000、bitOrder=MSBFIRST、dataMode=SPI_MODE0が設定される。
*/

/*
 * クラスを使用するのが久しぶりなので確認用
 * https://monakaice88.hatenablog.com/entry/20130404/1365016051
 */

 /*
  *コンストラクタ
  *https://lang-ship.com/reference/Arduino/latest/class_s_p_i_settings.html
  *Interface:
  *min typical max
  *SPI® message rate 1Hz 1kHz 10kHz –
  *SPI® clock rate 100kHz 1MHz 7MHz –
  *
  *The interface will transfer 4 bytes (32 bits) in each message. The message rate will be 1kHz (nom), (1Hz-min,
  *10kHz-max) with a SPI® clock frequency of 1MHz (nom), (100kHz-min, 7MHz-max).
  *
  *The sensor will be a slave on the interface. All accesses shall use SPI® Mode 0.
  *In all messages to and from the sensor a 4-bit CRC (data bits D3:0) shall be added. The CRC polynomial
  *used shall be x4+1. A seed value of “1010” shall be used with a calculation order MSB to LSB.
  *
  *https://stupiddog.jp/note/archives/976
  *
  */

int CLK_freq = 4000000;
SPISettings cms300(CLK_freq,MSBFIRST,SPI_MODE0);

/*
 *センサから出力される情報を保存する変数received variable
 *データは4バイト
 */
 byte r_data1 = 0;
 byte r_data2 = 0;
 byte r_data3 = 0;
 byte r_data4 = 0;

 byte t_data1 = 0x00;
 byte t_data2 = 0x00;
 byte t_data3 = 0xA1;
 byte t_data4 = 0x00;

 byte data_BIT_OK;

/*おそらく1なら動いて,０なら出力だめ*/
 int BIT_OK =7;
 /*resetはactive low つまり，1ならresetがかからない*/
 int RESET =6;


void setup() {
  // put your setup code here, to run once:
  /*シリアルモニタ用の設定*/
  Serial.begin(9600);
  SPI.begin();
  pinMode(BIT_OK,INPUT);
  pinMode(RESET,OUTPUT);
  pinMode(SS,OUTPUT);
  delay(500);

}

void loop() {
  // put your main code here, to run repeatedly:
  SPI.beginTransaction(cms300);
   //digitalWrite(SS,LOW);
  //digitalWrite(BIT_OK,HIGH);
  data_BIT_OK = digitalRead(BIT_OK);
  //digitalWrite(RESET,LOW);
  delay(10);
  digitalWrite(RESET,HIGH);
  //delay();//念のため
 
  while(1){
    digitalWrite(SS,LOW);
    delayMicroseconds(9);
 
  r_data1 = SPI.transfer(0x00);
  delayMicroseconds(5);
  r_data2 = SPI.transfer(0x00);
  delayMicroseconds(5);
  r_data3 = SPI.transfer(0xA1);
  delayMicroseconds(5);
  r_data4 = SPI.transfer(0x01);
  delayMicroseconds(5);
  digitalWrite(SS, HIGH);
 
  Serial.print(r_data1,BIN);
  Serial.print(" ");
  Serial.print(r_data2,BIN);
  Serial.print(" ");
  Serial.print(r_data3,BIN);
  Serial.print(" ");
  Serial.println(r_data4,BIN);
  //Serial.println(SCK);
  Serial.println(data_BIT_OK,BIN);
  //delay(100);
  } 
 
  //制御するデバイスに通信の終了を通知する
 // digitalWrite(SS, HIGH);
  //SPI 通信を終了し設定を以前の状態に戻す
  SPI.endTransaction();
  

}
