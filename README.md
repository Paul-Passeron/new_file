# New File Utility
Creates .c and .h files automatically

## Installation
```sh
git clone https://github.com/Paul-Passeron/new_file.git
cd new_file
make
sudo make install
cd .. 
rm -rf new_file
```

## Usage:
(In your project directory, containing an include and src folder)
```sh
new_file <name>
```

Creates two new files:
src/<name>.c
include/<name>.h

## Example:

```sh
new_file hello_world
```

include/hello_world.h:
```C
// HELLO_WORLD HEADER FILE
// Paul Passeron

// File created by the new_file tool !

#ifndef HELLO_WORLD_H
#define HELLO_WORLD_H

#endif // HELLO_WORLD_H
```

src/hello_wolrd.c:
```C
// HELLO_WORLD SOURCE FILE
// Paul Passeron

#include "../include/hello_world.h"

// File created by the new_file tool !
```
