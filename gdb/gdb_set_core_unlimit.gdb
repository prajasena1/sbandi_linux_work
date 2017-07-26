#set the corelimit of pid to unlimited
#example:
#
#for pid in `ps -ef| grep nmsweb|egrep -v grep|awk '{print $2}'`
#do
#    gdb --batch-silent --command=~/gdb_set_core_unlimit -p $pid
#done
set $rlim = &{0ll, 0ll}
print getrlimit(4, $rlim)
print *$rlim
set *$rlim[0] = -1
print setrlimit(4, $rlim)
detach
quit
