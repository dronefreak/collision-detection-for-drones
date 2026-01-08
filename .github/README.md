# Collision Detection for Drones

A collision detection system using up to 6 HC-SR04 ultrasonic sensors with Arduino to detect obstacles from 6 directions, publishing data into ROS (Robot Operating System).

![Hardware Setup](https://cloud.githubusercontent.com/assets/10280687/17396651/ff939cdc-5a51-11e6-8a77-9b91d15594bb.JPG)

## Overview

This project enables Arduino-based collision detection for drones and robotic systems. The Arduino samples data from any or all of the 6 sensors at a configurable rate and publishes the readings to ROS topics. The system has been tested on FlytPOD with FlytOS, but is compatible with any ROS setup.

## Features

- **Continuous Output Mode**: Stream sensor data continuously at a configurable rate
- **One-Time Poll Mode**: Query fresh data on demand
- **Sensor Selection**: Choose which sensors to listen to from the 6 available sensors
- **Configurable Poll Rate**: Adjust the sensor sampling rate dynamically
- **Web Interface**: Real-time visualization of sensor data through a browser-based GUI

![Web Interface](https://cloud.githubusercontent.com/assets/13434353/17547419/bfc44860-5f04-11e6-85e6-dbfcd2564dbf.png)

## Project Structure

```
collision-detection-for-drones/
├── arduino/              # Arduino firmware for sensor control
│   └── sonar_jig_6.ino  # Main sketch for 6 HC-SR04 sensors
├── flytsonar/           # Flask web application
│   ├── static/          # Frontend assets (HTML, CSS, JavaScript)
│   └── views.py         # Backend API endpoints
├── STL_files/           # 3D printable parts for sensor mounting
├── tests/               # Test suites (Python and JavaScript)
├── .github/             # GitHub workflows and configuration
│   └── workflows/       # CI/CD automation pipelines
├── requirements.txt     # Python dependencies
├── package.json         # JavaScript dependencies (documentation)
└── LICENSE              # Apache 2.0 license
```

### Directory Details

- **[`arduino/`](arduino/)**: Contains the Arduino sketch that interfaces with HC-SR04 sensors and publishes data to ROS using rosserial. Handles sensor polling, data formatting, and ROS communication.

- **[`flytsonar/`](flytsonar/)**: Flask-based web application providing a real-time visualization interface. Includes HTML5 frontend with WebSocket support for live sensor data display.

- **[`STL_files/`](STL_files/)**: 3D-printable mounting brackets and enclosures for positioning sensors around the drone frame.

- **[`tests/`](tests/)**: Unit and integration tests for Python backend and JavaScript frontend components.

- **[`.github/workflows/`](.github/workflows/)**: Automated CI/CD pipelines for linting, testing, security scanning, and dependency management.

## Hardware Requirements

- **Sensors**: 6x HC-SR04 ultrasonic distance sensors
- **Microcontroller**: Arduino Uno/Nano or TI Tiva C Launchpad
- **Power Supply**: 5V power source for sensors (separate from Arduino is recommended)
- **Cables**: USB cable for Arduino, jumper wires for sensor connections
- **Optional**: 3D printer for mounting brackets

## Hardware Setup

1. **3D Print Mounting Parts**: Use the STL files in [`STL_files/`](STL_files/) to print sensor mounts.

2. **Power Configuration**: Supply all sensors with a separate 5V power source to avoid voltage drops. The Arduino can be powered via USB.

3. **Wiring**: Connect each HC-SR04 sensor to the Arduino:
   - VCC → 5V
   - GND → Ground
   - TRIG → Digital pin (see [`arduino/sonar_jig_6.ino`](arduino/sonar_jig_6.ino) for pin mappings)
   - ECHO → Digital pin

## Software Setup

### ROS Installation

Install the rosserial package for Arduino communication:

```bash
sudo apt-get install ros-indigo-rosserial-arduino \
                     ros-indigo-rosserial \
                     ros-indigo-rosserial-msgs \
                     ros-indigo-rosserial-client \
                     ros-indigo-rosserial-python
```

**For TI Tiva C Launchpad users**, install rosserial_tivac from source:

```bash
cd <workspace_dir>/src
git clone https://github.com/robosavvy/rosserial_tivac.git
cd ..
catkin_make
catkin_make install
```

### Arduino Setup

1. Open [`arduino/sonar_jig_6.ino`](arduino/sonar_jig_6.ino) in the Arduino IDE
2. Install required libraries: `rosserial_arduino`, `NewPing`
3. Upload the sketch to your Arduino board

### Running the System

1. **Connect the Arduino**: Plug the Arduino into a USB port and power the sensors.

2. **Start the ROS Serial Node**:
   ```bash
   rosrun rosserial_python serial_node.py /dev/ttyACM0
   ```
   *Note: If the device is not found on ACM0, try ACM1 or disconnect/reconnect the device.*

3. **Verify Data Publication**:
   ```bash
   rostopic echo sonar
   ```

4. **Launch the Web Interface**:
   - Ensure FlytOS is running
   - Open your browser and navigate to: `http://<FlytPOD-IP>:9090/flytsonar`

### Installing FlytSonar App

To install the web application on your FlytOS SD card:

1. Clone this repository or download the source
2. Copy the [`flytsonar/`](flytsonar/) directory to `/flyt/flytapps/web/` (requires sudo)
3. Edit `apps.py` to add an entry for the new app
4. Restart FlytOS

## Configuration

- **Sensor Poll Rate**: Adjust via ROS topic or web interface (default: 100Hz, range: 1-200Hz)
- **Active Sensors**: Enable/disable individual sensors through the web interface
- **Distance Thresholds**: Configurable warning zones in the web UI

## Documentation

- **[CONTRIBUTING.md](CONTRIBUTING.md)**: Guidelines for contributing to the project
- **[SECURITY.md](SECURITY.md)**: Security policy and vulnerability reporting
- **[LICENSE](LICENSE)**: Apache 2.0 license details
- **[CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md)**: Community standards and expectations

## Contributing

Contributions are welcome! Please read our [Contributing Guide](CONTRIBUTING.md) for details on our code of conduct, development process, and how to submit pull requests.

## License

This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.

## Credits

**Original Contributor**: Saumya Saksena (f2013114@hyderabad.bits-pilani.ac.in)
**Maintainer**: Dhiraj (dhiraj@navstik.org)

## Support

For issues, questions, or feature requests, please open an issue in the [GitHub issue tracker](../../issues).