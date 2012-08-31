#!/usr/bin/lua

user = "dramaqueen"
group = "dramaqueen"
sslCert = "/home/roa/programming/examples/ssl_conn/ssl_example/servercert.pem"
sslKey = "/home/roa/programming/examples/ssl_conn/ssl_example/private.key"
xmppUser = "zabbix@localhost"
xmppPasswd = "test123"
bind = "localhost:9898"
xmpp = "1"
daemonDir = "/var/lib/dramaqueen/daemon/"
scriptDir = "/var/lib/dramaqueen/script/"
logDest  = "/var/log/dramaqueen/drama.log"
foreignHosts = { "localhost:9897", "localhost:9898", "playground.vm.over9000.org:9898" }
