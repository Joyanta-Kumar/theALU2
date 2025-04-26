// Indecis for command.
#define indexMode 6
#define indexOpt1 5
#define indexOpt0 4
#define indexA1 3
#define indexA0 2
#define indexB1 1
#define indexB0 0

uint8_t userStringInput[3];
uint8_t command = 0b0;
uint8_t result = 0b0;
// 8 bits:  1   [0]   [00]  [00]  [00]
//          1   mode  opt   numA  numB

const uint8_t numAPins[2] = { 12, 11 }; // [A0, A1]
const uint8_t numBPins[2] = { 10, 9 };  // [B0, B1]
const uint8_t optPins[3] = { 3, 2, 4 }; // [Opt0, Opt1, Mode]
const uint8_t resPins[3] = { A0, A1, A2 };  // [R0, R1, Opt]
// optPins [operation,   mode]
// Example:
//  00           1
//  arithmetic   subtract

//  01           1
//  and / or     or

//  10           1
//  bitShift     right

void setup() {
  for (uint8_t i = 0; i < 2; i++) {
    pinMode(numAPins[i], OUTPUT);
    pinMode(numBPins[i], OUTPUT);
    pinMode(optPins[i], OUTPUT);
  }
  pinMode(optPins[2], OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    uint8_t i = 0;
    while (Serial.available()) {
      if (i < 3) {
        userStringInput[i] = Serial.read();
        Serial.print((char) userStringInput[i]);
      }
      else {
        Serial.read();
      }
      delay(20);
      i++;
    }
    Serial.println("\tReceived frame.");
    delay(100);
    // Received frame.
    
    userStringInput[0] = (userStringInput[0] == '+' || userStringInput[0] == '-') ? 1 : userStringInput[0] - 48;
    userStringInput[2] = (userStringInput[2] == '+' || userStringInput[2] == '-') ? 1 : userStringInput[2] - 48;
    // Thank me.
    // you don't have to worry about the num++, num--, --num, ++num now.

    switch (userStringInput[1]) {
      case '+':
      case '-':
      setBit(&command, indexOpt0, 0);
      setBit(&command, indexOpt1, 0);
      setBit(&command, indexMode, userStringInput[1] == '-'); // 1 => subtract
      break;
      case '&':
      case '|':
      setBit(&command, indexOpt0, 1);
      setBit(&command, indexOpt1, 0);
      setBit(&command, indexMode, userStringInput[1] == '|'); // 1 => or
      break;
      case '<':
      case '>':
      setBit(&command, indexOpt0, 0);
      setBit(&command, indexOpt1, 1);
      setBit(&command, indexMode, userStringInput[1] == '>'); // 1 => right
      break;
    }
    
    setBit(&command, indexA1, getBit(userStringInput+0, 1));
    setBit(&command, indexA0, getBit(userStringInput+0, 0));
    setBit(&command, indexB1, getBit(userStringInput+2, 1));
    setBit(&command, indexB0, getBit(userStringInput+2, 0));

    Serial.print(getBit(&command, 6));
    Serial.print(getBit(&command, 5));
    Serial.print(getBit(&command, 4));
    Serial.print(getBit(&command, 3));
    Serial.print(getBit(&command, 2));
    Serial.print(getBit(&command, 1));
    Serial.print(getBit(&command, 0));
    Serial.println("\tConverted to BIN.");
    delay(100);

    digitalWrite(numAPins[0], getBit(&command, indexA0));
    digitalWrite(numAPins[1], getBit(&command, indexA1));
    digitalWrite(numBPins[0], getBit(&command, indexB0));
    digitalWrite(numBPins[1], getBit(&command, indexB1));
    digitalWrite(optPins[0], getBit(&command, indexOpt0));
    digitalWrite(optPins[1], getBit(&command, indexOpt1));
    digitalWrite(optPins[2], getBit(&command, indexMode));

    Serial.print(digitalRead(optPins[2]));
    Serial.print(digitalRead(optPins[1]));
    Serial.print(digitalRead(optPins[0]));
    Serial.print(digitalRead(numAPins[1]));
    Serial.print(digitalRead(numAPins[0]));
    Serial.print(digitalRead(numBPins[1]));
    Serial.print(digitalRead(numBPins[0]));
    Serial.println("\tWrote to GPIOS.");
    delay(100);

    setBit(&result, 2, digitalRead(resPins[2]));
    setBit(&result, 1, digitalRead(resPins[1]));
    setBit(&result, 0, digitalRead(resPins[0]));
    Serial.print(getBit(&result, 2));
    Serial.print(" ");
    Serial.print(getBit(&result, 1));
    Serial.print(getBit(&result, 0));
    Serial.println("\tGot result.");

    int8_t decimal = getBit(&result, 1) * 2 + getBit(&result, 0) * 1;
    if (!getBit(&result, 2) && getBit(&command, indexMode)) {
      decimal -= 4;
    }
    Serial.print(decimal);
    Serial.println("\tDecoded.");
    Serial.println("-------------------------");
  }
}


bool isNum(uint8_t hopefullyNum) {
  return hopefullyNum <= 57 && hopefullyNum >= 48;
}
bool getBit(uint8_t* byteAddress, uint8_t index) {
  return *byteAddress >> index & 0b1;
}

void setBit(uint8_t* byteAddress, uint8_t index, bool value) {
  if (value) {
    *byteAddress |= (1 << index);
  }
  else {
    *byteAddress &= ~(1 << index);
  }
}
