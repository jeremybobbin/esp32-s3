#include <stdint.h>
#include "soc/lldesc.h"

uint32_t lldesc_get_chain_length(lldesc_t *head)
{
	lldesc_t *ds = head;
	uint32_t len = 0;

	while (ds) {
		len += ds->length;
		ds = STAILQ_NEXT(ds, qe);
	}

	return len;
}

void lldesc_config(lldesc_t *ds, uint8_t owner, uint8_t eof, uint8_t sosf, uint16_t len)
{
	ds->owner  = owner;
	ds->eof    = eof;
	ds->sosf   = sosf;
	ds->length = len;
}
