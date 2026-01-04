# "The Game" – Engine  
A fast, multithreaded C++ engine for simulating the card game **“The Game”**  
(originally created by Steffen Benndorf and published by NSV).

> ⚠️ Disclaimer  
> This project is an **independent simulation engine**.  
> It contains **no original assets, artwork, text, or rulebook excerpts** from the official game.  
> It is not affiliated with or endorsed by NSV or Steffen Benndorf.  
> See the official instructions on [NSV’s website](https://www.nsv.de/wp-content/uploads/2024/04/TheGame_GB.pdf).  

---
## Demo
![Demo](demo.gif)

---

## Purpose

This engine simulates complete rounds of *"The Game"* to analyze:

- win probability  
- average leftover cards  
- the impact of different player counts  
- how well a deterministic strategy performs  
- statistical behavior over thousands of iterations  

It is designed for speed and clarity, using **multithreading** to distribute simulations across all CPU cores.

---

## How It Works

1. The user selects the number of players (1–5).  
2. The user enters the number of simulations (“repetitions”).  
3. The engine simulates an entire play round as many times as entered.
4. Results are aggregated and displayed.

---

## Features

- Supports Windows, Linux and macOS
- Written in C++  
- Multithreaded
- Implements: 
  - Player selection from 1-5
  - ±10 special rule  
  - Prediction of ±10 special rule 
  - Deterministic “best move” strategy 
  - Configurable game/engine rules (include/config.hpp)
- Clean separation of game logic, player logic, and engine logic  
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
_Note: macOS-Gatekeeper might block the execution for security reasons. In this case run `xattr -d com.apple.quarantine ./TGEngine` before executing. Also see [Verify Integrity](https://github.com/luisrslz/TGEngine?tab=readme-ov-file#verify-integrity)._
#### Windows
- In File Explorer, double-click `TGEngine-Windows.exe`
- Run from Console:
```
# PowerShell
.\TGEngine-Windows.exe

# CMD
TGEngine-Windows.exe
```

_Note: Windows SmartScreen may show a warning because this executable is not code-signed or is not yet widely recognized. You can verify the integrity of the download by checking its SHA-256 hash against the value provided in the release file `SHA256SUMS.txt`, or by building the executable yourself from the source code in this repository._

### Verify integrity
```
# Linux / macOS
sha256sum -c SHA256SUMS.txt

# Windows (PowerShell)
Get-FileHash .\TGEngine-Windows.exe -Algorithm SHA256
# Compare the displayed hash with the entry in SHA256SUMS.txt
```

---

## License
This project is licensed under the **MIT** License.  
See the `LICENSE` file for details.
