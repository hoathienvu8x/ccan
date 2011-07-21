#ifndef CCANLINT_LICENSES_H
#define CCANLINT_LICENSES_H
#include <stdbool.h>

enum license {
	LICENSE_LGPLv2_PLUS,
	LICENSE_LGPLv2,
	LICENSE_LGPLv3,
	LICENSE_LGPL,
	LICENSE_GPLv2_PLUS,
	LICENSE_GPLv2,
	LICENSE_GPLv3,
	LICENSE_GPL,
	LICENSE_BSD,
	LICENSE_MIT,
	LICENSE_PUBLIC_DOMAIN,
	LICENSE_UNKNOWN
};

#define NUM_CLAUSES 3

struct license_info {
	const char *name;
	const char *shortname;
	/* Edit distance is expensive, and this works quite well. */
	const char *clause[NUM_CLAUSES];
};

extern const struct license_info licenses[];

struct ccan_file;
bool find_boilerplate(struct ccan_file *f, enum license license);

#endif /* CCANLINT_LICENSES_H */