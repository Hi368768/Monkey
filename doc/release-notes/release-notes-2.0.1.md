Monkey Core v2.0.1 is now available from:

  <https://github.com/MONKEYPROJECT/Monkey/releases>

This is a new major version release, including various bug fixes and
performance improvements, as well as updated translations.

Please report bugs using the issue tracker at github:

  <https://github.com/MONKEYPROJECT/Monkey/issues>

How to Upgrade
==============

If you are running an older version, shut it down. Wait until it has completely shut down (which might take a few minutes for older versions), then run the installer (on Windows) or just copy over /Applications/Monkey-Qt (on Mac) or monkeyd/Monkey-Qt (on Linux).

Compatibility
==============

Monkey Core is extensively tested on multiple operating systems using
the Linux kernel, macOS 10.10+, and Windows 7 and later.

Microsoft ended support for Windows XP on [April 8th, 2014](https://www.microsoft.com/en-us/WindowsForBusiness/end-of-xp-support),
No attempt is made to prevent installing or running the software on Windows XP, you
can still do so at your own risk but be aware that there are known instabilities and issues.
Please do not report issues about Windows XP to the issue tracker.

Monkey Core should also work on most other Unix-like systems but is not
frequently tested on them.

Notable Changes
===============

Random-cookie RPC authentication
---------------------------------

When no `-rpcpassword` is specified, the daemon now uses a special 'cookie'
file for authentication. This file is generated with random content when the
daemon starts, and deleted when it exits. Its contents are used as
authentication token. Read access to this file controls who can access through
RPC. By default it is stored in the data directory but its location can be
overridden with the option `-rpccookiefile`.

This is similar to Tor's CookieAuthentication: see
https://www.torproject.org/docs/tor-manual.html.en

This allows running monkeyd without having to do any manual configuration.


v2.0.1 Change log
=================

- Options messages overhaul
- Added "Reset" function on settings to reset to default values
- Removed coin and net weight from gui / rpc, preparing this for upcoming Masternode release
- Coin control overhaul
- Fixed min fee under options
- Added stake split threshold ( "setstakesplitthreshold X" which defines minimum input size you want to use for staking )
- Added random-cookie RPC authentication
- Fixed wallet unlocking
- General UX improvements and fixes
- Added DNS seeding servers

Credits
=======

Thanks to everyone who directly or indirectly contributed to this release.

