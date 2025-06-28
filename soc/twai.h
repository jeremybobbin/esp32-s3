#include <stdint.h>
#include <stdbool.h>

#define TWAI_LL_STATUS_RBS      (0x1 << 0)      //Receive Buffer Status
#define TWAI_LL_STATUS_DOS      (0x1 << 1)      //Data Overrun Status
#define TWAI_LL_STATUS_TBS      (0x1 << 2)      //Transmit Buffer Status
#define TWAI_LL_STATUS_TCS      (0x1 << 3)      //Transmission Complete Status
#define TWAI_LL_STATUS_RS       (0x1 << 4)      //Receive Status
#define TWAI_LL_STATUS_TS       (0x1 << 5)      //Transmit Status
#define TWAI_LL_STATUS_ES       (0x1 << 6)      //Error Status
#define TWAI_LL_STATUS_BS       (0x1 << 7)      //Bus Status
#define TWAI_LL_STATUS_MS       (0x1 << 8)      //Miss Status

#define TWAI_LL_INTR_RI         (0x1 << 0)      //Receive Interrupt
#define TWAI_LL_INTR_TI         (0x1 << 1)      //Transmit Interrupt
#define TWAI_LL_INTR_EI         (0x1 << 2)      //Error Interrupt
#define TWAI_LL_INTR_EPI        (0x1 << 5)      //Error Passive Interrupt
#define TWAI_LL_INTR_ALI        (0x1 << 6)      //Arbitration Lost Interrupt
#define TWAI_LL_INTR_BEI        (0x1 << 7)      //Bus Error Interrupt

#define TWAI_EXTD_ID_MASK               0x1FFFFFFF  /**< Bit mask for 29 bit Extended Frame Format ID */
#define TWAI_STD_ID_MASK                0x7FF       /**< Bit mask for 11 bit Standard Frame Format ID */
#define TWAI_FRAME_MAX_DLC              8           /**< Max data bytes allowed in TWAI */
#define TWAI_FRAME_EXTD_ID_LEN_BYTES    4           /**< EFF ID requires 4 bytes (29bit) */
#define TWAI_FRAME_STD_ID_LEN_BYTES     2           /**< SFF ID requires 2 bytes (11bit) */
#define TWAI_ERR_PASS_THRESH            128         /**< Error counter threshold for error passive */

/** @cond */    //Doxy command to hide preprocessor definitions from docs
/**
 * @brief   TWAI Message flags
 *
 * The message flags are used to indicate the type of message transmitted/received.
 * Some flags also specify the type of transmission.
 */
#define TWAI_MSG_FLAG_NONE              0x00        /**< No message flags (Standard Frame Format) */
#define TWAI_MSG_FLAG_EXTD              0x01        /**< Extended Frame Format (29bit ID) */
#define TWAI_MSG_FLAG_RTR               0x02        /**< Message is a Remote Frame */
#define TWAI_MSG_FLAG_SS                0x04        /**< Transmit as a Single Shot Transmission. Unused for received. */
#define TWAI_MSG_FLAG_SELF              0x08        /**< Transmit as a Self Reception Request. Unused for received. */
#define TWAI_MSG_FLAG_DLC_NON_COMP      0x10        /**< Message's Data length code is larger than 8. This will break compliance with TWAI */



typedef union {
	struct {
		struct {
			uint8_t dlc: 4;				//Data length code (0 to 8) of the frame
			uint8_t self_reception: 1;	//This frame should be transmitted using self reception command
			uint8_t single_shot: 1;		//This frame should be transmitted using single shot command
			uint8_t rtr: 1;				//This frame is a remote transmission request
			uint8_t frame_format: 1;	//Format of the frame (1 = extended, 0 = standard)
		};
		union {
			struct {
				uint8_t id[2];			//11 bit standard frame identifier
				uint8_t data[8];		//Data bytes (0 to 8)
				uint8_t reserved8[2];
			} standard;
			struct {
				uint8_t id[4];			//29 bit extended frame identifier
				uint8_t data[8];		//Data bytes (0 to 8)
			} extended;
		};
	};
	uint8_t bytes[13];
} __attribute__((packed)) twai_ll_frame_buffer_t;

typedef volatile struct twai_dev_s {
	//Configuration and Control Registers
	union {
		struct {
			uint32_t rm: 1;                     /* MOD.0 Reset Mode */
			uint32_t lom: 1;                    /* MOD.1 Listen Only Mode */
			uint32_t stm: 1;                    /* MOD.2 Self Test Mode */
			uint32_t afm: 1;                    /* MOD.3 Acceptance Filter Mode */
			uint32_t reserved4: 28;             /* Internal Reserved. MOD.4 Sleep Mode not supported */
		};
		uint32_t val;
	} mode_reg;                                 /* Address 0x0000 */
	union {
		struct {
			uint32_t tr: 1;                     /* CMR.0 Transmission Request */
			uint32_t at: 1;                     /* CMR.1 Abort Transmission */
			uint32_t rrb: 1;                    /* CMR.2 Release Receive Buffer */
			uint32_t cdo: 1;                    /* CMR.3 Clear Data Overrun */
			uint32_t srr: 1;                    /* CMR.4 Self Reception Request */
			uint32_t reserved5: 27;             /* Internal Reserved */
		};
		uint32_t val;
	} command_reg;                              /* Address 0x0004 */
	union {
		struct {
			uint32_t rbs: 1;                    /* SR.0 Receive Buffer Status */
			uint32_t dos: 1;                    /* SR.1 Data Overrun Status */
			uint32_t tbs: 1;                    /* SR.2 Transmit Buffer Status */
			uint32_t tcs: 1;                    /* SR.3 Transmission Complete Status */
			uint32_t rs: 1;                     /* SR.4 Receive Status */
			uint32_t ts: 1;                     /* SR.5 Transmit Status */
			uint32_t es: 1;                     /* SR.6 Error Status */
			uint32_t bs: 1;                     /* SR.7 Bus Status */
			uint32_t ms: 1;                     /* SR.8 Miss Status */
			uint32_t reserved9: 23;             /* Internal Reserved */
		};
		uint32_t val;
	} status_reg;                               /* Address 0x0008 */
	union {
		struct {
			uint32_t ri: 1;                     /* IR.0 Receive Interrupt */
			uint32_t ti: 1;                     /* IR.1 Transmit Interrupt */
			uint32_t ei: 1;                     /* IR.2 Error Interrupt */
			uint32_t doi: 1;                    /* IR.3 Data Overrun Interrupt */
			uint32_t reserved4: 1;              /* Internal Reserved (Wake-up not supported) */
			uint32_t epi: 1;                    /* IR.5 Error Passive Interrupt */
			uint32_t ali: 1;                    /* IR.6 Arbitration Lost Interrupt */
			uint32_t bei: 1;                    /* IR.7 Bus Error Interrupt */
			uint32_t reserved8: 24;             /* Internal Reserved */
		};
		uint32_t val;
	} interrupt_reg;                           /* Address 0x000C */
	union {
		struct {
			uint32_t rie: 1;                    /* IER.0 Receive Interrupt Enable */
			uint32_t tie: 1;                    /* IER.1 Transmit Interrupt Enable */
			uint32_t eie: 1;                    /* IER.2 Error Interrupt Enable */
			uint32_t doie: 1;                   /* IER.3 Data Overrun Interrupt Enable */
			uint32_t reserved4: 1;              /* Internal Reserved (Wake-up not supported) */
			uint32_t epie: 1;                   /* IER.5 Error Passive Interrupt Enable */
			uint32_t alie: 1;                   /* IER.6 Arbitration Lost Interrupt Enable */
			uint32_t beie: 1;                   /* IER.7 Bus Error Interrupt Enable */
			uint32_t reserved8: 24;             /* Internal Reserved */
		};
		uint32_t val;
	} interrupt_enable_reg;                     /* Address 0x0010 */
	uint32_t reserved_14;
	union {
		struct {
			uint32_t brp: 13;                   /* BTR0[12:0] Baud Rate Prescaler */
			uint32_t reserved13: 1;             /* Internal Reserved */
			uint32_t sjw: 2;                    /* BTR0[15:14] Synchronization Jump Width*/
			uint32_t reserved16: 16;            /* Internal Reserved */
		};
		uint32_t val;
	} bus_timing_0_reg;                         /* Address 0x0018 */
	union {
		struct {
			uint32_t tseg1: 4;                  /* BTR1[3:0] Timing Segment 1 */
			uint32_t tseg2: 3;                  /* BTR1[6:4] Timing Segment 2 */
			uint32_t sam: 1;                    /* BTR1.7 Sampling*/
			uint32_t reserved8: 24;             /* Internal Reserved */
		};
		uint32_t val;
	} bus_timing_1_reg;                         /* Address 0x001C */
	uint32_t reserved_20;                       /* Address 0x0020 (Output control not supported) */
	uint32_t reserved_24;                       /* Address 0x0024 (Test Register not supported) */
	uint32_t reserved_28;                       /* Address 0x0028 */

	//Capture and Counter Registers
	union {
		struct {
			uint32_t alc: 5;                    /* ALC[4:0] Arbitration lost capture */
			uint32_t reserved5: 27;             /* Internal Reserved */
		};
		uint32_t val;
	} arbitration_lost_captue_reg;              /* Address 0x002C */
	union {
		struct {
			uint32_t seg: 5;                    /* ECC[4:0] Error Code Segment 0 to 5 */
			uint32_t dir: 1;                    /* ECC.5 Error Direction (TX/RX) */
			uint32_t errc: 2;                   /* ECC[7:6] Error Code */
			uint32_t reserved8: 24;             /* Internal Reserved */
		};
		uint32_t val;
	} error_code_capture_reg;                   /* Address 0x0030 */
	union {
		struct {
			uint32_t ewl: 8;                    /* EWL[7:0] Error Warning Limit */
			uint32_t reserved8: 24;             /* Internal Reserved */
		};
		uint32_t val;
	} error_warning_limit_reg;                  /* Address 0x0034 */
	union {
		struct {
			uint32_t rxerr: 8;                  /* RXERR[7:0] Receive Error Counter */
			uint32_t reserved8: 24;             /* Internal Reserved */
		};
		uint32_t val;
	} rx_error_counter_reg;                     /* Address 0x0038 */
	union {
		struct {
			uint32_t txerr: 8;                  /* TXERR[7:0] Receive Error Counter */
			uint32_t reserved8: 24;             /* Internal Reserved */
		};
		uint32_t val;
	} tx_error_counter_reg;                     /* Address 0x003C */

	//Shared Registers (TX Buff/RX Buff/Acc Filter)
	union {
		struct {
			union {
				struct {
					uint32_t byte: 8;           /* ACRx[7:0] Acceptance Code */
					uint32_t reserved8: 24;     /* Internal Reserved */
				};
				uint32_t val;
			} acr[4];
			union {
				struct {
					uint32_t byte: 8;           /* AMRx[7:0] Acceptance Mask */
					uint32_t reserved8: 24;     /* Internal Reserved */
				};
				uint32_t val;
			} amr[4];
			uint32_t reserved_60;
			uint32_t reserved_64;
			uint32_t reserved_68;
			uint32_t reserved_6c;
			uint32_t reserved_70;
		} acceptance_filter;
		union {
			struct {
				uint32_t byte: 8;               /* TX/RX Byte X [7:0] */
				uint32_t reserved24: 24;        /* Internal Reserved */
			};
			uint32_t val;
		} tx_rx_buffer[13];
	};                                          /* Address 0x0040 - 0x0070 */

	//Misc Registers
	union {
		struct {
			uint32_t rmc: 7;                    /* RMC[6:0] RX Message Counter */
			uint32_t reserved7: 25;             /* Internal Reserved */
		};
		uint32_t val;
	} rx_message_counter_reg;                   /* Address 0x0074 */
	uint32_t reserved_78;                       /* Address 0x0078 (RX Buffer Start Address not supported) */
	union {
		struct {
			uint32_t cd: 8;                     /* CDR[7:0] CLKOUT frequency selector based of fOSC */
			uint32_t co: 1;                     /* CDR.8 CLKOUT enable/disable */
			uint32_t reserved9: 23;             /* Internal Reserved  */
		};
		uint32_t val;
	} clock_divider_reg;                        /* Address 0x007C */
} twai_dev_t;

typedef enum {
	TWAI_MODE_NORMAL,               /**< Normal operating mode where TWAI controller can send/receive/acknowledge messages */
	TWAI_MODE_NO_ACK,               /**< Transmission does not require acknowledgment. Use this mode for self testing */
	TWAI_MODE_LISTEN_ONLY,          /**< The TWAI controller will not influence the bus (No transmissions or acknowledgments) but can receive messages */
} twai_mode_t;


extern twai_dev_t *TWAI;


void twai_ll_enter_reset_mode(twai_dev_t *hw);
void twai_ll_exit_reset_mode(twai_dev_t *hw);
bool twai_ll_is_in_reset_mode(twai_dev_t *hw);
void twai_ll_set_mode(twai_dev_t *hw, twai_mode_t mode);
void twai_ll_set_cmd_tx(twai_dev_t *hw);
void twai_ll_set_cmd_tx_single_shot(twai_dev_t *hw);
void twai_ll_set_cmd_abort_tx(twai_dev_t *hw);
void twai_ll_set_cmd_release_rx_buffer(twai_dev_t *hw);
void twai_ll_set_cmd_clear_data_overrun(twai_dev_t *hw);
void twai_ll_set_cmd_self_rx_request(twai_dev_t *hw);
void twai_ll_set_cmd_self_rx_single_shot(twai_dev_t *hw);
uint32_t twai_ll_get_status(twai_dev_t *hw);
bool twai_ll_is_fifo_overrun(twai_dev_t *hw);
bool twai_ll_is_last_tx_successful(twai_dev_t *hw);
uint32_t twai_ll_get_and_clear_intrs(twai_dev_t *hw);
void twai_ll_set_enabled_intrs(twai_dev_t *hw, uint32_t intr_mask);
void twai_ll_set_bus_timing(twai_dev_t *hw, uint32_t brp, uint32_t sjw, uint32_t tseg1, uint32_t tseg2, bool triple_sampling);
void twai_ll_clear_arb_lost_cap(twai_dev_t *hw);
void twai_ll_clear_err_code_cap(twai_dev_t *hw);
void twai_ll_set_err_warn_lim(twai_dev_t *hw, uint32_t ewl);
uint32_t twai_ll_get_err_warn_lim(twai_dev_t *hw);
uint32_t twai_ll_get_rec(twai_dev_t *hw);
void twai_ll_set_rec(twai_dev_t *hw, uint32_t rec);
uint32_t twai_ll_get_tec(twai_dev_t *hw);
void twai_ll_set_tec(twai_dev_t *hw, uint32_t tec);
void twai_ll_set_acc_filter(twai_dev_t* hw, uint32_t code, uint32_t mask, bool single_filter);
void twai_ll_set_tx_buffer(twai_dev_t *hw, twai_ll_frame_buffer_t *tx_frame);
void twai_ll_get_rx_buffer(twai_dev_t *hw, twai_ll_frame_buffer_t *rx_frame);
void twai_ll_format_frame_buffer(uint32_t id, uint8_t dlc, const uint8_t *data, uint32_t flags, twai_ll_frame_buffer_t *tx_frame);
void twai_ll_prase_frame_buffer(twai_ll_frame_buffer_t *rx_frame, uint32_t *id, uint8_t *dlc, uint8_t *data, uint32_t *flags);
uint32_t twai_ll_get_rx_msg_count(twai_dev_t *hw);
void twai_ll_set_clkout(twai_dev_t *hw, uint32_t divider);
