define showFixes
  set $i= headMeterFix
  set $n = 0
  while ($i != 0)
    set $p = $i->resolved_list
    set $x = $i->resolved_cnt
    set $j = 0 
    printf "%08x [%d] = {", $i, $x
    printf "%3d [%3d] %08x->%08x (D/R): %3d/%-3d - %3d/%-3d {", $n, $i, $x, $i->fix, $i->depend_cnt, dynArySizeDepList($i->depend_list), $i->resolved_cnt, dynArySizeDepList($i->resolved_list)
    while ($j < $x)
       printf " %08x", $p[$j]
       set $j=$j+1
    end
    printf " }\n"
    set $i = $i->next
    set $n = $n+1
  end
end
