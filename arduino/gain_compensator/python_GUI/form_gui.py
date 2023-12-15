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


# All the stuff inside your window.

def create_tab1():
    layout = [
        [sg.Text("PID:"), sg.Radio("Disabled", "RADIO1", default=True , key="manual_option", enable_events=True), sg.Radio("Enabled", "RADIO1", key="automatic_option", enable_events=True)],
        [sg.Text("Operation:"), sg.Radio("Read", "RADIO2", key = "read_option", enable_events=True), sg.Radio("Write", "RADIO2",default=True, key="write_option", enable_events=True)],
        [sg.Text("Channel:"), sg.Combo([str(i) for i in range(1, 9)], key="channel_option_tab1", size=(5, 1))],
        [sg.Text("Value:"), sg.InputText(key="value_to_write", size=(10, 1), do_not_clear=False)],
        [sg.Output(size=(60, 10))],  # Output element to display messages
        [sg.Button("Submit"), sg.Button("Exit")]
    ]
    return sg.Tab("Tab 1", layout)

def create_tab2():
    layout = [
        [sg.Text("Channel:"), sg.Combo([str(i) for i in range(1, 9)], key="channel_option_tab2", size=(5, 1))],
        [sg.Button("Plot Real-time Data")]
    ]
    return sg.Tab("Tab 2", layout)

def main():
    sg.theme('Dark Blue 3')   # Add a touch of color

    tabs = [create_tab1(), create_tab2()]

    layout = [
        [sg.TabGroup([tabs], enable_events=True, key="-TABS-")]
    ]

    window = sg.Window("Configuration Form", layout, finalize=True)

    while True:
        event, values = window.read()

        if event in (sg.WINDOW_CLOSED, "Exit"):
            break


        if values["automatic_option"]:
            window["value_to_write"].update(disabled=True)
            window["write_option"].update(disabled=True)
        else:
            window["value_to_write"].update(disabled=False)
            window["write_option"].update(disabled=False)

        if values["read_option"]:
            window["value_to_write"].update(disabled = True)

        if values["write_option"]:
            window["value_to_write"].update(disabled = False)

        if event == "Submit":
            # Code for handling submit button click
            print("Submit button clicked")
            print("Values:", values)

    window.close()

if __name__ == "__main__":
    main()
