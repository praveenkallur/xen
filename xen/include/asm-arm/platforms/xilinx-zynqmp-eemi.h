/* Xen specifics:  */
/* Main PM Mediator entry.  */
bool zynqmp_eemi_mediate(register_t fid,
                         register_t a0,
                         register_t a1,
                         register_t a2,
                         register_t a3,
                         register_t a4,
                         register_t a5,
                         register_t *ret);

/* Service calls.  */
#define SVC_MASK             0x3F000000
#define SVC_SIP              0x02000000    /* SoC Implementation Specific.  */
#define PM_SIP_SVC           0xC2000000
#define PM_GET_TRUSTZONE_VERSION	0xa03

/* SMC function IDs for SiP Service queries */
#define ZYNQMP_SIP_SVC_CALL_COUNT       0xff00
#define ZYNQMP_SIP_SVC_UID              0xff01
#define ZYNQMP_SIP_SVC_VERSION          0xff03

/* Generic PM defs:  */
/*
 * Version number is a 32bit value, like:
 * (PM_VERSION_MAJOR << 16) | PM_VERSION_MINOR
 */
#define PM_VERSION_MAJOR	1
#define PM_VERSION_MINOR	0

#define PM_VERSION	((PM_VERSION_MAJOR << 16) | PM_VERSION_MINOR)

/* Capabilities for RAM */
#define PM_CAP_ACCESS	0x1U
#define PM_CAP_CONTEXT	0x2U

#define MAX_LATENCY	(~0U)
#define MAX_QOS		100U

/* State arguments of the self suspend */
#define PM_STATE_CPU_IDLE		0x0U
#define PM_STATE_SUSPEND_TO_RAM		0xFU

enum pm_api_id {
	/* Miscellaneous API functions: */
	PM_GET_API_VERSION = 1, /* Do not change or move */
	PM_SET_CONFIGURATION,
	PM_GET_NODE_STATUS,
	PM_GET_OP_CHARACTERISTIC,
	PM_REGISTER_NOTIFIER,
	/* API for suspending of PUs: */
	PM_REQ_SUSPEND,
	PM_SELF_SUSPEND,
	PM_FORCE_POWERDOWN,
	PM_ABORT_SUSPEND,
	PM_REQ_WAKEUP,
	PM_SET_WAKEUP_SOURCE,
	PM_SYSTEM_SHUTDOWN,
	/* API for managing PM slaves: */
	PM_REQ_NODE,
	PM_RELEASE_NODE,
	PM_SET_REQUIREMENT,
	PM_SET_MAX_LATENCY,
	/* Direct control API functions: */
	PM_RESET_ASSERT,
	PM_RESET_GET_STATUS,
	PM_MMIO_WRITE,
	PM_MMIO_READ,
	PM_INIT,
	PM_FPGA_LOAD,
	PM_FPGA_GET_STATUS,
	PM_GET_CHIPID,
	/* ID 25 is been used by U-boot to process secure boot images */
	/* Secure library generic API functions */
	PM_SECURE_SHA = 26,
	PM_SECURE_RSA,
	/* Pin control API functions */
	PM_PINCTRL_REQUEST,
	PM_PINCTRL_RELEASE,
	PM_PINCTRL_GET_FUNCTION,
	PM_PINCTRL_SET_FUNCTION,
	PM_PINCTRL_CONFIG_PARAM_GET,
	PM_PINCTRL_CONFIG_PARAM_SET,
	/* PM IOCTL API */
	PM_IOCTL,
	/* API to query information from firmware */
	PM_QUERY_DATA,
	/* Clock control API functions */
	PM_CLOCK_ENABLE,
	PM_CLOCK_DISABLE,
	PM_CLOCK_GETSTATE,
	PM_CLOCK_SETDIVIDER,
	PM_CLOCK_GETDIVIDER,
	PM_CLOCK_SETRATE,
	PM_CLOCK_GETRATE,
	PM_CLOCK_SETPARENT,
	PM_CLOCK_GETPARENT,
	PM_API_MAX
};

enum pm_node_id {
	NODE_UNKNOWN = 0,
	NODE_APU,
	NODE_APU_0,
	NODE_APU_1,
	NODE_APU_2,
	NODE_APU_3,
	NODE_RPU,
	NODE_RPU_0,
	NODE_RPU_1,
	NODE_PLD,
	NODE_FPD,
	NODE_OCM_BANK_0,
	NODE_OCM_BANK_1,
	NODE_OCM_BANK_2,
	NODE_OCM_BANK_3,
	NODE_TCM_0_A,
	NODE_TCM_0_B,
	NODE_TCM_1_A,
	NODE_TCM_1_B,
	NODE_L2,
	NODE_GPU_PP_0,
	NODE_GPU_PP_1,
	NODE_USB_0,
	NODE_USB_1,
	NODE_TTC_0,
	NODE_TTC_1,
	NODE_TTC_2,
	NODE_TTC_3,
	NODE_SATA,
	NODE_ETH_0,
	NODE_ETH_1,
	NODE_ETH_2,
	NODE_ETH_3,
	NODE_UART_0,
	NODE_UART_1,
	NODE_SPI_0,
	NODE_SPI_1,
	NODE_I2C_0,
	NODE_I2C_1,
	NODE_SD_0,
	NODE_SD_1,
	NODE_DP,
	NODE_GDMA,
	NODE_ADMA,
	NODE_NAND,
	NODE_QSPI,
	NODE_GPIO,
	NODE_CAN_0,
	NODE_CAN_1,
	NODE_AFI,
	NODE_APLL,
	NODE_VPLL,
	NODE_DPLL,
	NODE_RPLL,
	NODE_IOPLL,
	NODE_DDR,
	NODE_IPI_APU,
	NODE_IPI_RPU_0,
	NODE_GPU,
	NODE_PCIE,
	NODE_PCAP,
	NODE_RTC,
	NODE_LPD,
	NODE_VCU,
	NODE_IPI_RPU_1,
	NODE_IPI_PL_0,
	NODE_IPI_PL_1,
	NODE_IPI_PL_2,
	NODE_IPI_PL_3,
	NODE_PL,
	NODE_MAX
};

enum pm_request_ack {
	REQ_ACK_NO = 1,
	REQ_ACK_BLOCKING,
	REQ_ACK_NON_BLOCKING,
};

enum pm_abort_reason {
	ABORT_REASON_WKUP_EVENT = 100,
	ABORT_REASON_PU_BUSY,
	ABORT_REASON_NO_PWRDN,
	ABORT_REASON_UNKNOWN,
};

enum pm_suspend_reason {
	SUSPEND_REASON_PU_REQ = 201,
	SUSPEND_REASON_ALERT,
	SUSPEND_REASON_SYS_SHUTDOWN,
};

enum pm_ram_state {
	PM_RAM_STATE_OFF = 1,
	PM_RAM_STATE_RETENTION,
	PM_RAM_STATE_ON,
};

enum pm_opchar_type {
	PM_OPCHAR_TYPE_POWER = 1,
	PM_OPCHAR_TYPE_TEMP,
	PM_OPCHAR_TYPE_LATENCY,
};

/**
 * @PM_RET_SUCCESS:             success
 * @PM_RET_ERROR_ARGS:          illegal arguments provided (deprecated)
 * @PM_RET_ERROR_NOTSUPPORTED:  feature not supported  (deprecated)
 * @PM_RET_INVALID_PARAM:       invalid argument
 * @PM_RET_ERROR_INTERNAL:      internal error
 * @PM_RET_ERROR_CONFLICT:      conflict
 * @PM_RET_ERROR_ACCESS:        access rights violation
 * @PM_RET_ERROR_INVALID_NODE:  invalid node
 * @PM_RET_ERROR_DOUBLE_REQ:    duplicate request for same node
 * @PM_RET_ERROR_ABORT_SUSPEND: suspend procedure has been aborted
 * @PM_RET_ERROR_TIMEOUT:       timeout in communication with PMU
 * @PM_RET_ERROR_NODE_USED:     node is already in use
 */
enum pm_ret_status {
    PM_RET_SUCCESS,
    PM_RET_ERROR_ARGS = 1,
    PM_RET_ERROR_NOTSUPPORTED = 4,
    PM_RET_INVALID_PARAM = 15,
    PM_RET_ERROR_INTERNAL = 2000,
    PM_RET_ERROR_CONFLICT = 2001,
    PM_RET_ERROR_ACCESS = 2002,
    PM_RET_ERROR_INVALID_NODE = 2003,
    PM_RET_ERROR_DOUBLE_REQ = 2004,
    PM_RET_ERROR_ABORT_SUSPEND = 2005,
    PM_RET_ERROR_TIMEOUT = 2006,
    PM_RET_ERROR_NODE_USED = 2007
};

/**
 * @PM_INITIAL_BOOT:	boot is a fresh system startup
 * @PM_RESUME:		boot is a resume
 * @PM_BOOT_ERROR:	error, boot cause cannot be identified
 */
enum pm_boot_status {
	PM_INITIAL_BOOT,
	PM_RESUME,
	PM_BOOT_ERROR,
};

enum pm_shutdown_type {
	PMF_SHUTDOWN_TYPE_SHUTDOWN,
	PMF_SHUTDOWN_TYPE_RESET,
};

enum pm_shutdown_subtype {
	PMF_SHUTDOWN_SUBTYPE_SUBSYSTEM,
	PMF_SHUTDOWN_SUBTYPE_PS_ONLY,
	PMF_SHUTDOWN_SUBTYPE_SYSTEM,
};

enum pm_reset {
	PM_RESET_START = 999,
	PM_RESET_PCIE_CFG,
	PM_RESET_PCIE_BRIDGE,
	PM_RESET_PCIE_CTRL,
	PM_RESET_DP,
	PM_RESET_SWDT_CRF,
	PM_RESET_AFI_FM5,
	PM_RESET_AFI_FM4,
	PM_RESET_AFI_FM3,
	PM_RESET_AFI_FM2,
	PM_RESET_AFI_FM1,
	PM_RESET_AFI_FM0,
	PM_RESET_GDMA,
	PM_RESET_GPU_PP1,
	PM_RESET_GPU_PP0,
	PM_RESET_GPU,
	PM_RESET_GT,
	PM_RESET_SATA,
	PM_RESET_ACPU3_PWRON,
	PM_RESET_ACPU2_PWRON,
	PM_RESET_ACPU1_PWRON,
	PM_RESET_ACPU0_PWRON,
	PM_RESET_APU_L2,
	PM_RESET_ACPU3,
	PM_RESET_ACPU2,
	PM_RESET_ACPU1,
	PM_RESET_ACPU0,
	PM_RESET_DDR,
	PM_RESET_APM_FPD,
	PM_RESET_SOFT,
	PM_RESET_GEM0,
	PM_RESET_GEM1,
	PM_RESET_GEM2,
	PM_RESET_GEM3,
	PM_RESET_QSPI,
	PM_RESET_UART0,
	PM_RESET_UART1,
	PM_RESET_SPI0,
	PM_RESET_SPI1,
	PM_RESET_SDIO0,
	PM_RESET_SDIO1,
	PM_RESET_CAN0,
	PM_RESET_CAN1,
	PM_RESET_I2C0,
	PM_RESET_I2C1,
	PM_RESET_TTC0,
	PM_RESET_TTC1,
	PM_RESET_TTC2,
	PM_RESET_TTC3,
	PM_RESET_SWDT_CRL,
	PM_RESET_NAND,
	PM_RESET_ADMA,
	PM_RESET_GPIO,
	PM_RESET_IOU_CC,
	PM_RESET_TIMESTAMP,
	PM_RESET_RPU_R50,
	PM_RESET_RPU_R51,
	PM_RESET_RPU_AMBA,
	PM_RESET_OCM,
	PM_RESET_RPU_PGE,
	PM_RESET_USB0_CORERESET,
	PM_RESET_USB1_CORERESET,
	PM_RESET_USB0_HIBERRESET,
	PM_RESET_USB1_HIBERRESET,
	PM_RESET_USB0_APB,
	PM_RESET_USB1_APB,
	PM_RESET_IPI,
	PM_RESET_APM_LPD,
	PM_RESET_RTC,
	PM_RESET_SYSMON,
	PM_RESET_AFI_FM6,
	PM_RESET_LPD_SWDT,
	PM_RESET_FPD,
	PM_RESET_RPU_DBG1,
	PM_RESET_RPU_DBG0,
	PM_RESET_DBG_LPD,
	PM_RESET_DBG_FPD,
	PM_RESET_APLL,
	PM_RESET_DPLL,
	PM_RESET_VPLL,
	PM_RESET_IOPLL,
	PM_RESET_RPLL,
	PM_RESET_GPO3_PL_0,
	PM_RESET_GPO3_PL_1,
	PM_RESET_GPO3_PL_2,
	PM_RESET_GPO3_PL_3,
	PM_RESET_GPO3_PL_4,
	PM_RESET_GPO3_PL_5,
	PM_RESET_GPO3_PL_6,
	PM_RESET_GPO3_PL_7,
	PM_RESET_GPO3_PL_8,
	PM_RESET_GPO3_PL_9,
	PM_RESET_GPO3_PL_10,
	PM_RESET_GPO3_PL_11,
	PM_RESET_GPO3_PL_12,
	PM_RESET_GPO3_PL_13,
	PM_RESET_GPO3_PL_14,
	PM_RESET_GPO3_PL_15,
	PM_RESET_GPO3_PL_16,
	PM_RESET_GPO3_PL_17,
	PM_RESET_GPO3_PL_18,
	PM_RESET_GPO3_PL_19,
	PM_RESET_GPO3_PL_20,
	PM_RESET_GPO3_PL_21,
	PM_RESET_GPO3_PL_22,
	PM_RESET_GPO3_PL_23,
	PM_RESET_GPO3_PL_24,
	PM_RESET_GPO3_PL_25,
	PM_RESET_GPO3_PL_26,
	PM_RESET_GPO3_PL_27,
	PM_RESET_GPO3_PL_28,
	PM_RESET_GPO3_PL_29,
	PM_RESET_GPO3_PL_30,
	PM_RESET_GPO3_PL_31,
	PM_RESET_RPU_LS,
	PM_RESET_PS_ONLY,
	PM_RESET_PL,
	PM_RESET_END
};

enum pm_clock {
    PM_CLOCK_IOPLL,
    PM_CLOCK_RPLL,
    PM_CLOCK_APLL,
    PM_CLOCK_DPLL,
    PM_CLOCK_VPLL,
    PM_CLOCK_IOPLL_TO_FPD,
    PM_CLOCK_RPLL_TO_FPD,
    PM_CLOCK_APLL_TO_LPD,
    PM_CLOCK_DPLL_TO_LPD,
    PM_CLOCK_VPLL_TO_LPD,
    PM_CLOCK_ACPU,
    PM_CLOCK_ACPU_HALF,
    PM_CLOCK_DBG_FPD,
    PM_CLOCK_DBG_LPD,
    PM_CLOCK_DBG_TRACE,
    PM_CLOCK_DBG_TSTMP,
    PM_CLOCK_DP_VIDEO_REF,
    PM_CLOCK_DP_AUDIO_REF,
    PM_CLOCK_DP_STC_REF,
    PM_CLOCK_GDMA_REF,
    PM_CLOCK_DPDMA_REF,
    PM_CLOCK_DDR_REF,
    PM_CLOCK_SATA_REF,
    PM_CLOCK_PCIE_REF,
    PM_CLOCK_GPU_REF,
    PM_CLOCK_GPU_PP0_REF,
    PM_CLOCK_GPU_PP1_REF,
    PM_CLOCK_TOPSW_MAIN,
    PM_CLOCK_TOPSW_LSBUS,
    PM_CLOCK_GTGREF0_REF,
    PM_CLOCK_LPD_SWITCH,
    PM_CLOCK_LPD_LSBUS,
    PM_CLOCK_USB0_BUS_REF,
    PM_CLOCK_USB1_BUS_REF,
    PM_CLOCK_USB3_DUAL_REF,
    PM_CLOCK_USB0,
    PM_CLOCK_USB1,
    PM_CLOCK_CPU_R5,
    PM_CLOCK_CPU_R5_CORE,
    PM_CLOCK_CSU_SPB,
    PM_CLOCK_CSU_PLL,
    PM_CLOCK_PCAP,
    PM_CLOCK_IOU_SWITCH,
    PM_CLOCK_GEM_TSU_REF,
    PM_CLOCK_GEM_TSU,
    PM_CLOCK_GEM0_TX,
    PM_CLOCK_GEM1_TX,
    PM_CLOCK_GEM2_TX,
    PM_CLOCK_GEM3_TX,
    PM_CLOCK_GEM0_RX,
    PM_CLOCK_GEM1_RX,
    PM_CLOCK_GEM2_RX,
    PM_CLOCK_GEM3_RX,
    PM_CLOCK_QSPI_REF,
    PM_CLOCK_SDIO0_REF,
    PM_CLOCK_SDIO1_REF,
    PM_CLOCK_UART0_REF,
    PM_CLOCK_UART1_REF,
    PM_CLOCK_SPI0_REF,
    PM_CLOCK_SPI1_REF,
    PM_CLOCK_NAND_REF,
    PM_CLOCK_I2C0_REF,
    PM_CLOCK_I2C1_REF,
    PM_CLOCK_CAN0_REF,
    PM_CLOCK_CAN1_REF,
    PM_CLOCK_CAN0,
    PM_CLOCK_CAN1,
    PM_CLOCK_DLL_REF,
    PM_CLOCK_ADMA_REF,
    PM_CLOCK_TIMESTAMP_REF,
    PM_CLOCK_AMS_REF,
    PM_CLOCK_PL0_REF,
    PM_CLOCK_PL1_REF,
    PM_CLOCK_PL2_REF,
    PM_CLOCK_PL3_REF,
    PM_CLOCK_WDT,
    PM_CLOCK_IOPLL_INT,
    PM_CLOCK_IOPLL_PRE_SRC,
    PM_CLOCK_IOPLL_HALF,
    PM_CLOCK_IOPLL_INT_MUX,
    PM_CLOCK_IOPLL_POST_SRC,
    PM_CLOCK_RPLL_INT,
    PM_CLOCK_RPLL_PRE_SRC,
    PM_CLOCK_RPLL_HALF,
    PM_CLOCK_RPLL_INT_MUX,
    PM_CLOCK_RPLL_POST_SRC,
    PM_CLOCK_APLL_INT,
    PM_CLOCK_APLL_PRE_SRC,
    PM_CLOCK_APLL_HALF,
    PM_CLOCK_APLL_INT_MUX,
    PM_CLOCK_APLL_POST_SRC,
    PM_CLOCK_DPLL_INT,
    PM_CLOCK_DPLL_PRE_SRC,
    PM_CLOCK_DPLL_HALF,
    PM_CLOCK_DPLL_INT_MUX,
    PM_CLOCK_DPLL_POST_SRC,
    PM_CLOCK_VPLL_INT,
    PM_CLOCK_VPLL_PRE_SRC,
    PM_CLOCK_VPLL_HALF,
    PM_CLOCK_VPLL_INT_MUX,
    PM_CLOCK_VPLL_POST_SRC,
    PM_CLOCK_CAN0_MIO,
    PM_CLOCK_CAN1_MIO,
    PM_CLOCK_ACPU_FULL,
    PM_CLOCK_GEM0_REF,
    PM_CLOCK_GEM1_REF,
    PM_CLOCK_GEM2_REF,
    PM_CLOCK_GEM3_REF,
    PM_CLOCK_GEM0_REF_UNGATED,
    PM_CLOCK_GEM1_REF_UNGATED,
    PM_CLOCK_GEM2_REF_UNGATED,
    PM_CLOCK_GEM3_REF_UNGATED,
    PM_CLOCK_END,
};
