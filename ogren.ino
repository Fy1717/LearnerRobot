#include<Servo.h>
#include <QueueList.h>

QueueList <int> kiskacQue;
QueueList <int> tabanQue;
QueueList <int> solQue;
QueueList <int> sagQue;

bool ogrensinmi = 0;

#define buton 12
int butonDurumu ;
int sayac = 1;
int engel ;
String engelDurumu ;




Servo kiskac;
const byte kiskacPotPini = A0;
int kiskacPotDeger;
int kiskacYeniDeger;

Servo taban;
const byte tabanPotPini = A1;
int tabanPotDeger;
int tabanYeniDeger;

Servo sol;
const byte solPotPini = A2;
int solPotDeger;
int solYeniDeger;

Servo sag;
const byte sagPotPini = A3;
int sagPotDeger;
int sagYeniDeger;



void setup() {
  
  Serial.begin(9600);
  pinMode(buton , INPUT_PULLUP);
  pinMode(6, INPUT);
  
  kiskac.attach(7);
  taban.attach(8);
  sol.attach(9);
  sag.attach(10);

  kiskacQue.setPrinter (Serial);
  tabanQue.setPrinter (Serial);
  solQue.setPrinter (Serial);
  sagQue.setPrinter (Serial);



}

void loop() {
  engel = digitalRead(6);                         // Dijital olarak MZ-80 mesafe sensörünün  değerini okuyoruz
 
  int butonOku = digitalRead(buton) ;

  while (butonOku == 0)
  {
    if (ogrensinmi)
      while (digitalRead(buton) == 0)
        ogrensinmi = 0;
    else
      while (digitalRead(buton) == 0)
        ogrensinmi = 1;
        
    butonOku = digitalRead(buton) ;
  }



  if (!ogrensinmi) {


    kiskacPotDeger = analogRead(kiskacPotPini);
    kiskacYeniDeger = map(kiskacPotDeger, 1, 1024, 80, 170);
    kiskacQue.push(kiskacYeniDeger);
    kiskac.write(kiskacYeniDeger);
    delay(60);

    tabanPotDeger = analogRead(tabanPotPini);
    tabanYeniDeger = map(tabanPotDeger, 1, 1024, 20, 160);
    tabanQue.push(tabanYeniDeger);
    taban.write(tabanYeniDeger);
    delay(60);

    solPotDeger = analogRead(solPotPini);
    solYeniDeger = map(solPotDeger, 1, 1024, 80, 170);
    solQue.push(solYeniDeger);
    sol.write(solYeniDeger);
    delay(60);

    sagPotDeger = analogRead(sagPotPini);
    sagYeniDeger = map(sagPotDeger, 1, 1024, 45, 135);
    sagQue.push(sagYeniDeger);
    sag.write(sagYeniDeger);
    delay(60);


  }
  else {

    kiskac.write(kiskacQue.pop());
    delay(40);
    taban.write(tabanQue.pop());
    delay(40);
    sol.write(solQue.pop());
    delay(40);
    sag.write(sagQue.pop());
    delay(40);
  }
}

 
void potaGore() {
  Serial.println("\nPotlara Göre Çalışılıyor\n");
  durumlar();

  kiskacPotDeger = analogRead(kiskacPotPini);
  kiskacYeniDeger = map(kiskacPotDeger, 1, 1023, 80, 160);
  kiskac.write(kiskacYeniDeger);
  Serial.print("\n\n\nKiskac Açi Değeri =  ");
  Serial.println(kiskacYeniDeger);

  tabanPotDeger = analogRead(tabanPotPini);
  tabanYeniDeger = map(tabanPotDeger, 1, 1023, 40, 140);
  taban.write(tabanYeniDeger);
  Serial.print("Taban Açi Değeri =  ");
  Serial.println(tabanYeniDeger);

  solPotDeger = analogRead(solPotPini);
  solYeniDeger = map(solPotDeger, 1, 1023, 80, 170);
  sol.write(solYeniDeger);
  Serial.print("Sol Açi Değeri =  ");
  Serial.println(solYeniDeger);

  sagPotDeger = analogRead(sagPotPini);
  sagYeniDeger = map(sagPotDeger, 1, 1023, 45, 145);
  sag.write(sagYeniDeger);
  Serial.print("Sag Açi Değeri =  ");
  Serial.println(sagYeniDeger);
}

void mesafeyeGore() {
  taban.write(20);
  Serial.println("\nMesafeye Göre Çalışılıyor\n");
  durumlar();

}

void durumlar() {
  Serial.print("\nButon Durumu : ");
  Serial.println(butonDurumu);
  Serial.print("Sayaç          : ");
  Serial.println(sayac);
  Serial.print("Mod            : ");
  Serial.println(sayac % 3);
  Serial.print("Engel Durumu : ");
  Serial.println(engelDurumu);
  Serial.println("--------------------------");
  //delay(1000);


}
