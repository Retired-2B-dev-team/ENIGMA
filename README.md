[![GitHub stars](https://img.shields.io/github/stars/JENOT-ANT/ENIGMA?style=for-the-badge)](https://github.com/JENOT-ANT/ENIGMA/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/JENOT-ANT/ENIGMA?style=for-the-badge)](https://github.com/JENOT-ANT/ENIGMA/network)

| `status`         | `maintained` | `maintainers` | `version` | `next-release-deadline` |
| :--------------: | :----------: | :-----------: | :-------: | :---------------------: |
| work-in-progress | yes          | 6             |  0.0.0    | 01-September-2022       |

[![GitHub license](https://img.shields.io/github/license/JENOT-ANT/ENIGMA?style=for-the-badge)](https://github.com/JENOT-ANT/ENIGMA/blob/main/LICENSE)
[![GitHub issues](https://img.shields.io/github/issues/JENOT-ANT/ENIGMA?style=for-the-badge)](https://github.com/JENOT-ANT/ENIGMA/issues)

# ENIGMA

## Description:
This project is going to become **a simulation of the ENIGMA encryption machine** maybe.

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
## Contents:
- *[/libraries/](/libraries)* -> project's libraries folder
- *[/enigma-vm.cpp](/enigma-vm.cpp)* -> main project file
