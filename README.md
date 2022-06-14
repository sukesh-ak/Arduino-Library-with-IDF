# INTEGRATING ARDUINO LIBRARY IN ESP-IDF
**Make sure to use latest ESP-IDF & Arduino released version**  
We are going to integrate `SparkFun_u-blox_GNSS_Arduino_Library` as a component to our sample `ESP-IDF` project.   
This `Sparkfun` library is taken as an example so you could use any other library you need.

## Detailed Steps below
 > 1. Clone my ESP-IDF C++ template `git clone https://github.com/sukesh-ak/ESP-IDF-CPP-Template.git`  
 > 2. Set device target `idf.py set-target esp32` (or esp32s2 / esp32c3 / esp32s3)  
 > 3. Change firmware/project name in CMakeLists.txt file in the root [CMakeLists.txt](CMakeLists.txt)   
 > 4. Create `components` folder `mkdir components && cd components`  
 > 5. Add `Arduino` as submodule  with folder name `arduino` 
 ```
 git submodule add https://github.com/espressif/arduino-esp32.git arduino 
 ```  
 > 6. Add `SparkFun_u-blox_GNSS_Arduino_Library` as submodule with folder name `SparkFun_u-blox_GNSS`
 ```
 git submodule add https://github.com/sparkfun/SparkFun_u-blox_GNSS_Arduino_Library.git SparkFun_u-blox_GNSS
 ```  
> 7. Create CMakeLists.txt file inside the `SparkFun_u-blox_GNSS` library folder   

```CMake
# CMakeFiles.txt inside "SparkFun_u-blox_GNSS" folder
cmake_minimum_required(VERSION 3.5)
idf_component_register(SRCS "src/SparkFun_u-blox_GNSS_Arduino_Library.cpp"
                    INCLUDE_DIRS "src/."
                    REQUIRES "arduino" # Library requires Arduino
                    )

project(SparkFun_u-blox_GNSS)
```
> 8. Update CMakeLists.txt file in the main folder   
See the file content here [CMakeLists.txt](main/CMakeLists.txt)
```CMake
# Application requires SparkFun_u-blox_GNSS
set(COMPONENT_REQUIRES "SparkFun_u-blox_GNSS")
idf_component_register(SRCS "main.cpp"
                    INCLUDE_DIRS ".")
```                    
 > 9. Run `idf.py menuconfig`  
 > 10. Build `idf.py build`  
 > 11. Flash `idf.py -p <serial-port> flash`  

## Folder contents
The project contains one source file in C++ language [main.cpp](main/main.cpp). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── components [step 4]
│   ├── arduino [submodules - step 5]
│   └── SparkFun_u-blox_GNSS [submodules - step 6]
│       └── CMakeLists.txt [created in Step 7]
├── main
│   ├── CMakeLists.txt
│   └── main.cpp
└── README.md                  This is the file you are currently reading
```

## Credits
[Sparkfun U-Blox GNSS Library](https://github.com/sparkfun/SparkFun_u-blox_GNSS_Arduino_Library)  
