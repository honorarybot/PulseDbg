# PulseDBG

!!! Now moving to !!!
https://pulsedbg.com

Hypervisor-based debugger

What does it consist of:
- Hypervisor part: loaded on a debuggee site
- Client part: client for the debugger
- Transport: maintains communication between debuggee and debugger (which are different machines)

Supported environment:
- Intel Core I* processor
- UEFI capable firmware
- UEFI capable OS: by this I mean it was installed in UEFI mode on GPT partition
- CSM capable firmware: i.e. UEFI that supports Compatibility Support Module for launching legacy bootloaders

Supported transports:
- Internal COM port
- FireWire 1394 controller
- USB 2 Debug Port (with USB 2.0 Debug Cable)
- Intel Network Cards

What's next:
- Checkout project wiki pages
- Check out a video by ApertureSecurity as an example of debugger configuration with VmWare https://www.youtube.com/watch?v=RU09zWsfIa0
- Check out SDK documentation at https://github.com/honorarybot/PulseDbg/wiki/SDK-documentation
