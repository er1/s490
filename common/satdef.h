#ifndef SAT_DEF_H
#define SAT_DEF_H

#define GROUND_CALLSIGN        ("VE2ECQ-1")
#define SAT_CALLSIGN           ("VA2HAX-1")

#ifdef  USE_AX25
#define SAT_PROTO              (PF_AX25)
#define SAT_PROTO_T            (SOCK_SEQPACKET)
#else   
#define SAT_PROTO              (AF_INET)
#define SAT_PROTO_T            (SOCK_DGRAM)
#endif

#endif
