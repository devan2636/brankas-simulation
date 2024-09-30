// Devandri Suherman
// 191354007
// Sistem Brankas Sederhana
// Default Password 123456
#include <Keypad.h>
#include<LiquidCrystal.h>
#include<EEPROM.h>
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
char password[6];
char initial_password[6],new_password[6];
int i=0;
//definisikan pin
const int buzzer = 4;
const int lock = 3;
const int kondisi_pintu = 5;
char key_pressed=0;
const byte ROWS = 4; //4 baris
const byte COLS = 3; //3 kolom
//set mapping tombol
char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[ROWS] = {10, 9, 8, 7}; //set pinout baris
byte colPins[COLS] = {13, 12, 11}; //set pinout kolom
//membuat objek bernama keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS,
COLS );
void setup(){
pinMode(buzzer, OUTPUT);
pinMode(lock, OUTPUT);
pinMode(kondisi_pintu, INPUT);
lcd.begin(20,4);
lcd.print("--Sistem Brankas--");
lcd.setCursor(0,1);
lcd.print("--------------------");
lcd.setCursor(0,2);
lcd.print("Devandri Suherman");
lcd.setCursor(0,3);
lcd.print("-----191354007-----");
delay(2000);
lcd.clear();
lcd.print("Masukan Password"); //password default 123456
lcd.setCursor(0,1);
initialpassword();
digitalWrite(buzzer, LOW);
digitalWrite(lock, LOW);
}
void loop()
{
key_pressed = keypad.getKey();
if(key_pressed =='#')
change();
if (key_pressed)
{
password[i++]=key_pressed;
lcd.print(key_pressed);
}
if(i==6)
{
delay(200);
for(int j=0;j<6;j++)
initial_password[j]=EEPROM.read(j);
if(!(strncmp(password, initial_password,6))) // strncmp : me
mbandingkan 2 string
{
lcd.clear();
lcd.print("Password Benar");
//lcd.setCursor(0,1);
membuka();
delay(10000);
kondisipintu();
delay(3000);
//mengubah password
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Press # change pass");
delay(1000);
lcd.clear();
lcd.print("Enter Password:");
lcd.setCursor(0,1);
i=0;
}
else
{
lcd.clear();
lcd.print("Password Salah");
lcd.setCursor(0,1);
lcd.print("Silahkan Coba Lagi");
delay(1000);
lcd.clear();
lcd.print("Enter Password");
lcd.setCursor(0,1);
i=0;
} }
}
void change()
{
int j=0;
lcd.clear();
lcd.print("Now Password");
lcd.setCursor(0,1);
while(j<6)
{
char key=keypad.getKey();
if(key)
{
new_password[j++]=key;
lcd.print(key);
}
key=0;
}
delay(500);
if((strncmp(new_password, initial_password, 6)))
{
lcd.clear();
lcd.print("Correct Password");
lcd.setCursor(0,1);
lcd.print("Coba lagi");
delay(1000);
}
else
{ j
=0;
lcd.clear();
lcd.print("Password Baru:");
lcd.setCursor(0,1);
while(j<6)
{
char key=keypad.getKey();
if(key)
{
initial_password[j]=key;
lcd.print(key);
EEPROM.write(j,key);
j++;
}
}
lcd.print("Password diubah");
delay(1000);
}
lcd.clear();
lcd.print("Masukkan Password");
lcd.setCursor(0,1);
key_pressed=0;
}
void initialpassword(){
for(int j=0;j<6;j++)
EEPROM.write(j, j+49);
for(int j=0;j<6;j++)
initial_password[j]=EEPROM.read(j);
}
void kondisipintu(){
lcd.clear();
int bacapintu;
for (bacapintu=0;bacapintu<3;bacapintu++){
if(digitalRead(kondisi_pintu) == 0){
lcd.clear();
lcd.println("Pintu Terbuka");
lcd.setCursor(0,1);
lcd.println("Tutup Kembali");
notifikasi();
}
else{
menutup();
} }
}
void notifikasi(){
//notifikasi selama 5 detik
int n ;
for (n=0; n<5; n++){
digitalWrite(buzzer,HIGH);
delay(500);
digitalWrite(buzzer,LOW);
delay(500);
}
}
void membuka(){
//membuka pintu
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Pintu Terbuka");
digitalWrite(lock, HIGH);
delay(500);
digitalWrite(lock, LOW);
delay(500);
}
void menutup(){
//menutup pintu
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Pintu Tertutup");
lcd.setCursor(0,1);
lcd.print("Brankas Terkunci");
digitalWrite(lock, HIGH);
delay(500);
digitalWrite(lock, LOW);
delay(500);
}
