### NAOqi Humotion Adapter

### Installation

You will need to install naoqi-sdk-*-linux64 >= naoqi-sdk-2.1.2.17-linux64
You will also need qibuild (https://github.com/aldebaran/qibuild)

### Building

    mkdir build
    cd build
    cmake -DCMAKE_INSTALL_PREFIX=$prefix -DQI_SDK_DIR=/path/to/naoqi-sdk-2.1.2.17-linux64/ ..

### Usage

    $prefix/bin/nao_humotion_adapter robots_ip_address robots_port