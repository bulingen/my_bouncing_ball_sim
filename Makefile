.PHONY: help setup build run clean

help:
	@echo "Available commands:"
	@echo "  make setup   - Initial setup: create build directory and configure CMake"
	@echo "  make build   - Build the simulator"
	@echo "  make run     - Run the simulator"
	@echo "  make clean   - Remove build directory"

setup:
	@echo "Setting up build environment..."
	@mkdir -p build
	@cd build && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
	@echo "Setup complete! Run 'make build' to compile."

build:
	@echo "Building simulator..."
	@cd build && make
	@echo "Build complete! Run 'make run' to start."

run:
	@cd build && ./bouncing_ball

clean:
	@echo "Cleaning build directory..."
	@rm -rf build
	@echo "Clean complete!"
