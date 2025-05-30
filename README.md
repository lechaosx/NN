# TinyNN

TinyNN is a simple work-in-progress neural network implementation in C++ and its integration with Godot engine. It provides example tools for training, testing, and experimenting with neural networks, with support for MNIST data and Godot-based UI components.

## Features

- **C++ Core Library**: Implements core neural network functionality using `Eigen`.
- **C++ Utility**: Contains tool for training a simple neural network on MNIST dataset.
- **Godot Integration**: Integrates the core library as a `gdscript` Node in Godot engine.
- **Godot Project**: Provides UI for experimenting with classification of MNIST dataset.
- **Python Utilities**: Includes Python scripts for data preprocessing and additional neural network implementations using `numpy` and `pytorch`.

## Project Structure

- **`libnn/`**: Core neural network implementation in C++.
- **`python/`**: Python scripts for neural network experiments and data handling.
- **`godot/`**: Godot project files for UI and visualization.
- **`tools/`**: Additional tools and utilities, including a main executable.
- **`gdextension/`**: Godot C++ extensions for neural network integration.

## Dependencies

Project dependencies are managed via [Nix](https://nixos.org/) package manager.
This will drop you into a shell with all required dependencies available:

```
nix develop
```

Alternatively, you can provide the dependencies via your favourite approach and hope for the best. 
See [flake.nix](flake.nix) for a list of packages used to develop this.

## Compilation

```
cmake --preset default
cmake --build build
```

## Examples
### Train

The [tools](tools) folder contains a tool for training neural network with simple fixed architecture working on MNIST dataset. It can be used as follows:

```
./train <path-to-train-inputs> <path-to-train-labels> <path-to-test-inputs> <path-to-test-labels>
```

Where the inputs and labels are provided by the MNIST datasets.
The tool creates file `output.json` with the training weights and biases.

### Godot

The [gdextension](gdextension) folder contains integration of `libnn` with the Godot engine.

The [godot](godot) folder contains a simple Godot project with interactive drawing-like application that can use trained weights and biases (`output.json`) for interactive numeral classification.