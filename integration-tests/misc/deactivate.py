#!/usr/bin/python3

# requirements: something to activate, e.g. LUKS and LVM


from storage import *
from storageitu import *


set_logger(get_logfile_logger())


environment = Environment(False)

storage = Storage(environment)

status = storage.deactivate_v2()

print("multipath:", status.multipath())
print("dm-raid:", status.dm_raid())
print("md:", status.md())
print("lvm-lv:", status.lvm_lv())
print("luks:", status.luks())
print("bitlocker:", status.bitlocker())

