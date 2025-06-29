#include <stdint.h>
//#include "sys/queue.h"

#define LLDESC_TX_MBLK_SIZE                 268 /* */
#define LLDESC_RX_SMBLK_SIZE                64  /* small block size, for small mgmt frame */
#define LLDESC_RX_MBLK_SIZE                 524 /* rx is large sinec we want to contain mgmt frame in one block*/
#define LLDESC_RX_AMPDU_ENTRY_MBLK_SIZE    64  /* it is a small buffer which is a cycle link*/
#define LLDESC_RX_AMPDU_LEN_MBLK_SIZE      256 /*for ampdu entry*/
#ifdef ESP_MAC_5
#define LLDESC_TX_MBLK_NUM                  116  /* 64K / 256 */
#define LLDESC_RX_MBLK_NUM                  82 /* 64K / 512 MAX 172*/
#define LLDESC_RX_AMPDU_ENTRY_MBLK_NUM     4
#define LLDESC_RX_AMPDU_LEN_MLBK_NUM       12
#else
#ifdef SBUF_RXTX
#define LLDESC_TX_MBLK_NUM_MAX    (2 * 48) /* 23K / 260 - 8 */
#define LLDESC_RX_MBLK_NUM_MAX    (2 * 48) /* 23K / 524 */
#define LLDESC_TX_MBLK_NUM_MIN    (2 * 16) /* 23K / 260 - 8 */
#define LLDESC_RX_MBLK_NUM_MIN    (2 * 16) /* 23K / 524 */
#endif
#define LLDESC_TX_MBLK_NUM      10      //(2 * 32) /* 23K / 260 - 8 */

#ifdef IEEE80211_RX_AMPDU
#define LLDESC_RX_MBLK_NUM      30
#else
#define LLDESC_RX_MBLK_NUM      10
#endif /*IEEE80211_RX_AMPDU*/

#define LLDESC_RX_AMPDU_ENTRY_MBLK_NUM  4
#define LLDESC_RX_AMPDU_LEN_MLBK_NUM    8

#define	STAILQ_NEXT(elm, field)	((elm)->field.stqe_next)

#endif /* !ESP_MAC_5 */
#define	STAILQ_FIRST(head)	((head)->stqh_first)

#define	STAILQ_HEAD(name, type)						\
struct name {								\
	struct type *stqh_first;/* first element */			\
	struct type **stqh_last;/* addr of last next element */		\
}

#define	STAILQ_ENTRY(type)						\
struct {								\
	struct type *stqe_next;	/* next element */			\
}

#define	STAILQ_INSERT_TAIL(head, elm, field) do {			\
	STAILQ_NEXT((elm), field) = NULL;				\
	*(head)->stqh_last = (elm);					\
	(head)->stqh_last = &STAILQ_NEXT((elm), field);			\
} while (0)

#define	STAILQ_INIT(head) do {						\
	STAILQ_FIRST((head)) = NULL;					\
	(head)->stqh_last = &STAILQ_FIRST((head));			\
} while (0)

#define	STAILQ_FOREACH(var, head, field)				\
	for((var) = STAILQ_FIRST((head));				\
	   (var);							\
	   (var) = STAILQ_NEXT((var), field))


/*
 *  SLC2 DMA Desc struct, aka lldesc_t
 *
 * --------------------------------------------------------------
 * | own | EoF | sub_sof | 5'b0   | length [11:0] | size [11:0] |
 * --------------------------------------------------------------
 * |            buf_ptr [31:0]                                  |
 * --------------------------------------------------------------
 * |            next_desc_ptr [31:0]                            |
 * --------------------------------------------------------------
 */

/* this bitfield is start from the LSB!!! */
typedef struct lldesc_s {
	volatile uint32_t size  : 12,
			 length: 12,
			 offset: 5, /* h/w reserved 5bit, s/w use it as offset in buffer */
			 sosf  : 1, /* start of sub-frame */
			 eof   : 1, /* end of frame */
			 owner : 1; /* hw or sw */
	volatile uint8_t *buf;       /* point to buffer data */
	union {
		volatile uint32_t empty;
		STAILQ_ENTRY(lldesc_s) qe;  /* pointing to the next desc */
	};
} lldesc_t;

typedef struct tx_ampdu_entry_s {
	uint32_t sub_len  : 12,
			 dili_num : 7,
			 : 1,
			 null_byte: 2,
			 data     : 1,
			 enc      : 1,
			 seq      : 8;
} tx_ampdu_entry_t;

typedef struct lldesc_chain_s {
	lldesc_t *head;
	lldesc_t *tail;
} lldesc_chain_t;

#ifdef SBUF_RXTX
enum sbuf_mask_s  {
	SBUF_MOVE_NO = 0,
	SBUF_MOVE_TX2RX,
	SBUF_MOVE_RX2TX,
} ;

#define SBUF_MOVE_STEP 8
#endif
#define LLDESC_SIZE  sizeof(struct lldesc_s)

/* SLC Descriptor  */
#define LLDESC_OWNER_MASK                  0x80000000
#define LLDESC_OWNER_SHIFT                         31
#define LLDESC_SW_OWNED                             0
#define LLDESC_HW_OWNED                             1

#define LLDESC_EOF_MASK                    0x40000000
#define LLDESC_EOF_SHIFT                           30

#define LLDESC_SOSF_MASK                   0x20000000
#define LLDESC_SOSF_SHIFT                          29

#define LLDESC_LENGTH_MASK                 0x00fff000
#define LLDESC_LENGTH_SHIFT                        12

#define LLDESC_SIZE_MASK                   0x00000fff
#define LLDESC_SIZE_SHIFT                           0

#define LLDESC_ADDR_MASK                    0x000fffff

void lldesc_build_chain(uint8_t *descptr, uint32_t desclen, uint8_t *mblkptr, uint32_t buflen, uint32_t blksz, uint8_t owner, lldesc_t **head, lldesc_t **one_before_tail, lldesc_t **tail);
lldesc_t *lldesc_num2link(lldesc_t *head, uint16_t nblks);
lldesc_t *lldesc_set_owner(lldesc_t *head, uint16_t nblks, uint8_t owner);
uint32_t lldesc_get_chain_length(lldesc_t *head);
void lldesc_config(lldesc_t *ds, uint8_t owner, uint8_t eof, uint8_t sosf, uint16_t len);

#define LLDESC_CONFIG(_desc, _owner, _eof, _sosf, _len)  \
	do {                                                 \
			(_desc)->owner  = (_owner);                  \
			(_desc)->eof    = (_eof);                    \
			(_desc)->sosf   = (_sosf);                   \
			(_desc)->length = (_len);                    \
	} while(0)

#define LLDESC_FROM_HOST_CLEANUP(ds) LLDESC_CONFIG((ds), LLDESC_HW_OWNED, 0, 0, 0)
#define LLDESC_MAC_RX_CLEANUP(ds) LLDESC_CONFIG((ds), LLDESC_HW_OWNED, 0, 0, (ds)->size)
#define LLDESC_TO_HOST_CLEANUP(ds) LLDESC_CONFIG((ds), LLDESC_HW_OWNED, 0, 0, 0)
