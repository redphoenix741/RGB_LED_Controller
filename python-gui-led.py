import tkinter
import serial
import time

#Function that sends data to UART COM 6
def rgb_write(red, green, blue):
  #delay for PIC UART
  # ts = 0.01
  ser = serial.Serial('COM6', 9600)

  print(red)
  print("\r\nSending Data to PIC....")
  
  ##Send Start .
  ser.write(b'start:')  
  ##Send RED  
  ser.write(b'red:')
  ser.write(repr(red).encode('utf-8'))
  ##Send GRN
  ser.write(b'green:')
  ser.write(repr(green).encode('utf-8'))  
  ##Send BLUE
  ser.write(b'blue:')
  ser.write(repr(blue).encode('utf-8'))   


  print("Data Sent!.. Closing Port")
  ser.close()

#Create Window
main_window = tkinter.Tk()
main_window.title('RGB Controller')

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







