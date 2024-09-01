# luna.sh
Welcome to `luna.sh` 🌙. A shell I am building as I learn C++. Stay tuned!

## Prerequisites:
- This application currently supports only macOS.
- Ensure Conda and Make are installed on your system.

## Setup Instructions:
1. Create the Conda environment from `luna-environment.yml`:
  ```bash
  conda env create -f luna-environment.yml
  ```
2. Activate the Conda environment
  ```bash
  conda activate luna-env
  ```
3. Build `luna.sh`
  ```bash
  make all # or `make`
  ```
4. Execute `luna.sh`
  ```bash
  make luna
  ```
4. Remove build
  ```bash
  make clean
  ```

To run in testing mode:
  ```bash
  make test
  ```
