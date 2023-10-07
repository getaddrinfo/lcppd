# lcppd

A LCPDFR-like mod written in C++, using [Zolika's C++ IV SDK](https://github.com/Zolika1351/iv-sdk) (big thank you to them). Currently very very work-in-progress.

## Notice

All c++ (.cpp) files are included into `dllmain.cpp` as this is then built as a single dynamic library. This is the most stable (and simplest) way I could find to build it.

Mostly using `Native Script` methods, as their methods are generally more usable than classes such as `CVehicle`.

## License

MIT