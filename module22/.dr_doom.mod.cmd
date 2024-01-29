cmd_/home/cs695/module22/dr_doom.mod := printf '%s\n'   dr_doom.o | awk '!x[$$0]++ { print("/home/cs695/module22/"$$0) }' > /home/cs695/module22/dr_doom.mod
