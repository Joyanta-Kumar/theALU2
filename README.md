# The ALU of 2 bits

A basic ALU circuit that can perform addition, subtraction of 2-bit numbers.\
It can also perform some bitwise operations.

I programmed a decoder in the control unit (Arduino Nano) so that we can see the output nicely in `"%d"` (decimal) format.

The whole system is built on two merged breadboards, connected with CAT6 wires. Communication with my computer is done via USB cable using UART serial transmission, and a GUI made in Python with `customtkinter` handles user interaction.

---

## ✨ Features

- 2-bit Arithmetic (Add, Subtract, Increment, Decrement)
- 2-bit Bitwise Operations (AND, OR, Shifts)
- 3-bit Output with Carry Handling
- GUI for Input and Output (Built with Python `customtkinter`)
- UART Communication (9600 baud rate)
- Hardware built with 74xx logic chips and a single 4:1 multiplexer

---

## 🛠 Circuit Components

| Component       | Chip Model        | Quantity |
| --------------- | ----------------- | -------- |
| XOR gates       | 74LS86            | 2        | 
| OR gates        | 74LS32            | 1        | 
| AND gates       | 74LS08            | 2        | 
| 4:1 Multiplexer | 74LS153           | 1        | 
| Control Unit    | Arduino Nano      | 1        | 
| Wires           | CAT6              | Mela     |
| Breadboards     |                   | 2        | 

---

## 📜 Operations

### Arithmetic

1. [Add / Subtract](#add--subtract)
2. [Increment / Decrement](#increment--decrement)

### Bitwise

1. [Left Shift / Right Shift](#bit-shift)
2. [AND / OR](#and--or)

---

## ⚙️ How It Operates

### Add / Subtract

- It can only display results that are representable within 2 bits.
- But, I was surprised when I looked at the results of subtraction.
- If the difference between two given numbers fits in 2 bits, the result is correct.
- Also, a 3rd bit (Carry/Borrow) is available if needed.

Example input format:

```
[num1][+][num2]
[num1][-][num2]
```

---

### Increment / Decrement

- These are not distinct functions.
- When the system receives a command like `num++` or `++num`, the other number is automatically assumed to be `1`.
- Same thing for `num--` or `--num`.

Example:

```
[num][+][+]
[-][-][num]
```

---

### Bit Shift

- Shifts the number by **one bit**.
- Shifting direction is defined by `<` or `>`.

Example:

```
[num][>][>]
[num][<][<]

[<][<][num] // Same as above.
[num][<][>] // Bad input, don't do this.
```

---

### AND / OR

- Performs bitwise `&` or `|` operations between two 2-bit numbers.

Example:

```
[num1][&][num2]
[num1][|][num2]
```

---

## ⚠️ Cautions

1. This system was designed to work with another control unit, but our lack of experience hindered us.
2. It was meant to be combined with another 2-bit ALU to form a `4-bit` circuit. However, due to poorly managed wiring, this is hardly possible.
3. Do not enter commands with spaces. Use the format:\
   `[num1][option][num2]` (without the `'['` or `']'` characters.)
4. **Do not input negative numbers.**\
   User input is transferred as a `String` to the control unit.\
   Only the first 3 characters are read.
5. If you mess up the input, there is no error handling.\
   You are the operator. You do not make mistakes. Period.

---

## 🛠 Problems We Faced

1. Keeping the team alive is hard. Their absence let me forget their names.
2. Managing time for other works while spending more than 18 hours a day on this project.
3. Reading `UART` — the baudrate, port, and random unrecognizable characters from serial mismatch.
4. Cutting wires and shaping them nicely.\
   Tool selection and quantity were... limited.
5. Losing track of wires because we didn't color-code input/output wires.\
   (Bad decision. Do not recommend.)

---

## 🎯 Things We Acknowledged

1. The `Serial.read()` function **takes time**.
2. Keeping your teeth away from wires **helps**.
3. The 74xxx chips are **tough**, but not tough enough to **bite**.
4. Thank God we live in the era of **tiny chips** and not **vacuum tubes**.
5. It's okay to fail.

---

## 💾 System Diagram

```plaintext
+----------------+    UART (9600)   +------------------+      Wires     +----------------+
| Python GUI     |  <-------------> | Arduino Nano     |  <-----------> | 2-bit ALU      |
| (customtkinter)|                  | (Control Unit)   |                | (Logic Circuit)|
+----------------+                  +------------------+                +----------------+
```

---

## ❓ Who are we ?

```json
"teamName" : "Overflow",
"members": [
   {
      "Name": "Joyanta Kumar",
      "Department": "CSE",
      "Batch": 6,
      "Contact": "https://github.com/joyanta-kumar"
   },
   {
      "Name": "MD Mosharraf Hossain",
      "Department": "CSE",
      "Batch": 6,
      "Contact": "Jani na"
   },
   {
      "Name": "MD Jubaer Hossain Fahad",
      "Department": "CSE",
      "Batch": 6,
      "Contact": "01xx"
   },
   {
      "Name": "Nafis Ahsan",
      "Department": "EEE",
      "Batch": 15,
      "Contact": "Jani na too"
   },
]
```

---

# ✨ Final Words

I made this ALU for learning, struggle, fun, and memories.\
Maybe someday I’ll look back and smile at these two breadboards.\
Until then, one step at a time.

And also, this file was only formatted with chatgpt.\
It added icons and proper spacing between line.

**– Joyanta**

---

