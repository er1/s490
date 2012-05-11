
#   Copyright 2012 Corey Clayton, Eric Chan, Mathieu Dumais-Savard

#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at

#       http://www.apache.org/licenses/LICENSE-2.0

#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.


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
