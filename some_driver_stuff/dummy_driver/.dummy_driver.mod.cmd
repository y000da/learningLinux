savedcmd_dummy_driver.mod := printf '%s\n'   dummy_driver.o | awk '!x[$$0]++ { print("./"$$0) }' > dummy_driver.mod
