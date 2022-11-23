# Installing

## System requirements

Only Linux is actively supported at this time.

Exact hardware specs is unknown; the overall footprint is minimal, so even a Raspberry Pi should be able to run it.

## Compiling and installing

TODO

## Database setup

The database setup requires some manual setup, because all the proper databases are non-portable trash that cannot easily be configured.

Spaceport takes care of all table setup on its own. It's the rest that's a problem

### Database choice

Spaceport uses postgresql, because it has the least miserable config, it has functional DB libraries (soci/soci, the only decent MySQL interface for C++, refused to work), and it just worked when I wrote code for it.

That's the entire reasoning. I don't care, it works, it stores data, I was able to set up the database and the code interface, I'm happy. Mostly. Proper databases suck to set up, and that unfortunately affects you, the unfortunate reader who now gets to set this up on your own.

### Packages

At the bare minimum, you need `postgresql` and `postgresql-client`. Compile dependencies are self-managed, so don't worry about that.

If you know what you're doing and know the instructions off the top of your head: make a user with a password, make sure the user can be accessed via a password as any user (because runtime), paste username and password into `/etc/spaceport/spaceport.json`.

The rest of this is written for people like me, who have 0 experience with postgresql, because the learning curve for these databases are worse than the learning curve for Vim. Seriously.

---

First of all, set up a user:
```sh
# Recommended username: spaceport, though not required.
# The account _probably_ shouldn't be a superuser, but /shrug? I don't know. Pick one, if it breaks, pick the other: https://chartio.com/resources/tutorials/how-to-change-a-user-to-superuser-in-postgresql/
sudo -u postgres createuser --interactive
# Second, make a password:
sudo -u postgres psql
# Make it good, don't lose it, copy it into the "password" field in /etc/spaceport/spaceport.json
```

**Note**: all future commands assume the username is spaceport. If you picked something else, it needs to be replaced. Also note that because naming:tm:, the database is also called spaceport, and cannot be changed.
```sql
ALTER USER spaceport WITH PASSWORD 'your password here';
```

Because postgresql, along with all the other databases, are annoying as fuck, you need to make a manual change in `pg_hba.conf`:

```sh
sudo vim /etc/postgresql/14/main/pg_hba.conf
```

`14` may need to be replaced with a different version.

Specifically, the line `local all all peer` needs to be replaced with `local all all scram-sha-256`. Indentation and alignment is irrelevant, you can generally get away with just replacing `peer` with `scram-sha-256` on a line starting with `local all all`.

you should now be able to `psql -U spaceport --password`, write or paste the password, and get access to a promt.

## Config 

TODO
