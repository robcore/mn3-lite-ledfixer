static ssize_t allregs_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf,
				   "TAIKO_A_CHIP_CTL: reg %d value %d\n"
				   "TAIKO_A_CHIP_STATUS: reg %d value %d\n"
				   "TAIKO_A_CHIP_ID_BYTE_0: reg %d value %d\n"
				   "TAIKO_A_CHIP_ID_BYTE_1: reg %d value %d\n"
				   "TAIKO_A_CHIP_ID_BYTE_2: reg %d value %d\n"
				   "TAIKO_A_CHIP_ID_BYTE_3: reg %d value %d\n"
				   "TAIKO_A_CHIP_VERSION: reg %d value %d\n"
				   "TAIKO_A_SLAVE_ID_1: reg %d value %d\n"
				   "TAIKO_A_SLAVE_ID_2: reg %d value %d\n"
				   "TAIKO_A_SLAVE_ID_3: reg %d value %d\n"
				   "TAIKO_A_PIN_CTL_OE0: reg %d value %d\n"
				   "TAIKO_A_PIN_CTL_OE1: reg %d value %d\n"
				   "TAIKO_A_PIN_CTL_DATA0: reg %d value %d\n"
				   "TAIKO_A_PIN_CTL_DATA1: reg %d value %d\n"
				   "TAIKO_A_HDRIVE_GENERIC: reg %d value %d\n"
				   "TAIKO_A_HDRIVE_OVERRIDE: reg %d value %d\n"
				   "TAIKO_A_ANA_CSR_WAIT_STATE: reg %d value %d\n"
				   "TAIKO_A_PROCESS_MONITOR_CTL0: reg %d value %d\n"
				   "TAIKO_A_PROCESS_MONITOR_CTL1: reg %d value %d\n"
				   "TAIKO_A_PROCESS_MONITOR_CTL2: reg %d value %d\n"
				   "TAIKO_A_PROCESS_MONITOR_CTL3: reg %d value %d\n"
				   "TAIKO_A_QFUSE_CTL: reg %d value %d\n"
				   "TAIKO_A_QFUSE_STATUS: reg %d value %d\n"
				   "TAIKO_A_QFUSE_DATA_OUT0: reg %d value %d\n"
				   "TAIKO_A_QFUSE_DATA_OUT1: reg %d value %d\n"
				   "TAIKO_A_QFUSE_DATA_OUT2: reg %d value %d\n"
				   "TAIKO_A_QFUSE_DATA_OUT3: reg %d value %d\n"
				   "TAIKO_A_QFUSE_DATA_OUT4: reg %d value %d\n"
				   "TAIKO_A_QFUSE_DATA_OUT5: reg %d value %d\n"
				   "TAIKO_A_QFUSE_DATA_OUT6: reg %d value %d\n"
				   "TAIKO_A_QFUSE_DATA_OUT7: reg %d value %d\n"
				   "TAIKO_A_CDC_CTL: reg %d value %d\n"
				   "TAIKO_A_LEAKAGE_CTL: reg %d value %d\n"
				   "TAIKO_A_INTR_MODE: reg %d value %d\n"
				   "TAIKO_A_INTR_MASK0: reg %d value %d\n"
				   "TAIKO_A_INTR_MASK1: reg %d value %d\n"
				   "TAIKO_A_INTR_MASK2: reg %d value %d\n"
				   "TAIKO_A_INTR_MASK3: reg %d value %d\n"
				   "TAIKO_A_INTR_STATUS0: reg %d value %d\n"
				   "TAIKO_A_INTR_STATUS1: reg %d value %d\n"
				   "TAIKO_A_INTR_STATUS2: reg %d value %d\n"
				   "TAIKO_A_INTR_STATUS3: reg %d value %d\n"
				   "TAIKO_A_INTR_CLEAR0: reg %d value %d\n"
				   "TAIKO_A_INTR_CLEAR1: reg %d value %d\n"
				   "TAIKO_A_INTR_CLEAR2: reg %d value %d\n"
				   "TAIKO_A_INTR_CLEAR3: reg %d value %d\n"
				   "TAIKO_A_INTR_LEVEL0: reg %d value %d\n"
				   "TAIKO_A_INTR_LEVEL1: reg %d value %d\n"
				   "TAIKO_A_INTR_LEVEL2: reg %d value %d\n"
				   "TAIKO_A_INTR_LEVEL3: reg %d value %d\n"
				   "TAIKO_A_INTR_TEST0: reg %d value %d\n"
				   "TAIKO_A_INTR_TEST1: reg %d value %d\n"
				   "TAIKO_A_INTR_TEST2: reg %d value %d\n"
				   "TAIKO_A_INTR_TEST3: reg %d value %d\n"
				   "TAIKO_A_INTR_SET0: reg %d value %d\n"
				   "TAIKO_A_INTR_SET1: reg %d value %d\n"
				   "TAIKO_A_INTR_SET2: reg %d value %d\n"
				   "TAIKO_A_INTR_SET3: reg %d value %d\n"
				   "TAIKO_A_INTR_DESTN0: reg %d value %d\n"
				   "TAIKO_A_INTR_DESTN1: reg %d value %d\n"
				   "TAIKO_A_INTR_DESTN2: reg %d value %d\n"
				   "TAIKO_A_INTR_DESTN3: reg %d value %d\n"
				   "TAIKO_A_CDC_TX_I2S_SCK_MODE: reg %d value %d\n"
				   "TAIKO_A_CDC_TX_I2S_WS_MODE: reg %d value %d\n"
				   "TAIKO_A_CDC_DMIC_DATA0_MODE: reg %d value %d\n"
				   "TAIKO_A_CDC_DMIC_CLK0_MODE: reg %d value %d\n"
				   "TAIKO_A_CDC_DMIC_DATA1_MODE: reg %d value %d\n"
				   "TAIKO_A_CDC_DMIC_CLK1_MODE: reg %d value %d\n"
				   "TAIKO_A_CDC_RX_I2S_SCK_MODE: reg %d value %d\n"
				   "TAIKO_A_CDC_RX_I2S_WS_MODE: reg %d value %d\n"
				   "TAIKO_A_CDC_DMIC_DATA2_MODE: reg %d value %d\n"
				   "TAIKO_A_CDC_DMIC_CLK2_MODE: reg %d value %d\n"
				   "TAIKO_A_CDC_INTR1_MODE: reg %d value %d\n"
				   "TAIKO_A_CDC_SB_NRZ_SEL_MODE: reg %d value %d\n"
				   "TAIKO_A_CDC_INTR2_MODE: reg %d value %d\n"
				   "TAIKO_A_CDC_RF_PA_ON_MODE: reg %d value %d\n"
				   "TAIKO_A_BIAS_REF_CTL: reg %d value %d\n"
				   "TAIKO_A_BIAS_CENTRAL_BG_CTL: reg %d value %d\n"
				   "TAIKO_A_BIAS_PRECHRG_CTL: reg %d value %d\n"
				   "TAIKO_A_BIAS_CURR_CTL_1: reg %d value %d\n"
				   "TAIKO_A_BIAS_CURR_CTL_2: reg %d value %d\n"
				   "TAIKO_A_BIAS_OSC_BG_CTL: reg %d value %d\n"
				   "TAIKO_A_CLK_BUFF_EN1: reg %d value %d\n"
				   "TAIKO_A_CLK_BUFF_EN2: reg %d value %d\n"
				   "TAIKO_A_LDO_H_MODE_1: reg %d value %d\n"
				   "TAIKO_A_LDO_H_MODE_2: reg %d value %d\n"
				   "TAIKO_A_LDO_H_LOOP_CTL: reg %d value %d\n"
				   "TAIKO_A_LDO_H_COMP_1: reg %d value %d\n"
				   "TAIKO_A_LDO_H_COMP_2: reg %d value %d\n"
				   "TAIKO_A_LDO_H_BIAS_1: reg %d value %d\n"
				   "TAIKO_A_LDO_H_BIAS_2: reg %d value %d\n"
				   "TAIKO_A_LDO_H_BIAS_3: reg %d value %d\n"
				   "TAIKO_A_VBAT_CLK: reg %d value %d\n"
				   "TAIKO_A_VBAT_LOOP: reg %d value %d\n"
				   "TAIKO_A_VBAT_REF: reg %d value %d\n"
				   "TAIKO_A_VBAT_ADC_TEST: reg %d value %d\n"
				   "TAIKO_A_VBAT_FE: reg %d value %d\n"
				   "TAIKO_A_VBAT_BIAS_1: reg %d value %d\n"
				   "TAIKO_A_VBAT_BIAS_2: reg %d value %d\n"
				   "TAIKO_A_VBAT_ADC_DATA_MSB: reg %d value %d\n"
				   "TAIKO_A_VBAT_ADC_DATA_LSB: reg %d value %d\n"
				   "TAIKO_A_MICB_CFILT_1_CTL: reg %d value %d\n"
				   "TAIKO_A_MICB_CFILT_1_VAL: reg %d value %d\n"
				   "TAIKO_A_MICB_CFILT_1_PRECHRG: reg %d value %d\n"
				   "TAIKO_A_MICB_1_CTL: reg %d value %d\n"
				   "TAIKO_A_MICB_1_INT_RBIAS: reg %d value %d\n"
				   "TAIKO_A_MICB_1_MBHC: reg %d value %d\n"
				   "TAIKO_A_MICB_CFILT_2_CTL: reg %d value %d\n"
				   "TAIKO_A_MICB_CFILT_2_VAL: reg %d value %d\n"
				   "TAIKO_A_MICB_CFILT_2_PRECHRG: reg %d value %d\n"
				   "TAIKO_A_MICB_2_CTL: reg %d value %d\n"
				   "TAIKO_A_MICB_2_INT_RBIAS: reg %d value %d\n"
				   "TAIKO_A_MICB_2_MBHC: reg %d value %d\n"
				   "TAIKO_A_MICB_CFILT_3_CTL: reg %d value %d\n"
				   "TAIKO_A_MICB_CFILT_3_VAL: reg %d value %d\n"
				   "TAIKO_A_MICB_CFILT_3_PRECHRG: reg %d value %d\n"
				   "TAIKO_A_MICB_3_CTL: reg %d value %d\n"
				   "TAIKO_A_MICB_3_INT_RBIAS: reg %d value %d\n"
				   "TAIKO_A_MICB_3_MBHC: reg %d value %d\n"
				   "TAIKO_A_MICB_4_CTL: reg %d value %d\n"
				   "TAIKO_A_MICB_4_INT_RBIAS: reg %d value %d\n"
				   "TAIKO_A_MICB_4_MBHC: reg %d value %d\n"
				   "TAIKO_A_MBHC_INSERT_DETECT: reg %d value %d\n"
				   "TAIKO_A_MBHC_INSERT_DET_STATUS: reg %d value %d\n"
				   "TAIKO_A_TX_COM_BIAS: reg %d value %d\n"
				   "TAIKO_A_MBHC_SCALING_MUX_1: reg %d value %d\n"
				   "TAIKO_A_MBHC_SCALING_MUX_2: reg %d value %d\n"
				   "TAIKO_A_MAD_ANA_CTRL: reg %d value %d\n"
				   "TAIKO_A_TX_SUP_SWITCH_CTRL_1: reg %d value %d\n"
				   "TAIKO_A_TX_SUP_SWITCH_CTRL_2: reg %d value %d\n"
				   "TAIKO_A_TX_1_2_EN: reg %d value %d\n"
				   "TAIKO_A_TX_1_2_TEST_EN: reg %d value %d\n"
				   "TAIKO_A_TX_1_2_ADC_CH1: reg %d value %d\n"
				   "TAIKO_A_TX_1_2_ADC_CH2: reg %d value %d\n"
				   "TAIKO_A_TX_1_2_ATEST_REFCTRL: reg %d value %d\n"
				   "TAIKO_A_TX_1_2_TEST_CTL: reg %d value %d\n"
				   "TAIKO_A_TX_1_2_TEST_BLOCK_EN: reg %d value %d\n"
				   "TAIKO_A_TX_1_2_TXFE_CLKDIV: reg %d value %d\n"
				   "TAIKO_A_TX_1_2_SAR_ERR_CH1: reg %d value %d\n"
				   "TAIKO_A_TX_1_2_SAR_ERR_CH2: reg %d value %d\n"
				   "TAIKO_A_TX_3_4_EN: reg %d value %d\n"
				   "TAIKO_A_TX_3_4_TEST_EN: reg %d value %d\n"
				   "TAIKO_A_TX_3_4_ADC_CH3: reg %d value %d\n"
				   "TAIKO_A_TX_3_4_ADC_CH4: reg %d value %d\n"
				   "TAIKO_A_TX_3_4_ATEST_REFCTRL: reg %d value %d\n"
				   "TAIKO_A_TX_3_4_TEST_CTL: reg %d value %d\n"
				   "TAIKO_A_TX_3_4_TEST_BLOCK_EN: reg %d value %d\n"
				   "TAIKO_A_TX_3_4_TXFE_CKDIV: reg %d value %d\n"
				   "TAIKO_A_TX_3_4_SAR_ERR_CH3: reg %d value %d\n"
				   "TAIKO_A_TX_3_4_SAR_ERR_CH4: reg %d value %d\n"
				   "TAIKO_A_TX_5_6_EN: reg %d value %d\n"
				   "TAIKO_A_TX_5_6_TEST_EN: reg %d value %d\n"
				   "TAIKO_A_TX_5_6_ADC_CH5: reg %d value %d\n"
				   "TAIKO_A_TX_5_6_ADC_CH6: reg %d value %d\n"
				   "TAIKO_A_TX_5_6_ATEST_REFCTRL: reg %d value %d\n"
				   "TAIKO_A_TX_5_6_TEST_CTL: reg %d value %d\n"
				   "TAIKO_A_TX_5_6_TEST_BLOCK_EN: reg %d value %d\n"
				   "TAIKO_A_TX_5_6_TXFE_CKDIV: reg %d value %d\n"
				   "TAIKO_A_TX_5_6_SAR_ERR_CH5: reg %d value %d\n"
				   "TAIKO_A_TX_5_6_SAR_ERR_CH6: reg %d value %d\n"
				   "TAIKO_A_TX_7_MBHC_EN: reg %d value %d\n"
				   "TAIKO_A_TX_7_MBHC_ATEST_REFCTRL: reg %d value %d\n"
				   "TAIKO_A_TX_7_MBHC_ADC: reg %d value %d\n"
				   "TAIKO_A_TX_7_MBHC_TEST_CTL: reg %d value %d\n"
				   "TAIKO_A_TX_7_MBHC_SAR_ERR: reg %d value %d\n"
				   "TAIKO_A_TX_7_TXFE_CLKDIV: reg %d value %d\n"
				   "TAIKO_A_BUCK_MODE_1: reg %d value %d\n"
				   "TAIKO_A_BUCK_MODE_2: reg %d value %d\n"
				   "TAIKO_A_BUCK_MODE_3: reg %d value %d\n"
				   "TAIKO_A_BUCK_MODE_4: reg %d value %d\n"
				   "TAIKO_A_BUCK_MODE_5: reg %d value %d\n"
				   "TAIKO_A_BUCK_CTRL_VCL_1: reg %d value %d\n"
				   "TAIKO_A_BUCK_CTRL_VCL_2: reg %d value %d\n"
				   "TAIKO_A_BUCK_CTRL_VCL_3: reg %d value %d\n"
				   "TAIKO_A_BUCK_CTRL_CCL_1: reg %d value %d\n"
				   "TAIKO_A_BUCK_CTRL_CCL_2: reg %d value %d\n"
				   "TAIKO_A_BUCK_CTRL_CCL_3: reg %d value %d\n"
				   "TAIKO_A_BUCK_CTRL_CCL_4: reg %d value %d\n"
				   "TAIKO_A_BUCK_CTRL_PWM_DRVR_1: reg %d value %d\n"
				   "TAIKO_A_BUCK_CTRL_PWM_DRVR_2: reg %d value %d\n"
				   "TAIKO_A_BUCK_CTRL_PWM_DRVR_3: reg %d value %d\n"
				   "TAIKO_A_BUCK_TMUX_A_D: reg %d value %d\n"
				   "TAIKO_A_NCP_BUCKREF: reg %d value %d\n"
				   "TAIKO_A_NCP_EN: reg %d value %d\n"
				   "TAIKO_A_NCP_CLK: reg %d value %d\n"
				   "TAIKO_A_NCP_STATIC: reg %d value %d\n"
				   "TAIKO_A_NCP_VTH_LOW: reg %d value %d\n"
				   "TAIKO_A_NCP_VTH_HIGH: reg %d value %d\n"
				   "TAIKO_A_NCP_ATEST: reg %d value %d\n"
				   "TAIKO_A_NCP_DTEST: reg %d value %d\n"
				   "TAIKO_A_NCP_DLY1: reg %d value %d\n"
				   "TAIKO_A_NCP_DLY2: reg %d value %d\n"
				   "TAIKO_A_RX_AUX_SW_CTL: reg %d value %d\n"
				   "TAIKO_A_RX_PA_AUX_IN_CONN: reg %d value %d\n"
				   "TAIKO_A_RX_COM_TIMER_DIV: reg %d value %d\n"
				   "TAIKO_A_RX_COM_OCP_CTL: reg %d value %d\n"
				   "TAIKO_A_RX_COM_OCP_COUNT: reg %d value %d\n"
				   "TAIKO_A_RX_COM_DAC_CTL: reg %d value %d\n"
				   "TAIKO_A_RX_COM_BIAS: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_AUTO_CHOP: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_CHOP_CTL: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_BIAS_PA: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_BIAS_LDO: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_BIAS_CNP: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_BIAS_WG_OCP: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_OCP_CTL: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_CNP_EN: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_CNP_WG_CTL: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_CNP_WG_TIME: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_L_GAIN: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_L_TEST: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_L_PA_CTL: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_L_DAC_CTL: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_L_ATEST: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_L_STATUS: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_R_GAIN: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_R_TEST: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_R_PA_CTL: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_R_DAC_CTL: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_R_ATEST: reg %d value %d\n"
				   "TAIKO_A_RX_HPH_R_STATUS: reg %d value %d\n"
				   "TAIKO_A_RX_EAR_BIAS_PA: reg %d value %d\n"
				   "TAIKO_A_RX_EAR_BIAS_CMBUFF: reg %d value %d\n"
				   "TAIKO_A_RX_EAR_EN: reg %d value %d\n"
				   "TAIKO_A_RX_EAR_GAIN: reg %d value %d\n"
				   "TAIKO_A_RX_EAR_CMBUFF: reg %d value %d\n"
				   "TAIKO_A_RX_EAR_ICTL: reg %d value %d\n"
				   "TAIKO_A_RX_EAR_CCOMP: reg %d value %d\n"
				   "TAIKO_A_RX_EAR_VCM: reg %d value %d\n"
				   "TAIKO_A_RX_EAR_CNP: reg %d value %d\n"
				   "TAIKO_A_RX_EAR_DAC_CTL_ATEST: reg %d value %d\n"
				   "TAIKO_A_RX_EAR_STATUS: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_BIAS_PA: reg %d value %d\n"
				   "TAIKO_A_RX_BUCK_BIAS1: reg %d value %d\n"
				   "TAIKO_A_RX_BUCK_BIAS2: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_COM: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_CNP_EN: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_CNP_WG_CTL: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_CNP_WG_TIME: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_1_GAIN: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_1_TEST: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_1_DAC_CTL: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_1_STATUS: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_2_GAIN: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_2_TEST: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_2_DAC_CTL: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_2_STATUS: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_3_GAIN: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_3_TEST: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_3_DAC_CTL: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_3_STATUS: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_4_GAIN: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_4_TEST: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_4_DAC_CTL: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_4_STATUS: reg %d value %d\n"
				   "TAIKO_A_RX_LINE_CNP_DBG: reg %d value %d\n"
				   "TAIKO_A_SPKR_DRV_EN: reg %d value %d\n"
				   "TAIKO_A_SPKR_DRV_GAIN: reg %d value %d\n"
				   "TAIKO_A_SPKR_DRV_DAC_CTL: reg %d value %d\n"
				   "TAIKO_A_SPKR_DRV_OCP_CTL: reg %d value %d\n"
				   "TAIKO_A_SPKR_DRV_CLIP_DET: reg %d value %d\n"
				   "TAIKO_A_SPKR_DRV_IEC: reg %d value %d\n"
				   "TAIKO_A_SPKR_DRV_DBG_DAC: reg %d value %d\n"
				   "TAIKO_A_SPKR_DRV_DBG_PA: reg %d value %d\n"
				   "TAIKO_A_SPKR_DRV_DBG_PWRSTG: reg %d value %d\n"
				   "TAIKO_A_SPKR_DRV_BIAS_LDO: reg %d value %d\n"
				   "TAIKO_A_SPKR_DRV_BIAS_INT: reg %d value %d\n"
				   "TAIKO_A_SPKR_DRV_BIAS_PA: reg %d value %d\n"
				   "TAIKO_A_SPKR_DRV_STATUS_OCP: reg %d value %d\n"
				   "TAIKO_A_SPKR_DRV_STATUS_PA: reg %d value %d\n"
				   "TAIKO_A_SPKR_PROT_EN: reg %d value %d\n"
				   "TAIKO_A_SPKR_PROT_ADC_EN: reg %d value %d\n"
				   "TAIKO_A_SPKR_PROT_ISENSE_BIAS: reg %d value %d\n"
				   "TAIKO_A_SPKR_PROT_VSENSE_BIAS: reg %d value %d\n"
				   "TAIKO_A_SPKR_PROT_ADC_ATEST_REFCTRL: reg %d value %d\n"
				   "TAIKO_A_SPKR_PROT_ADC_TEST_CTL: reg %d value %d\n"
				   "TAIKO_A_SPKR_PROT_TEST_BLOCK_EN: reg %d value %d\n"
				   "TAIKO_A_SPKR_PROT_ATEST: reg %d value %d\n"
				   "TAIKO_A_SPKR_PROT_V_SAR_ERR: reg %d value %d\n"
				   "TAIKO_A_SPKR_PROT_I_SAR_ERR: reg %d value %d\n"
				   "TAIKO_A_SPKR_PROT_LDO_CTRL: reg %d value %d\n"
				   "TAIKO_A_SPKR_PROT_ISENSE_CTRL: reg %d value %d\n"
				   "TAIKO_A_SPKR_PROT_VSENSE_CTRL: reg %d value %d\n"
				   "TAIKO_A_RC_OSC_FREQ: reg %d value %d\n"
				   "TAIKO_A_RC_OSC_TEST: reg %d value %d\n"
				   "TAIKO_A_RC_OSC_STATUS: reg %d value %d\n"
				   "TAIKO_A_RC_OSC_TUNER: reg %d value %d\n"
				   "TAIKO_A_MBHC_HPH: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC1_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC2_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC1_SHIFT: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC2_SHIFT: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC1_IIR_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC2_IIR_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC1_IIR_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC2_IIR_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC1_IIR_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC2_IIR_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC1_LPF_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC2_LPF_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC1_LPF_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC2_LPF_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC1_SPARE: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC2_SPARE: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC1_SMLPF_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC2_SMLPF_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC1_DCFLT_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC2_DCFLT_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC1_GAIN_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC2_GAIN_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC1_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_ANC2_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX1_VOL_CTL_TIMER: reg %d value %d\n"
				   "TAIKO_A_CDC_TX2_VOL_CTL_TIMER: reg %d value %d\n"
				   "TAIKO_A_CDC_TX3_VOL_CTL_TIMER: reg %d value %d\n"
				   "TAIKO_A_CDC_TX4_VOL_CTL_TIMER: reg %d value %d\n"
				   "TAIKO_A_CDC_TX5_VOL_CTL_TIMER: reg %d value %d\n"
				   "TAIKO_A_CDC_TX6_VOL_CTL_TIMER: reg %d value %d\n"
				   "TAIKO_A_CDC_TX7_VOL_CTL_TIMER: reg %d value %d\n"
				   "TAIKO_A_CDC_TX8_VOL_CTL_TIMER: reg %d value %d\n"
				   "TAIKO_A_CDC_TX9_VOL_CTL_TIMER: reg %d value %d\n"
				   "TAIKO_A_CDC_TX10_VOL_CTL_TIMER: reg %d value %d\n"
				   "TAIKO_A_CDC_TX1_VOL_CTL_GAIN: reg %d value %d\n"
				   "TAIKO_A_CDC_TX2_VOL_CTL_GAIN: reg %d value %d\n"
				   "TAIKO_A_CDC_TX3_VOL_CTL_GAIN: reg %d value %d\n"
				   "TAIKO_A_CDC_TX4_VOL_CTL_GAIN: reg %d value %d\n"
				   "TAIKO_A_CDC_TX5_VOL_CTL_GAIN: reg %d value %d\n"
				   "TAIKO_A_CDC_TX6_VOL_CTL_GAIN: reg %d value %d\n"
				   "TAIKO_A_CDC_TX7_VOL_CTL_GAIN: reg %d value %d\n"
				   "TAIKO_A_CDC_TX8_VOL_CTL_GAIN: reg %d value %d\n"
				   "TAIKO_A_CDC_TX9_VOL_CTL_GAIN: reg %d value %d\n"
				   "TAIKO_A_CDC_TX10_VOL_CTL_GAIN: reg %d value %d\n"
				   "TAIKO_A_CDC_TX1_VOL_CTL_CFG: reg %d value %d\n"
				   "TAIKO_A_CDC_TX2_VOL_CTL_CFG: reg %d value %d\n"
				   "TAIKO_A_CDC_TX3_VOL_CTL_CFG: reg %d value %d\n"
				   "TAIKO_A_CDC_TX4_VOL_CTL_CFG: reg %d value %d\n"
				   "TAIKO_A_CDC_TX5_VOL_CTL_CFG: reg %d value %d\n"
				   "TAIKO_A_CDC_TX6_VOL_CTL_CFG: reg %d value %d\n"
				   "TAIKO_A_CDC_TX7_VOL_CTL_CFG: reg %d value %d\n"
				   "TAIKO_A_CDC_TX8_VOL_CTL_CFG: reg %d value %d\n"
				   "TAIKO_A_CDC_TX9_VOL_CTL_CFG: reg %d value %d\n"
				   "TAIKO_A_CDC_TX10_VOL_CTL_CFG: reg %d value %d\n"
				   "TAIKO_A_CDC_TX1_MUX_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX2_MUX_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX3_MUX_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX4_MUX_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX5_MUX_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX6_MUX_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX7_MUX_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX8_MUX_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX9_MUX_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX10_MUX_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX1_CLK_FS_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX2_CLK_FS_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX3_CLK_FS_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX4_CLK_FS_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX5_CLK_FS_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX6_CLK_FS_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX7_CLK_FS_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX8_CLK_FS_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX9_CLK_FS_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX10_CLK_FS_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX1_DMIC_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX2_DMIC_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX3_DMIC_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX4_DMIC_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX5_DMIC_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX6_DMIC_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX7_DMIC_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX8_DMIC_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX9_DMIC_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TX10_DMIC_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_DEBUG_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_DEBUG_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_DEBUG_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_DEBUG_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_DEBUG_B5_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_DEBUG_B6_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_DEBUG_B7_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_SRC1_PDA_CFG: reg %d value %d\n"
				   "TAIKO_A_CDC_SRC2_PDA_CFG: reg %d value %d\n"
				   "TAIKO_A_CDC_SRC1_FS_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_SRC2_FS_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX1_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX2_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX3_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX4_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX5_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX6_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX7_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX1_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX2_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX3_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX4_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX5_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX6_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX7_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX1_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX2_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX3_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX4_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX5_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX6_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX7_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX1_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX2_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX3_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX4_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX5_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX6_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX7_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX1_B5_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX2_B5_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX3_B5_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX4_B5_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX5_B5_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX6_B5_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX7_B5_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX1_B6_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX2_B6_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX3_B6_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX4_B6_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX5_B6_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX6_B6_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX7_B6_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX1_VOL_CTL_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX2_VOL_CTL_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX3_VOL_CTL_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX4_VOL_CTL_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX5_VOL_CTL_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX6_VOL_CTL_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX7_VOL_CTL_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX1_VOL_CTL_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX2_VOL_CTL_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX3_VOL_CTL_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX4_VOL_CTL_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX5_VOL_CTL_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX6_VOL_CTL_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_RX7_VOL_CTL_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_VBAT_CFG: reg %d value %d\n"
				   "TAIKO_A_CDC_VBAT_ADC_CAL1: reg %d value %d\n"
				   "TAIKO_A_CDC_VBAT_ADC_CAL2: reg %d value %d\n"
				   "TAIKO_A_CDC_VBAT_ADC_CAL3: reg %d value %d\n"
				   "TAIKO_A_CDC_VBAT_PK_EST1: reg %d value %d\n"
				   "TAIKO_A_CDC_VBAT_PK_EST2: reg %d value %d\n"
				   "TAIKO_A_CDC_VBAT_PK_EST3: reg %d value %d\n"
				   "TAIKO_A_CDC_VBAT_RF_PROC1: reg %d value %d\n"
				   "TAIKO_A_CDC_VBAT_RF_PROC2: reg %d value %d\n"
				   "TAIKO_A_CDC_VBAT_TAC1: reg %d value %d\n"
				   "TAIKO_A_CDC_VBAT_TAC2: reg %d value %d\n"
				   "TAIKO_A_CDC_VBAT_TAC3: reg %d value %d\n"
				   "TAIKO_A_CDC_VBAT_TAC4: reg %d value %d\n"
				   "TAIKO_A_CDC_VBAT_GAIN_UPD1: reg %d value %d\n"
				   "TAIKO_A_CDC_VBAT_GAIN_UPD2: reg %d value %d\n"
				   "TAIKO_A_CDC_VBAT_GAIN_UPD3: reg %d value %d\n"
				   "TAIKO_A_CDC_VBAT_GAIN_UPD4: reg %d value %d\n"
				   "TAIKO_A_CDC_VBAT_DEBUG1: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_ANC_RESET_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_RX_RESET_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_TX_RESET_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_TX_RESET_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_DMIC_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_DMIC_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_RX_I2S_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_TX_I2S_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_OTHR_RESET_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_OTHR_RESET_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_TX_CLK_EN_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_TX_CLK_EN_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_OTHR_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_RDAC_CLK_EN_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_ANC_CLK_EN_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_RX_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_RX_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_MCLK_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_PDM_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_SD_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLK_POWER_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLSH_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLSH_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLSH_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CLSH_BUCK_NCP_VARS: reg %d value %d\n"
				   "TAIKO_A_CDC_CLSH_IDLE_HPH_THSD: reg %d value %d\n"
				   "TAIKO_A_CDC_CLSH_IDLE_EAR_THSD: reg %d value %d\n"
				   "TAIKO_A_CDC_CLSH_FCLKONLY_HPH_THSD: reg %d value %d\n"
				   "TAIKO_A_CDC_CLSH_FCLKONLY_EAR_THSD: reg %d value %d\n"
				   "TAIKO_A_CDC_CLSH_K_ADDR: reg %d value %d\n"
				   "TAIKO_A_CDC_CLSH_K_DATA: reg %d value %d\n"
				   "TAIKO_A_CDC_CLSH_I_PA_FACT_HPH_L: reg %d value %d\n"
				   "TAIKO_A_CDC_CLSH_I_PA_FACT_HPH_U: reg %d value %d\n"
				   "TAIKO_A_CDC_CLSH_I_PA_FACT_EAR_L: reg %d value %d\n"
				   "TAIKO_A_CDC_CLSH_I_PA_FACT_EAR_U: reg %d value %d\n"
				   "TAIKO_A_CDC_CLSH_V_PA_HD_EAR: reg %d value %d\n"
				   "TAIKO_A_CDC_CLSH_V_PA_HD_HPH: reg %d value %d\n"
				   "TAIKO_A_CDC_CLSH_V_PA_MIN_EAR: reg %d value %d\n"
				   "TAIKO_A_CDC_CLSH_V_PA_MIN_HPH: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR1_GAIN_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR2_GAIN_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR1_GAIN_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR2_GAIN_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR1_GAIN_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR2_GAIN_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR1_GAIN_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR2_GAIN_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR1_GAIN_B5_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR2_GAIN_B5_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR1_GAIN_B6_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR2_GAIN_B6_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR1_GAIN_B7_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR2_GAIN_B7_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR1_GAIN_B8_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR2_GAIN_B8_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR1_GAIN_TIMER_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR2_GAIN_TIMER_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR1_COEF_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR2_COEF_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR1_COEF_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_IIR2_COEF_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_TOP_GAIN_UPDATE: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP0_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP1_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP2_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP0_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP1_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP2_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP0_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP1_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP2_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP0_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP1_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP2_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP0_B5_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP1_B5_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP2_B5_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP0_B6_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP1_B6_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP2_B6_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP0_SHUT_DOWN_STATUS: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP1_SHUT_DOWN_STATUS: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP2_SHUT_DOWN_STATUS: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP0_FS_CFG: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP1_FS_CFG: reg %d value %d\n"
				   "TAIKO_A_CDC_COMP2_FS_CFG: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX1_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX1_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX1_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX2_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX2_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX2_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX3_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX3_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX4_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX4_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX5_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX5_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX6_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX6_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX7_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX7_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX7_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_ANC_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_ANC_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_TX_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_TX_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_TX_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_TX_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_EQ1_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_EQ1_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_EQ1_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_EQ1_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_EQ2_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_EQ2_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_EQ2_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_EQ2_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_SRC1_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_SRC1_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_SRC2_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_SRC2_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_TX_SB_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_TX_SB_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_TX_SB_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_TX_SB_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_TX_SB_B5_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_TX_SB_B6_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_TX_SB_B7_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_TX_SB_B8_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_TX_SB_B9_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_TX_SB_B10_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_TX_SB_B11_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX_SB_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_RX_SB_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_CLSH_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_MISC: reg %d value %d\n"
				   "TAIKO_A_CDC_CONN_MAD: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_EN_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_FIR_B1_CFG: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_FIR_B2_CFG: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_TIMER_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_TIMER_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_TIMER_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_TIMER_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_TIMER_B5_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_TIMER_B6_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_B1_STATUS: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_B2_STATUS: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_B3_STATUS: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_B4_STATUS: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_B5_STATUS: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_VOLT_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_VOLT_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_VOLT_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_VOLT_B4_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_VOLT_B5_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_VOLT_B6_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_VOLT_B7_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_VOLT_B8_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_VOLT_B9_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_VOLT_B10_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_VOLT_B11_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_VOLT_B12_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_CLK_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_INT_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_DEBUG_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_MBHC_SPARE: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_MAIN_CTL_1: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_MAIN_CTL_2: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_AUDIO_CTL_1: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_AUDIO_CTL_2: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_AUDIO_CTL_3: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_AUDIO_CTL_4: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_AUDIO_CTL_5: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_AUDIO_CTL_6: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_AUDIO_CTL_7: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_AUDIO_CTL_8: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_AUDIO_IIR_CTL_PTR: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_AUDIO_IIR_CTL_VAL: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_ULTR_CTL_1: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_ULTR_CTL_2: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_ULTR_CTL_3: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_ULTR_CTL_4: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_ULTR_CTL_5: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_ULTR_CTL_6: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_ULTR_CTL_7: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_BEACON_CTL_1: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_BEACON_CTL_2: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_BEACON_CTL_3: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_BEACON_CTL_4: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_BEACON_CTL_5: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_BEACON_CTL_6: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_BEACON_CTL_7: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_BEACON_CTL_8: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_BEACON_IIR_CTL_PTR: reg %d value %d\n"
				   "TAIKO_A_CDC_MAD_BEACON_IIR_CTL_VAL: reg %d value %d\n"
				   "TAIKO_A_CDC_SPKR_CLIPDET_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_SPKR_CLIPDET_VAL0: reg %d value %d\n"
				   "TAIKO_A_CDC_SPKR_CLIPDET_VAL1: reg %d value %d\n"
				   "TAIKO_A_CDC_SPKR_CLIPDET_VAL2: reg %d value %d\n"
				   "TAIKO_A_CDC_SPKR_CLIPDET_VAL3: reg %d value %d\n"
				   "TAIKO_A_CDC_SPKR_CLIPDET_VAL4: reg %d value %d\n"
				   "TAIKO_A_CDC_SPKR_CLIPDET_VAL5: reg %d value %d\n"
				   "TAIKO_A_CDC_SPKR_CLIPDET_VAL6: reg %d value %d\n"
				   "TAIKO_A_CDC_SPKR_CLIPDET_VAL7: reg %d value %d\n"
				   "TAIKO_A_CDC_PA_RAMP_B1_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_PA_RAMP_B2_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_PA_RAMP_B3_CTL: reg %d value %d\n"
				   "TAIKO_A_CDC_PA_RAMP_B4_CTL: reg %d value %d\n",
				   TAIKO_A_CHIP_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CHIP_CTL),
				   TAIKO_A_CHIP_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CHIP_STATUS),
				   TAIKO_A_CHIP_ID_BYTE_0, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CHIP_ID_BYTE_0),
				   TAIKO_A_CHIP_ID_BYTE_1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CHIP_ID_BYTE_1),
				   TAIKO_A_CHIP_ID_BYTE_2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CHIP_ID_BYTE_2),
				   TAIKO_A_CHIP_ID_BYTE_3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CHIP_ID_BYTE_3),
				   TAIKO_A_CHIP_VERSION, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CHIP_VERSION),
				   TAIKO_A_SLAVE_ID_1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SLAVE_ID_1),
				   TAIKO_A_SLAVE_ID_2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SLAVE_ID_2),
				   TAIKO_A_SLAVE_ID_3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SLAVE_ID_3),
				   TAIKO_A_PIN_CTL_OE0, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_PIN_CTL_OE0),
				   TAIKO_A_PIN_CTL_OE1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_PIN_CTL_OE1),
				   TAIKO_A_PIN_CTL_DATA0, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_PIN_CTL_DATA0),
				   TAIKO_A_PIN_CTL_DATA1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_PIN_CTL_DATA1),
				   TAIKO_A_HDRIVE_GENERIC, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_HDRIVE_GENERIC),
				   TAIKO_A_HDRIVE_OVERRIDE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_HDRIVE_OVERRIDE),
				   TAIKO_A_ANA_CSR_WAIT_STATE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_ANA_CSR_WAIT_STATE),
				   TAIKO_A_PROCESS_MONITOR_CTL0, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_PROCESS_MONITOR_CTL0),
				   TAIKO_A_PROCESS_MONITOR_CTL1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_PROCESS_MONITOR_CTL1),
				   TAIKO_A_PROCESS_MONITOR_CTL2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_PROCESS_MONITOR_CTL2),
				   TAIKO_A_PROCESS_MONITOR_CTL3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_PROCESS_MONITOR_CTL3),
				   TAIKO_A_QFUSE_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_QFUSE_CTL),
				   TAIKO_A_QFUSE_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_QFUSE_STATUS),
				   TAIKO_A_QFUSE_DATA_OUT0, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_QFUSE_DATA_OUT0),
				   TAIKO_A_QFUSE_DATA_OUT1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_QFUSE_DATA_OUT1),
				   TAIKO_A_QFUSE_DATA_OUT2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_QFUSE_DATA_OUT2),
				   TAIKO_A_QFUSE_DATA_OUT3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_QFUSE_DATA_OUT3),
				   TAIKO_A_QFUSE_DATA_OUT4, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_QFUSE_DATA_OUT4),
				   TAIKO_A_QFUSE_DATA_OUT5, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_QFUSE_DATA_OUT5),
				   TAIKO_A_QFUSE_DATA_OUT6, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_QFUSE_DATA_OUT6),
				   TAIKO_A_QFUSE_DATA_OUT7, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_QFUSE_DATA_OUT7),
				   TAIKO_A_CDC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CTL),
				   TAIKO_A_LEAKAGE_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_LEAKAGE_CTL),
				   TAIKO_A_INTR_MODE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_MODE),
				   TAIKO_A_INTR_MASK0, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_MASK0),
				   TAIKO_A_INTR_MASK1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_MASK1),
				   TAIKO_A_INTR_MASK2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_MASK2),
				   TAIKO_A_INTR_MASK3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_MASK3),
				   TAIKO_A_INTR_STATUS0, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_STATUS0),
				   TAIKO_A_INTR_STATUS1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_STATUS1),
				   TAIKO_A_INTR_STATUS2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_STATUS2),
				   TAIKO_A_INTR_STATUS3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_STATUS3),
				   TAIKO_A_INTR_CLEAR0, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_CLEAR0),
				   TAIKO_A_INTR_CLEAR1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_CLEAR1),
				   TAIKO_A_INTR_CLEAR2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_CLEAR2),
				   TAIKO_A_INTR_CLEAR3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_CLEAR3),
				   TAIKO_A_INTR_LEVEL0, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_LEVEL0),
				   TAIKO_A_INTR_LEVEL1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_LEVEL1),
				   TAIKO_A_INTR_LEVEL2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_LEVEL2),
				   TAIKO_A_INTR_LEVEL3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_LEVEL3),
				   TAIKO_A_INTR_TEST0, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_TEST0),
				   TAIKO_A_INTR_TEST1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_TEST1),
				   TAIKO_A_INTR_TEST2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_TEST2),
				   TAIKO_A_INTR_TEST3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_TEST3),
				   TAIKO_A_INTR_SET0, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_SET0),
				   TAIKO_A_INTR_SET1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_SET1),
				   TAIKO_A_INTR_SET2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_SET2),
				   TAIKO_A_INTR_SET3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_SET3),
				   TAIKO_A_INTR_DESTN0, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_DESTN0),
				   TAIKO_A_INTR_DESTN1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_DESTN1),
				   TAIKO_A_INTR_DESTN2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_DESTN2),
				   TAIKO_A_INTR_DESTN3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_INTR_DESTN3),
				   TAIKO_A_CDC_TX_I2S_SCK_MODE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX_I2S_SCK_MODE),
				   TAIKO_A_CDC_TX_I2S_WS_MODE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX_I2S_WS_MODE),
				   TAIKO_A_CDC_DMIC_DATA0_MODE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_DMIC_DATA0_MODE),
				   TAIKO_A_CDC_DMIC_CLK0_MODE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_DMIC_CLK0_MODE),
				   TAIKO_A_CDC_DMIC_DATA1_MODE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_DMIC_DATA1_MODE),
				   TAIKO_A_CDC_DMIC_CLK1_MODE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_DMIC_CLK1_MODE),
				   TAIKO_A_CDC_RX_I2S_SCK_MODE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX_I2S_SCK_MODE),
				   TAIKO_A_CDC_RX_I2S_WS_MODE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX_I2S_WS_MODE),
				   TAIKO_A_CDC_DMIC_DATA2_MODE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_DMIC_DATA2_MODE),
				   TAIKO_A_CDC_DMIC_CLK2_MODE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_DMIC_CLK2_MODE),
				   TAIKO_A_CDC_INTR1_MODE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_INTR1_MODE),
				   TAIKO_A_CDC_SB_NRZ_SEL_MODE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_SB_NRZ_SEL_MODE),
				   TAIKO_A_CDC_INTR2_MODE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_INTR2_MODE),
				   TAIKO_A_CDC_RF_PA_ON_MODE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RF_PA_ON_MODE),
				   TAIKO_A_BIAS_REF_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BIAS_REF_CTL),
				   TAIKO_A_BIAS_CENTRAL_BG_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BIAS_CENTRAL_BG_CTL),
				   TAIKO_A_BIAS_PRECHRG_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BIAS_PRECHRG_CTL),
				   TAIKO_A_BIAS_CURR_CTL_1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BIAS_CURR_CTL_1),
				   TAIKO_A_BIAS_CURR_CTL_2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BIAS_CURR_CTL_2),
				   TAIKO_A_BIAS_OSC_BG_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BIAS_OSC_BG_CTL),
				   TAIKO_A_CLK_BUFF_EN1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CLK_BUFF_EN1),
				   TAIKO_A_CLK_BUFF_EN2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CLK_BUFF_EN2),
				   TAIKO_A_LDO_H_MODE_1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_LDO_H_MODE_1),
				   TAIKO_A_LDO_H_MODE_2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_LDO_H_MODE_2),
				   TAIKO_A_LDO_H_LOOP_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_LDO_H_LOOP_CTL),
				   TAIKO_A_LDO_H_COMP_1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_LDO_H_COMP_1),
				   TAIKO_A_LDO_H_COMP_2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_LDO_H_COMP_2),
				   TAIKO_A_LDO_H_BIAS_1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_LDO_H_BIAS_1),
				   TAIKO_A_LDO_H_BIAS_2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_LDO_H_BIAS_2),
				   TAIKO_A_LDO_H_BIAS_3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_LDO_H_BIAS_3),
				   TAIKO_A_VBAT_CLK, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_VBAT_CLK),
				   TAIKO_A_VBAT_LOOP, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_VBAT_LOOP),
				   TAIKO_A_VBAT_REF, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_VBAT_REF),
				   TAIKO_A_VBAT_ADC_TEST, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_VBAT_ADC_TEST),
				   TAIKO_A_VBAT_FE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_VBAT_FE),
				   TAIKO_A_VBAT_BIAS_1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_VBAT_BIAS_1),
				   TAIKO_A_VBAT_BIAS_2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_VBAT_BIAS_2),
				   TAIKO_A_VBAT_ADC_DATA_MSB, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_VBAT_ADC_DATA_MSB),
				   TAIKO_A_VBAT_ADC_DATA_LSB, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_VBAT_ADC_DATA_LSB),
				   TAIKO_A_MICB_CFILT_1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_CFILT_1_CTL),
				   TAIKO_A_MICB_CFILT_1_VAL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_CFILT_1_VAL),
				   TAIKO_A_MICB_CFILT_1_PRECHRG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_CFILT_1_PRECHRG),
				   TAIKO_A_MICB_1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_1_CTL),
				   TAIKO_A_MICB_1_INT_RBIAS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_1_INT_RBIAS),
				   TAIKO_A_MICB_1_MBHC, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_1_MBHC),
				   TAIKO_A_MICB_CFILT_2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_CFILT_2_CTL),
				   TAIKO_A_MICB_CFILT_2_VAL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_CFILT_2_VAL),
				   TAIKO_A_MICB_CFILT_2_PRECHRG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_CFILT_2_PRECHRG),
				   TAIKO_A_MICB_2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_2_CTL),
				   TAIKO_A_MICB_2_INT_RBIAS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_2_INT_RBIAS),
				   TAIKO_A_MICB_2_MBHC, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_2_MBHC),
				   TAIKO_A_MICB_CFILT_3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_CFILT_3_CTL),
				   TAIKO_A_MICB_CFILT_3_VAL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_CFILT_3_VAL),
				   TAIKO_A_MICB_CFILT_3_PRECHRG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_CFILT_3_PRECHRG),
				   TAIKO_A_MICB_3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_3_CTL),
				   TAIKO_A_MICB_3_INT_RBIAS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_3_INT_RBIAS),
				   TAIKO_A_MICB_3_MBHC, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_3_MBHC),
				   TAIKO_A_MICB_4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_4_CTL),
				   TAIKO_A_MICB_4_INT_RBIAS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_4_INT_RBIAS),
				   TAIKO_A_MICB_4_MBHC, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MICB_4_MBHC),
				   TAIKO_A_MBHC_INSERT_DETECT, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MBHC_INSERT_DETECT),
				   TAIKO_A_MBHC_INSERT_DET_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MBHC_INSERT_DET_STATUS),
				   TAIKO_A_TX_COM_BIAS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_COM_BIAS),
				   TAIKO_A_MBHC_SCALING_MUX_1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MBHC_SCALING_MUX_1),
				   TAIKO_A_MBHC_SCALING_MUX_2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MBHC_SCALING_MUX_2),
				   TAIKO_A_MAD_ANA_CTRL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MAD_ANA_CTRL),
				   TAIKO_A_TX_SUP_SWITCH_CTRL_1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_SUP_SWITCH_CTRL_1),
				   TAIKO_A_TX_SUP_SWITCH_CTRL_2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_SUP_SWITCH_CTRL_2),
				   TAIKO_A_TX_1_2_EN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_1_2_EN),
				   TAIKO_A_TX_1_2_TEST_EN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_1_2_TEST_EN),
				   TAIKO_A_TX_1_2_ADC_CH1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_1_2_ADC_CH1),
				   TAIKO_A_TX_1_2_ADC_CH2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_1_2_ADC_CH2),
				   TAIKO_A_TX_1_2_ATEST_REFCTRL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_1_2_ATEST_REFCTRL),
				   TAIKO_A_TX_1_2_TEST_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_1_2_TEST_CTL),
				   TAIKO_A_TX_1_2_TEST_BLOCK_EN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_1_2_TEST_BLOCK_EN),
				   TAIKO_A_TX_1_2_TXFE_CLKDIV, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_1_2_TXFE_CLKDIV),
				   TAIKO_A_TX_1_2_SAR_ERR_CH1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_1_2_SAR_ERR_CH1),
				   TAIKO_A_TX_1_2_SAR_ERR_CH2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_1_2_SAR_ERR_CH2),
				   TAIKO_A_TX_3_4_EN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_3_4_EN),
				   TAIKO_A_TX_3_4_TEST_EN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_3_4_TEST_EN),
				   TAIKO_A_TX_3_4_ADC_CH3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_3_4_ADC_CH3),
				   TAIKO_A_TX_3_4_ADC_CH4, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_3_4_ADC_CH4),
				   TAIKO_A_TX_3_4_ATEST_REFCTRL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_3_4_ATEST_REFCTRL),
				   TAIKO_A_TX_3_4_TEST_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_3_4_TEST_CTL),
				   TAIKO_A_TX_3_4_TEST_BLOCK_EN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_3_4_TEST_BLOCK_EN),
				   TAIKO_A_TX_3_4_TXFE_CKDIV, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_3_4_TXFE_CKDIV),
				   TAIKO_A_TX_3_4_SAR_ERR_CH3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_3_4_SAR_ERR_CH3),
				   TAIKO_A_TX_3_4_SAR_ERR_CH4, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_3_4_SAR_ERR_CH4),
				   TAIKO_A_TX_5_6_EN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_5_6_EN),
				   TAIKO_A_TX_5_6_TEST_EN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_5_6_TEST_EN),
				   TAIKO_A_TX_5_6_ADC_CH5, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_5_6_ADC_CH5),
				   TAIKO_A_TX_5_6_ADC_CH6, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_5_6_ADC_CH6),
				   TAIKO_A_TX_5_6_ATEST_REFCTRL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_5_6_ATEST_REFCTRL),
				   TAIKO_A_TX_5_6_TEST_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_5_6_TEST_CTL),
				   TAIKO_A_TX_5_6_TEST_BLOCK_EN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_5_6_TEST_BLOCK_EN),
				   TAIKO_A_TX_5_6_TXFE_CKDIV, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_5_6_TXFE_CKDIV),
				   TAIKO_A_TX_5_6_SAR_ERR_CH5, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_5_6_SAR_ERR_CH5),
				   TAIKO_A_TX_5_6_SAR_ERR_CH6, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_5_6_SAR_ERR_CH6),
				   TAIKO_A_TX_7_MBHC_EN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_7_MBHC_EN),
				   TAIKO_A_TX_7_MBHC_ATEST_REFCTRL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_7_MBHC_ATEST_REFCTRL),
				   TAIKO_A_TX_7_MBHC_ADC, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_7_MBHC_ADC),
				   TAIKO_A_TX_7_MBHC_TEST_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_7_MBHC_TEST_CTL),
				   TAIKO_A_TX_7_MBHC_SAR_ERR, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_7_MBHC_SAR_ERR),
				   TAIKO_A_TX_7_TXFE_CLKDIV, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_TX_7_TXFE_CLKDIV),
				   TAIKO_A_BUCK_MODE_1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BUCK_MODE_1),
				   TAIKO_A_BUCK_MODE_2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BUCK_MODE_2),
				   TAIKO_A_BUCK_MODE_3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BUCK_MODE_3),
				   TAIKO_A_BUCK_MODE_4, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BUCK_MODE_4),
				   TAIKO_A_BUCK_MODE_5, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BUCK_MODE_5),
				   TAIKO_A_BUCK_CTRL_VCL_1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BUCK_CTRL_VCL_1),
				   TAIKO_A_BUCK_CTRL_VCL_2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BUCK_CTRL_VCL_2),
				   TAIKO_A_BUCK_CTRL_VCL_3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BUCK_CTRL_VCL_3),
				   TAIKO_A_BUCK_CTRL_CCL_1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BUCK_CTRL_CCL_1),
				   TAIKO_A_BUCK_CTRL_CCL_2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BUCK_CTRL_CCL_2),
				   TAIKO_A_BUCK_CTRL_CCL_3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BUCK_CTRL_CCL_3),
				   TAIKO_A_BUCK_CTRL_CCL_4, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BUCK_CTRL_CCL_4),
				   TAIKO_A_BUCK_CTRL_PWM_DRVR_1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BUCK_CTRL_PWM_DRVR_1),
				   TAIKO_A_BUCK_CTRL_PWM_DRVR_2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BUCK_CTRL_PWM_DRVR_2),
				   TAIKO_A_BUCK_CTRL_PWM_DRVR_3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BUCK_CTRL_PWM_DRVR_3),
				   TAIKO_A_BUCK_TMUX_A_D, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_BUCK_TMUX_A_D),
				   TAIKO_A_NCP_BUCKREF, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_NCP_BUCKREF),
				   TAIKO_A_NCP_EN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_NCP_EN),
				   TAIKO_A_NCP_CLK, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_NCP_CLK),
				   TAIKO_A_NCP_STATIC, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_NCP_STATIC),
				   TAIKO_A_NCP_VTH_LOW, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_NCP_VTH_LOW),
				   TAIKO_A_NCP_VTH_HIGH, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_NCP_VTH_HIGH),
				   TAIKO_A_NCP_ATEST, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_NCP_ATEST),
				   TAIKO_A_NCP_DTEST, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_NCP_DTEST),
				   TAIKO_A_NCP_DLY1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_NCP_DLY1),
				   TAIKO_A_NCP_DLY2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_NCP_DLY2),
				   TAIKO_A_RX_AUX_SW_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_AUX_SW_CTL),
				   TAIKO_A_RX_PA_AUX_IN_CONN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_PA_AUX_IN_CONN),
				   TAIKO_A_RX_COM_TIMER_DIV, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_COM_TIMER_DIV),
				   TAIKO_A_RX_COM_OCP_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_COM_OCP_CTL),
				   TAIKO_A_RX_COM_OCP_COUNT, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_COM_OCP_COUNT),
				   TAIKO_A_RX_COM_DAC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_COM_DAC_CTL),
				   TAIKO_A_RX_COM_BIAS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_COM_BIAS),
				   TAIKO_A_RX_HPH_AUTO_CHOP, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_AUTO_CHOP),
				   TAIKO_A_RX_HPH_CHOP_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_CHOP_CTL),
				   TAIKO_A_RX_HPH_BIAS_PA, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_BIAS_PA),
				   TAIKO_A_RX_HPH_BIAS_LDO, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_BIAS_LDO),
				   TAIKO_A_RX_HPH_BIAS_CNP, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_BIAS_CNP),
				   TAIKO_A_RX_HPH_BIAS_WG_OCP, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_BIAS_WG_OCP),
				   TAIKO_A_RX_HPH_OCP_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_OCP_CTL),
				   TAIKO_A_RX_HPH_CNP_EN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_CNP_EN),
				   TAIKO_A_RX_HPH_CNP_WG_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_CNP_WG_CTL),
				   TAIKO_A_RX_HPH_CNP_WG_TIME, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_CNP_WG_TIME),
				   TAIKO_A_RX_HPH_L_GAIN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_L_GAIN),
				   TAIKO_A_RX_HPH_L_TEST, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_L_TEST),
				   TAIKO_A_RX_HPH_L_PA_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_L_PA_CTL),
				   TAIKO_A_RX_HPH_L_DAC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_L_DAC_CTL),
				   TAIKO_A_RX_HPH_L_ATEST, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_L_ATEST),
				   TAIKO_A_RX_HPH_L_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_L_STATUS),
				   TAIKO_A_RX_HPH_R_GAIN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_R_GAIN),
				   TAIKO_A_RX_HPH_R_TEST, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_R_TEST),
				   TAIKO_A_RX_HPH_R_PA_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_R_PA_CTL),
				   TAIKO_A_RX_HPH_R_DAC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_R_DAC_CTL),
				   TAIKO_A_RX_HPH_R_ATEST, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_R_ATEST),
				   TAIKO_A_RX_HPH_R_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_HPH_R_STATUS),
				   TAIKO_A_RX_EAR_BIAS_PA, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_EAR_BIAS_PA),
				   TAIKO_A_RX_EAR_BIAS_CMBUFF, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_EAR_BIAS_CMBUFF),
				   TAIKO_A_RX_EAR_EN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_EAR_EN),
				   TAIKO_A_RX_EAR_GAIN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_EAR_GAIN),
				   TAIKO_A_RX_EAR_CMBUFF, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_EAR_CMBUFF),
				   TAIKO_A_RX_EAR_ICTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_EAR_ICTL),
				   TAIKO_A_RX_EAR_CCOMP, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_EAR_CCOMP),
				   TAIKO_A_RX_EAR_VCM, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_EAR_VCM),
				   TAIKO_A_RX_EAR_CNP, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_EAR_CNP),
				   TAIKO_A_RX_EAR_DAC_CTL_ATEST, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_EAR_DAC_CTL_ATEST),
				   TAIKO_A_RX_EAR_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_EAR_STATUS),
				   TAIKO_A_RX_LINE_BIAS_PA, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_BIAS_PA),
				   TAIKO_A_RX_BUCK_BIAS1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_BUCK_BIAS1),
				   TAIKO_A_RX_BUCK_BIAS2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_BUCK_BIAS2),
				   TAIKO_A_RX_LINE_COM, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_COM),
				   TAIKO_A_RX_LINE_CNP_EN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_CNP_EN),
				   TAIKO_A_RX_LINE_CNP_WG_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_CNP_WG_CTL),
				   TAIKO_A_RX_LINE_CNP_WG_TIME, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_CNP_WG_TIME),
				   TAIKO_A_RX_LINE_1_GAIN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_1_GAIN),
				   TAIKO_A_RX_LINE_1_TEST, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_1_TEST),
				   TAIKO_A_RX_LINE_1_DAC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_1_DAC_CTL),
				   TAIKO_A_RX_LINE_1_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_1_STATUS),
				   TAIKO_A_RX_LINE_2_GAIN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_2_GAIN),
				   TAIKO_A_RX_LINE_2_TEST, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_2_TEST),
				   TAIKO_A_RX_LINE_2_DAC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_2_DAC_CTL),
				   TAIKO_A_RX_LINE_2_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_2_STATUS),
				   TAIKO_A_RX_LINE_3_GAIN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_3_GAIN),
				   TAIKO_A_RX_LINE_3_TEST, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_3_TEST),
				   TAIKO_A_RX_LINE_3_DAC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_3_DAC_CTL),
				   TAIKO_A_RX_LINE_3_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_3_STATUS),
				   TAIKO_A_RX_LINE_4_GAIN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_4_GAIN),
				   TAIKO_A_RX_LINE_4_TEST, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_4_TEST),
				   TAIKO_A_RX_LINE_4_DAC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_4_DAC_CTL),
				   TAIKO_A_RX_LINE_4_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_4_STATUS),
				   TAIKO_A_RX_LINE_CNP_DBG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RX_LINE_CNP_DBG),
				   TAIKO_A_SPKR_DRV_EN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_DRV_EN),
				   TAIKO_A_SPKR_DRV_GAIN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_DRV_GAIN),
				   TAIKO_A_SPKR_DRV_DAC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_DRV_DAC_CTL),
				   TAIKO_A_SPKR_DRV_OCP_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_DRV_OCP_CTL),
				   TAIKO_A_SPKR_DRV_CLIP_DET, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_DRV_CLIP_DET),
				   TAIKO_A_SPKR_DRV_IEC, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_DRV_IEC),
				   TAIKO_A_SPKR_DRV_DBG_DAC, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_DRV_DBG_DAC),
				   TAIKO_A_SPKR_DRV_DBG_PA, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_DRV_DBG_PA),
				   TAIKO_A_SPKR_DRV_DBG_PWRSTG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_DRV_DBG_PWRSTG),
				   TAIKO_A_SPKR_DRV_BIAS_LDO, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_DRV_BIAS_LDO),
				   TAIKO_A_SPKR_DRV_BIAS_INT, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_DRV_BIAS_INT),
				   TAIKO_A_SPKR_DRV_BIAS_PA, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_DRV_BIAS_PA),
				   TAIKO_A_SPKR_DRV_STATUS_OCP, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_DRV_STATUS_OCP),
				   TAIKO_A_SPKR_DRV_STATUS_PA, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_DRV_STATUS_PA),
				   TAIKO_A_SPKR_PROT_EN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_PROT_EN),
				   TAIKO_A_SPKR_PROT_ADC_EN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_PROT_ADC_EN),
				   TAIKO_A_SPKR_PROT_ISENSE_BIAS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_PROT_ISENSE_BIAS),
				   TAIKO_A_SPKR_PROT_VSENSE_BIAS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_PROT_VSENSE_BIAS),
				   TAIKO_A_SPKR_PROT_ADC_ATEST_REFCTRL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_PROT_ADC_ATEST_REFCTRL),
				   TAIKO_A_SPKR_PROT_ADC_TEST_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_PROT_ADC_TEST_CTL),
				   TAIKO_A_SPKR_PROT_TEST_BLOCK_EN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_PROT_TEST_BLOCK_EN),
				   TAIKO_A_SPKR_PROT_ATEST, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_PROT_ATEST),
				   TAIKO_A_SPKR_PROT_V_SAR_ERR, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_PROT_V_SAR_ERR),
				   TAIKO_A_SPKR_PROT_I_SAR_ERR, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_PROT_I_SAR_ERR),
				   TAIKO_A_SPKR_PROT_LDO_CTRL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_PROT_LDO_CTRL),
				   TAIKO_A_SPKR_PROT_ISENSE_CTRL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_PROT_ISENSE_CTRL),
				   TAIKO_A_SPKR_PROT_VSENSE_CTRL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_SPKR_PROT_VSENSE_CTRL),
				   TAIKO_A_RC_OSC_FREQ, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RC_OSC_FREQ),
				   TAIKO_A_RC_OSC_TEST, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RC_OSC_TEST),
				   TAIKO_A_RC_OSC_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RC_OSC_STATUS),
				   TAIKO_A_RC_OSC_TUNER, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_RC_OSC_TUNER),
				   TAIKO_A_MBHC_HPH, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_MBHC_HPH),
				   TAIKO_A_CDC_ANC1_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC1_B1_CTL),
				   TAIKO_A_CDC_ANC2_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC2_B1_CTL),
				   TAIKO_A_CDC_ANC1_SHIFT, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC1_SHIFT),
				   TAIKO_A_CDC_ANC2_SHIFT, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC2_SHIFT),
				   TAIKO_A_CDC_ANC1_IIR_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC1_IIR_B1_CTL),
				   TAIKO_A_CDC_ANC2_IIR_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC2_IIR_B1_CTL),
				   TAIKO_A_CDC_ANC1_IIR_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC1_IIR_B2_CTL),
				   TAIKO_A_CDC_ANC2_IIR_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC2_IIR_B2_CTL),
				   TAIKO_A_CDC_ANC1_IIR_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC1_IIR_B3_CTL),
				   TAIKO_A_CDC_ANC2_IIR_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC2_IIR_B3_CTL),
				   TAIKO_A_CDC_ANC1_LPF_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC1_LPF_B1_CTL),
				   TAIKO_A_CDC_ANC2_LPF_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC2_LPF_B1_CTL),
				   TAIKO_A_CDC_ANC1_LPF_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC1_LPF_B2_CTL),
				   TAIKO_A_CDC_ANC2_LPF_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC2_LPF_B2_CTL),
				   TAIKO_A_CDC_ANC1_SPARE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC1_SPARE),
				   TAIKO_A_CDC_ANC2_SPARE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC2_SPARE),
				   TAIKO_A_CDC_ANC1_SMLPF_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC1_SMLPF_CTL),
				   TAIKO_A_CDC_ANC2_SMLPF_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC2_SMLPF_CTL),
				   TAIKO_A_CDC_ANC1_DCFLT_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC1_DCFLT_CTL),
				   TAIKO_A_CDC_ANC2_DCFLT_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC2_DCFLT_CTL),
				   TAIKO_A_CDC_ANC1_GAIN_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC1_GAIN_CTL),
				   TAIKO_A_CDC_ANC2_GAIN_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC2_GAIN_CTL),
				   TAIKO_A_CDC_ANC1_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC1_B2_CTL),
				   TAIKO_A_CDC_ANC2_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_ANC2_B2_CTL),
				   TAIKO_A_CDC_TX1_VOL_CTL_TIMER, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX1_VOL_CTL_TIMER),
				   TAIKO_A_CDC_TX2_VOL_CTL_TIMER, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX2_VOL_CTL_TIMER),
				   TAIKO_A_CDC_TX3_VOL_CTL_TIMER, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX3_VOL_CTL_TIMER),
				   TAIKO_A_CDC_TX4_VOL_CTL_TIMER, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX4_VOL_CTL_TIMER),
				   TAIKO_A_CDC_TX5_VOL_CTL_TIMER, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX5_VOL_CTL_TIMER),
				   TAIKO_A_CDC_TX6_VOL_CTL_TIMER, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX6_VOL_CTL_TIMER),
				   TAIKO_A_CDC_TX7_VOL_CTL_TIMER, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX7_VOL_CTL_TIMER),
				   TAIKO_A_CDC_TX8_VOL_CTL_TIMER, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX8_VOL_CTL_TIMER),
				   TAIKO_A_CDC_TX9_VOL_CTL_TIMER, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX9_VOL_CTL_TIMER),
				   TAIKO_A_CDC_TX10_VOL_CTL_TIMER, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX10_VOL_CTL_TIMER),
				   TAIKO_A_CDC_TX1_VOL_CTL_GAIN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX1_VOL_CTL_GAIN),
				   TAIKO_A_CDC_TX2_VOL_CTL_GAIN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX2_VOL_CTL_GAIN),
				   TAIKO_A_CDC_TX3_VOL_CTL_GAIN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX3_VOL_CTL_GAIN),
				   TAIKO_A_CDC_TX4_VOL_CTL_GAIN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX4_VOL_CTL_GAIN),
				   TAIKO_A_CDC_TX5_VOL_CTL_GAIN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX5_VOL_CTL_GAIN),
				   TAIKO_A_CDC_TX6_VOL_CTL_GAIN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX6_VOL_CTL_GAIN),
				   TAIKO_A_CDC_TX7_VOL_CTL_GAIN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX7_VOL_CTL_GAIN),
				   TAIKO_A_CDC_TX8_VOL_CTL_GAIN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX8_VOL_CTL_GAIN),
				   TAIKO_A_CDC_TX9_VOL_CTL_GAIN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX9_VOL_CTL_GAIN),
				   TAIKO_A_CDC_TX10_VOL_CTL_GAIN, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX10_VOL_CTL_GAIN),
				   TAIKO_A_CDC_TX1_VOL_CTL_CFG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX1_VOL_CTL_CFG),
				   TAIKO_A_CDC_TX2_VOL_CTL_CFG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX2_VOL_CTL_CFG),
				   TAIKO_A_CDC_TX3_VOL_CTL_CFG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX3_VOL_CTL_CFG),
				   TAIKO_A_CDC_TX4_VOL_CTL_CFG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX4_VOL_CTL_CFG),
				   TAIKO_A_CDC_TX5_VOL_CTL_CFG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX5_VOL_CTL_CFG),
				   TAIKO_A_CDC_TX6_VOL_CTL_CFG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX6_VOL_CTL_CFG),
				   TAIKO_A_CDC_TX7_VOL_CTL_CFG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX7_VOL_CTL_CFG),
				   TAIKO_A_CDC_TX8_VOL_CTL_CFG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX8_VOL_CTL_CFG),
				   TAIKO_A_CDC_TX9_VOL_CTL_CFG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX9_VOL_CTL_CFG),
				   TAIKO_A_CDC_TX10_VOL_CTL_CFG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX10_VOL_CTL_CFG),
				   TAIKO_A_CDC_TX1_MUX_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX1_MUX_CTL),
				   TAIKO_A_CDC_TX2_MUX_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX2_MUX_CTL),
				   TAIKO_A_CDC_TX3_MUX_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX3_MUX_CTL),
				   TAIKO_A_CDC_TX4_MUX_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX4_MUX_CTL),
				   TAIKO_A_CDC_TX5_MUX_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX5_MUX_CTL),
				   TAIKO_A_CDC_TX6_MUX_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX6_MUX_CTL),
				   TAIKO_A_CDC_TX7_MUX_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX7_MUX_CTL),
				   TAIKO_A_CDC_TX8_MUX_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX8_MUX_CTL),
				   TAIKO_A_CDC_TX9_MUX_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX9_MUX_CTL),
				   TAIKO_A_CDC_TX10_MUX_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX10_MUX_CTL),
				   TAIKO_A_CDC_TX1_CLK_FS_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX1_CLK_FS_CTL),
				   TAIKO_A_CDC_TX2_CLK_FS_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX2_CLK_FS_CTL),
				   TAIKO_A_CDC_TX3_CLK_FS_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX3_CLK_FS_CTL),
				   TAIKO_A_CDC_TX4_CLK_FS_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX4_CLK_FS_CTL),
				   TAIKO_A_CDC_TX5_CLK_FS_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX5_CLK_FS_CTL),
				   TAIKO_A_CDC_TX6_CLK_FS_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX6_CLK_FS_CTL),
				   TAIKO_A_CDC_TX7_CLK_FS_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX7_CLK_FS_CTL),
				   TAIKO_A_CDC_TX8_CLK_FS_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX8_CLK_FS_CTL),
				   TAIKO_A_CDC_TX9_CLK_FS_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX9_CLK_FS_CTL),
				   TAIKO_A_CDC_TX10_CLK_FS_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX10_CLK_FS_CTL),
				   TAIKO_A_CDC_TX1_DMIC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX1_DMIC_CTL),
				   TAIKO_A_CDC_TX2_DMIC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX2_DMIC_CTL),
				   TAIKO_A_CDC_TX3_DMIC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX3_DMIC_CTL),
				   TAIKO_A_CDC_TX4_DMIC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX4_DMIC_CTL),
				   TAIKO_A_CDC_TX5_DMIC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX5_DMIC_CTL),
				   TAIKO_A_CDC_TX6_DMIC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX6_DMIC_CTL),
				   TAIKO_A_CDC_TX7_DMIC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX7_DMIC_CTL),
				   TAIKO_A_CDC_TX8_DMIC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX8_DMIC_CTL),
				   TAIKO_A_CDC_TX9_DMIC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX9_DMIC_CTL),
				   TAIKO_A_CDC_TX10_DMIC_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TX10_DMIC_CTL),
				   TAIKO_A_CDC_DEBUG_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_DEBUG_B1_CTL),
				   TAIKO_A_CDC_DEBUG_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_DEBUG_B2_CTL),
				   TAIKO_A_CDC_DEBUG_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_DEBUG_B3_CTL),
				   TAIKO_A_CDC_DEBUG_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_DEBUG_B4_CTL),
				   TAIKO_A_CDC_DEBUG_B5_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_DEBUG_B5_CTL),
				   TAIKO_A_CDC_DEBUG_B6_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_DEBUG_B6_CTL),
				   TAIKO_A_CDC_DEBUG_B7_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_DEBUG_B7_CTL),
				   TAIKO_A_CDC_SRC1_PDA_CFG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_SRC1_PDA_CFG),
				   TAIKO_A_CDC_SRC2_PDA_CFG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_SRC2_PDA_CFG),
				   TAIKO_A_CDC_SRC1_FS_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_SRC1_FS_CTL),
				   TAIKO_A_CDC_SRC2_FS_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_SRC2_FS_CTL),
				   TAIKO_A_CDC_RX1_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX1_B1_CTL),
				   TAIKO_A_CDC_RX2_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX2_B1_CTL),
				   TAIKO_A_CDC_RX3_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX3_B1_CTL),
				   TAIKO_A_CDC_RX4_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX4_B1_CTL),
				   TAIKO_A_CDC_RX5_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX5_B1_CTL),
				   TAIKO_A_CDC_RX6_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX6_B1_CTL),
				   TAIKO_A_CDC_RX7_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX7_B1_CTL),
				   TAIKO_A_CDC_RX1_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX1_B2_CTL),
				   TAIKO_A_CDC_RX2_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX2_B2_CTL),
				   TAIKO_A_CDC_RX3_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX3_B2_CTL),
				   TAIKO_A_CDC_RX4_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX4_B2_CTL),
				   TAIKO_A_CDC_RX5_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX5_B2_CTL),
				   TAIKO_A_CDC_RX6_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX6_B2_CTL),
				   TAIKO_A_CDC_RX7_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX7_B2_CTL),
				   TAIKO_A_CDC_RX1_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX1_B3_CTL),
				   TAIKO_A_CDC_RX2_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX2_B3_CTL),
				   TAIKO_A_CDC_RX3_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX3_B3_CTL),
				   TAIKO_A_CDC_RX4_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX4_B3_CTL),
				   TAIKO_A_CDC_RX5_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX5_B3_CTL),
				   TAIKO_A_CDC_RX6_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX6_B3_CTL),
				   TAIKO_A_CDC_RX7_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX7_B3_CTL),
				   TAIKO_A_CDC_RX1_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX1_B4_CTL),
				   TAIKO_A_CDC_RX2_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX2_B4_CTL),
				   TAIKO_A_CDC_RX3_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX3_B4_CTL),
				   TAIKO_A_CDC_RX4_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX4_B4_CTL),
				   TAIKO_A_CDC_RX5_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX5_B4_CTL),
				   TAIKO_A_CDC_RX6_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX6_B4_CTL),
				   TAIKO_A_CDC_RX7_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX7_B4_CTL),
				   TAIKO_A_CDC_RX1_B5_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX1_B5_CTL),
				   TAIKO_A_CDC_RX2_B5_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX2_B5_CTL),
				   TAIKO_A_CDC_RX3_B5_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX3_B5_CTL),
				   TAIKO_A_CDC_RX4_B5_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX4_B5_CTL),
				   TAIKO_A_CDC_RX5_B5_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX5_B5_CTL),
				   TAIKO_A_CDC_RX6_B5_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX6_B5_CTL),
				   TAIKO_A_CDC_RX7_B5_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX7_B5_CTL),
				   TAIKO_A_CDC_RX1_B6_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX1_B6_CTL),
				   TAIKO_A_CDC_RX2_B6_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX2_B6_CTL),
				   TAIKO_A_CDC_RX3_B6_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX3_B6_CTL),
				   TAIKO_A_CDC_RX4_B6_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX4_B6_CTL),
				   TAIKO_A_CDC_RX5_B6_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX5_B6_CTL),
				   TAIKO_A_CDC_RX6_B6_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX6_B6_CTL),
				   TAIKO_A_CDC_RX7_B6_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX7_B6_CTL),
				   TAIKO_A_CDC_RX1_VOL_CTL_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX1_VOL_CTL_B1_CTL),
				   TAIKO_A_CDC_RX2_VOL_CTL_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX2_VOL_CTL_B1_CTL),
				   TAIKO_A_CDC_RX3_VOL_CTL_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX3_VOL_CTL_B1_CTL),
				   TAIKO_A_CDC_RX4_VOL_CTL_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX4_VOL_CTL_B1_CTL),
				   TAIKO_A_CDC_RX5_VOL_CTL_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX5_VOL_CTL_B1_CTL),
				   TAIKO_A_CDC_RX6_VOL_CTL_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX6_VOL_CTL_B1_CTL),
				   TAIKO_A_CDC_RX7_VOL_CTL_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX7_VOL_CTL_B1_CTL),
				   TAIKO_A_CDC_RX1_VOL_CTL_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX1_VOL_CTL_B2_CTL),
				   TAIKO_A_CDC_RX2_VOL_CTL_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX2_VOL_CTL_B2_CTL),
				   TAIKO_A_CDC_RX3_VOL_CTL_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX3_VOL_CTL_B2_CTL),
				   TAIKO_A_CDC_RX4_VOL_CTL_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX4_VOL_CTL_B2_CTL),
				   TAIKO_A_CDC_RX5_VOL_CTL_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX5_VOL_CTL_B2_CTL),
				   TAIKO_A_CDC_RX6_VOL_CTL_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX6_VOL_CTL_B2_CTL),
				   TAIKO_A_CDC_RX7_VOL_CTL_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_RX7_VOL_CTL_B2_CTL),
				   TAIKO_A_CDC_VBAT_CFG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_VBAT_CFG),
				   TAIKO_A_CDC_VBAT_ADC_CAL1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_VBAT_ADC_CAL1),
				   TAIKO_A_CDC_VBAT_ADC_CAL2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_VBAT_ADC_CAL2),
				   TAIKO_A_CDC_VBAT_ADC_CAL3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_VBAT_ADC_CAL3),
				   TAIKO_A_CDC_VBAT_PK_EST1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_VBAT_PK_EST1),
				   TAIKO_A_CDC_VBAT_PK_EST2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_VBAT_PK_EST2),
				   TAIKO_A_CDC_VBAT_PK_EST3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_VBAT_PK_EST3),
				   TAIKO_A_CDC_VBAT_RF_PROC1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_VBAT_RF_PROC1),
				   TAIKO_A_CDC_VBAT_RF_PROC2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_VBAT_RF_PROC2),
				   TAIKO_A_CDC_VBAT_TAC1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_VBAT_TAC1),
				   TAIKO_A_CDC_VBAT_TAC2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_VBAT_TAC2),
				   TAIKO_A_CDC_VBAT_TAC3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_VBAT_TAC3),
				   TAIKO_A_CDC_VBAT_TAC4, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_VBAT_TAC4),
				   TAIKO_A_CDC_VBAT_GAIN_UPD1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_VBAT_GAIN_UPD1),
				   TAIKO_A_CDC_VBAT_GAIN_UPD2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_VBAT_GAIN_UPD2),
				   TAIKO_A_CDC_VBAT_GAIN_UPD3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_VBAT_GAIN_UPD3),
				   TAIKO_A_CDC_VBAT_GAIN_UPD4, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_VBAT_GAIN_UPD4),
				   TAIKO_A_CDC_VBAT_DEBUG1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_VBAT_DEBUG1),
				   TAIKO_A_CDC_CLK_ANC_RESET_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_ANC_RESET_CTL),
				   TAIKO_A_CDC_CLK_RX_RESET_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_RX_RESET_CTL),
				   TAIKO_A_CDC_CLK_TX_RESET_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_TX_RESET_B1_CTL),
				   TAIKO_A_CDC_CLK_TX_RESET_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_TX_RESET_B2_CTL),
				   TAIKO_A_CDC_CLK_DMIC_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_DMIC_B1_CTL),
				   TAIKO_A_CDC_CLK_DMIC_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_DMIC_B2_CTL),
				   TAIKO_A_CDC_CLK_RX_I2S_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_RX_I2S_CTL),
				   TAIKO_A_CDC_CLK_TX_I2S_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_TX_I2S_CTL),
				   TAIKO_A_CDC_CLK_OTHR_RESET_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_OTHR_RESET_B1_CTL),
				   TAIKO_A_CDC_CLK_OTHR_RESET_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_OTHR_RESET_B2_CTL),
				   TAIKO_A_CDC_CLK_TX_CLK_EN_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_TX_CLK_EN_B1_CTL),
				   TAIKO_A_CDC_CLK_TX_CLK_EN_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_TX_CLK_EN_B2_CTL),
				   TAIKO_A_CDC_CLK_OTHR_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_OTHR_CTL),
				   TAIKO_A_CDC_CLK_RDAC_CLK_EN_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_RDAC_CLK_EN_CTL),
				   TAIKO_A_CDC_CLK_ANC_CLK_EN_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_ANC_CLK_EN_CTL),
				   TAIKO_A_CDC_CLK_RX_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_RX_B1_CTL),
				   TAIKO_A_CDC_CLK_RX_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_RX_B2_CTL),
				   TAIKO_A_CDC_CLK_MCLK_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_MCLK_CTL),
				   TAIKO_A_CDC_CLK_PDM_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_PDM_CTL),
				   TAIKO_A_CDC_CLK_SD_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_SD_CTL),
				   TAIKO_A_CDC_CLK_POWER_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLK_POWER_CTL),
				   TAIKO_A_CDC_CLSH_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLSH_B1_CTL),
				   TAIKO_A_CDC_CLSH_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLSH_B2_CTL),
				   TAIKO_A_CDC_CLSH_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLSH_B3_CTL),
				   TAIKO_A_CDC_CLSH_BUCK_NCP_VARS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLSH_BUCK_NCP_VARS),
				   TAIKO_A_CDC_CLSH_IDLE_HPH_THSD, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLSH_IDLE_HPH_THSD),
				   TAIKO_A_CDC_CLSH_IDLE_EAR_THSD, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLSH_IDLE_EAR_THSD),
				   TAIKO_A_CDC_CLSH_FCLKONLY_HPH_THSD, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLSH_FCLKONLY_HPH_THSD),
				   TAIKO_A_CDC_CLSH_FCLKONLY_EAR_THSD, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLSH_FCLKONLY_EAR_THSD),
				   TAIKO_A_CDC_CLSH_K_ADDR, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLSH_K_ADDR),
				   TAIKO_A_CDC_CLSH_K_DATA, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLSH_K_DATA),
				   TAIKO_A_CDC_CLSH_I_PA_FACT_HPH_L, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLSH_I_PA_FACT_HPH_L),
				   TAIKO_A_CDC_CLSH_I_PA_FACT_HPH_U, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLSH_I_PA_FACT_HPH_U),
				   TAIKO_A_CDC_CLSH_I_PA_FACT_EAR_L, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLSH_I_PA_FACT_EAR_L),
				   TAIKO_A_CDC_CLSH_I_PA_FACT_EAR_U, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLSH_I_PA_FACT_EAR_U),
				   TAIKO_A_CDC_CLSH_V_PA_HD_EAR, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLSH_V_PA_HD_EAR),
				   TAIKO_A_CDC_CLSH_V_PA_HD_HPH, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLSH_V_PA_HD_HPH),
				   TAIKO_A_CDC_CLSH_V_PA_MIN_EAR, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLSH_V_PA_MIN_EAR),
				   TAIKO_A_CDC_CLSH_V_PA_MIN_HPH, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CLSH_V_PA_MIN_HPH),
				   TAIKO_A_CDC_IIR1_GAIN_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR1_GAIN_B1_CTL),
				   TAIKO_A_CDC_IIR2_GAIN_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR2_GAIN_B1_CTL),
				   TAIKO_A_CDC_IIR1_GAIN_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR1_GAIN_B2_CTL),
				   TAIKO_A_CDC_IIR2_GAIN_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR2_GAIN_B2_CTL),
				   TAIKO_A_CDC_IIR1_GAIN_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR1_GAIN_B3_CTL),
				   TAIKO_A_CDC_IIR2_GAIN_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR2_GAIN_B3_CTL),
				   TAIKO_A_CDC_IIR1_GAIN_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR1_GAIN_B4_CTL),
				   TAIKO_A_CDC_IIR2_GAIN_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR2_GAIN_B4_CTL),
				   TAIKO_A_CDC_IIR1_GAIN_B5_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR1_GAIN_B5_CTL),
				   TAIKO_A_CDC_IIR2_GAIN_B5_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR2_GAIN_B5_CTL),
				   TAIKO_A_CDC_IIR1_GAIN_B6_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR1_GAIN_B6_CTL),
				   TAIKO_A_CDC_IIR2_GAIN_B6_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR2_GAIN_B6_CTL),
				   TAIKO_A_CDC_IIR1_GAIN_B7_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR1_GAIN_B7_CTL),
				   TAIKO_A_CDC_IIR2_GAIN_B7_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR2_GAIN_B7_CTL),
				   TAIKO_A_CDC_IIR1_GAIN_B8_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR1_GAIN_B8_CTL),
				   TAIKO_A_CDC_IIR2_GAIN_B8_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR2_GAIN_B8_CTL),
				   TAIKO_A_CDC_IIR1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR1_CTL),
				   TAIKO_A_CDC_IIR2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR2_CTL),
				   TAIKO_A_CDC_IIR1_GAIN_TIMER_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR1_GAIN_TIMER_CTL),
				   TAIKO_A_CDC_IIR2_GAIN_TIMER_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR2_GAIN_TIMER_CTL),
				   TAIKO_A_CDC_IIR1_COEF_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR1_COEF_B1_CTL),
				   TAIKO_A_CDC_IIR2_COEF_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR2_COEF_B1_CTL),
				   TAIKO_A_CDC_IIR1_COEF_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR1_COEF_B2_CTL),
				   TAIKO_A_CDC_IIR2_COEF_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_IIR2_COEF_B2_CTL),
				   TAIKO_A_CDC_TOP_GAIN_UPDATE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_TOP_GAIN_UPDATE),
				   TAIKO_A_CDC_COMP0_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP0_B1_CTL),
				   TAIKO_A_CDC_COMP1_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP1_B1_CTL),
				   TAIKO_A_CDC_COMP2_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP2_B1_CTL),
				   TAIKO_A_CDC_COMP0_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP0_B2_CTL),
				   TAIKO_A_CDC_COMP1_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP1_B2_CTL),
				   TAIKO_A_CDC_COMP2_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP2_B2_CTL),
				   TAIKO_A_CDC_COMP0_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP0_B3_CTL),
				   TAIKO_A_CDC_COMP1_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP1_B3_CTL),
				   TAIKO_A_CDC_COMP2_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP2_B3_CTL),
				   TAIKO_A_CDC_COMP0_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP0_B4_CTL),
				   TAIKO_A_CDC_COMP1_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP1_B4_CTL),
				   TAIKO_A_CDC_COMP2_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP2_B4_CTL),
				   TAIKO_A_CDC_COMP0_B5_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP0_B5_CTL),
				   TAIKO_A_CDC_COMP1_B5_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP1_B5_CTL),
				   TAIKO_A_CDC_COMP2_B5_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP2_B5_CTL),
				   TAIKO_A_CDC_COMP0_B6_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP0_B6_CTL),
				   TAIKO_A_CDC_COMP1_B6_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP1_B6_CTL),
				   TAIKO_A_CDC_COMP2_B6_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP2_B6_CTL),
				   TAIKO_A_CDC_COMP0_SHUT_DOWN_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP0_SHUT_DOWN_STATUS),
				   TAIKO_A_CDC_COMP1_SHUT_DOWN_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP1_SHUT_DOWN_STATUS),
				   TAIKO_A_CDC_COMP2_SHUT_DOWN_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP2_SHUT_DOWN_STATUS),
				   TAIKO_A_CDC_COMP0_FS_CFG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP0_FS_CFG),
				   TAIKO_A_CDC_COMP1_FS_CFG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP1_FS_CFG),
				   TAIKO_A_CDC_COMP2_FS_CFG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_COMP2_FS_CFG),
				   TAIKO_A_CDC_CONN_RX1_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX1_B1_CTL),
				   TAIKO_A_CDC_CONN_RX1_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX1_B2_CTL),
				   TAIKO_A_CDC_CONN_RX1_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX1_B3_CTL),
				   TAIKO_A_CDC_CONN_RX2_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX2_B1_CTL),
				   TAIKO_A_CDC_CONN_RX2_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX2_B2_CTL),
				   TAIKO_A_CDC_CONN_RX2_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX2_B3_CTL),
				   TAIKO_A_CDC_CONN_RX3_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX3_B1_CTL),
				   TAIKO_A_CDC_CONN_RX3_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX3_B2_CTL),
				   TAIKO_A_CDC_CONN_RX4_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX4_B1_CTL),
				   TAIKO_A_CDC_CONN_RX4_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX4_B2_CTL),
				   TAIKO_A_CDC_CONN_RX5_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX5_B1_CTL),
				   TAIKO_A_CDC_CONN_RX5_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX5_B2_CTL),
				   TAIKO_A_CDC_CONN_RX6_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX6_B1_CTL),
				   TAIKO_A_CDC_CONN_RX6_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX6_B2_CTL),
				   TAIKO_A_CDC_CONN_RX7_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX7_B1_CTL),
				   TAIKO_A_CDC_CONN_RX7_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX7_B2_CTL),
				   TAIKO_A_CDC_CONN_RX7_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX7_B3_CTL),
				   TAIKO_A_CDC_CONN_ANC_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_ANC_B1_CTL),
				   TAIKO_A_CDC_CONN_ANC_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_ANC_B2_CTL),
				   TAIKO_A_CDC_CONN_TX_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_TX_B1_CTL),
				   TAIKO_A_CDC_CONN_TX_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_TX_B2_CTL),
				   TAIKO_A_CDC_CONN_TX_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_TX_B3_CTL),
				   TAIKO_A_CDC_CONN_TX_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_TX_B4_CTL),
				   TAIKO_A_CDC_CONN_EQ1_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_EQ1_B1_CTL),
				   TAIKO_A_CDC_CONN_EQ1_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_EQ1_B2_CTL),
				   TAIKO_A_CDC_CONN_EQ1_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_EQ1_B3_CTL),
				   TAIKO_A_CDC_CONN_EQ1_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_EQ1_B4_CTL),
				   TAIKO_A_CDC_CONN_EQ2_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_EQ2_B1_CTL),
				   TAIKO_A_CDC_CONN_EQ2_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_EQ2_B2_CTL),
				   TAIKO_A_CDC_CONN_EQ2_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_EQ2_B3_CTL),
				   TAIKO_A_CDC_CONN_EQ2_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_EQ2_B4_CTL),
				   TAIKO_A_CDC_CONN_SRC1_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_SRC1_B1_CTL),
				   TAIKO_A_CDC_CONN_SRC1_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_SRC1_B2_CTL),
				   TAIKO_A_CDC_CONN_SRC2_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_SRC2_B1_CTL),
				   TAIKO_A_CDC_CONN_SRC2_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_SRC2_B2_CTL),
				   TAIKO_A_CDC_CONN_TX_SB_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_TX_SB_B1_CTL),
				   TAIKO_A_CDC_CONN_TX_SB_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_TX_SB_B2_CTL),
				   TAIKO_A_CDC_CONN_TX_SB_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_TX_SB_B3_CTL),
				   TAIKO_A_CDC_CONN_TX_SB_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_TX_SB_B4_CTL),
				   TAIKO_A_CDC_CONN_TX_SB_B5_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_TX_SB_B5_CTL),
				   TAIKO_A_CDC_CONN_TX_SB_B6_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_TX_SB_B6_CTL),
				   TAIKO_A_CDC_CONN_TX_SB_B7_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_TX_SB_B7_CTL),
				   TAIKO_A_CDC_CONN_TX_SB_B8_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_TX_SB_B8_CTL),
				   TAIKO_A_CDC_CONN_TX_SB_B9_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_TX_SB_B9_CTL),
				   TAIKO_A_CDC_CONN_TX_SB_B10_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_TX_SB_B10_CTL),
				   TAIKO_A_CDC_CONN_TX_SB_B11_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_TX_SB_B11_CTL),
				   TAIKO_A_CDC_CONN_RX_SB_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX_SB_B1_CTL),
				   TAIKO_A_CDC_CONN_RX_SB_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_RX_SB_B2_CTL),
				   TAIKO_A_CDC_CONN_CLSH_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_CLSH_CTL),
				   TAIKO_A_CDC_CONN_MISC, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_MISC),
				   TAIKO_A_CDC_CONN_MAD, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_CONN_MAD),
				   TAIKO_A_CDC_MBHC_EN_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_EN_CTL),
				   TAIKO_A_CDC_MBHC_FIR_B1_CFG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_FIR_B1_CFG),
				   TAIKO_A_CDC_MBHC_FIR_B2_CFG, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_FIR_B2_CFG),
				   TAIKO_A_CDC_MBHC_TIMER_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_TIMER_B1_CTL),
				   TAIKO_A_CDC_MBHC_TIMER_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_TIMER_B2_CTL),
				   TAIKO_A_CDC_MBHC_TIMER_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_TIMER_B3_CTL),
				   TAIKO_A_CDC_MBHC_TIMER_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_TIMER_B4_CTL),
				   TAIKO_A_CDC_MBHC_TIMER_B5_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_TIMER_B5_CTL),
				   TAIKO_A_CDC_MBHC_TIMER_B6_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_TIMER_B6_CTL),
				   TAIKO_A_CDC_MBHC_B1_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_B1_STATUS),
				   TAIKO_A_CDC_MBHC_B2_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_B2_STATUS),
				   TAIKO_A_CDC_MBHC_B3_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_B3_STATUS),
				   TAIKO_A_CDC_MBHC_B4_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_B4_STATUS),
				   TAIKO_A_CDC_MBHC_B5_STATUS, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_B5_STATUS),
				   TAIKO_A_CDC_MBHC_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_B1_CTL),
				   TAIKO_A_CDC_MBHC_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_B2_CTL),
				   TAIKO_A_CDC_MBHC_VOLT_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_VOLT_B1_CTL),
				   TAIKO_A_CDC_MBHC_VOLT_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_VOLT_B2_CTL),
				   TAIKO_A_CDC_MBHC_VOLT_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_VOLT_B3_CTL),
				   TAIKO_A_CDC_MBHC_VOLT_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_VOLT_B4_CTL),
				   TAIKO_A_CDC_MBHC_VOLT_B5_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_VOLT_B5_CTL),
				   TAIKO_A_CDC_MBHC_VOLT_B6_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_VOLT_B6_CTL),
				   TAIKO_A_CDC_MBHC_VOLT_B7_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_VOLT_B7_CTL),
				   TAIKO_A_CDC_MBHC_VOLT_B8_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_VOLT_B8_CTL),
				   TAIKO_A_CDC_MBHC_VOLT_B9_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_VOLT_B9_CTL),
				   TAIKO_A_CDC_MBHC_VOLT_B10_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_VOLT_B10_CTL),
				   TAIKO_A_CDC_MBHC_VOLT_B11_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_VOLT_B11_CTL),
				   TAIKO_A_CDC_MBHC_VOLT_B12_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_VOLT_B12_CTL),
				   TAIKO_A_CDC_MBHC_CLK_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_CLK_CTL),
				   TAIKO_A_CDC_MBHC_INT_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_INT_CTL),
				   TAIKO_A_CDC_MBHC_DEBUG_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_DEBUG_CTL),
				   TAIKO_A_CDC_MBHC_SPARE, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MBHC_SPARE),
				   TAIKO_A_CDC_MAD_MAIN_CTL_1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_MAIN_CTL_1),
				   TAIKO_A_CDC_MAD_MAIN_CTL_2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_MAIN_CTL_2),
				   TAIKO_A_CDC_MAD_AUDIO_CTL_1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_AUDIO_CTL_1),
				   TAIKO_A_CDC_MAD_AUDIO_CTL_2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_AUDIO_CTL_2),
				   TAIKO_A_CDC_MAD_AUDIO_CTL_3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_AUDIO_CTL_3),
				   TAIKO_A_CDC_MAD_AUDIO_CTL_4, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_AUDIO_CTL_4),
				   TAIKO_A_CDC_MAD_AUDIO_CTL_5, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_AUDIO_CTL_5),
				   TAIKO_A_CDC_MAD_AUDIO_CTL_6, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_AUDIO_CTL_6),
				   TAIKO_A_CDC_MAD_AUDIO_CTL_7, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_AUDIO_CTL_7),
				   TAIKO_A_CDC_MAD_AUDIO_CTL_8, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_AUDIO_CTL_8),
				   TAIKO_A_CDC_MAD_AUDIO_IIR_CTL_PTR, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_AUDIO_IIR_CTL_PTR),
				   TAIKO_A_CDC_MAD_AUDIO_IIR_CTL_VAL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_AUDIO_IIR_CTL_VAL),
				   TAIKO_A_CDC_MAD_ULTR_CTL_1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_ULTR_CTL_1),
				   TAIKO_A_CDC_MAD_ULTR_CTL_2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_ULTR_CTL_2),
				   TAIKO_A_CDC_MAD_ULTR_CTL_3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_ULTR_CTL_3),
				   TAIKO_A_CDC_MAD_ULTR_CTL_4, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_ULTR_CTL_4),
				   TAIKO_A_CDC_MAD_ULTR_CTL_5, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_ULTR_CTL_5),
				   TAIKO_A_CDC_MAD_ULTR_CTL_6, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_ULTR_CTL_6),
				   TAIKO_A_CDC_MAD_ULTR_CTL_7, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_ULTR_CTL_7),
				   TAIKO_A_CDC_MAD_BEACON_CTL_1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_BEACON_CTL_1),
				   TAIKO_A_CDC_MAD_BEACON_CTL_2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_BEACON_CTL_2),
				   TAIKO_A_CDC_MAD_BEACON_CTL_3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_BEACON_CTL_3),
				   TAIKO_A_CDC_MAD_BEACON_CTL_4, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_BEACON_CTL_4),
				   TAIKO_A_CDC_MAD_BEACON_CTL_5, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_BEACON_CTL_5),
				   TAIKO_A_CDC_MAD_BEACON_CTL_6, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_BEACON_CTL_6),
				   TAIKO_A_CDC_MAD_BEACON_CTL_7, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_BEACON_CTL_7),
				   TAIKO_A_CDC_MAD_BEACON_CTL_8, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_BEACON_CTL_8),
				   TAIKO_A_CDC_MAD_BEACON_IIR_CTL_PTR, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_BEACON_IIR_CTL_PTR),
				   TAIKO_A_CDC_MAD_BEACON_IIR_CTL_VAL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_MAD_BEACON_IIR_CTL_VAL),
				   TAIKO_A_CDC_SPKR_CLIPDET_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_SPKR_CLIPDET_B1_CTL),
				   TAIKO_A_CDC_SPKR_CLIPDET_VAL0, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_SPKR_CLIPDET_VAL0),
				   TAIKO_A_CDC_SPKR_CLIPDET_VAL1, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_SPKR_CLIPDET_VAL1),
				   TAIKO_A_CDC_SPKR_CLIPDET_VAL2, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_SPKR_CLIPDET_VAL2),
				   TAIKO_A_CDC_SPKR_CLIPDET_VAL3, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_SPKR_CLIPDET_VAL3),
				   TAIKO_A_CDC_SPKR_CLIPDET_VAL4, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_SPKR_CLIPDET_VAL4),
				   TAIKO_A_CDC_SPKR_CLIPDET_VAL5, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_SPKR_CLIPDET_VAL5),
				   TAIKO_A_CDC_SPKR_CLIPDET_VAL6, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_SPKR_CLIPDET_VAL6),
				   TAIKO_A_CDC_SPKR_CLIPDET_VAL7, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_SPKR_CLIPDET_VAL7),
				   TAIKO_A_CDC_PA_RAMP_B1_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_PA_RAMP_B1_CTL),
				   TAIKO_A_CDC_PA_RAMP_B2_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_PA_RAMP_B2_CTL),
				   TAIKO_A_CDC_PA_RAMP_B3_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_PA_RAMP_B3_CTL),
				   TAIKO_A_CDC_PA_RAMP_B4_CTL, (int)wcd9xxx_reg_read(&sound_control_codec_ptr->core_res, TAIKO_A_CDC_PA_RAMP_B4_CTL);
}
