--- ./include/opcode/vfpu.h.orig	2012-01-21 13:31:35.000000000 +0000
+++ ./include/opcode/vfpu.h	2012-01-21 13:31:35.000000000 +0000
@@ -0,0 +1,261 @@
+#ifndef _VFPU_H_
+#define _VFPU_H_
+
+////////////////////////////////////
+// data type
+#define VFPU_MASK_DTYPE        0x8080
+#define VFPU_QUAD      0x8080
+#define VFPU_TRIPLE        0x8000
+#define VFPU_PAIR      0x0080
+#define VFPU_SINGLE        0x0000
+
+////////////////////////////////////
+// register index
+#define VFPU_MASK_VT       0x7f0000
+#define VFPU_MASK_VS       0x007f00
+#define VFPU_MASK_VD       0x00007f
+
+////////////////////////////////////
+// condition and comapre inst
+#define VFPU_PADD_BIN_CMP  0x70
+
+////////////////////////////////////
+// load/store left/right
+#define VFPU_MASK_LDST_LR  0x2
+#define VFPU_LDST_L        0x0
+#define VFPU_LDST_R        0x2
+
+////////////////////////////////////
+// load/store memory/buffer
+#define VFPU_MASK_LDST_MB  0x2
+#define VFPU_LDST_M        0x0
+#define VFPU_LDST_B        0x2
+
+////////////////////////////////////
+// coprocessor move
+#define VFPU_MASK_COP_MV   0xff80
+#define VFPU_MASK_COP_MVC  0xff00
+
+////////////////////////////////////
+// sync code
+#define    VFPU_MASK_SYNC_CODE 0xffff
+#define    VFPU_SYNC_CODE_DEFAULT  0x0320
+#define    VFPU_SYNC_CODE_NOP  0x0000
+#define    VFPU_SYNC_CODE_FLUSH    0x040d
+
+////////////////////////////////////
+#define VFPU_INST_BR_F     0x49000000
+#define VFPU_MASK_BR_F     0xffe30000
+#define VFPU_INST_BR_FL        0x49020000
+#define VFPU_MASK_BR_FL        0xffe30000
+#define VFPU_INST_BR_T     0x49010000
+#define VFPU_MASK_BR_T     0xffe30000
+#define VFPU_INST_BR_TL        0x49030000
+#define VFPU_MASK_BR_TL        0xffe30000
+
+#define VFPU_INST_COP_LD_S     0xc8000000
+#define VFPU_MASK_COP_LD_S     0xfc000000
+#define VFPU_INST_COP_ST_S     0xe8000000
+#define VFPU_MASK_COP_ST_S     0xfc000000
+#define VFPU_INST_COP_LD_Q     0xd8000000
+#define VFPU_MASK_COP_LD_Q     0xfc000000
+#define VFPU_INST_COP_ST_Q     0xf8000000
+#define VFPU_MASK_COP_ST_Q     0xfc000000
+#define VFPU_INST_COP_LD_U     0xd4000000
+#define VFPU_MASK_COP_LD_U     0xfc000000
+#define VFPU_INST_COP_ST_U     0xf4000000
+#define VFPU_MASK_COP_ST_U     0xfc000000
+#define VFPU_INST_COP_MF   0x48600000
+#define VFPU_MASK_COP_MF   0xffe00000
+#define VFPU_INST_COP_MT   0x48e00000
+#define VFPU_MASK_COP_MT   0xffe00000
+
+#define VFPU_INST_BIN_ADD  0x60000000
+#define VFPU_MASK_BIN_ADD  0xff800000
+#define VFPU_INST_BIN_SUB  0x60800000
+#define VFPU_MASK_BIN_SUB  0xff800000
+#define VFPU_INST_BIN_SBN  0x61000000
+#define VFPU_MASK_BIN_SBN  0xff800000
+#define VFPU_INST_BIN_DIV  0x63800000
+#define VFPU_MASK_BIN_DIV  0xff800000
+#define VFPU_INST_BIN_MUL  0x64000000
+#define VFPU_MASK_BIN_MUL  0xff800000
+#define VFPU_INST_BIN_DOT  0x64800000
+#define VFPU_MASK_BIN_DOT  0xff800000
+#define VFPU_INST_BIN_SCL  0x65000000
+#define VFPU_MASK_BIN_SCL  0xff800000
+#define VFPU_INST_BIN_HDP  0x66000000
+#define VFPU_MASK_BIN_HDP  0xff800000
+#define VFPU_INST_BIN_CRS  0x66800000
+#define VFPU_MASK_BIN_CRS  0xff800000
+#define VFPU_INST_BIN_DET  0x67000000
+#define VFPU_MASK_BIN_DET  0xff800000
+#define VFPU_INST_BIN_CMP  0x6c000000
+#define VFPU_MASK_BIN_CMP  0xff800000
+#define VFPU_INST_BIN_MIN  0x6d000000
+#define VFPU_MASK_BIN_MIN  0xff800000
+#define VFPU_INST_BIN_MAX  0x6d800000
+#define VFPU_MASK_BIN_MAX  0xff800000
+#define VFPU_INST_BIN_SCMP     0x6e800000
+#define VFPU_MASK_BIN_SCMP     0xff800000
+#define VFPU_INST_BIN_SGE  0x6f000000
+#define VFPU_MASK_BIN_SGE  0xff800000
+#define VFPU_INST_BIN_SLT  0x6f800000
+#define VFPU_MASK_BIN_SLT  0xff800000
+
+#define VFPU_INST_UNR_MOV  0xd0000000
+#define VFPU_MASK_UNR_MOV  0xffff0000
+#define VFPU_INST_UNR_ABS  0xd0010000
+#define VFPU_MASK_UNR_ABS  0xffff0000
+#define VFPU_INST_UNR_NEG  0xd0020000
+#define VFPU_MASK_UNR_NEG  0xffff0000
+#define VFPU_INST_UNR_IDT  0xd0030000
+#define VFPU_MASK_UNR_IDT  0xffff0000
+#define VFPU_INST_UNR_SAT0     0xd0040000
+#define VFPU_MASK_UNR_SAT0     0xffff0000
+#define VFPU_INST_UNR_SAT1     0xd0050000
+#define VFPU_MASK_UNR_SAT1     0xffff0000
+#define VFPU_INST_UNR_ZERO     0xd0060000
+#define VFPU_MASK_UNR_ZERO     0xffff0000
+#define VFPU_INST_UNR_ONE  0xd0070000
+#define VFPU_MASK_UNR_ONE  0xffff0000
+#define VFPU_INST_UNR_RCP  0xd0100000
+#define VFPU_MASK_UNR_RCP  0xffff0000
+#define VFPU_INST_UNR_RSQ  0xd0110000                                                                                                      
+#define VFPU_MASK_UNR_RSQ  0xffff0000
+#define VFPU_INST_UNR_SIN  0xd0120000
+#define VFPU_MASK_UNR_SIN  0xffff0000
+#define VFPU_INST_UNR_COS  0xd0130000
+#define VFPU_MASK_UNR_COS  0xffff0000
+#define VFPU_INST_UNR_EXP2     0xd0140000
+#define VFPU_MASK_UNR_EXP2     0xffff0000
+#define VFPU_INST_UNR_LOG2     0xd0150000
+#define VFPU_MASK_UNR_LOG2     0xffff0000
+#define VFPU_INST_UNR_SQR  0xd0160000
+#define VFPU_MASK_UNR_SQR  0xffff0000
+#define VFPU_INST_UNR_ASIN     0xd0170000
+#define VFPU_MASK_UNR_ASIN     0xffff0000
+#define VFPU_INST_UNR_NRCP     0xd0180000
+#define VFPU_MASK_UNR_NRCP     0xffff0000
+#define VFPU_INST_UNR_NSIN     0xd01a0000
+#define VFPU_MASK_UNR_NSIN     0xffff0000
+#define VFPU_INST_UNR_REXP2    0xd01c0000
+#define VFPU_MASK_UNR_REXP2    0xffff0000
+#define VFPU_INST_UNR_RNDS     0xd0200000
+#define VFPU_MASK_UNR_RNDS     0xffff0000
+#define VFPU_INST_UNR_RNDI     0xd0210000
+#define VFPU_MASK_UNR_RNDI     0xffff0000
+#define VFPU_INST_UNR_RNDF1    0xd0220000
+#define VFPU_MASK_UNR_RNDF1    0xffff0000
+#define VFPU_INST_UNR_RNDF2    0xd0230000
+#define VFPU_MASK_UNR_RNDF2    0xffff0000
+#define VFPU_INST_UNR_F2H  0xd0320000
+#define VFPU_MASK_UNR_F2H  0xffff0000
+#define VFPU_INST_UNR_H2F  0xd0330000
+#define VFPU_MASK_UNR_H2F  0xffff0000
+#define VFPU_INST_UNR_SBZ  0xd0360000
+#define VFPU_MASK_UNR_SBZ  0xffff0000
+#define VFPU_INST_UNR_LGB  0xd0370000
+#define VFPU_MASK_UNR_LGB  0xffff0000
+#define    VFPU_INST_UNR_US2I  0xd03a0000
+#define    VFPU_MASK_UNR_US2I  0xffff0000
+#define    VFPU_INST_UNR_S2I   0xd03b0000
+#define    VFPU_MASK_UNR_S2I   0xffff0000
+#define    VFPU_INST_UNR_I2UC  0xd03c0000
+#define    VFPU_MASK_UNR_I2UC  0xffff0000
+#define    VFPU_INST_UNR_I2C   0xd03d0000
+#define    VFPU_MASK_UNR_I2C   0xffff0000
+#define    VFPU_INST_UNR_I2US  0xd03e0000
+#define    VFPU_MASK_UNR_I2US  0xffff0000
+#define    VFPU_INST_UNR_I2S   0xd03f0000
+#define    VFPU_MASK_UNR_I2S   0xffff0000
+#define VFPU_INST_UNR_SRT1     0xd0400000
+#define VFPU_MASK_UNR_SRT1     0xffff0000
+#define VFPU_INST_UNR_SRT2     0xd0410000
+#define VFPU_MASK_UNR_SRT2     0xffff0000
+#define VFPU_INST_UNR_BFY1     0xd0420000
+#define VFPU_MASK_UNR_BFY1     0xffff0000
+#define VFPU_INST_UNR_BFY2     0xd0430000
+#define VFPU_MASK_UNR_BFY2     0xffff0000
+#define VFPU_INST_UNR_OCP  0xd0440000
+#define VFPU_MASK_UNR_OCP  0xffff0000
+#define VFPU_INST_UNR_SOCP     0xd0450000
+#define VFPU_MASK_UNR_SOCP     0xffff0000
+#define VFPU_INST_UNR_FAD  0xd0460000
+#define VFPU_MASK_UNR_FAD  0xffff0000
+#define VFPU_INST_UNR_AVG  0xd0470000
+#define VFPU_MASK_UNR_AVG  0xffff0000
+#define VFPU_INST_UNR_SRT3     0xd0480000
+#define VFPU_MASK_UNR_SRT3     0xffff0000
+#define VFPU_INST_UNR_SRT4     0xd0490000
+#define VFPU_MASK_UNR_SRT4     0xffff0000
+#define VFPU_INST_UNR_SGN  0xd04a0000
+#define VFPU_MASK_UNR_SGN  0xffff0000
+#define VFPU_INST_UNR_CF   0xd0500000
+#define VFPU_MASK_UNR_CF   0xffff0080
+#define VFPU_INST_UNR_CT   0xd0510000
+#define VFPU_MASK_UNR_CT   0xffff8000
+#define VFPU_INST_UNR_T4444    0xd0590000
+#define VFPU_MASK_UNR_T4444    0xffff0000
+#define VFPU_INST_UNR_T5551    0xd05a0000
+#define VFPU_MASK_UNR_T5551    0xffff0000
+#define VFPU_INST_UNR_T5650    0xd05b0000
+#define VFPU_MASK_UNR_T5650    0xffff0000
+#define VFPU_INST_UNR_CST  0xd0600000
+#define VFPU_MASK_UNR_CST  0xffe00000
+
+#define VFPU_INST_UNRI_F2I_N   0xd2000000
+#define VFPU_MASK_UNRI_F2I_N   0xffe00000
+#define VFPU_INST_UNRI_F2I_Z   0xd2200000
+#define VFPU_MASK_UNRI_F2I_Z   0xffe00000
+#define VFPU_INST_UNRI_F2I_U   0xd2400000
+#define VFPU_MASK_UNRI_F2I_U   0xffe00000
+#define VFPU_INST_UNRI_F2I_D   0xd2600000
+#define VFPU_MASK_UNRI_F2I_D   0xffe00000
+#define VFPU_INST_UNRI_I2F     0xd2800000
+#define VFPU_MASK_UNRI_I2F     0xffe00000
+#define VFPU_INST_UNRI_CMOV_T  0xd2a00000
+#define VFPU_MASK_UNRI_CMOV_T  0xfff80000
+#define VFPU_INST_UNRI_CMOV_F  0xd2a80000
+#define VFPU_MASK_UNRI_CMOV_F  0xfff80000
+#define VFPU_INST_UNRI_WBN     0xd3000000
+#define VFPU_MASK_UNRI_WBN     0xff000000
+
+#define VFPU_INST_PFX_RA   0xdc000000
+#define VFPU_MASK_PFX_RA   0xff000000
+#define VFPU_INST_PFX_RB   0xdd000000
+#define VFPU_MASK_PFX_RB   0xff000000
+#define VFPU_INST_PFX_W    0xde000000
+#define VFPU_MASK_PFX_W    0xff000000
+#define VFPU_INST_IIM      0xdf000000
+#define VFPU_MASK_IIM      0xff800000
+#define VFPU_INST_FIM      0xdf800000
+#define VFPU_MASK_FIM      0xff800000
+
+#define VFPU_INST_RPT_MMUL     0xf0000000
+#define VFPU_MASK_RPT_MMUL     0xff800000
+#define VFPU_INST_RPT_TFM2     0xf0800000
+#define VFPU_MASK_RPT_TFM2     0xff800000
+#define VFPU_INST_RPT_TFM3     0xf1000000
+#define VFPU_MASK_RPT_TFM3     0xff800000
+#define VFPU_INST_RPT_TFM4     0xf1800000
+#define VFPU_MASK_RPT_TFM4     0xff800000
+#define VFPU_INST_RPT_MSCL     0xf2000000
+#define VFPU_MASK_RPT_MSCL     0xff800000
+#define VFPU_INST_RPT_QMUL     0xf2800000
+#define VFPU_MASK_RPT_QMUL     0xff800000
+#define VFPU_INST_RPT_MMOV     0xf3800000
+#define VFPU_MASK_RPT_MMOV     0xffff0000
+#define VFPU_INST_RPT_MIDT     0xf3830000
+#define VFPU_MASK_RPT_MIDT     0xffff0000
+#define VFPU_INST_RPT_MZERO    0xf3860000
+#define VFPU_MASK_RPT_MZERO    0xffff0000
+#define VFPU_INST_RPT_MONE     0xf3870000
+#define VFPU_MASK_RPT_MONE     0xffff0000
+#define VFPU_INST_RPT_ROT  0xf3a00000
+#define VFPU_MASK_RPT_ROT  0xffe00000
+
+#define VFPU_INST_SYNC     0xffff0000
+#define VFPU_MASK_SYNC     0xffff0000
+
+#endif /* _VFPU_H_ */
