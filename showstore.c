static ssize_t v255_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d %d %d\n", v255_val[0], v255_val[1], v255_val[2]);
}

static ssize_t v255_store(struct kobject *kobj,
		 struct kobj_attribute *attr, const char *buf, ssize_t count)
{
	int new_r, new_g, new_b;
	sscanf(buf, "%d %d %d", &new_r, &new_g, &new_b);
	v255_val[0] = new_r;
	v255_val[1] = new_g;
	v255_val[2] = new_b;
	smart_dimming_full_reinit();
	return count;
}

static ssize_t v203_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d %d %d\n", v203_val[0], v203_val[1], v203_val[2]);
}

static ssize_t v203_store(struct kobject *kobj,
		 struct kobj_attribute *attr, const char *buf, ssize_t count)
{
	int new_r, new_g, new_b;
	sscanf(buf, "%d %d %d", &new_r, &new_g, &new_b);
	v203_val[0] = new_r;
	v203_val[1] = new_g;
	v203_val[2] = new_b;
	smart_dimming_full_reinit();
	return count;
}

static ssize_t v151_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d %d %d\n", v151_val[0], v151_val[1], v151_val[2]);
}

static ssize_t v151_store(struct kobject *kobj,
		 struct kobj_attribute *attr, const char *buf, ssize_t count)
{
	int new_r, new_g, new_b;
	sscanf(buf, "%d %d %d", &new_r, &new_g, &new_b);
	v151_val[0] = new_r;
	v151_val[1] = new_g;
	v151_val[2] = new_b;
	smart_dimming_full_reinit();
	return count;
}

static ssize_t v87_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d %d %d\n", v87_val[0], v87_val[1], v87_val[2]);
}

static ssize_t v87_store(struct kobject *kobj,
		 struct kobj_attribute *attr, const char *buf, ssize_t count)
{
	int new_r, new_g, new_b;
	sscanf(buf, "%d %d %d", &new_r, &new_g, &new_b);
	v87_val[0] = new_r;
	v87_val[1] = new_g;
	v87_val[2] = new_b;
	smart_dimming_full_reinit();
	return count;
}

static ssize_t v51_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d %d %d\n", v51_val[0], v51_val[1], v51_val[2]);
}

static ssize_t v51_store(struct kobject *kobj,
		 struct kobj_attribute *attr, const char *buf, ssize_t count)
{
	int new_r, new_g, new_b;
	sscanf(buf, "%d %d %d", &new_r, &new_g, &new_b);
	v51_val[0] = new_r;
	v51_val[1] = new_g;
	v51_val[2] = new_b;
	smart_dimming_full_reinit();
	return count;
}

static ssize_t v35_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d %d %d\n", v35_val[0], v35_val[1], v35_val[2]);
}

static ssize_t v35_store(struct kobject *kobj,
		 struct kobj_attribute *attr, const char *buf, ssize_t count)
{
	int new_r, new_g, new_b;
	sscanf(buf, "%d %d %d", &new_r, &new_g, &new_b);
	v35_val[0] = new_r;
	v35_val[1] = new_g;
	v35_val[2] = new_b;
	smart_dimming_full_reinit();
	return count;
}

static ssize_t v23_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d %d %d\n", v23_val[0], v23_val[1], v23_val[2]);
}

static ssize_t v23_store(struct kobject *kobj,
		 struct kobj_attribute *attr, const char *buf, ssize_t count)
{
	int new_r, new_g, new_b;
	sscanf(buf, "%d %d %d", &new_r, &new_g, &new_b);
	v23_val[0] = new_r;
	v23_val[1] = new_g;
	v23_val[2] = new_b;
	smart_dimming_full_reinit();
	return count;
}

static ssize_t v11_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d %d %d\n", v11_val[0], v11_val[1], v11_val[2]);
}

static ssize_t v11_store(struct kobject *kobj,
		 struct kobj_attribute *attr, const char *buf, ssize_t count)
{
	int new_r, new_g, new_b;
	sscanf(buf, "%d %d %d", &new_r, &new_g, &new_b);
	v11_val[0] = new_r;
	v11_val[1] = new_g;
	v11_val[2] = new_b;
	smart_dimming_full_reinit();
	return count;
}

static ssize_t v3_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d %d %d\n", v3_val[0], v3_val[1], v3_val[2]);
}

static ssize_t v3_store(struct kobject *kobj,
		 struct kobj_attribute *attr, const char *buf, ssize_t count)
{
	int new_r, new_g, new_b;
	sscanf(buf, "%d %d %d", &new_r, &new_g, &new_b);
	v3_val[0] = new_r;
	v3_val[1] = new_g;
	v3_val[2] = new_b;
	smart_dimming_full_reinit();
	return count;
}

static struct kobj_attribute v255_attribute =
	__ATTR(v255, 0644,
		v255_show,
		v255_store);

static struct kobj_attribute v203_attribute =
	__ATTR(v203, 0644,
		v203_show,
		v203_store);

static struct kobj_attribute v151_attribute =
	__ATTR(v151, 0644,
		v151_show,
		v151_store);

static struct kobj_attribute v87_attribute =
	__ATTR(v87, 0644,
		v87_show,
		v87_store);

static struct kobj_attribute v51_attribute =
	__ATTR(v51, 0644,
		v51_show,
		v51_store);

static struct kobj_attribute v35_attribute =
	__ATTR(v35, 0644,
		v35_show,
		v35_store);

static struct kobj_attribute v23_attribute =
	__ATTR(v23, 0644,
		v23_show,
		v23_store);

static struct kobj_attribute v11_attribute =
	__ATTR(v11, 0644,
		v11_show,
		v11_store);

static struct kobj_attribute v3_attribute =
	__ATTR(v3, 0644,
		v3_show,
		v3_store);

