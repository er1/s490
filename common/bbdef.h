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

#ifndef BBDEF_H
#define	BBDEF_H

#define BB_SOCK_PATH           ("/tmp/blackboard.sock")

#define BO_GEN_NULL             (0)
#define BO_GEN_PING             (1)
#define BO_GEN_PONG             (2)
#define BO_GEN_ACK              (6)
#define BO_GEN_NAK              (19)
#define BO_GEN_HUP              (4)
#define BO_GEN_ECHO             (32)


///////////////////////////////
/// Control Shell Interface ///
///////////////////////////////

//opcodes -- requests from client (CS to BB)
#define BO_CS_SUBSCRIBE_TO      (64)
#define BO_CS_GET_RECENT        (66)

//opcodes -- responses to client (BB to CS)
#define BO_CS_UPDATE            (96)
#define BO_CS_RECENT               (97)
////////////////////////////////
// Knowledge Source Interface //
////////////////////////////////

//opcodes -- KS to BB
#define BO_KS_SUBSCRIBE_AS      (128)
#define BO_KS_UPDATE            (129)

//opcodes -- BB to KS
#define BO_KS_SUBSCRIPTION_SUCCESS      (130)
#define BO_KS_SUBSCRIPTION_FAILED       (131)

#define BO_KS_UPDATE_SUCCESS    (132)
#define BO_KS_UPDATE_FAILED     (133)

// gen

#define BO_DEBUG_DUMP_KISET     (65537)

#endif	/* BBDEF_H */

