import serial
import sys
import time
import SendKeys
import serial.tools.list_ports

# A simple program to look for the commands from the Arduino and interpret them as keypresses.

def main(serial_port):
    serial_speed = 9600

    print "Establishing the communication with the Arduino using port: " + serial_port
    ser = None
    try:
      ser = serial.Serial(serial_port, serial_speed, timeout=1)
    except (OSError, serial.SerialException):
      print "Unable to establish communication.  Do you have the right port?"
      l = serial.tools.list_ports.comports()
      for c in l:
        print "Com port: " + c[0] + ", name: " + c[1]
      sys.exit(1)

    print "Waiting for arduino bootloader to finish"
    time.sleep(2)

    print "Connected"

    while True:
      key = ser.readline()

      if key == '':
        continue
      if key[0] == '*':
        print "Debugging information: " + key
      else:
        key = key[:-2]
        print "Received keypress from Arduino: '" + key + "'"
        SendKeys.SendKeys( key )
        time.sleep(0.01)

if __name__ == "__main__":
   if len(sys.argv) > 2:
     print "Too many arguments.  Just pass the port number or leave it blank"
   elif len(sys.argv) == 2:
     main('COM' + sys.argv[1])
   else:
     main('COM7')

