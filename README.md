# ncurses-clock

Draws a clock in the terminal window using the ncurses library

!["Example window running clock"](./docs/images/example_window.png)

## Setup

```
# Clone this repository
git clone 

# Compile the program using the Makefile
cd ncurses-clock
make all

# Start the clock; can be quit by typing 'Q'
./ncurses-clock
```

## Usage

There are a few alternate usage mode available.

```
Usage: ncurses-clock [options]
  options:
    -12h       Use 12-hour clock mode (default)
    -24h       Use 24-hour clock mode
    -secs=on   Display time including seconds (default)
    -secs=off  Display time without seconds
    -help      Show this help message
```

## License

The code in this repository is licensed under the [MIT License](./LICENSE).