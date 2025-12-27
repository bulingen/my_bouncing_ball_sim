# Bouncing Ball Simulator

A simple Stonefish simulator demonstrating a ball in the ocean.

## Prerequisites

Install Stonefish as described in the [official documentation](https://stonefish.readthedocs.io/en/latest/install.html).

## Quick Start

```bash
make setup    # First time only
make build    # Compile the simulator
make run      # Run the simulator
```

Run `make` without arguments to see all available commands.

## Controls

- `w s a d z x` - Move viewport
- Mouse left button - Select objects
- Mouse right button - Rotate viewport
- Mouse middle button - Move rotation center
- `h` - Show/hide GUI
- `c` - Show/hide console
- `k` - Show keymap

## TODO
Making it turn would be nice
Maybe set forward thrust with another button
And steer up/down with the arrow keys.
Make it a bit narrower

Then if that works, I could drive it around in the water, really nice
Maybe follow it with the camera automatically?

And if that works I could try reading out some sensors?

Hmm. Should I continue with that? Sensors?
Or just move on? I think I'll just move on anyway?
Read up on the ros2 package