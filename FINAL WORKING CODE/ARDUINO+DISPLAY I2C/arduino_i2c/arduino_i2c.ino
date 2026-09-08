#include <Wire.h>

#define BUZZER_PIN  8
#define LED_PIN     7


#define CMD_LED_BLINK  0x20
#define CMD_BUZZER_ON  0x10

// Value to send back when master requests read
volatile uint16_t g_display_value = 0;
volatile bool     g_new_uart_value = false;

// I2C receive (master writing TO arduino)
volatile uint8_t g_cmd    = 0;
volatile bool    g_newCmd = false;

void onReceive(int bytes)
{
    while (Wire.available())
    {
        uint8_t b = Wire.read();
        if (!g_newCmd)
        {
            g_cmd    = b;
            g_newCmd = true;
        }
    }
}

// I2C request (master reading FROM arduino)
// BS84C12CA calls IIC_ReadData() -> triggers this
void onRequest()
{
    // Send high byte then low byte of value
    Wire.write((g_display_value >> 8) & 0xFF);  // high byte e.g. 0x03
    Wire.write(g_display_value & 0xFF);          // low byte  e.g. 0xE8
                                                 // 0x03E8 = 1000
}

void setup()
{
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_PIN,    OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN,    LOW);

    Wire.begin(0x55);
    Wire.onReceive(onReceive);
    Wire.onRequest(onRequest);   // ← new: respond to master reads

    Serial.begin(9600);
    Serial.println("\nReady\n");
}

void loop()
{
    //  Handle UART input 
    if (Serial.available())
    {
        String input = Serial.readStringUntil('\n');
        input.trim();
        int val = input.toInt();

        if (val >= 500 && val <= 3500)
        {
            g_display_value = (uint16_t)val;
            Serial.print("Value set to: ");
            Serial.println(val);
        }
        else
        {
            Serial.println("Invalid. Enter 500 to 3500.");
        }
    }

    //  Handle I2C commands 
    if (!g_newCmd) return;

    noInterrupts();
    uint8_t cmd = g_cmd;
    g_newCmd    = false;
    interrupts();

    switch (cmd)
    {
        case CMD_LED_BLINK:
            Serial.println("LED BLINK");
            digitalWrite(LED_PIN, HIGH);
            delay(300);
            digitalWrite(LED_PIN, LOW);
            break;

        case CMD_BUZZER_ON:
            Serial.println("BUZZER ON");
            digitalWrite(BUZZER_PIN, HIGH);
            delay(1000);
            digitalWrite(BUZZER_PIN, LOW);
            break;

        default:
            Serial.print("Unknown: 0x");
            Serial.println(cmd, HEX);
            break;
    }
}