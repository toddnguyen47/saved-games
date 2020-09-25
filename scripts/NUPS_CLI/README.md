# NUPS CLI

Command Line Interface (CLI) version of Nintenlord's NUPS patcher.

# How to Build

Run `build_release.bat` on Windows.

# Sample Usage

- Find the `NupsCli.exe` file in `release/win32` folder. Run it with a terminal.

```
NupsCli.exe --gba <path_to_gba_file> --ups <path_to_ups_file>
```

- You can also optionally supply an `--output` argument to have the file renamed to whatever you want.
- If you need help, type `NupsCli.exe --help`

# References

Ref for new & delete pairs: https://stackoverflow.com/a/4255641/6323360

```
malloc / free, new / delete, new[] / delete[]
```
