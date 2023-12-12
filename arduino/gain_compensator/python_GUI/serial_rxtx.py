import serial 
import time 
import PySimpleGUI as sg
"""
arduino = serial.Serial(port='COM6', baudrate=115200, timeout=1) 

def write_read(x): 
    arduino.write(bytes(x, 'utf-8')) 
    time.sleep(0.5) 
    data = arduino.readline() 
    return str(data)


while True: 
    num = input("Enter a command: ") # Taking input from user 
    value = write_read(num).split('\'')[1].split('\\')[0]
    print(value) # printing the value 
"""

 #  "1?3?200"  write in A7 200

sg.theme('DarkAmber')   # Add a touch of color
# All the stuff inside your window.
import PySimpleGUI as sg

def create_tab1():
    layout = [
        [sg.Text("Configuration:"), sg.Radio("Manual", "RADIO1", default=True), sg.Radio("Automatic", "RADIO1")],
        [sg.Text("Operation:"), sg.Radio("Read", "RADIO2", default=True), sg.Radio("Write", "RADIO2")],
        [sg.Text("Value:"), sg.InputText(key="value", size=(10, 1), disabled=True)],
        [sg.Text("Write Options:"), sg.Combo([str(i) for i in range(1, 9)], key="write_option", size=(5, 1), disabled=True),
         sg.Text("Value:"), sg.InputText(key="write_value", size=(10, 1), disabled=True)],
        [sg.Button("Submit"), sg.Button("Exit")]
    ]
    return sg.Tab("Tab 1", layout)

def create_tab2():
    layout = [
        [sg.Text("Select Option:"), sg.Combo([str(i) for i in range(1, 9)], key="plot_option", size=(5, 1))],
        [sg.Button("Plot Real-time Data")]
    ]
    return sg.Tab("Tab 2", layout)

def main():
    sg.theme("Default1")

    tabs = [create_tab1(), create_tab2()]

    layout = [
        [sg.TabGroup([tabs], enable_events=True, key="-TABS-")],
        [sg.Output(size=(60, 10))],  # Output element to display messages
    ]

    window = sg.Window("Configuration Form", layout, finalize=True)

    while True:
        event, values = window.read()

        if event in (sg.WINDOW_CLOSED, "Exit"):
            break

        if event == "-TABS-":
            # Handle tab change events
            if values["-TABS-"] == "Tab 1":
                window["value"].update(disabled=not values[3])
                window["write_option"].update(disabled=not values[5])
                window["write_value"].update(disabled=not values[5])
            elif values["-TABS-"] == "Tab 2":
                # Code for handling events in Tab 2 (future implementation)
                pass

        if event == "Submit":
            # Code for handling submit button click
            print("Submit button clicked")
            print("Values:", values)

    window.close()

if __name__ == "__main__":
    main()
