// Reads data from serial port
// Example:
//
// 30;54;20E
//
// 30 - CPU % usage
// 54 - GPU % usage
// 20 - RAM % usage
// E - end of the massage
//; - end of the value
#include <Wire.h>
#include <Arduino.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//1 - 4
//2 - 8
//3 - 12
//4 - 16
#define IN_DATA_SIZE 16

char inData[IN_DATA_SIZE];

//Temp variables for data from serial port
char c;
int i = 0;

void updateDisplay();
void clearInData();

void setup()
{
	Serial.begin(9600);
	lcd.begin(16, 2);

	lcd.setCursor(0, 0);
	lcd.print("CPU:");

	lcd.setCursor(0, 1);
	lcd.print("GPU:");	
	
	lcd.setCursor(8, 0);
	lcd.print("CPU:");

	lcd.setCursor(8, 1);
	lcd.print("RAM:");
}

int size =0;
void loop()
{
	while (Serial.available() > 0)
	{
		c = Serial.read();

		// reading values
		if (c != 'E')
		{
			inData[i++] = c;
		} // ending massage
		else
		{
			i = 0;
			updateDisplay();
		}
	}
}

void updateDisplay()
{
    char* rest = inData;
	// CPU
	lcd.setCursor(4, 0);
	lcd.print(strtok_r(rest, ";", &rest));
	lcd.print("% ");

	// CPU Temp	
	lcd.setCursor(12, 0);
	lcd.print(strtok_r(rest, ";", &rest));
	lcd.write(223);

	// GPU
	lcd.setCursor(4, 1);
	lcd.print(strtok_r(rest, ";", &rest));
	lcd.print("% ");

	// RAM
	lcd.setCursor(12, 1);
	lcd.print(strtok_r(rest, ";", &rest));
	lcd.print("% ");



	clearInData();
}

void clearInData()
{
	for (int i = 0; i < IN_DATA_SIZE; i++)
	{
		inData[i] = '\0';
	}
}