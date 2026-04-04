# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),

---

## [Unreleased]

### Added
- Placeholder for future changes (new features, hardware revisions, etc.)

### Changed

### Fixed

---

## [2.2]

**Initial open-source release of the Arecorder v2.2 PTR edition**  
*Maintained by bartekM*

### Added
- Complete hardware design files:
  - KiCad schematic and PCB layout
  - Ready-to-order Gerber files
  - Full BOM
- Optional H3LIS331 adapter board design (included in the main project)
- Firmware source code with improved calibration routines and SD-card write reliability
- Analysis and calibration tools
- Comprehensive documentation:
  - `README.md` (setup, features, quick start)
  - `FAQ.md`
  - Original 2016 English and Polish manuals (PDF)
  - Assembly guide
- GitHub repository structure and licensing files
- Community links

### Changed
- Sensor support updated from original MMA6519 (±80 g) to MMA6827 (±120 g) as the primary option (drop-in replacement)
- H3LIS331 (±400 g capable) added as a recommended alternative due to better availability and performance
- Firmware ported and optimized from the 2016 closed-source version (better calibration accuracy, fixed SD-card corruption issues when card is not formatted)
- Documentation modernized and expanded for open-source community use
- Double-layer PCB layout preserved (no electrical or mechanical changes from the PTR production boards)

### Historical context (pre-GitHub)
- **2016-07-30** — Original Arecorder v2.2 released by Arkadiusz Palinski (closed source).
- **2020-08-12** — bartekM begins PTR edition development on the Polish Rocketry Society forum.
- **2020–2021** — Firmware improvements, sensor upgrade to MMA6827, flight testing on *Solaris* rocket, workshops, and production of ~50 units.