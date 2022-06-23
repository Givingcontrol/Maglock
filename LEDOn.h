

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  bool LedOn = false;
  bool SwitchClosed = false; // ask if switch closed># >> send switch position
  bool activateRelay = false; //tell to activate relay
  bool deactivateRelay = false; // replying relay state
} struct_message;

// Create a struct_message called myData
struct_message sentData;

// Create a struct_message to hold incoming data
struct_message receivedData;
