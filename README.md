# MIDI Scroller

This repository contains two Python scripts that allow you to control the scrolling behaviour on your system using a MIDI pedal. The idea behind this tool is to make it easier for pianists to scroll through their sheet music whilst playing, without needing to manually interact with the computer. The **left pedal**, which is often underutilised in piano playing, is a perfect candidate for this task.

- **`midi-scroller-mac.py`**: A version that uses macOS Quartz for smooth scrolling, designed specifically for macOS.
- **`midi-scroller-other.py`**: A cross-platform version that works on both Windows and Linux, but does not have smooth scrolling.
- **`midi-scroller-mac.c`**: A Mac version in C with smooth scrolling and lower runtime bloat.

## Purpose

When playing the piano, musicians often need to manually scroll through their sheet music as they progress through a piece. Whilst this is not difficult when performing with a single page or short pieces, it can become distracting and cumbersome when dealing with longer sheets or when a pianist’s hands are already fully engaged with the keyboard.

The **left pedal** on many pianos, often the **soft pedal** (or **una corda** in some pianos), is typically underutilised during performances, as it modifies the sound rather than the playability of the music. As such, it makes an ideal candidate for repurposing to control functions like scrolling, giving pianists a simple way to continue performing without losing focus on the music or needing to interrupt their playing.

By connecting the **left pedal** to a MIDI interface, this tool allows the pianist to control scrolling through their sheet music automatically. Pressing the left pedal starts the scroll, and releasing it stops the scrolling, ensuring the musician can keep their hands on the keyboard whilst the pages move on their screen.

## Features

- Press the MIDI pedal to start scrolling.
- Release the MIDI pedal to stop scrolling.
- Smooth scrolling on macOS (`midi-scroller-mac.py`).
- Basic scrolling on Windows/Linux (`midi-scroller-other.py`).

## Requirements

### For `midi-scroller-mac.py` (Smooth Scrolling)
- macOS
- Python 3.x
- `mido` (for MIDI communication)
- `pyobjc-framework-Quartz` (for interacting with macOS Quartz APIs)

You can install the necessary Python packages with:

```bash
pip install mido pyobjc-framework-Quartz
```

### For `midi-scroller-other.py` (Windows/Linux)
- Windows or Linux
- Python 3.x
- `mido` (for MIDI communication)
- `pyautogui` (for simulating scrolling events)

You can install the necessary Python packages with:

```bash
pip install mido pyautogui
```

### For `midi-scroller-mac.c` (Mac only)
- macOS
- `clang` and `make`

You can install the necessary tools with:

```
xcode-select --install
```

To compile the project, run:

```bash
make
```

And to clean the build files:

```bash
make clean
```

## Contributing

Thank you for your interest in contributing to this project! If you'd like to help out, please feel free to contribute in any of the following ways:

### How to Contribute

1. **Report Bugs**: If you find any bugs or issues, please open an issue on the repository, providing detailed steps to reproduce the problem.
2. **Fix Bugs**: If you notice any bugs, feel free to fork the repository, make the fix, and create a pull request.
3. **Suggest Features**: If you have a new feature in mind or an idea to improve the current functionality, please feel free to submit an issue or a pull request.
4. **Code Quality**: Please make sure the code adheres to the current style guidelines used throughout the project. This will make reviewing your pull request faster.
5. **Documentation**: If you want to improve the documentation, whether it's adding more clarity or adding new sections, contributions are always welcome!
6. **Propose Stylistic Changes**: I can consider code style or repository restructuring if you make a pull request that applies the proposed changes across all of the files, with a justification of why it is an improvement.

### Bringing Smooth Scrolling to Linux and Windows

While this project has its roots in macOS, there is potential to extend the functionality to **Linux** and **Windows** platforms, especially for the Python version. These enhancements are important to ensure that users across different operating systems can experience the same smooth scrolling functionality. Contributions to port the code to these platforms are highly encouraged.

- **Linux**: For Linux, integrating with system-level APIs such as `X11` or `Wayland` to simulate scroll events would be ideal. Libraries like `python-evdev` or `python-uinput` could be useful for the Python version, or `Xlib` for the C version.
  
- **Windows**: For Windows, we can explore using the Windows API (`SendInput`, `mouse_event`, or `keybd_event`) for simulating scrolling events. This would enable smooth scrolling in a way that's consistent with Windows' input handling.

### C Version Port for Linux and Windows

It is also possible to bring the C version of the smooth scrolling tool to both Linux and Windows. The C language's efficiency and low-level access to system resources make it an ideal choice for this project, as it ensures minimal bloat and high performance. We would maintain similar functionality across all versions (Linux, Windows, and macOS), including:

- **User prompts**
- **Command-line arguments**
- **Consistent scrolling behaviour**

### Why C Instead of Python?

Whilst Python is a powerful and accessible language for many users, it's not always the most efficient choice for real-time interaction with hardware and system-level input control. A C version would allow for greater performance, lower latency, and better integration with system APIs, ensuring easier development and lower runtime bloat.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.