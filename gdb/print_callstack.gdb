#gdb -x print_callstack.gdb -p pid
#Way1) Manual. Execute as above on shell. Keep pressing Ctrl+C repeatedly on shell prompt.
# OR
#Way2)send signals to pid repeatedly same number of times on another shell as in below loop
#let count=0; while [ $count -le 100 ]; do kill -INT pid ; sleep 0.10; let $count=$count+1; done
set pagination 0
set $count = 0
while $count < 100
    backtrace
    continue
    set $count = $count + 1
end
detach
quit
