# Bouncing Ball Simulator

A simple Stonefish simulator demonstrating a bouncing ball on a flat surface.

## Prerequisites

Install Stonefish as described in the [official documentation](https://stonefish.readthedocs.io/en/latest/install.html).

## Building

```bash
mkdir build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
make
```

**Note:** The `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON` flag generates a `compile_commands.json` file for VS Code IntelliSense. The `.vscode/c_cpp_properties.json` file is already configured to use it.

## Running

```bash
cd build
./bouncing_ball
```

## Controls

- `w s a d z x` - Move viewport
- Mouse left button - Select objects
- Mouse right button - Rotate viewport
- Mouse middle button - Move rotation center
- `h` - Show/hide GUI
- `c` - Show/hide console
- `k` - Show keymap
