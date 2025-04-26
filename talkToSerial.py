import serial
import time
import threading
import customtkinter as ctk
from datetime import datetime

ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
time.sleep(2)

def send_command():
    command = entry_input.get()
    ser.write(command.encode('utf-8'))
    log_output(f"Sent: {command}")

def log_output(message):
    timestamp = datetime.now().strftime("%H:%M:%S.") + f"{datetime.now().microsecond // 1000:03d}"
    message_with_timestamp = f"[{timestamp}] {message}"

    output_text.configure(state='normal')
    output_text.insert(ctk.END, message_with_timestamp + "\n")
    output_text.see(ctk.END)
    output_text.configure(state='disabled')

def read_serial():
    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            if line:
                log_output(line)

ctk.set_appearance_mode("light")
ctk.set_default_color_theme("dark-blue")
root = ctk.CTk()
root.title("Arduino ALU Controller ⚡")
root.geometry("500x300")

frame = ctk.CTkFrame(root)
frame.pack(fill="both", expand=True, padx=20, pady=20)

entry_input = ctk.CTkEntry(frame, width=200, font=("Hurmit Nerd Font", 18))
entry_input.grid(row=0, column=0, padx=10, pady=10)

send_button = ctk.CTkButton(frame, text="Send", font=("Hurmit Nerd Font", 18), command=send_command)
send_button.grid(row=0, column=1, padx=10, pady=10)

output_text = ctk.CTkTextbox(frame, font=("Hurmit Nerd Font", 16), wrap="word", state='disabled')
output_text.grid(row=1, column=0, columnspan=2, padx=10, pady=10, sticky="nsew")

frame.rowconfigure(0, weight=1)
frame.rowconfigure(1, weight=3)
frame.columnconfigure(0, weight=3)
frame.columnconfigure(1, weight=1)

serial_thread = threading.Thread(target=read_serial, daemon=True)
serial_thread.start()

root.mainloop()
