@numKSSET = (1, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100, 120, 140, 160, 180, 200, 250, 300, 350, 400, 500);
@numCSSET = (1, 3, 5, 10);
@delaySET = (1000);

for $delay (@delaySET) {
	for $numKS (@numKSSET) {
		for $numCS (@numCSSET) {
			print "$numKS	x KS	$numCS	x CS	$delay	ms update interval\n";

			system "../Blackboard/blackboard &";# > data_$numKS"."_$numCS"."_$delay &";
			sleep 1;

			for $tag (1..$numKS) {
				system "./slamKS $tag $delay &> /dev/null &";
				for (1..$numCS) {
					system "./slamCS $tag &> /dev/null &";
				}
			}

			system "{ echo -n $delay $numKS $numCS ' ' ; ./ckload; } >> data_log.txt";

			system "killall slamKS";
			system "killall slamCS";
			system "killall blackboard";
		}
	}
}
