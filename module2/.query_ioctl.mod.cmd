cmd_/home/cs695/module2/query_ioctl.mod := printf '%s\n'   query_ioctl.o | awk '!x[$$0]++ { print("/home/cs695/module2/"$$0) }' > /home/cs695/module2/query_ioctl.mod
