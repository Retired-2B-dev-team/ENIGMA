[![GitHub stars](https://img.shields.io/github/stars/JENOT-ANT/ENIGMA?style=for-the-badge)](https://github.com/JENOT-ANT/ENIGMA/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/JENOT-ANT/ENIGMA?style=for-the-badge)](https://github.com/JENOT-ANT/ENIGMA/network)

| `status`         | `maintained` | `maintainers` | `version`      | `next-release-deadline` | `website`                                     |
| :--------------: | :----------: | :-----------: | :------------: | :---------------------: | :-------------------------------------------: |
| work-in-progress | not realy    | 6             |  v1-beta.1.0   | <hr>                    | https://retired-2b-dev-team.github.io/ENIGMA/ |

[![GitHub license](https://img.shields.io/github/license/JENOT-ANT/ENIGMA?style=for-the-badge)](https://github.com/JENOT-ANT/ENIGMA/blob/main/LICENSE)
[![GitHub issues](https://img.shields.io/github/issues/JENOT-ANT/ENIGMA?style=for-the-badge)](https://github.com/JENOT-ANT/ENIGMA/issues)

# ENIGMA

## Description:
This is **a simulation of the ENIGMA encryption machine**.

## [Official website](https://retired-2b-dev-team.github.io/ENIGMA/)
## Download:
You can easly download files from `Releases` tab (you need only one sorce code pack, probably with .zip if your platform is Windows):
To work properly, you should:
  1. Extract archive.
  2. Put the executable file in the folder `*your-extarction-path*/ENIGMA-*version*/ENIGMA-*version*` (near files like help.info, setings.txt and enigma-app.cpp).
  3. Alternatively you can just build the executable file by yourself just compiling enigma-app.cpp and putting executable into the same directory as the source.
  
  > GUI app can be fund in 'GUI' directory, to use it, run .py file (you need to have compiled c++ core code first to use the python GUI wrapper)
  > Current version supports CMD usage, so to run program you should fire up the terminal in folder with executable file and run program as command with correct parameters (you can run `enigma -h` for help or just read help.info)
  
  
  **REMEMBER!** THIS IS **PRE-RELEASE** VERSION! It's **not** tested well, **nor** it has a good error handling. Use it **wisely** and take **responsibility** of what you are doing!
  If you are not sure, **just wait** for a more stable release or ask in the **Discussion** tab.

## Attributions:
  - [Browser Enigma emulator](https://piotte13.github.io/enigma-cipher/)
    > Huge thanks for providing a great source that: helped to understand how the mechanism of the Enigma works inside, and made possible to test and find bugs inside our code.
  ***
  - [Rotors specifications](https://en.wikipedia.org/wiki/Enigma_rotor_details)
  - [Polish article about Enigma](https://pl.wikipedia.org/wiki/Enigma)
  - [English article about Enigma](https://en.wikipedia.org/wiki/Enigma_machine)
    > We also appreciate Wikipedia articles about Enigma, that provided detailed, technical info about machine construction.

## Requirements:
  - `C++ compiler` (If You prefer to buld the program from source on your own, what is recomended actually)
  - `Python v3.9.0 or higher` (to run the GUI app, optionally).

## Example:
- ALPHABET:

    Letter indexes:
    ```
      0. 1. 2. 3. 4.
     [A, B, C, D, F]
    ```

- MACHINE'S FRAGMENT:
```
Disk index:              0.     1.     2.
                         |      |      |
--------   /  0.   [0]->[3]-   [0]    [4]
|Letter|  |   1.    ^   [0] \  [4]    [1]
|index | <    2.    ^   [1]  \ [3] /--[3] => (D)
--------  |   3.    ^   [4]   -[2]/   [0]
           \  4.    ^   [2]    [1]    [2]
                    ^    |      |      |
     (A) => input->>^    |      |      |
                        Disks represented
                           by 1D arrays
                          (connections)
```
