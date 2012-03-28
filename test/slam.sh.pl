$prg = shift;
$num = shift;
$delay = shift;

print "$prg $_ $delay &\n" for 1000000..(1000000+$num);
