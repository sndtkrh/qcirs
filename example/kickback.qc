-- phase kick back trick

define @qc 4
add @qc X{3}
add @qc H{0} (x) H{1} (x) H{2} (x) H{3}
measure @qc {0,1,2}
print @qc
