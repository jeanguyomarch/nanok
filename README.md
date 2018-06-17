# NanoK

A kernel for micro-controllers that is so small it is a nano-kernel (hence NanoK).

## Dependencies

Ky consists in bare-metal C sources, and a make-based build system.

You will need an `arm-none-eabi-` toolchain. For instance, you can use
[arm-none-eabi-gcc-7.2.1][1]. Uncompress the archive, and add the `bin/`
directory contained within the archive to your `PATH` environment variable.

You will also need to install [st-link][2]. If it is not available through
your package manager, you will need to install it from the sources:

```bash
git clone https://github.com/texane/stlink.git
make -C stlink release
make -C stlink/build/Release install # as root (e.g. sudo ...)
```


## Build System

NanoK uses its own build system (`nanokbs`). It consits in a simple python
script and a bunch of Jinja2 template files. Nanokbs is called by providing two
positional parameters:

1. a JSON file that describes the NanoK application to be built;
2. a Jinja2 template (that can extend build-in templates), so a build sytem
   can be generated.


### Build tests on a PC (e.g. Linux)

```bash
./nanokbs/nanokbs.py tests/pc/unit.json tests/pc/unit-mk.j2 > Makefile
make check
```


### Build the stm32 proto

```
./nanokbs/nanokbs.py tests/target/disco.json tests/target/proto-mk.j2 > Makefile
make gdb-test-run
# load
# continue
```



[1]: https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/7-2017q4/gcc-arm-none-eabi-7-2017-q4-major-linux.tar.bz2
[2]: https://github.com/texane/stlink
