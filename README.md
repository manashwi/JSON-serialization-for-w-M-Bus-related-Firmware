# JSON-serialization-for-w-M-Bus-related-Firmware
The goal of this project was to design and implementat an embedded-friendly software library that serializes structured meter data into a predefined JSON format

# Key Features
Written in pure C
No dynamic memory allocation
No external JSON libraries
Buffer overflow protected
Embedded-friendly and portable
JSON format matches the required structure exactly

#Why This Design?
1. Why C?
C is widely used in embedded firmware
Full control over memory
Minimal runtime overhead
Works on microcontrollers and Linux targets

3. Why No JSON Library?
Embedded systems often have limited memory
JSON libraries increase binary size
Manual serialization ensures exact output format
No hidden heap usage

5. Why Fixed-Size Buffers?
Predictable memory usage
Avoids fragmentation
Safer than dynamic allocation in firmware
Easier to analyze and test

7. Why Manual Buffer Handling
Prevents buffer overflow
Every write checks remaining space
Errors are returned safely
Suitable for safety-critical systems
