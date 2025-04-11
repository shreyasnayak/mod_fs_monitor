# fs_monitor

**fs_monitor** is a custom [FreeSWITCH](https://freeswitch.com/) module written in Qt C++ for monitoring FreeSWITCH events and activity in real time. 

## Features

- Real-time monitoring of FreeSWITCH core events

## Prerequisites

Before building and running `fs_monitor`, ensure the following are installed:

- FreeSWITCH (core libraries and headers)
- Qt Framework (Qt5 or Qt6 depending on your environment)
- CMake
- A C++ compiler (e.g., `g++`, `clang++`)

## Installation

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/shreyasnayak/mod_fs_monitor.git
   ```

2. **Navigate to the Project Directory**:

   ```bash
   cd mod_fs_monitor
   ```

3. **Build the Module**:

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Install the Module**:

   ```bash
   sudo make install
   ```

## Usage

Once installed, load the `fs_monitor` module into your FreeSWITCH instance. It will hook into FreeSWITCH events and begin 

> For advanced configuration and module usage, refer to the [FreeSWITCH Module Documentation]([https://freeswitch.org/confluence/display/FREESWITCH/FreeSWITCH+Modules](https://developer.signalwire.com/freeswitch/FreeSWITCH-Explained/Modules/)).

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your improvements.

## Contact

If you have any questions or would like to collaborate, feel free to reach out:  
📬 [LinkedIn – Shreyas Nayak](https://linkedin.com/in/shreyas-nayak-1826a710a)

