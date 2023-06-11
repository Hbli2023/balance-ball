#define BUTTONCOUNT 4
//#define HIGHMODE 

int Mode=0;
const int ButtonPin[BUTTONCOUNT] = { 2,3,4,5 };
int ButtonStat[BUTTONCOUNT] = { 0 };
void setup()
{
	Serial.begin(9600);
	IintButton();
	//IintButton(LOWMODE);
}
void IintButton()
{
	// #if define HIGHMODE
	//   Mode=1;
	// #else
	//   Mode=0;
	// #endif
	for (int i = 0; i < BUTTONCOUNT; ++i)
	{
		if (Mode)
			pinMode(ButtonPin[i], INPUT);
		else
			pinMode(ButtonPin[i], INPUT_PULLUP);
		ButtonStat[i] = 0;
	}
}
int ScanButton()
{
	for (int i = 0; i < BUTTONCOUNT; ++i)
	{
		if (digitalRead(ButtonPin[i])==Mode)
		{
			if (ButtonStat[i] != 1)
			{
				if (!ButtonStat[i])
				{
					ButtonStat[i] = -1;
					delay(10);
				}
				else if (ButtonStat[i] == -1)
				{
					ButtonStat[i] = 1;
					return i + 1;
				}
			}

		}
		else
		{
			if (ButtonStat[i] == -1)
			{
				ButtonStat[i] = 0;
			}
			else if (ButtonStat[i] == 1)
			{
				ButtonStat[i] = 0;
				return -1 * (i + 1);
			}
		}
	}
	return 0;
}
void loop()
{
	int button = ScanButton();
	if (button)
	{
		Serial.println(button);
	}
	
}
