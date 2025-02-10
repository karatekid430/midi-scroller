#include <CoreMIDI/CoreMIDI.h>
#include <QuartzCore/QuartzCore.h>
#include <pthread.h>

// Global flag for scrolling status
volatile int scrolling = 0;
pthread_t scroll_thread;

// Function to create a scroll event
void scroll_event(int amount) {
    CGEventRef scrollEvent = CGEventCreateScrollWheelEvent(NULL, kCGScrollEventUnitPixel, 1, amount);
    CGEventPost(kCGHIDEventTap, scrollEvent);
    CFRelease(scrollEvent);
}

// Scroll loop to keep scrolling while the pedal is pressed
void *scroll_loop(void *arg) {
    while (scrolling) {
        scroll_event(-1);  // Scroll down
        usleep(10000);     // Wait for a short period (10ms) to simulate smooth scrolling
    }
    return NULL;
}

// MIDI input callback function
void MIDI_callback(const MIDIPacketList *pktlist, void *readProcRefCon, void *srcConnRefCon) {
    MIDIPacket *packet = (MIDIPacket *)pktlist->packet;

    for (int i = 0; i < pktlist->numPackets; i++) {
        if (packet->data[0] == 0xB0 && packet->data[1] == 67) { // Control change, pedal
            if (packet->data[2] > 0 && !scrolling) {  // Pedal pressed
                printf("Pedal pressed - Starting smooth scroll\n");
                scrolling = 1;
                pthread_create(&scroll_thread, NULL, scroll_loop, NULL);
            } else if (packet->data[2] == 0 && scrolling) {  // Pedal released
                printf("Pedal released - Stopping scroll\n");
                scrolling = 0;
                pthread_join(scroll_thread, NULL);  // Wait for the scroll thread to finish
            }
        }
        packet = MIDIPacketNext(packet);
    }
}

// Function to list available MIDI devices
void list_midi_devices() {
    ItemCount numDevices = MIDIGetNumberOfSources();
    if (numDevices == 0) {
        printf("No MIDI devices found. Make sure your keyboard is connected.\n");
        return;
    }
    printf("\nAvailable MIDI Devices:\n");
    for (int i = 0; i < numDevices; i++) {
        MIDIEndpointRef source = MIDIGetSource(i);
        CFStringRef name;
        MIDIObjectGetStringProperty(source, kMIDIPropertyDisplayName, &name);
        printf("%d: %s\n", i, CFStringGetCStringPtr(name, kCFStringEncodingUTF8));
    }
}

// Function to start MIDI listening
void start_midi_listening(int device_index) {
    MIDIClientRef client;
    MIDIPortRef inPort;
    MIDIEndpointRef input;

    // Create MIDI client
    MIDIClientCreate(CFSTR("MIDI_Scroll_Client"), NULL, NULL, &client);

    // Get the selected MIDI device
    input = MIDIGetSource(device_index);  // Use the selected MIDI source
    if (input == -1) {
        printf("Invalid MIDI device selected.\n");
        return;
    }

    MIDIInputPortCreate(client, CFSTR("Input Port"), MIDI_callback, NULL, &inPort);
    MIDIPortConnectSource(inPort, input, NULL);
    
    printf("Listening for MIDI input...\n");
    
    // Keep listening
    CFRunLoopRun();
}

int main() {
    // List available MIDI devices
    list_midi_devices();

    // Take the user's selection
    int selected_device = -1;
    printf("\nEnter the number of your MIDI device: ");
    if (scanf("%d", &selected_device) != 1 || selected_device < 0) {
        printf("Invalid selection. Exiting...\n");
        return -1;
    }

    // Start listening to the selected device
    start_midi_listening(selected_device);
    return 0;
}