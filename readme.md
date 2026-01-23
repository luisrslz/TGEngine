# "The Game" – Engine  
A fast, multithreaded C++ engine for simulating the card game **“The Game”**  
(originally created by Steffen Benndorf and published by NSV).

> ⚠️ Disclaimer  
> This project is an **independent simulation engine**.  
> It contains **no original assets, artwork, text, or rulebook excerpts** from the official game.  
> It is not affiliated with or endorsed by NSV or Steffen Benndorf.  
> See the official instructions on [NSV’s website](https://www.nsv.de/wp-content/uploads/2024/04/TheGame_GB.pdf).
---
## Results
_You don't need to run the program yourself._   
The chances of winning "THE GAME" are:   

**1 Player**:  ~ 3.69%   
**2 Players**: ~ 10.78%   
**3 Players**: ~ 4.41%   
**4 Players**: ~ 7.11%   
**5 Players**: ~ 8.26%

> Percentages with the current [algorithm](https://github.com/luisrslz/TGEngine?tab=readme-ov-file#features). The algorithm lacks many things real players are capable of, therefore the real percentages should be higher. 

---
## Demo
![Demo](demo.gif)

---

## Purpose

This engine simulates complete rounds of *"The Game"* to analyze:

- Win probability  
- Average leftover cards  
- How many rounds each game takes on average 
- How often the special rule occurs
- Statistical behavior over millions of iterations  
- The impact of different player counts  

It uses **multithreading** to make the simulations as fast as possible.

---

## Features  
- Player selection from 1-5
- ±10 special rule _("backwards trick")_ is respected, predicted and prioritized
- Decides if a player should make more moves than he has to 
- _[2 Players only]_ Decides if a player should tell the other player to _not_ play on a specific pile
- Millions of simulations in a short amount of time
- Command‑line interface  

---

## Run
Download the suitable executable for your OS in [Releases](https://github.com/luisrslz/TGEngine/releases).

#### Linux / macOS
###### Open your `Downloads` folder in any terminal and run:
```
# Make sure the file is executable
chmod +x ./TGEngine-<OS>

# Execute
./TGEngine
```
_Note: macOS-Gatekeeper might block the execution for security reasons. In this case run `xattr -d com.apple.quarantine ./TGEngine` before executing. Alternatively you can always build the program yourself with the provided source code._
#### Windows
- In File Explorer, double-click `TGEngine-Windows.exe`
- Run from Console:
```
# PowerShell
.\TGEngine-Windows.exe

# CMD
TGEngine-Windows.exe
```

_Note: Windows SmartScreen may show a warning or Windows Defender may falsely detect a virus because this executable is not code-signed or is not yet widely recognized. You can verify the integrity of the download by checking its SHA-256 hash against the value provided in the release file `SHA256SUMS.txt`, or by building the executable yourself from the source code in this repository._

### Build Manually
- Requirements: C++20, CMake
- Download the source code from the newest [Release](https://github.com/luisrslz/TGEngine/releases) or clone the repo.
```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release 
cmake --build build
./TGEngine # .\TGEngine on Windows
```

---

## License
This project is licensed under the **MIT** License.  
See the `LICENSE` file for details.
