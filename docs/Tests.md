# Running tests

**Note:** I do not recommend manually running tests. They require access to a database, and will eat anything that conflicts with test dependencies or tables. It needs a user called `spaceport-test` that can log in without a password, into a database by the same name. This has security implications if the database config is set up incorrectly. Due to the nature of Spaceport, it's exposed outside the device. This can open an attack vector in improperly configured databases.

Postgresql is extremely unfriendly from a consumer test POV, by not offering an (easily discoverable) way to automate testing.

Tests are generated into build/bin/tests. The tests themselves are automated even though the database setup is not. I strongly recommend looking at the GitHub Action to see the general exact command flow, as this won't be documented here.

As an aside, if you know of a better way to automate this testing, consider creating a pull request. I have 0 experience with postgresql or other large-scale databases (except mongodb, but even that automation was a pain in the ass, and it was brief at best), and the whole lot appear to be equally unfriendly for this type of use.


