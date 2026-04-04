# FAQ

### What is the Arecorder?
The Arecorder is a flight data recorder (accelerometer logger) built for amateur and model rocketry. It records 3-axis acceleration (up to 120 g) and orientation data to an SD card so you can analyze rocket performance, stability, motor burn, parachute deployment, and more after the flight.

### Is this the same device sold by PTR?
Yes – this repository contains the exact design files for the **Arecorder v2.2 PTR edition** that was produced and used by Polskie Towarzystwo Rakietowe. The project is now fully open-source.

### What sensors does it use?
- Default: **MMA6827** (±120 g)
- Alternative: **H3LIS331** (adapter board is included in the design files – recommended if MMA6827 is hard to source)

### Why was the sensor changed?
The original MMA6519 (80 g) became unavailable due to global component shortages. The MMA6827 (120 g) was chosen as a drop-in replacement with only a small reduction in resolution.

### Do I need to format the SD card?
**Yes.** Always format the card (FAT32) before flight. Unformatted or previously used cards can cause file corruption. This was a known issue that is now well-documented.

### How do I calibrate the accelerometer?
Calibration is **not** described in the official manual and is not recomended for normal users.  
It requires the **Areconfig_rebuild** software (included in the `software/Areconfig_rebuild/` folder of this repository) that is a newer, rebuilt version of the original Areconfig tool.

### What kind of rockets is it suitable for?
Any model rocket that can accommodate a small payload bay. It has been successfully flown on **(!) many (!)** PTR rockets such as *Solaris*, *Carbonara*, *Bigos* and used at multiple launches and workshops.

### Can I modify the design?
Absolutely! The whole point of open-sourcing it is to let the community improve it. Feel free to create forks, add new sensors, change the form factor, etc.

### Is there firmware source code?
Yes – fully included in the `firmware/` folder. It is Arduino-compatible and easy to modify.

### Where can I get help or discuss the project?
- GitHub Issues / Discussions (preferred for technical questions)
- PTR Discord server
- Original forum thread: https://forum.rakiety.org.pl/viewtopic.php?t=3039

### Will there be a next version (v3)?
A major redesign (4-layer PCB, new sensors, mechanical improvements) is planned once v2.2 production and community feedback are complete. This repo will be updated when that happens.

### How can I support the project?
- Build one and share your flight data
- Contribute improvements via GitHub
- Buy the maintainer a coffee: https://www.buymeacoffee.com/bartekM

---

**Still have questions?** Open a GitHub issue or join the PTR Discord – the community is friendly and helpful.