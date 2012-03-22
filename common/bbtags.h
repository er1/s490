#ifndef BBTAGS_H
#define	BBTAGS_H

#include <stdint.h>

typedef uint32_t bbtag;

#define BBTAG_TESTREAD ((bbtag)3331)
#define POWER_VOLTAGE_BATTERIES_TAG ((bbtag)1)
#define POWER_CURRENT_TAG ((bbtag)2)
#define POWER_VOLTAGE_PANELS_TAG ((bbtag)3)

#endif	/* BBTAGS_H */

