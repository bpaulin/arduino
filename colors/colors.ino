// Les leds sont sont les pins 8 à 10
const int minLedPin = 8;
const int maxLedPin = 10;
// Le bouton est sur le pin 2
const int buttonPin = 2;

// Led actuellement allumée
int currentLedPin = minLedPin;
// Offest de la prochaine led
int directionLedPin = 1;

// MS du dernier changement de led
unsigned long previousMillis = 0;

// Intervalle avant un changement de led
long interval = 1000;

// Led aleatoire finale
long randNumber;

// flag: est ce que le choix est fini
boolean colorPicked = false;

// Nombre d'allumage de la led choisie avant de bloquer l'affichage
int counterPicked = 10;


void setup()
{
    // Pin d'affichage
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);

    // On allume la premiere
    digitalWrite(8, HIGH);
    // On eteind les autres
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);

    // Pin de lecture pour le bouton
    pinMode(2, INPUT_PULLUP);

    // Init du random
    randomSeed(analogRead(0));

    randNumber = random(8, 11);
}

void loop()
{
    unsigned long currentMillis = millis();

    int sensorVal = digitalRead(2);

    if (sensorVal == LOW)
    {
        currentLedPin = minLedPin;
        interval = 1000;
        directionLedPin = 1;
        digitalWrite(8, HIGH);
        pinMode(9, OUTPUT);
        digitalWrite(9, LOW);
        pinMode(10, OUTPUT);
        digitalWrite(10, LOW);
        colorPicked = false;

        randNumber = random(8, 11);
        previousMillis = currentMillis;
        counterPicked = 10;
    }
    else
    {
        if (!colorPicked && currentMillis - previousMillis >= interval)
        {
            digitalWrite(currentLedPin, LOW);
            previousMillis = currentMillis;
            if (currentLedPin == maxLedPin)
            {
                directionLedPin = -1;
            }
            else if (currentLedPin == minLedPin)
            {
                directionLedPin = 1;
            }

            currentLedPin = currentLedPin + directionLedPin;
            if (interval > 100)
            {
                interval = interval - 100;
            }

            digitalWrite(currentLedPin, HIGH);

            if (interval == 100 && currentLedPin == randNumber)
            {
                if (counterPicked == 0)
                {
                    colorPicked = true;
                }
                else
                {
                    counterPicked = counterPicked - 1;
                }
            }
        }
    }
}
