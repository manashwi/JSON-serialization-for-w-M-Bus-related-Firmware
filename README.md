# JSON-serialization-for-w-M-Bus-related-Firmware
The goal of this project was to design and implementat an embedded-friendly software library that serializes structured meter data into a predefined JSON format

# Key Features
Written in pure C, No dynamic memory allocation, No external JSON libraries, Buffer overflow protected, Embedded-friendly and portable, JSON format matches the required structure exactly

# Why This Design?
1. Why C? <br/>
  C is widely used in embedded firmware <br/>
  Full control over memory <br/>
  Minimal runtime overhead <br/>
  Works on microcontrollers and Linux targets <br/>
  
2. Why No JSON Library? <br/>
  Embedded systems often have limited memory <br/>
  JSON libraries increase binary size <br/>
  Manual serialization ensures exact output format <br/>
  No hidden heap usage <br/>

3. Why Fixed-Size Buffers? <br/>
  Predictable memory usage <br/>
  Avoids fragmentation <br/>
  Safer than dynamic allocation in firmware <br/>
  Easier to analyze and test <br/>

7. Why Manual Buffer Handling <br/>
  Prevents buffer overflow <br/>
  Every write checks remaining space <br/>
  Errors are returned safely <br/>
  Suitable for safety-critical systems <br/>

# How to Build and Run
Using GCC <br/>
gcc examples/demo.c src/json_serializer.c -Iinclude -o demo <br/>
./demo

# Example Output
[ <br/>
  { <br/>
    "gateway_id":"GW001", <br/>
    "date":"2024-01-01", <br/>
    "device_type":"water", <br/>
    "interval_minutes":60, <br/>
    "total_readings":2, <br/>
    "values":{ <br/>
      "readings":[ <br/>
        { <br/>
          "media":"water", <br/>
          "meter":"flow", <br/>
          "device_id":"DEV001", <br/>
          "unit":"m3", <br/>
          "data":[ <br/>
          { <br/>
              "timestamp":"2024-01-01T00:00", <br/>
              "meter_datetime":"2024-01-01T00:00", <br/>
              "total_m3":12.345, <br/>
              "status":"OK" <br/>
            } <br/>
          ] <br/>
        } <br/>
      ] <br/>
    } <br/>
  } <br/>
] 

# Assumptions
Maximum number of devices and data points is fixed at compile time <br/>
Input strings are valid and null-terminated <br/>
JSON format must not be modified

# Conclusion
This project demonstrates safe and efficient JSON serialization suitable for embedded systems. <br/>
The design prioritizes clarity, reliability, and memory safety, making it suitable for real-world firmware applications.
