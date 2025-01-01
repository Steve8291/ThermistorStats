#include <Arduino.h>
#include <ThermistorStats.h>

const int BAUD_RATE = 115200;
const int SAMPLE_SIZE = 31;

// Create instance of ThermistorStats
ThermistorStats temp_probe = ThermistorStats(SAMPLE_SIZE);


void setup() {
    Serial.begin(BAUD_RATE);
}

void loop() {
    delay(10000);  // Delay to slow down for demo.

    if (temp_probe.isBufferFull()) Serial.println("Buffer is Full");
    else Serial.println("Buffer not filled");

    Serial.println("Attempting to print buffer without adding any values:");
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        Serial.print(temp_probe.getElement(i));
        Serial.print(" ");
    }
    Serial.println();

    Serial.println("Randomly filling buffer with values.");
    Serial.println("Adjust min and max to see how it affects StdDev");
    srand(time(0));
    int min = 4090;
    int max = 4095;
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        int random_num = min + (rand() % (max - min + 1));
        temp_probe.add(random_num);
    }

    if (temp_probe.isBufferFull()) Serial.println("Buffer is Full");
    else Serial.println("Buffer not filled");

    Serial.println("Printing unsorted buffer:");
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        Serial.print(temp_probe.getElement(i));
        Serial.print(" ");
    }
    Serial.println();

    Serial.println("Printing sorted buffer:");
    for (int i = 0; i < SAMPLE_SIZE; i++) {
        Serial.print(temp_probe.getSortedElement(i));
        Serial.print(" ");
    }
    Serial.println();
    
    Serial.print("Median: ");
    Serial.println(temp_probe.getMedian());

    Serial.print("StdDev: ");
    Serial.println(temp_probe.getStdDev());

    temp_probe.resize(127);
    Serial.print("\n\n\n");
    
}


