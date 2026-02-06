from flask import Flask, render_template, Response
from camera import VideoCamera, gen
import serial
import time

app = Flask(__name__)

# --- ARDUINO SERIAL CONFIGURATION ---
PORT = 'COM5' 
try:
    ser = serial.Serial(PORT, 9600, timeout=0.1)
    time.sleep(2)  # Wait for Arduino to reboot
    print(f"Connected to Arduino on {PORT}")
except Exception as e:
    print(f"Serial Error: {e}")
    ser = None

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/video_feed')
def video_feed():
    return Response(gen(VideoCamera()),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/control/<action>/<state>')
def control_robot(action, state):
    if ser and ser.is_open:
        cmd_map = {
            # Standard Directions
            #UP - U u
            #DOWN - D d
            #LEFT - L l
            #RIGHT - R r
            'forward_start': 'U', 'forward_stop': 'u',
            'backward_start': 'D', 'backward_stop': 'd',
            'left_start': 'L', 'left_stop': 'l',
            'right_start': 'R', 'right_stop': 'r',
            
            # Diagonal Directions
            #UPLEFT - Q q
            #UPRIGHT - E e
            #DOWNLEFT - Z z
            #DOWNRIGHT - C c
            'upleft_start': 'Q', 'upleft_stop': 'q',
            'upright_start': 'E', 'upright_stop': 'e',
            'downleft_start': 'Z', 'downleft_stop': 'z',
            'downright_start': 'C', 'downright_stop': 'c',
            
            # Toggles
            #HORN - H h
            #LIGHT - N F
            'horn_start': 'H', 'horn_stop': 'h',
            'light_on': 'N', 'light_off': 'F'
        }
        
        lookup = f"{action}_{state}"
        command = cmd_map.get(lookup)
        
        if command:
            ser.write(command.encode())
            print(f"Action: {lookup} -> Arduino Sent: {command}")
            
    return "OK", 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True, threaded=True)