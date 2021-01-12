#include "DHT.h"   // Librairie des capteurs DHT

#define DHTPIN 2    // Changer le pin sur lequel est branché le DHT

#define DHTTYPE DHT11     // DHT 11 
//#define DHTTYPE DHT22       // DHT 22  (AM2302)
//#define DHTTYPE DHT21     // DHT 21 (AM2301)

int Led_activation = 13;           //Pin allumage led Marche/Arret
int Demarrage_value = 0; // Valeur demarrage = 0 pour entrer dans la boucle contenant le code
int limite_temp = 26;    //Température de fontionnement (basculement)
int valeur = 0;
int Led_activation_2 = 12;           //Pin allumage led Marche/Arret

DHT dht(DHTPIN, DHTTYPE);
void setup() {

  pinMode(Led_activation_2, OUTPUT);
  pinMode(Led_activation, OUTPUT);
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
}

void loop() {
  // Délai de 500ms secondes entre chaque mesure. La lecture prend 250 millisecondes
  delay(250);

  // Lecture du taux d'humidité
  float h = dht.readHumidity();
  // Lecture de la température en Celcius
  float t = dht.readTemperature();
  // Pour lire la température en Fahrenheit
  float f = dht.readTemperature(true);

  // Stop le programme et renvoie un message d'erreur si le capteur ne renvoie aucune mesure
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Echec de lecture !");
    return;

  }

  // Calcul la température ressentie. Il calcul est effectué à partir de la température en Fahrenheit
  // On fait la conversion en Celcius
  float hi = dht.computeHeatIndex(f, h);


 // Serial.print("Humidite: ");
 // Serial.print(h);
 // Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("Temperature ressentie: ");
  Serial.print(dht.convertFtoC(hi));
  Serial.println(" *C");
  Serial.println(limite_temp);

if (dht.convertFtoC(hi) > limite_temp)
    valeur=1; //case 1
else
    valeur=2; //case 2
 
    switch (valeur)
{
    case 1:
    Demarrage_value++;
    break;

    case 2:
    break;

    default:
    break;
}
  

   
while (Demarrage_value < 1)
{
//  digitalWrite(Commande_Relai, HIGH);   //Activer le relai et basculer sur resistance 20k
    digitalWrite(Led_activation, HIGH);   //Allumer la LED (info activation)
    delay(5000);                          //Attendre 5 secondes
//  digitalWrite(Commande_Relai, LOW);    //Desactiver le relai et basculer sur resistance 20k
    digitalWrite(Led_activation, LOW);    //Eteindre la LED
    Demarrage_value++;
}

if (Demarrage_value = 1)
   digitalWrite(Led_activation_2, HIGH); // Allumer Led rouge pour validation


  }
