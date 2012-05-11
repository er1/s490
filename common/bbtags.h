/*
   Copyright 2012 Corey Clayton, Eric Chan, Mathieu Dumais-Savard

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef BBTAGS_H
#define	BBTAGS_H

#include <stdint.h>

typedef uint32_t bbtag;

#define BBTAG_TESTREAD ((bbtag)3331)
#define BBTAG_SIMPLETIME ((bbtag)1200)
#define BBTAG_DEMO10BOOL ((bbtag)1210)

#define POWER_VOLTAGE_BATTERIES_TAG ((bbtag)1)
#define POWER_CURRENT_TAG ((bbtag)2)
#define POWER_VOLTAGE_PANELS_TAG ((bbtag)3)

#endif	/* BBTAGS_H */

