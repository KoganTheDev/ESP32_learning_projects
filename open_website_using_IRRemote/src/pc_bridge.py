import serial
import webbrowser
import time
import pyautogui

# Check if we are using the correct library
if not hasattr(serial, 'Serial'):
    print("--------------------------------------------------")
    print("ERROR: You still have a file named 'serial.py' in this folder.")
    print(f"Location of conflicting file: {serial.__file__}")
    print("Please rename that file and delete __pycache__.")
    print("--------------------------------------------------")
    exit()

# Configuration
PORT = 'COM5'  # Update this to your port from Device Manager
BAUD = 115200
URL = "https://www.youtube.com"

def run_bridge():
    try:
        device = serial.Serial(PORT, BAUD, timeout=1)
        print(f"Connected to {PORT}. Waiting for remote...")
    except Exception as e:
        print(f"Connection error: {e}")
        return

    while True:
        try:
            if device.in_waiting > 0:
                line = device.readline().decode('utf-8', errors='ignore').strip()
                
                if line == "COMMAND:OPEN_WEBSITE":
                    print("Signal received. Opening site...")
                    webbrowser.open(URL)
                    time.sleep(3) 
                    pyautogui.press('f11')
                
                elif "RECEIVED_HEX" in line:
                    print(f"Detected Code: {line}")
                    
        except KeyboardInterrupt:
            break
    
    device.close()

if __name__ == "__main__":
    run_bridge()