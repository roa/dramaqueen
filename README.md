dramaqueen
==========

# installation

dependencies:
	openssl>=1.0.0
	lua>=5.1
	gloox>=1.0

clone repo:
	git clone git://github.com/roa/dramaqueen.git

then compile:
	make

that was easy, wasn't it?

if you are on gentoo, you can use the ebuild provided with the source.

# main configuration

the main config file is specified with the -c switch
	dramaqueen -c /path/to/config/init.lua

you can name the main config as you wish. a full commented example
can be found in ./ebuild/net-analyzer/dramaqueen/files/init.lua


# daemon configuration

you might want to use daemons as well
daemons have their own config files, which 
are located in the daemonDir specified in the main config file.    

a typical config file looks like this. a detailed explaination
for config files can be found in Daemon.hpp headerfile.

	#!/usr/bin/lua

    checkTime = 1
    script    = "script.lua"
    recipients = { "roa@localhost" }
    hosts = { "localhost:9898" }

# How to use it

you need to install at least one dramaqueen node with
enabled xmpp flag. then you can use the xmpp interface
to give commands to all other node or you can install
daemons to get regularly updates from your nodes.
As you are expected to create your own openssl certs,
you must distribute them on all nodes.

# How to contribute

fork!
