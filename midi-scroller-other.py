import mido
import threading
import time
import pyautogui

scrolling = False

def smooth_scroll(amount):
    pyautogui.scroll(amount)

def scroll_loop():
    global scrolling
    while scrolling:
        smooth_scroll(-1)
        time.sleep(0.01)

def find_midi_device():
    for name in mido.get_input_names():
        if "Your MIDI Keyboard Name" in name:
            return name
    return None

def listen_midi(device_name):
    with mido.open_input(device_name) as inport:
        print(f"Listening for MIDI input on {device_name}...")

        global scrolling
        for msg in inport:
            if msg.type == 'control_change' and msg.control == 67:
                if msg.value > 0 and not scrolling:
                    print("Pedal pressed - Starting smooth scrolling")
                    scrolling = True
                    threading.Thread(target=scroll_loop, daemon=True).start()
                elif msg.value == 0 and scrolling:
                    print("Pedal released - Stopping scroll")
                    scrolling = False

def list_midi_devices():
    devices = mido.get_input_names()
    if not devices:
        print("No MIDI devices found. Make sure your keyboard is connected.")
        return None
    print("\nAvailable MIDI Devices:")
    for i, device in enumerate(devices):
        print(f"{i}: {device}")
    return devices

def select_midi_device():
    devices = list_midi_devices()
    if not devices:
        return None
    try:
        choice = int(input("\nEnter the number of your MIDI device: "))
        if 0 <= choice < len(devices):
            return devices[choice]
        else:
            print("Invalid selection. Please restart and try again.")
            return None
    except ValueError:
        print("Invalid input. Please restart and enter a valid number.")
        return None

if __name__ == "__main__":
    selected_device = select_midi_device()
    listen_midi(selected_device)