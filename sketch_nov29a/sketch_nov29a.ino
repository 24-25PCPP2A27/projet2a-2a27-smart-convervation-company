#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 7 // Pin de connexion du capteur DHT
#define DHTTYPE DHT11 // Type de capteur DHT (DHT11 ou DHT22)

DHT dht(DHTPIN, DHTTYPE);

int buzzer = 6; // Pin de connexion du buzzer

void setup() {
  Serial.begin(9600); // Initialisation de la communication série
  Serial.println(F("Test DHTxx!"));

  dht.begin(); // Initialisation du capteur DHT

  pinMode(buzzer, OUTPUT); // Configuration du buzzer comme sortie
}

void loop() {
  // Lecture des valeurs du capteur DHT
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Échec de la lecture depuis le capteur DHT !"));
    return;
  }

  // Afficher les valeurs de température et d'humidité dans le moniteur série
  Serial.print("Humidité : ");
  Serial.print(h);
  Serial.println(" %");

  Serial.print("Température : ");
  Serial.print(t);
  Serial.println(" °C");

  // Vérifier si la température est supérieure à 30.0
  if (t > 27.0) {
    digitalWrite(buzzer, HIGH); // Activer le buzzer
    Serial.println("E");
  } else {
    digitalWrite(buzzer, LOW); // Désactiver le buzzer
    Serial.println("N");
  }

  delay(2000); // Pause de 2 secondes avant la prochaine mesure
}