# Arecorder - Open Source Flight Data Recorder

**Version:** v2.2 (PTR edition)  
**Maintained by:** bartekM  

A compact, high-g flight data recorder designed specifically for model and amateur rocketry. The Arecorder logs 3-axis acceleration and orientation data to an SD card during launch, ascent, apogee, and recovery. Developed and used by the **Polskie Towarzystwo Rakietowe (PTR)** – the Polish Rocketry Society.

This repository contains all **design files** needed to build your own Arecorder: KiCad schematics & PCB layout, Gerber files, Bill of Materials (BOM), assembly notes, and firmware source code.

- **Original forum thread** (Polish/English discussion): [forum.rakiety.org.pl/viewtopic.php?t=3039](https://forum.rakiety.org.pl/viewtopic.php?t=3039)
- **PTR Discord** (support & community)

---

## Features

- High-range 3-axis accelerometer:
  - Primary: **MMA6827** (±120 g)
  - Alternative: **H3LIS331** (with adapter board, higher availability and better specs)
- On-board SD card slot for raw flight data logging
- Improved firmware with better calibration accuracy and write reliability
- Compact design suitable for most model rockets (fits standard payload bays)
- Easy post-flight analysis (data saved in simple format)
- Open-source hardware & firmware – build it yourself or modify it

---


---

## Quick Start

1. **Order PCBs** – use the Gerbers in `hardware/gerbers/` (any PCB manufacturer, e.g. JLCPCB, PCBWay).
2. **Buy components** – see `hardware/BOM.csv`.
3. **Assemble** – most soldering can be done by hand; complex parts can be outsourced.
4. **Flash firmware** – use MPLAB X IDE + PIC debugger.
5. **Format SD card** (FAT32) before first use.
6. **Calibrate** the accelerometer (detailed in the manual).
7. **Fly** – insert into rocket, power on, launch, retrieve data after flight.

Full assembly and usage instructions are in the original manual and `docs/assembly-guide.md`.

---

## Hardware Notes (v2.2 PTR)

- Double-layer PCB (no changes planned for this revision)
- Sensor upgrade from original MMA6519 (80 g) to MMA6827 (120 g)
- Optional H3LIS331 adapter board included in the design files

---

## License

- **Hardware designs** – [CERN Open Hardware Licence Version 2 – Strongly Reciprocal](LICENSE_hardware)  
- **Firmware & software** – [MIT LICENSE](LICENSE)
- **Documentation** – CC-BY-SA 4.0

See [LICENSE](LICENSE) file for details.

---

## Contributing

Pull requests are welcome! Whether it's:
- Bug fixes
- New features
- Better documentation
- Improved firmware

Just open an issue or PR. You can also support development via [Buy Me a Coffee](https://www.buymeacoffee.com/bartekM).

---

## Contact

- Maintainer: **bartekM** (GitHub @bartekM or PM on PTR forum/Discord)
- Community: PTR Discord server

---

**Happy flying and safe recoveries!** 🚀
