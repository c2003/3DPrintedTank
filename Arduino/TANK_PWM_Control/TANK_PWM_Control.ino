


int IN1 = 8; // Motor 1
int IN2 = 9; // Motor 1
int IN3 = 10; //Motor 2
int IN4 = 11; //Motor 2

void setup() {
  Serial.begin(9600);
  Serial.println("Program STarts");



   pinMode(IN1, OUTPUT);  //sağ motor - right motor 
   pinMode(IN2, OUTPUT);  
   pinMode(IN3, OUTPUT);
   pinMode(IN4, OUTPUT);  //sol motor - left motor
}

void loop() {
  
  String input = "";

  
     digitalWrite(IN1, LOW); //öncelikle motorları durduruyoruz! - first we stop the motors! 
     digitalWrite(IN2, LOW); 
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW); 

  while(Serial.available() > 0) {
    input += (char)Serial.read();
    delay(5);
  }

  String directt;
  int tvalue = 0 ;
   
  String directd;
  int dvalue = 0;
  
  if (input != "") {
    Serial.println(input);
    int tdi = input.indexOf('T');
    int dotdi = input.indexOf(':', tdi);
    
    if (dotdi - tdi == 1) {
      directt = input.substring(dotdi +1, input.indexOf('-', dotdi));
     // Serial.println(directt);
    } else {
    //  Serial.println("invalid input");
    }

    int tvi = input.indexOf('-', dotdi + 2); //since this is a character, it should be two length....
    int start1 = input.indexOf('*', tvi);

    

      tvalue = input.substring(tvi +1, start1).toInt();
     // Serial.println(tvalue);


   int ddi = input.indexOf('D', input.indexOf('*')); // T:F-48*D:R-50   we are going to search after the first star..
   int ddoti = input.indexOf(':', ddi);

   if (ddoti - ddi == 1) {
     directd = input.substring(ddoti +1, input.indexOf('-', ddoti));
   //  Serial.println(directd);
   } else {
     // Serial.println("Error");
   }

   

    int dash2 = input.indexOf('-', ddoti);
    int star2 = input.indexOf('*', dash2);

    dvalue = input.substring(dash2 + 1, star2).toInt();
    //Serial.println(dvalue);
    
  }


  if (directt.indexOf("F") > -1) {
    if (directd.indexOf("L") > -1) {

          dvalue = 100 - dvalue;
          dvalue = map(dvalue, 0 , 100, 0 ,255);
          analogWrite(IN2, dvalue);
          digitalWrite(IN1, LOW);

          digitalWrite(IN3, HIGH );
          digitalWrite(IN4, LOW);
      
    } else if (directd.indexOf("R") > -1) {
          dvalue = 100 - dvalue;
          dvalue = map(dvalue, 0 , 100, 0 ,255);
          digitalWrite(IN2, HIGH );
          digitalWrite(IN1, LOW);

          analogWrite(IN3, dvalue );
          digitalWrite(IN4, LOW);    
    } 
          Serial.print(directt + " " + directd + " ");
          Serial.println(dvalue);
          Serial.println(tvalue);
          
  } else if (directt.indexOf("B") > -1) {
    if (directd.indexOf("L") > -1) {

          dvalue = 100 - dvalue;
           dvalue = map(dvalue, 0 , 100, 0 ,255);
          analogWrite(IN1, dvalue );
          digitalWrite(IN2, LOW);

          digitalWrite(IN4, HIGH );
          digitalWrite(IN3, LOW);
      
    } else if (directd.indexOf("R") > -1) {
          dvalue = 100 - dvalue;
          dvalue = map(dvalue, 0 , 100, 0 ,255);
          digitalWrite(IN1, HIGH );
          digitalWrite(IN2, LOW);

          analogWrite(IN4, dvalue );
          digitalWrite(IN3, LOW);
    }    
          Serial.print(directt + " " + directd + " ");
          Serial.println(dvalue);
          Serial.println(tvalue); 
  }
 



  
  delay(2000);

}