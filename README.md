arch-battery
============

##### battery status utility

author: Andrei Duma (andrei.duma.dorian@gmail.com) (github.com/AndreiDuma)

### usage
    battery {-p, --percent}     # for getting an int in [0, 100] - self explained

or

    battery {-s, --status}      # for getting charging status: "full", "charging", "on battery" or "critical"

or

    battery {-t, --time}        # for getting time left to exhaustion or to complete charging

##### note: tool developed for Fujitsu Esprimo Mobile v6555 under Arch Linux. May work on other systems as well.
