# Model

A multi-device architecture is fundamentally tricky.

For security, none of my servers, but especially the server exposed to the internet, has access to any SSH keys. This would massively weaken the integrity of my internal security of the first layer is breached, as every other device (well, one other device, I don't have that many servers ~~yet~~) could be trivially breached. In other words, servers do not have the keys to access each other.

This, however, is a bit of a problem from a data acquisition POV. The consequence is that the root node can't access the other devices for data. Not that it matters; any commands accessing system-level information would necessitate root SSH, and that shit is a highway to privilege escalation. 

I would like to note for the record that I'm assuming a scenario where the public-facing services are breached and Spaceport is used to escalate privileges. To reiterate, Starport is not designed to deal with traffic from the public internet. I do not use it that way, nor do I have the technical expertise to enable that securely and efficiently. Don't expose Starport to the public internet.

Back to the point, however... this requires a special model to deal with data acquisition and, eventually, command distribution.

## Data and command management

Command distribution, if added, is done entirely async. This does prevent immediate command execution, but it enables it without needing ssh keys. Critically, this is supported via the stock client and a workflow that's eventually going to be documented for fully custom implementations. However, truly arbitrary command execution similar to what Ansible has will not be supported, because I'm paranoid. Instead, clients declare their supported commands. Command execution is handled by a name (treated as an ID) only. This does make the approach less flexible, but it covers the majority of use-cases; updates or other non-scheduled restart automation, and reduces the damage if the hub is breached.

Admittedly, this system does come with some more overhead for individual devices. They're responsible for their own config and runners. However, for certain services with already public-facing systems, this may be a non-issue, particularly if an API is provided. Client -> server API is the main approach I'll be using on my network, but server -> client API is going to be supported out of necessity.

Admittedly, this is based on a whole bunch of guesswork and hypotheticals. I have zero experience with these applications, soooooooo...

**TL;DR:** client -> server uploads data, server -> api requires server config.

## Scheduled events

For timed automation, use crontab or similar. There are far more and better established tools that cover what's needed, and where the config is easily bundled with most dotfile repos or other bundle repos depending on the application.

Non-recurring events can use at, atq, atrm, or one of the many other alternatives.

