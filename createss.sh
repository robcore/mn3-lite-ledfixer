#!/bin/bash

rm /root/mn3lite/showstore.c &>/dev/null

createshowstore() {

echo -n 'static ssize_t ' >> /root/mn3lite/showstore.c
echo -n "$1" >> /root/mn3lite/showstore.c
echo '_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)' >> /root/mn3lite/showstore.c
echo '{' >> /root/mn3lite/showstore.c
echo -n '	return sprintf(buf, "%d %d %d\n", ' >> /root/mn3lite/showstore.c
echo -n "$1" >> /root/mn3lite/showstore.c
echo -n '_val[0], ' >> /root/mn3lite/showstore.c
echo -n "$1" >> /root/mn3lite/showstore.c
echo -n '_val[1], ' >> /root/mn3lite/showstore.c
echo -n "$1" >> /root/mn3lite/showstore.c
echo '_val[2]);' >> /root/mn3lite/showstore.c
echo '}' >> /root/mn3lite/showstore.c
echo ""  >> /root/mn3lite/showstore.c
echo -n 'static ssize_t ' >> /root/mn3lite/showstore.c
echo -n "$1" >> /root/mn3lite/showstore.c
echo '_store(struct kobject *kobj,' >> /root/mn3lite/showstore.c
echo '		 struct kobj_attribute *attr, const char *buf, ssize_t count)' >> /root/mn3lite/showstore.c
echo '{' >> /root/mn3lite/showstore.c
echo '	int new_r, new_g, new_b;' >> /root/mn3lite/showstore.c
echo '	sscanf(buf, "%d %d %d", &new_r, &new_g, &new_b);' >> /root/mn3lite/showstore.c
echo -n	"	$1" >> /root/mn3lite/showstore.c
echo '_val[0] = new_r;' >> /root/mn3lite/showstore.c
echo -n	"	$1" >> /root/mn3lite/showstore.c
echo '_val[1] = new_g;' >> /root/mn3lite/showstore.c
echo -n	"	$1" >> /root/mn3lite/showstore.c
echo '_val[2] = new_b;' >> /root/mn3lite/showstore.c
echo '	smart_dimming_full_reinit();' >> /root/mn3lite/showstore.c
echo '	return count;' >> /root/mn3lite/showstore.c
echo '}' >> /root/mn3lite/showstore.c
echo "" >> /root/mn3lite/showstore.c

}

createattrib() {

echo -n 'static struct kobj_attribute ' >> /root/mn3lite/showstore.c
echo -n "$1" >> /root/mn3lite/showstore.c
echo '_attribute =' >> /root/mn3lite/showstore.c
echo -n '	__ATTR(' >> /root/mn3lite/showstore.c
echo  -n "$1" >> /root/mn3lite/showstore.c
echo ', 0644,' >> /root/mn3lite/showstore.c
echo -n "		$1" >> /root/mn3lite/showstore.c
echo '_show,' >> /root/mn3lite/showstore.c
echo -n "		$1" >> /root/mn3lite/showstore.c
echo '_store);' >> /root/mn3lite/showstore.c
echo "" >> /root/mn3lite/showstore.c

}

for GVAL in v255 v203 v151 v87 v51 v35 v23 v11 v3;
do
	echo "Processing $GVAL"
	createshowstore "$GVAL"
done

for GVAL in v255 v203 v151 v87 v51 v35 v23 v11 v3;
do
	echo "Processing $GVAL"
	createattrib "$GVAL"
done

echo "Done"
