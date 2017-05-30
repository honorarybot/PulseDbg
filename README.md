# PulseDBG
Hypervisor-based debugger

What is this:
This is a first super early alpha release. So, there are some limitations in current implementation:
- Read-only mode: no memory writes, no context setting
- Visible breakpoints: breakpoint patches are visible to the debuggee
- Unprotected transport: transport controller is visible from the guest (protection will only apply for the external cards)
- Not too optimized: it's about architecture, the compiler optimizations are on (Maximize speed) and verified for correctness

What's next:
- Checkout project wiki pages
