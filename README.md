# sufa – A Minimal Shell Implemented in C++

```
  ______
  L,.   ',
   \      ',_
    \   @   ',
     \ ^~^    ',
      \    NR   ',
       \___'98fw  ',_                          _..----.._
       [______       "'==.I\_____________..--"<__\\_n@___4\,_
     ,..-=T         __   ____________          \/  "'" O<==  ""-+.._
     I____|_____    }_>=========I>=**""''==-------------==-   " |   "'-.,___
     [_____,.--'"             _______         ""--=<""-----=====+==--''""
     ""'-=+..,,__,-----,_____|       |         -=* |
                 |__   /     |---,--'"---+------+-'"
                    """     d"b="        '-----+t
                            q_p                '@
```

---

## Name

**sufa** (Hebrew: "סופה") is the name of the Israeli variant of the F-16 fighter aircraft (F-16I *Sufa*).
This name is chosen to represent a fast, and capable shell—compact yet powerful, much like the aircraft.

---

## Overview

**sufa** is a small, modular, and educational shell implemented in modern C++.
It provides a command loop, support for internal C++ built-ins, and POSIX-compatible external command execution through `fork` and `execvp`.

The project aims to be:

* Clear and easy to understand
* Suitable for learning Unix shell internals
* A minimal base for experimentation or extension

---

## Build Instructions

### Requirements

* CMake ≥ 4
* A C++17-capable compiler
* Standard POSIX environment

### Build Procedure

```bash
git clone https://github.com/IdanKoblik/sufa
cd sufa
mkdir build
cd build
cmake ..
make
```

The compiled `sufa` binary will appear in the build directory.

---

## Usage

Start the shell:

```bash
./sufa
```

Example prompt:

```
sufa>
```

### External Commands

Any executable available in your `PATH` can be invoked:

```
sufa> ls -l
sufa> echo hello
sufa> pwd
```

### Exit

```
sufa> exit
```

---

## Adding Built-ins

To define a new built-in command:

1. Add a new `.cpp` and `.h` file under `cmd/`.

2. Implement a function with the signature:

   ```cpp
   int builtin_name(const std::vector<std::string>& args);
   ```

3. Register the built-in in the shell’s dispatch table (typically in `main.cpp`).

This model keeps the code organized and modular.
