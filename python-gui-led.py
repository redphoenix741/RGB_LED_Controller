import tkinter
from tkcolorpicker import askcolor
import serial
import time

#Function that sends data to UART COM 6
def rgb_write(red, green, blue):
  #delay for PIC UART
  # ts = 0.01
  ser = serial.Serial('COM6', 9600)

  print("\r\nSending Data to PIC....")
  
  ##Send Start .
  ser.write(b's.')  
  ##Send RED  
  ser.write(str(red).encode('utf-8'))
  ##Send GRN
  ser.write(b'.')
  ser.write(str(green).encode('utf-8'))  
  ##Send BLUE
  ser.write(b'.')
  ser.write(str(blue).encode('utf-8'))   
  ser.write(b'.e')

  print("Data Sent!.. Closing Port")
  ser.close()

#OpenBGDialog
def openbgdialog():
  rgb_value = askcolor()
  # Write To LED
  rgb_write(rgb_value[0][0],rgb_value[0][1],rgb_value[0][2])
  
  #Set Sliders
  set_val_red.set(rgb_value[0][0])
  set_val_green.set(rgb_value[0][1])
  set_val_blue.set(rgb_value[0][2])

#Python Start ==================================================        
#Create Window
main_window = tkinter.Tk()
main_window.title('RGB Controller')

#Color Picker
set_color = tkinter.Button(main_window, text='Set Color', command=lambda:openbgdialog())
set_color.pack()

#Scale
set_val_red = tkinter.Scale(main_window, from_=0, to=255, orient=tkinter.HORIZONTAL)
set_val_red.pack()
set_val_green = tkinter.Scale(main_window, from_=0, to=255, orient=tkinter.HORIZONTAL)
set_val_green.pack()
set_val_blue = tkinter.Scale(main_window, from_=0, to=255, orient=tkinter.HORIZONTAL)
set_val_blue.pack()

#Button
send_val = tkinter.Button(main_window, text='Send Value', command=lambda : rgb_write(set_val_red.get(),set_val_green.get(),set_val_blue.get()))
send_val.pack()

main_window.mainloop()







