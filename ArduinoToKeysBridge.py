import serial
import sys
import time
import serial.tools.list_ports
from pynput.keyboard import Controller, Key

# A simple program to look for the commands from the Arduino and interpret them as keypresses.

def main(serial_port):
    serial_speed = 9600
    keyboard = Controller()

    print(f"Establishing the communication with the Arduino using port: {serial_port}")
    ser = None
    try:
      ser = serial.Serial(serial_port, serial_speed, timeout=1)
    except (OSError, serial.SerialException):
      print("Unable to establish communication.  Do you have the right port?")
      l = serial.tools.list_ports.comports()
      for c in l:
        print(f"Com port: {c[0]}, name: {c[1]}")
      sys.exit(1)

    print("Waiting for arduino bootloader to finish")
    time.sleep(2)

    print("Connected")

    while True:
      command = ser.readline().decode()

      if len(command)==0:
        continue
        
      if command[0] == '*':
        print(f"Debugging information: '{command.strip()}'")
        continue

      command = command[:-2]

      key = None
      if command == "{DOWN}":
          key = Key.down
      elif command == "{UP}":
          key = Key.up
      elif command == "{LEFT}":
          key = Key.left
      elif command == "{RIGHT}":
          key = Key.right
      elif command == "{PGUP}":
          key = Key.page_up
      elif command == "{PGDN}":
          key = Key.page_down
      elif command == "0":
          key = "0"
      elif command == "-":
          key = "-"
      elif command == "=":
          key = "="

      if key is None:
        print(f"Received invalid keypress from Arduino: '{command}'")
      else:
        print(f"Received keypress from Arduino: '{key}'")
        keyboard.press(key)
        keyboard.release(key)
        time.sleep(0.01)

if __name__ == "__main__":
   if len(sys.argv) > 2:
     print("Too many arguments.  Just pass the port number or leave it blank")
   elif len(sys.argv) == 2:
     main(f'COM{sys.argv[1]}')
   else:
     main('COM3')
