import PySimpleGUI as sg
import serial 
import subprocess
import time

# global variable that handles the serial communication
arduino = None

# All the stuff inside the window.

def create_initial_window():
    # read the ports available
    result = subprocess.run(['python', '-m', 'serial.tools.list_ports'], capture_output=True, text=True, check=True)
    output_coms = result.stdout.splitlines()

    layout = [
        [sg.Text("Select the communication port:")],
        [sg.Combo(output_coms, key="com_port", size=(9, 1))],
        [sg.Button("Next"), sg.Button("Exit")]
    ]

    return layout


def create_tab1():
    layout = [
        [sg.Text("PID:"), sg.Radio("Disabled", "RADIO1", default=True , key="manual_option", enable_events=True), sg.Radio("Enabled", "RADIO1", key="automatic_option", enable_events=True)],
        [sg.Text("Operation:"), sg.Radio("Read", "RADIO2", key = "read_option", enable_events=True), sg.Radio("Write", "RADIO2",default=True, key="write_option", enable_events=True)],
        [sg.Text("Channel:"), sg.Combo([str(i) for i in range(1, 9)], key="channel_option_tab1", size=(5, 1))],
        [sg.Text("Value:"), sg.Slider(range=(0,255), orientation='h', size=(20, 15), default_value=0, key="value_to_write")],
        [sg.Output(size=(60, 10))],  # Output element to display messages
        [sg.Button("Submit"), sg.Button("Exit")]
    ]
    return sg.Tab("Read/Write data", layout)

def create_tab2():
    layout = [
        [sg.Text("Channel:"), sg.Combo([str(i) for i in range(1, 9)], key="channel_option_tab2", size=(5, 1))],
        [sg.Button("Plot Real-time Data")]
    ]
    return sg.Tab("Plot", layout)


def transform_values_to_serial_command(values):
    command = ""
    if values["read_option"]:
        command += "0?"
    else:
        command += "1?"

    command += values["channel_option_tab1"]
    command += "?"

    command += str(int(values["value_to_write"]))

    return command


def create_secondary_window():
        
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
            command = transform_values_to_serial_command(values)
            print("Command to send:")
            print(command)
            arduino.write(bytes(command, 'utf-8'))
            time.sleep(0.5) 
            data = str(arduino.readline()).split('\'')[1].split('\\')[0]
            print("Response:")
            print(data + "\n")
        
        window["value_to_write"].update(0)

    window.close()


def main():
    sg.theme('Dark Blue 3')   # Add a touch of color

    window = sg.Window("Selecting port...",create_initial_window(), finalize=True)

    while True:
        event, values = window.read()

        if event in (sg.WINDOW_CLOSED, "Exit"):
            break

        if event == 'Next':
            try:
                global arduino
                com_port_selected = values["com_port"]
                arduino = serial.Serial(port=com_port_selected, baudrate=115200, timeout=1) 
                window.close()
                create_secondary_window()
                break
            except:
                sg.popup_error("The selected COM port is not available.")      

    window.close()


if __name__ == "__main__":
    main()
