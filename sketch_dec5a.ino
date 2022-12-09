/* Berikut merupakan kodingan
 * Wall Follower untuk menyelesaikan
 * rintangan seperti berikut:
 *  
 * FINISH FINISH
 * _|   |   |_
 *|      |      |
 *|   _|_   |
 *|      |      |
 *|_   |   _|
 *|      |      |
 *|   _|_   |
 *|   |     |   |
 *START     START
 * 
 * Legenda:
 * + START    =  Posisi awal robot
 * + FINISH   =  Tujuan akhir robot
 * + ---      =  dinding atau checkpoint
 * +  |       =  dinding atau checkpoint
 */

//Deklarasi pin motor
int M11 = 5;
int M12 = 6;
int M21 = 9;
int M22 = 10;

int jarak = 25;       //jarak untuk belok
int jarakstop = 10;    //jaral untuk stop
int checkpoint = 1;   //menghitung checkpoint

void setup() {
  //Baud Rate untuk komunikasi mikrokontroler dengan komputer
  Serial.begin(9600);
  
  //Penentuan mode pin sebagai output
  pinMode(M11, OUTPUT);
  pinMode(M12, OUTPUT);
  pinMode(M21, OUTPUT);
  pinMode(M22, OUTPUT);
}

void loop() {
  //Penentuan pin Trigger, Echo 
  int cm = sensor_ping(8,7);

  // Penentuan Kondisi
  if (cm > jarak) { //Kondisi maju
    MAJU ();
  }
  else if (cm <= jarak && checkpoint == 1) { //checkpoint pertama
    KANAN();
    delay(450); //100-1000
    checkpoint++;
  }
  else if (cm <= jarak && checkpoint == 2) { //checkpoint kedua
    KIRI();
    delay(450);
    checkpoint++;
  }
  else if (cm <= jarak && checkpoint == 3) { //checkpoint ketiga
    KIRI();
    delay(450);
    checkpoint++;
  }
  else if (cm <= jarak && checkpoint == 4) { //checkpoint keempat
    KANAN();
    delay(450);
    checkpoint++;
  }
  else if (cm <= jarak && checkpoint == 5) { //checkpoint kelima
    KANAN();
    delay(450);
    checkpoint++;
  }
  else if (cm <= jarak && checkpoint == 6) { //checkpoint keenam
    KIRI();
    delay(450);
    checkpoint++;

  }
    else if (cm <= jarakstop && checkpoint == 7) { //checkpoint keenam
    STOP();
    delay(450);
    checkpoint++;

  }
  
}

//fungsi maju
void MAJU (){
  analogWrite(M11, 75);
  analogWrite(M12, 0);
  analogWrite(M21, 75);
  analogWrite(M22, 0);
}

//fungsi stop
void STOP(){
  analogWrite(M11, 0);
  analogWrite(M12, 0);
  analogWrite(M21, 0);
  analogWrite(M22, 0);
}

//fungsi belok kanan
void KANAN(){
  analogWrite(M11, 0);
  analogWrite(M12, 75);
  analogWrite(M21, 75);
  analogWrite(M22, 0);
}

//fungsi belok kiri
void KIRI(){
  analogWrite(M11, 75);
  analogWrite(M12, 0);
  analogWrite(M21, 0);
  analogWrite(M22, 75);
}

//fungsi mendeteksi dengan sensor, menggunakan pin Trigger dan Echo  
int sensor_ping(const int trigPin,const int echoPin) {
  long duration, cm ;
  
  //pinmode trigpin sebagai output
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //pinmode echopin sebagai input
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);

  //Mengeprint output pada serial monitor 
  Serial.print(cm);
  Serial.print(" cm");

  //Memberikan jarak 1 line kebawah (ENTER)
  Serial.println();
  delay(70);
  return(cm);
}

//mengkonversi data sensor menjadi satuan detik
long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
