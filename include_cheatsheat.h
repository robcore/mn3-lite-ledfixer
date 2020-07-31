
/* line_gain */
#define SNDRV_CTL_TLVT_DB_SCALE	1       /* dB scale */

#define TLV_LENGTH(...) \
	((unsigned int)sizeof((const unsigned int[]) { __VA_ARGS__ }))

#define TLV_ITEM(type, ...) \
	(type), TLV_LENGTH(__VA_ARGS__), __VA_ARGS__

#define TLV_DB_SCALE_MASK	0xffff
#define TLV_DB_SCALE_MUTE	0x10000
#define TLV_DB_SCALE_ITEM(min, step, mute)			\
	TLV_ITEM(SNDRV_CTL_TLVT_DB_SCALE,			\
		 (min),					\
		 ((step) & TLV_DB_SCALE_MASK) |		\
			((mute) ? TLV_DB_SCALE_MUTE : 0))

#define DECLARE_TLV_DB_SCALE(name, min, step, mute) \
	unsigned int name[] = { TLV_DB_SCALE_ITEM(min, step, mute) }

static const DECLARE_TLV_DB_SCALE(line_gain, 0, 7, 1);

/* HPHL Volume */

#define	SNDRV_CTL_ELEM_IFACE_MIXER	((__force snd_ctl_elem_iface_t) 2) /* virtual mixer device */

#define SOC_SINGLE_TLV(xname, reg, shift, max, invert, tlv_array) \
{	.iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ |\
		 SNDRV_CTL_ELEM_ACCESS_READWRITE,\
	.tlv.p = (tlv_array), \
	.info = snd_soc_info_volsw, .get = snd_soc_get_volsw,\
	.put = snd_soc_put_volsw, \
	.private_value =  SOC_SINGLE_VALUE(reg, shift, max, invert) }
