
#define DECLARE_TLV_DB_SCALE(name, min, step, mute) \
	unsigned int name[] = { TLV_DB_SCALE_ITEM(min, step, mute) }