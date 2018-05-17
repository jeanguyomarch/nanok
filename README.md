# ky

Nanokernel for micro-controllers.

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


[1]: https://armkeil.blob.core.windows.net/developer/Files/downloads/gnu-rm/7-2017q4/gcc-arm-none-eabi-7-2017-q4-major-linux.tar.bz2
[2]: https://github.com/texane/stlink
